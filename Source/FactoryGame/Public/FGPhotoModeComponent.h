// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "Components/ActorComponent.h"
#include "Engine/DataAsset.h"
#include "GameFramework/Character.h"
#include "FGPhotoModeComponent.generated.h"

struct FInputActionValue;
class AFGPlayerController;
class AFGCharacterPlayer;
class AFGPhotoModeCamera;

UENUM( BlueprintType )
enum class EPhotoCameraMode : uint8
{
	PCM_FirstPerson		UMETA( DisplayName = "First Person" ),
	PCM_Decoupled		UMETA( DisplayName = "Decoupled" ),
	PCM_Selfie			UMETA( DisplayName = "Selfie" )
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnPMOptionChanged, FString, optionKey, float, optionValue, bool, isValueReset );
DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPMOMapCleared );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPhotoModeToggled, bool, isOn );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnPhotoCameraModeChanged, EPhotoCameraMode, previousMode, EPhotoCameraMode, newMode );

UCLASS( Blueprintable )
class FACTORYGAME_API UPhotoModeOptionBase : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FString mID;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FText mName;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float mDefaultValue;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	bool mIsAdvancedMode;
};

USTRUCT( Blueprintable )
struct FACTORYGAME_API FPhotoModeOptionSubcategory
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FText mName;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TArray< TObjectPtr<UPhotoModeOptionBase> > mOptions;
};

USTRUCT( Blueprintable )
struct FACTORYGAME_API FPhotoModeOptionCategory
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	FText mName;
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TArray< FPhotoModeOptionSubcategory > mSubcategories;
};

UCLASS( Blueprintable )
class FACTORYGAME_API UPhotoModeOptions : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	TArray< FPhotoModeOptionCategory > mCategories;
};

/**
 * Stores and handles all info related to Photo Mode.
 */
UCLASS( Blueprintable, Within = FGPlayerState )
class FACTORYGAME_API UFGPhotoModeComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UFGPhotoModeComponent();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	static UFGPhotoModeComponent* GetUFGPhotoModeComponent( const APlayerController* playerController );

	/** Returns the camera component for the photo mode camera. Might not be available immediately when playing as a client, use InitializeCameraControllerSettings */
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	class UCineCameraComponent* GetCameraComponent() const;

	/** Returns the camera character for this photo mode component */
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	FORCEINLINE AFGPhotoModeCamera* GetPhotoModeCameraCharacter() const { return mCameraCharacter; }

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void TakePhoto( const int captureX = 0, const int captureY = 0, const int captureW = 0, const int captureH = 0 );

	bool TogglePhotoMode();
	bool EnterPhotoMode();
	bool ExitPhotoMode();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void SetPlayerVisibilityInPhotoMode( const bool isVisible );

	UFUNCTION( BlueprintCallable )
	void SetPhotoCameraMode( EPhotoCameraMode mode );
	
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetIsPhotoModeOn() const { return mIsPhotoModeOn; }
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetIsDecoupledCameraOn() const { return mPhotoCameraMode == EPhotoCameraMode::PCM_Decoupled; }
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	bool GetIsPlayerVisible() const { return mIsPlayerVisible; }

	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
	EPhotoCameraMode GetPhotoCameraMode() const { return mPhotoCameraMode; }

	void MoveForward( const float moveValue );
	void MoveBackwards( const float moveValue );
	void MoveLeft( const float moveValue );
	void MoveRight( const float moveValue );
	void MoveUp( const float moveValue );
	void MoveDown( const float moveValue );
	void LookAxis( const FInputActionValue& actionValue ) const;
	void MoveFaster( const float moveValue );
	void MoveSlower( const float moveValue );

	UPROPERTY( BlueprintAssignable, Category = "Photo Mode" )
	FOnPhotoModeToggled mOnPhotoModeToggled;
	
	/** Called when a Photo Mode Option is modified. */
	UPROPERTY( BlueprintAssignable, Category = "Photo Mode" )
	FOnPMOptionChanged mOnPMOptionChanged;

	/** Called when the Photo Mode Option is cleared. */
	UPROPERTY( BlueprintAssignable, Category = "Photo Mode" )
	FOnPMOMapCleared mOnPMOMapCleared;

	/** Called whenever the photo camera mode changes. */
	UPROPERTY( BlueprintAssignable, Category = "Photo Mode" )
	FOnPhotoCameraModeChanged mOnPhotoCameraModeChanged;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Photo Mode" )
	TObjectPtr<UPhotoModeOptions> mAllOptions;

	/** Class of photo mode camera to use for decoupled camera */
	UPROPERTY( EditDefaultsOnly, Category = "Photo Mode" )
	TSubclassOf<AFGPhotoModeCamera> mPhotoModeCameraClass;

	UPROPERTY( BlueprintReadWrite, Category = "Photo Mode"  )
	float mDCMoveDistanceLimit = 3000.0f;
	UPROPERTY( BlueprintReadWrite, Category = "Photo Mode"  )
	float mDCCutoffDistanceLimit = 4000.0f;
	
protected:
	/** Returns a constant reference to the Modified Photo Mode Options map. */
	UFUNCTION( BlueprintCallable, BlueprintPure, Category = "Photo Mode" )
	const TMap< FString, float >& GetModifiedPMOptions() const { return mModifiedPMOptions; };

	/** Writes to an entry (or creates a new one if none exists) in the Modified Photo Mode Options map. Then notifies the FOnPMOptionChanged delegate.
	 * @return Returns false if the optionKey is invalid. Such as being empty. Returns true otherwise.
	 */
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	bool SetPMOption( const FString& optionKey, const float optionValue, const bool isResetCall = false );

	/** Removes an option from the Modified Photo Mode Options map.
	 * @return Returns true if the key entry existed and was succesfully removed. False otherwise.
	 */
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	bool ClearPMOption( const FString& optionKey );
	
	/** Empties the Modified Photo Mode Options map.
	 * @param expectedNumElements Optionally send in the number of Photo Mode Options available to the player to allocate correct size to the map. Defaults to 0.
	 */
	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void ClearPMOMap( const int expectedNumElements = 0 );

	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "Photo Mode" )
	void OnPhotoTaken();
	
	UFUNCTION( BlueprintPure, Category = "Photo Mode" )
    float GetOptionValueFromID( const FString& ID ) const;

	UFUNCTION( Server, Reliable )
	void Server_SetPhotoCameraMode( EPhotoCameraMode newMode );

	UFUNCTION( Server, Reliable )
	void Server_TogglePhotoMode( const bool isOn );
	
	AFGCharacterPlayer* GetOwnerPlayerCharacter() const;
	AFGPlayerController* GetPlayerController() const;

	/** Called when camera controller is replicated and available */
	UFUNCTION( BlueprintImplementableEvent, Category = "Photo Mode" )
	void InitializeCameraControllerSettings();

	UFUNCTION( BlueprintCallable, Category = "Photo Mode" )
	void SetHandEquipmentVisibility( const bool isVisible );

	UFUNCTION( BlueprintCallable )
	FString CreateScreenShotPath() const;
	static FString CreateScreenShotName();

private:
	FString CreateScreenShotCommand( const int captureX = 0, const int captureY = 0, const int captureW = 0, const int captureH = 0 ) const;

	void HandleDecoupledCameraPlacing();
	void PlaceDecoupledCameraAtPlayerCharacter( const AFGCharacterPlayer* playerCharacter );

	void OnPhotoCameraModeChanged( EPhotoCameraMode prevMode );
	
	UFUNCTION()
	void OnRep_CameraCharacter();

	UFUNCTION()
	void OnRep_PhotoCameraMode( EPhotoCameraMode prevMode );

	/** The camera character used for the photo mode camera and the decoupled camera. */
	UPROPERTY( ReplicatedUsing = OnRep_CameraCharacter )
	TObjectPtr<class AFGPhotoModeCamera> mCameraCharacter;

	/** A map that stores all Photo Mode options (and their values) that the player has modified this play session. */
	TMap< FString, float > mModifiedPMOptions;
	
	bool mIsPhotoModeOn = false;	
	bool mIsPlayerVisible = true;

	UPROPERTY( ReplicatedUsing = OnRep_PhotoCameraMode )
	EPhotoCameraMode mPhotoCameraMode;

	UPROPERTY( EditDefaultsOnly, Category = "Photo Mode" )
	FTransform mSelfieModeRelativeTransform;
};

UCLASS( Blueprintable )
class FACTORYGAME_API AFGPhotoModeCamera : public ACharacter
{
	GENERATED_BODY()
public:
	AFGPhotoModeCamera();

	/** The character that we were controlling before we used the decoupled camera */
	UPROPERTY( Replicated )
	TObjectPtr<class AFGCharacterPlayer> mControllingPlayerCharacter;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Photo Mode" )
	TObjectPtr<class UCineCameraComponent> mCameraComp;

	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = "Photo Mode" )
	TObjectPtr<class USpringArmComponent> mSpringArmComp;

	void HandleDecoupledCameraMoveSpeed();

	UFUNCTION( Server, Reliable )
	void Server_SetMoveSpeed( const float newSpeed );
	
	FVector mPreviousCameraLocation;
	FRotator mPreviousCameraRotation;
	bool mHasDecoupledInThisPhotoModeSession = false;
	bool mIsSprinting = false;
	bool mIsCrawling = false;
	float mOldFlySpeed;
	
};

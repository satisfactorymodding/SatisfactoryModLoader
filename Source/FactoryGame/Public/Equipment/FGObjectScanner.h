// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Equipment/FGEquipment.h"
#include "FGObjectScanner.generated.h"

/** Cycle direction for the object scanner */
UENUM( BlueprintType )
enum class EFGScannerCycleDirection : uint8
{
	CD_None,
	CD_Forward,
	CD_Backward,
	CD_Automatic
};

/** Item state struct for the object scanner */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FFGObjectScannerItemState
{
	GENERATED_BODY()
	
	/** The currently descriptor we would like to scan for */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, SaveGame, Category = "ItemState|ObjectScanner" )
	TSubclassOf<class UFGItemDescriptor> CurrentScanDescriptor;
};

/**
*
*/
UCLASS()
class FACTORYGAME_API AFGObjectScanner : public AFGEquipment
{
	GENERATED_BODY()
public:
	/** Ctor */
	AFGObjectScanner();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float deltaTime ) override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const override;
	// End AActor interface

	// Begin AFGEquipment interface
	virtual void Equip(AFGCharacterPlayer* character) override;
	virtual void UnEquip() override;
	virtual void OnCameraModeChanged_Implementation(ECameraMode newCameraMode) override;
	virtual void LoadFromItemState_Implementation(const FFGDynamicStruct& itemState) override;
	virtual FFGDynamicStruct SaveToItemState_Implementation() const override;
	virtual void AddEquipmentActionBindings() override;
	// End AFGEquipment interface
	
	/** 
	 * Cycles scannable type forward and updates the light on the attachment 
	 * @return true if there was a setting change, false means there was nothing to cycle to
	 */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
	bool CycleForward();

	/** 
	 * Cycles scannable type backward and updates the light on the attachment 
	 * @return true if there was a setting change, false means there was nothing to cycle to
	 */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
	bool CycleBackward();

	/** Returns whether or not object scanner has a valid currently selected object */
	UFUNCTION( BlueprintCallable, Category = "Scanner" )
 	bool HasValidCurrentDetails() const;

	/** Returns the aticve scannable desriptor. Can be nullptr */
	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FORCEINLINE TSubclassOf<UFGItemDescriptor> GetCurrentScannableDescriptor() const { return mCurrentScannableDescriptor; }

	/** Returns array with all descriptors that we can search for */
	UFUNCTION( BlueprintCallable, Category = "Scanner" ) 
	void GetAvailableScannableDescriptors( TArray < TSubclassOf<UFGItemDescriptor> >& out_availableDescriptors );

	/** Sets which descriptor that we want to search for */
	UFUNCTION( BlueprintCallable, Category = "Scanner" ) 
	void SetScannableDescriptor( TSubclassOf<UFGItemDescriptor> newScannableDescriptor, EFGScannerCycleDirection cycleDirection = EFGScannerCycleDirection::CD_Forward, bool shouldPlayAnimation = true );
	
protected:
	void OnScannableResourceChanged();
	
	void OpenScannerInteractUI();
	void ForceCloseScannerInteractUI();
	
	/** Input Actions*/
	void Input_OpenMenu( const FInputActionValue& actionValue );
	void Input_Cycle( const FInputActionValue& actionValue );

	UFUNCTION( Server, Reliable )
	void Server_SetScannableDescriptor( TSubclassOf<UFGItemDescriptor> newScannableDescriptor, EFGScannerCycleDirection cycleDirection, bool shouldPlayAnimation = true );
	
	/** A multicast to play a cycle animation */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayCycleAnimation( EFGScannerCycleDirection cycleDirection );

	/** Makes sure the local distance/object in range properties are up to date and calls the K2 callback to play the beep VFX */
	UFUNCTION( NetMulticast, Reliable )
	void Multicast_PlayBeepAnimation();

	/** Returns the location of the object closest to the scanner if it is loaded, otherwise returns null */
	UFUNCTION( BlueprintPure, Category = "Scanner" )
	AActor* GetClosestObjectIfLoaded() const;

	/** Returns the location of the object closest to the scanner. If the object is not loaded, returns the estimated location */
	UFUNCTION( BlueprintPure, Category = "Scanner" )
	FVector GetClosestObjectLocation() const;

	/** Called when the scanner should play the "Beep" VFX when the object is in range */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner", DisplayName = "PlayScannerBeepVFX" )
	void K2_PlayScannerBeepVFX();
	
	/** Plays the animation and the sound of the cycling left/right on the scanner */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner" )
	void PlayCycleAnimation( EFGScannerCycleDirection cycleDirection );

	/** Called when the resource we are scanning for changes. Used to update the light color and other effects on the BP side */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner", DisplayName = "OnScannableResourceChanged" )
	void K2_OnScannableResourceChanged();

	/** Called when the state of the closest object changes: notably, whenever it is in the scannable range or it's type */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner", DisplayName = "OnClosestObjectStateChanged" )
	void K2_OnClosestObjectStateChanged();

	/** Called to paint the scanner screen */
	UFUNCTION( BlueprintImplementableEvent, Category = "Scanner" )
	void PaintScannerScreen( UCanvas* canvas, int32 width, int32 height );
private:
	UFUNCTION()
	void OnRep_CurrentScannableDescriptor();
	UFUNCTION()
	void OnRep_ClosestObject();
	
	bool Internal_CycleObjects( EFGScannerCycleDirection direction );
	
	/** Loops through the cached list of Objects and finds the closest one. This may call RemoveInvalidObjectsFromCache if a null is found */
	void UpdateClosestObject();
	/** Updates the current cached distance to the closest object */
	void UpdateDistanceToClosestObject( bool force = false );

	void RecreateScreenMaterial();
	void DestroyScreenMaterial();
	/** Updates the data on the screen of the scanner */
	void UpdateScreenMaterialData( float dt = 0.0f );
	void RepaintScreenRenderTarget() const;

	/** Calls PlayBeep() and sets up timer for the next beep */
	void Internal_PlayBeep();
	void Local_PlayBeep();

	/** If no object has been selected, this will try and equip the first available object in the object scanner */
	void EquipDefaultScannableResource();
	
public:
	/** Mesh that the scanner is using */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Scanner" )
	USkeletalMeshComponent* mScannerSkeletalMesh;
	
protected:
	/** Maximum delay (in seconds) between each beep */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mBeepDelayMax;

	/** Minimum delay (in seconds) between each beep */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mBeepDelayMin;

	/** Detection range of the scanner */
	UPROPERTY( BlueprintReadOnly, EditDefaultsOnly, Category = "Scanner" )
	float mDetectionRange;

	/** "the closest" Object doesn't really need to be updated every frame. Maybe every second, or 2, or so. */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	float mUpdateClosestObjectTime;

	/** The current closest Object */
	UPROPERTY( ReplicatedUsing = OnRep_ClosestObject )
	FScannableActorDetails mClosestObject;

	UPROPERTY( BlueprintReadOnly, Category = "Scanner" )
	bool mClosestObjectInScanRange;

	UPROPERTY( BlueprintReadOnly, Category = "Scanner" )
	float mNormalizedDistanceToClosestObject;

	/** Angle to the closest object from the player forward orientation, in degrees */
	UPROPERTY( BlueprintReadOnly, Category = "Scanner" )
	float mAngleToClosestObject;

	/** Class of the menu opened by interacting with the scanner */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	TSubclassOf<UFGInteractWidget> mScannerMenuWidgetClass;

	/** Screen material to base the dynamic instance on in 3P */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	UMaterialInterface* mScreenMaterial3P;

	/** Screen material to base the dynamic instance on in 1P */
	UPROPERTY( EditDefaultsOnly, Category = "Scanner" )
	UMaterialInterface* mScreenMaterial1P;
private:
	/** Currently open scanner menu widget */
	UPROPERTY( Transient )
	UFGInteractWidget* mScannerMenuWidget;

	/** Material instance of the screen material */
	UPROPERTY( Transient )
	UMaterialInstanceDynamic* mScreenMaterialInstance;

	/** The texture we are rendering into for the screen material */
	UPROPERTY( Transient )
	class UCanvasRenderTarget2D* mScreenCanvasRenderTarget2D;
	
	/** The currently descriptor we would like to scan for */
	UPROPERTY( SaveGame, ReplicatedUsing = "OnRep_CurrentScannableDescriptor" )
	TSubclassOf<class UFGItemDescriptor> mCurrentScannableDescriptor;

	/** Amount of time till the next beep effect */
	float mTimeUntilNextBeep;
	/* Time until we try to update the closest object again */
	float mTimeUntilClosestObjectUpdate;
	/** The delay between beeps is variable based on distance from the object. This is the current beep delay. */
	float mCurrentBeepDelay;
	/** Delta time accumulated across multiple ticks for screen interpolation */
	float mScreenInterpolationTime;

	bool mHasBeenUpdatedOnce = false;
	
};

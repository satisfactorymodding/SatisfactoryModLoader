//Copyright 2016 Coffee Stain Studios.All Rights Reserved.
#pragma once

#include "Blueprint/UserWidgetPool.h"
#include "Equipment/FGEquipment.h"
#include "FGHUDBase.h"
#include "FactoryGame.h"

#include "FGHUD.generated.h"

class AFGCharacterBase;
UENUM( BlueprintType )
enum class ECrosshairState : uint8
{
		ECS_Default			UMETA( DisplayName="Default" ),
		ECS_GeneralUse		UMETA( DisplayName = "General" ),
		ECS_PickUp			UMETA( DisplayName = "Pickup" ),
		ECS_Vehicle			UMETA( DisplayName = "Vehicle" ),
		ECS_Weapon			UMETA( DisplayName = "Weapon" ),
		ECS_Workbench		UMETA( DisplayName = "Workbench" ),
		ECS_Dismantle		UMETA( DisplayName = "Dismantle" ),
		ECS_Build			UMETA( DisplayName = "Build" ),
		ECS_Custom			UMETA( DisplayName = "Custom" ),
		ECS_Hidden			UMETA( DisplayName = "Hidden" )
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPumpiModeChanged, bool, hideHUD );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPartialPumpiModeChanged, bool, partialHideHUD );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHiddenHUDModeChanged, bool, HideHUD );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnHUDVisibilityChanged, bool, hudVisibility );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnPlayerHitFeedback, AFGCharacterBase*, hitCharacter, AActor*, damageCauser );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams( FOnCrosshairUpdated, bool, crosshairVisibility, UTexture2D*, crossHairTexture, FLinearColor, color );

FACTORYGAME_API DECLARE_LOG_CATEGORY_EXTERN( LogHUD, Log, All );

UCLASS()
class FACTORYGAME_API AFGHUD : public AFGHUDBase
{
	GENERATED_BODY()
public:
	AFGHUD();

	//~ Begin AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//~ End AActor interface

	/** Adds a HUD of the widget class for the provided pawn. Needs a valid pawn */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	void AddPawnHUD( TSubclassOf<class UUserWidget> widgetClass, APawn* pawn );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	void ShowRespawnUI();

	/** Closes the respawn UI and enables the GameUI if not already enabled. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	void CloseRespawnUI();

	/** All widgets that inherits from UFGInteractWidget can be opened by calling this */
	UFUNCTION( BlueprintImplementableEvent, BlueprintCallable, Category = "FactoryGame|UI" )
	void OpenInteractUI( TSubclassOf< class UFGInteractWidget > widgetClass, UObject* interactObject );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	class UFGInteractWidget* RequestInteractWidget( TSubclassOf< class UFGInteractWidget > widgetClass, UObject* interactObject );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI", meta = (DeterminesOutputType = "widgetClass") )
	UUserWidget* RequestWidget( TSubclassOf< UUserWidget > widgetClass );
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	void ReleaseWidget( UUserWidget* widgetToRelease );

	/** Pointer to the cheat board widget */
	TSharedPtr<class SFGCheatBoardWidget> mCheatBoardWidget; 

	bool IsCheatBoardOpen() const { return mCheatBoardWidget.IsValid(); }

	/** ShowDebug is back! */
	virtual void ShowDebugInfo( float& YL, float& YPos ) override;

	UFUNCTION( BlueprintPure, Category = "FactoryGame|UI" )
	class UFGGameUI* GetGameUI() const { return mGameUI; }

	/** Getter */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE bool GetShowCrosshair() { return !mForceCrossHairHidden && mShowCrosshair; }

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetShowCrossHair( bool showCrosshair );

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetForceHideCrossHair( bool forceHide );

	/** HUD visibility */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	bool GetPumpiMode() const { return mForceHideHUD; }

	/** HUD visibility */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	bool GetPartialPumpiMode() { return mPartialForceHideHUD; }

	/** Hides all HUD including crosshair */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetPumpiMode( bool hideHUD );

	/** Hides all HUD including crosshair */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetPartialPumpiMode( bool hideHUD );

	/** Sets if we should Hide all HUD except interact widgets */
	void SetHiddenHUDMode( bool hideHUD );

	/** Gets if we should Hide all HUD except interact widgets */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	bool GetHiddenHUDMode() const { return mHiddenHUDMode; } 

	/** Getter */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE bool GetHUDVisibility() { return mHUDVisibility; }

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetHUDVisibility( bool hudVisibility );

	/** Getter for Crosshair State */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE ECrosshairState GetCrosshairState() { return mActiveCrosshairState; }

	/** Setter for Crosshair State */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetCrosshairState( ECrosshairState crosshairState );

	/**
	* Updates the crosshair to match set the proper CrosshairState
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|HUD" )
	void UpdateCrosshairState( class AFGCharacterPlayer* player );

	/**
	* Updates the crosshair color for weapons
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|HUD" )
	void UpdateCrosshairColorState( const FLinearColor& newColor );

	/**
	* Updates the crosshair to match set the proper CrosshairState
	*/
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|HUD" )
	void SetCrustomCrosshairTexture( UTexture2D* newTexture);

	/** Called when we want to add HUD for equipment 
	 * @param widgetClass - class to use for widget 
	 * @param slot - which slot the equipment is using
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|HUD" )
	void AddEquipmentHUD( TSubclassOf< UUserWidget > widgetClass, EEquipmentSlot slot );

	/** Removes all equipment HUD from a certain slot */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|HUD" )
	void RemoveEquipmentHUD( EEquipmentSlot slot );

	/** Returns the latest created pawn HUD widget. Can return nullptr */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE UUserWidget* GetPawnHUD() { return mPawnHUD; }

	/** Called when player hits something but it's not a weak spot or armor */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|HUD|Damage")
	void NotifyHitFeedbackNormal(AFGCharacterBase* hitCharacter, AActor* damageCauser);

	/** Called when player hits a weak spot */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|HUD|Damage")
	void NotifyHitFeedbackWeakSpot(AFGCharacterBase* hitCharacter, AActor* damageCauser);

	/** Called when player hits an armored spot */
	UFUNCTION( BlueprintImplementableEvent, Category="FactoryGame|HUD|Damage")
	void NotifyNotifyHitFeedbackArmor(AFGCharacterBase* hitCharacter, AActor* damageCauser);

#if WITH_CHEATS
	void ToggleCheatBoard();
#endif
	
private:
	/** Updates the crosshair by sending a delegate with current state */
	void UpdateCrosshair();

public:
	/** Called when the pumpi mode changes. */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnPumpiModeChanged mOnPumpiModeChanged;

	/** Called when the partial pumpi mode changes. */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnPartialPumpiModeChanged mOnPartialPumpiModeChanged;
	
	/** Called when the hidden HUD mode changes. */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" );
	FOnHiddenHUDModeChanged mOnHiddenHUDModeChanged;

	/** Called when HUD visibility changes. */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnHUDVisibilityChanged mOnHUDVisibilityChanged;
	
	/** Called when the player hits something normally (no weakspot or armor) */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnPlayerHitFeedback mOnHitFeedbackNormal;

	/** Called when the player hits something at an armored spot */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnPlayerHitFeedback mOnHitFeedbackArmor;

	/** Called when the player hits something at a weak spot */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnPlayerHitFeedback mOnHitFeedbackWeakSpot;

	/** Called when cross hair is updated */
	UPROPERTY( BlueprintAssignable, Category = "Game UI" )
	FOnCrosshairUpdated mOnCrosshairUpdated;
	
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Game UI" )
	TSubclassOf< UUserWidget > mGameUIClass;

	UPROPERTY( EditDefaultsOnly, Category = "Game UI" )
	TSubclassOf< UUserWidget > mRespawnUIClass;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mDefaultCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mPickupCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mVehicleCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mWeaponCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mWorkbenchCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mBuildCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mDismantleCrosshair;

	UPROPERTY( BlueprintReadWrite , Category = "Crosshair" )
	class UTexture2D* mCustomCrosshair;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Crosshair" )
	class UTexture2D* mGeneralCrosshair;
private:

	/** Current state of crosshair */
	ECrosshairState mActiveCrosshairState;

	FLinearColor mWeaponCrosshairColor = FLinearColor::White;

	/* Should we show the crosshair  */
	bool mShowCrosshair;

	/* Used when when setting the HUD visibility overall */
	bool mForceCrossHairHidden;

	/* Used when when setting the HUD visibility overall */
	bool mForceHideHUD;

	/* Used to hide all HUD elements except for pause menu */
	bool mPartialForceHideHUD;

	/* my commenting sucks */
	bool mHUDVisibility;

	/* Used to hide all HUD elements except for interact widgets */
	bool mHiddenHUDMode;

	/** Input component for blocking input during respawn */
	UPROPERTY()
	class UInputComponent* mRespawnInputComponent;

	UPROPERTY( transient )
	class UUserWidget* mRespawnUI;

	UPROPERTY( transient )
	class UFGGameUI* mGameUI;

	/** The latest created pawn HUD widget */
	UPROPERTY()
	UUserWidget* mPawnHUD;

	UPROPERTY()
	TMap< TSubclassOf< UUserWidget >, UUserWidget* > mCachedWidgets;

	FUserWidgetPool mUserWidgetPool;

	/** Runtime set crosshair to keep track of when we should trigger delegate updates */
	//UPROPERTY( Transient )
	//TPair<bool, UTexture2D*> mCachedCrosshairState;
};

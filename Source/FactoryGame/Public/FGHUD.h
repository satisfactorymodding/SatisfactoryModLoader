//Copyright 2016 Coffee Stain Studios.All Rights Reserved.
#pragma once 
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"
#include "GameFramework/HUD.h"
#include "Resources/FGItemDescriptor.h"
#include "FGHUDBase.h"
#include "FGHUD.generated.h"

// MODDING EDIT: doesn't inherit the one from FactoryGame.h
#ifndef WITH_CHEATS
#define WITH_CHEATS 0
#endif

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
		ECS_Custom		UMETA( DisplayName = "Cutom" )
};

UCLASS()
class FACTORYGAME_API AFGHUD : public AFGHUDBase
{
	GENERATED_BODY()
public:
	/** Z-order values for sub widgets. */
	enum EWidgetOrder
	{
		EWO_GameUI = 0,
		EWO_Respawn = 1
	};
public:
	AFGHUD();

	//~ Begin AActor interface
	virtual void PostInitializeComponents() override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	//~ End AActor interface

	virtual void DrawHUD() override;

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
	void OpenInteractUI( TSubclassOf< UFGInteractWidget > widgetClass, UObject* interactObject );

	/** Pointer to the cheat board widget */
	TSharedPtr<class SFGCheatBoardWidget> mCheatBoardWidget; 

	bool IsCheatBoardOpen() const { return mCheatBoardWidget.IsValid(); }

	/** ShowDebug is back! */
	virtual void ShowDebugInfo( float& YL, float& YPos ) override;

	UFUNCTION( BlueprintPure, Category = "FactoryGame|UI" )
	UFGGameUI* GetGameUI() const { return mGameUI; }

	/** Set the actor class to preview in a rendertarget */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ActorPreview" )
	void SetPreviewActorClass( TSubclassOf<AActor> actorClass );

	/** Set the distance we preview the actor from */
	UE_DEPRECATED( 4.16, "SetPreviewDistance is deprecated, use SetPreviewView instead" )
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ActorPreview", meta = ( DeprecatedFunction, DeprecationMessage = "SetPreviewDistance is deprecated, use SetPreviewView instead" ) )
	void SetPreviewDistance( float previewDistance );

	/** Set the view we preview the actor from  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|ActorPreview" )
	void SetPreviewView( const FItemView& view );

	/** Get the texture that we use to preview the actor */
	UFUNCTION( BlueprintPure, Category="FactoryGame|ActorPreview" )
	class UTextureRenderTarget2D* GetPreviewTexture() const;
	
	/** Start rendering the preview actor */
	UFUNCTION( BlueprintCallable, Category="FactoryGame|ActorPreview" )
	void BeginPreviewActor();

	/** stop rendering the preview actor */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|ActorPreview" )
	void EndPreviewActor();

	/** Getter */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE bool GetShowCrosshair() { return !mForceCrossHairHidden && mShowCrosshair; }

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetShowCrossHair( bool showCrosshair ) { mShowCrosshair = showCrosshair; }

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetForceHideCrossHair( bool forceHide ) { mForceCrossHairHidden = forceHide; }

	/** HUD visibility */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	bool GetPumpiMode() { return mForceHideHUD; }

	/** HUD visibility */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	bool GetPartialPumpiMode() { return mPartialForceHideHUD; }

	/** Hides all HUD including crosshair */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetPumpiMode( bool hideHUD );

	/** Hides all HUD including crosshair */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetPartialPumpiMode( bool hideHUD );

	/** Getter */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE bool GetHUDVisibility() { return mHUDVisibility; }

	/** Setter */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetHUDVisibility( bool hudVisibility ) { mHUDVisibility = hudVisibility; }

	/** Getter for Crosshair State */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|HUD" )
	FORCEINLINE ECrosshairState GetCrosshairState() { return mActiveCrosshairState; }

	/** Setter for Crosshair State */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetCrosshairState( ECrosshairState crosshairState ) { mActiveCrosshairState = crosshairState; }

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
private:
	/** Setup our preview for a building/vehicle from our current set preview class */
	void SetupActorPreview();

	/** Filter out what components we want to gather to preview a building */
	class USceneComponent* CreatePreviewComponent( class USceneComponent* attachParent, class UActorComponent* componentTemplate, const FName& componentName );

#if WITH_CHEATS
	/** Function that adds the cheat widget if it should */
	void PonderOpeningCheatBoard();
#endif

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

	/** Input component for blocking input during respawn */
	UPROPERTY()
	class UInputComponent* mRespawnInputComponent;

	UPROPERTY( transient )
	class UUserWidget* mRespawnUI;

	UPROPERTY( transient )
	class UFGGameUI* mGameUI;

	/** A world for previewing the current building */
	UPROPERTY( transient )
	class UWorld* mPreviewBuildingWorld;

	/** Class that stages the preview building item */
	UPROPERTY( EditDefaultsOnly, Category = "PreviewBuilding" )
	TSubclassOf<class AFGRenderTargetStage> mPreviewStageClass;

	// This isn't marked as UPROPERTY as this actor resides in another world, so I think the GC will be sad if we create a reference to it
	class AFGRenderTargetStage* mPreviewBuildingStage;

	/** The actor class we want to preview, we don't use buildable as we want to support vehicles too */
	UPROPERTY()
	TSubclassOf<class AActor> mPreviewActorClass;

	/** The latest created pawn HUD widget */
	UPROPERTY()
	UUserWidget* mPawnHUD;

public:
	FORCEINLINE ~AFGHUD() = default;
};

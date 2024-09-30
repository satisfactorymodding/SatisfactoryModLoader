//Copyright 2016 Coffee Stain Studios.All Rights Reserved.
#pragma once

#include "Blueprint/UserWidgetPool.h"
#include "Equipment/FGEquipment.h"
#include "FGHUDBase.h"
#include "FactoryGame.h"
#include "FGActorRepresentation.h"
#include "Widgets/SWeakWidget.h"

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

USTRUCT(BlueprintType)
struct FCompassEntry
{
	GENERATED_BODY()

	/** Offset on the compass */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	float Offset{0.0f};
	/** Current alpha value based on how close the entry is to the edge. */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	float Alpha{0.0f};
	/** Vertical alignment of the compass entry, 0 being below the compass line, -0.5 being centered on the compass line, and -1 being above the compass line */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	float HeightAlignment{0.0f};
	/** Scale of the compass entry. Default is 1.0, but it can be overriden by the representation */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	float Scale{1.0f};
	/** Text to display when centered. */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	FText Text;

	/** Brush to use for drawing the object. Usually a material based brush, but can also be a texture */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	FSlateBrush Brush;

	/** Brush to use for drawing the special effect on the object (like scanner ping). Visual effects are not restricted to compass object size boundaries */
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	FSlateBrush EffectBrush;

	bool bEnabled{true};
	bool bCanShowName{true};
	bool bDynamicScale{false};
	bool bHasSpecialEffect{false};
	bool bHasDynamicText{false};
	bool bImportantEntry{false};
	bool bIsFilteredOut{false};
	/** True if special effect is visible, special effect will be set to false if time left expires */
	bool bSpecialEffectVisible{true};
	float SpecialEffectTime{0.0f};
	bool bHasCachedTextDimensions{false};
	FVector2f CachedTextDimensions{ForceInit};
	float CachedDistanceToCamera{0.0f};

	float MaxDrawRange{-1.0f};
	FVector2f StaticDirection{ForceInit};
	float StaticDistanceToCamera{0.0f};
		
	// Should it display the name?
	UPROPERTY( EditAnywhere, Category = "Compass Entry" )
	bool bShouldShowName{false};

	/** The representation this compass entry is bound to. Can be NULL in some cases */
	UPROPERTY()
	UFGActorRepresentation* RepresentingActor{};
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
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick(float DeltaSeconds) override;
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

	/**
	 * Requests an interaction widget of the specified class, either retrieving it from cache if the widget supports that
	 * or creating a new one if necessary. The widget is initialized with the provided interactable object.
	 * @param widgetClass The subclass of UFGInteractWidget to request.
	 * @param interactObject The UObject to interact with using the widget.
	 * @return Pointer to the requested UFGInteractWidget instance.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|UI" )
	class UFGInteractWidget* RequestInteractWidget( TSubclassOf< class UFGInteractWidget > widgetClass, UObject* interactObject );
	/** Request and release functions for UFGGameUI::mUserWidgetPool. Kept this as well as the UFGGameUI functions for easier access */
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
	bool GetPartialPumpiMode() const { return mPartialForceHideHUD; }

	/** Hides all HUD including crosshair */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|HUD" )
	void SetPumpiMode( bool hideHUD );

	/** Hides all HUD including crosshair. Unlike SetPumpiMode, this does NOT hide the Pause Menu. Used by the Intro Sequence. */
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

	void ToggleCheatBoard();

	UFUNCTION()
	void OnActorRepresentationAdded( UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationRemoved( UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationUpdated( UFGActorRepresentation* actorRepresentation );

	UFUNCTION()
	void OnActorRepresentationFiltered( ERepresentationType type, bool visible );

	void SetCompassEntryVisibility(UFGActorRepresentation* actorRepresentation, bool visible);
	void RegisterCardinalCompassDirections();
	
	UFUNCTION()
	void OnSetupBinds();
	//void ShowCompass();

	UFUNCTION( BlueprintNativeEvent, Category = "Game UI", DisplayName = "OnViewportResized" )
	void OnViewportResizedEvent();

private:
	/** Updates the crosshair by sending a delegate with current state */
	void UpdateCrosshair();

	void OnViewportResized( class FViewport* Viewport, uint32 Unused );
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

	TArray<FCompassEntry>& GetCompassEntries() { return mCompassEntries; }
protected:
	UPROPERTY( EditDefaultsOnly, Category = "Game UI" )
	TSoftClassPtr< UUserWidget > mGameUIClass;

	UPROPERTY( EditDefaultsOnly, Category = "Game UI" )
	TSoftClassPtr< UUserWidget > mRespawnUIClass;

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

	// Entries in the compass.
	UPROPERTY()
	TArray<FCompassEntry> mCompassEntries;

	void UpdateCompassData( float deltaTime );

	UPROPERTY(EditDefaultsOnly)
	TMap<ERepresentationType,UTexture2D*> mCompassTextureOverrides;

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

	/** Widgets we cached to avoid recreating all the time. Legacy implementation. Could/should be replaced by UFGGameUI::mUserWidgetPool */
	UPROPERTY( Transient )
	TMap< TSubclassOf< UUserWidget >, UUserWidget* > mCachedWidgets;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGEquipment.h"
#include "FGFactoryColoringTypes.h"
#include "FGRecipeProducerInterface.h"
#include "GameFramework/Actor.h"
#include "Inventory.h"
#include "FGBuildGunModeDescriptor.h"
#include "FGBuildGun.generated.h"

 /**
  * States the build gun can be in.
  */
UENUM( BlueprintType )
enum class EBuildGunState : uint8
{
	BGS_NONE			UMETA( DisplayName = "None" ),
	BGS_MENU			UMETA( DisplayName = "Menu" ),
	BGS_BUILD			UMETA( DisplayName = "Build" ),
	BGS_DISMANTLE		UMETA( DisplayName = "Dismantle" ),
	BGS_PAINT			UMETA( DisplayName = "Paint" ),
	
	BGS_MAX				UMETA( Hidden )
};

UENUM( BlueprintType )
enum class EMenuStateSection : uint8
{
	MSS_NONE			UMETA( DisplayName = "None" ),
	MSS_BUILD			UMETA( DisplayName = "Build" ),
	MSS_CUSTOMIZE		UMETA( DisplayName = "Paint" ),
	MSS_BLUEPRINT		UMETA( DisplayName = "Blueprint" ),
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildGunStateChanged, EBuildGunState, newState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildGunMenuStateChanged, EMenuStateSection, newState );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildGunRecipeChanged, TSubclassOf< class UFGRecipe >, newRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRecipeSampled, TSubclassOf< class UFGRecipe >, newRecipe );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCustomizationsSampled, TArray< TSubclassOf< class UFGFactoryCustomizationDescriptor > >, newCustomizations );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBuildGunModeChanged, TSubclassOf< UFGBuildGunModeDescriptor >, newMode );

/**
 * Represents a state in the build gun, e.g. build, dismantle etc.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGBuildGunState : public UObject
{
	GENERATED_BODY()

public:
	UFGBuildGunState();
	
	/** Mark this class as supported for networking */
	virtual bool IsSupportedForNetworking() const override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the Callspace of the outer BuildGun. */
	virtual int32 GetFunctionCallspace( UFunction* Function, FFrame* Stack ) override;

	/** This is overloaded so that we can call Server/Client functions in this object by using the NetDriver of the outer BuildGun.*/
	virtual bool CallRemoteFunction( UFunction* Function, void* Parameters, FOutParmRec* OutParms, FFrame* Stack ) override;

	/** Checks if the outer build gun has authority. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	bool HasAuthority() const;

	/** Get the build guns world. */
	virtual UWorld* GetWorld() const override;

	/** Enter this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BeginState();

	/** Exit this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void EndState();

	/** Tick this state. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void TickState( float deltaTime );

	/** Is this state active. */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	FORCEINLINE bool IsActive() const{ return mIsActive; }

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void PrimaryFire();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void PrimaryFireRelease();

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void SecondaryFire();
	
	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BuildSamplePressed();

	/** If true, then the building is valid to sample in this state */
	virtual bool IsValidBuildingSample( class AFGBuildable* buildable ) const;

	/** If true, then this vehicle should be able to be sampled */
	virtual bool IsValidVehicleSample( class AFGVehicle* vehicle ) const;

	/**
	 * We have sampled a new recipe
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState|Build" )
	void OnRecipeSampled( TSubclassOf<class UFGRecipe> recipe );

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void BuildSampleRelease();

	/**
	 * We have sampled customizations
	 */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState|Paint" )
	void OnCustomizationsSampled( TArray< TSubclassOf< class UFGFactoryCustomizationDescriptor > >& newCustomizations );

	/** Redirected from the build gun. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void Scroll( int32 delta);

	/** Called whenever the buildgun changes mode. Called on both server and client. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	void OnBuildGunModeChanged( TSubclassOf< UFGBuildGunModeDescriptor > newMode );

	/** Get a list of the currently supported build modes for the current hologram.*/
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "BuildModeSelect" )
	void GetSupportedBuildModes( TArray< TSubclassOf< UFGBuildGunModeDescriptor > >& out_buildModes ) const;

	/** What buildgun mode we want to start in when we enter this state. */
	UFUNCTION( BlueprintNativeEvent, BlueprintPure, Category = "BuildModeSelect" )
	TSubclassOf< UFGBuildGunModeDescriptor > GetInitialBuildGunMode() const;

	/** Check if the buildgun's current mode is the one specified. */
	UFUNCTION( BlueprintPure, Category = "Hologram" )
	bool IsCurrentBuildGunMode( TSubclassOf< UFGBuildGunModeDescriptor > buildMode ) const;

	/** Used to override the range of the buildgun, results below 0 are ignored and default range will be used instead. */
	UFUNCTION( BlueprintNativeEvent, Category = "BuildGunState" )
	float GetBuildGunRangeOverride();

	/**
	 * Get the owning build gun.
	 * @return A valid build gun.
	 */
	UFUNCTION( BlueprintPure, Category = "BuildGunState" )
	class AFGBuildGun* GetBuildGun() const;

	/** Get the owning player state */
	class AFGPlayerState* GetPlayerState() const;
	
	/** 
	 * Get's current percentage of Build delay progress. 
	 * @return Returns between 0-1. Returns 0 if no build is in progress 
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState" )
	float GetBuildGunDelayPercentage() const;

	/**
	 * Overrideable function that will test if the basic requirements
	 * for the current build state to perform its action is met.
	 * @return true if the conditions required to use the build gun are met.
	 */
	virtual bool CanBeginBuildGunDelay() const { return true; }

	/** 
	 * Get's the build delay message
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGunState" )
	FText GetBuildGunDelayMessage() const { return mActionMessage; }

	UFUNCTION( Category = "BuildGunState" )
	virtual void BeginBuildGunDelay();

	/** sets mActionStartTime to 0 */
	UFUNCTION( Category = "BuildGunState" )
	virtual void ResetBuildGunDelay();

	/** @return true if the build gun delay is complete, or is 0 (ie. always complete) */
	UFUNCTION( Category = "BuildGunState" )
	bool BuildGunDelayIsComplete();

	/** @return true if there is an delay on this state. */
	UFUNCTION( Category = "BuildGunState" )
	bool HasBuildGunDelay();

	virtual void BindInputActions( class UFGEnhancedInputComponent* inputComponent );
	void ClearInputActions( class UEnhancedInputComponent* inputComponent );
	virtual bool OnShortcutPressed( int32 shortcutIndex ) { return false; }
protected:
	/** If true, then we can sample buildings in this state */
	virtual bool CanSampleBuildings() const;
	
	/** If true, the we can sample customizations in this state */
	virtual bool CanSampleCustomizations() const;
	
	/** If true, the we can sample blueprints in this state */
	virtual bool CanSampleBlueprints() const;

	/** Mapping context of this build gun state. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Input" )
	TObjectPtr< UInputMappingContext > mMappingContext;

private:
	/** Time (in seconds) it takes for the action (eg. Build, dismantle) */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGunState" )
	float mActionDelay;

	/** internal time for when action has begun (eg. Build, dismantle). if 0, ignore. */
	float mActionStartTime;

	/** Text to show while action is in progress */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGunState" )
	FText mActionMessage;

	/** Is this state active? */
	bool mIsActive;
};

/**
 * The latest iteration of a pink box with a red button.
 */
UCLASS()
class FACTORYGAME_API AFGBuildGun : public AFGEquipment, public IFGRecipeProducerInterface
{
	GENERATED_BODY()

public:
	AFGBuildGun();

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;

	// Begin AFGEquipment interface
	virtual void Equip( class AFGCharacterPlayer* character );
	virtual void UnEquip();
	virtual void OnInteractWidgetAddedOrRemoved( UFGInteractWidget* widget, bool added ) override;
	virtual bool OnShortcutPressed(int32 shortcutIndex) override;
	virtual bool CanPickBestUsableActor_Implementation() const override;
	// End AFGEquipment interface

	// Begin IFGRecipeProducerInterface
	virtual TSubclassOf<UFGItemDescriptor> GetRecipeProducerItemDescriptor_Implementation(UObject* WorldContext) const override;
	// End IFGRecipeProducerInterface

	void TraceForBuilding( APawn* owningPawn, FHitResult& hitresult ) const;
	void TraceForBuildingSample( APawn* owningPawn, FHitResult& hitresult );
	
	/** @return The FHitResult of this build gun. */
	FORCEINLINE FHitResult& GetHitResult(){ return mHitResult; }

	/**
	 * Gets all the recipes that can be built using this build gun.
	 * @note This is an expensive operation so cache the result.
	 * @param out_recipes Returns all recipes available to this build gun.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	void GetAvailableRecipes( TArray< TSubclassOf< class UFGRecipe > >& out_recipes, TArray < TSubclassOf< class UFGCustomizationRecipe > >& out_customizationRecipes ) const;

	/** Convenience function to get the cost for a recipe. */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	TArray< FItemAmount > GetCostForRecipe( TSubclassOf< class UFGRecipe > recipe ) const;

	/** Get the inventory to charge when building and refunding when dismantling. */
	UFUNCTION( BlueprintPure, Category = "BuildGun|Inventory" )
	class UFGInventoryComponent* GetInventory() const;
	
	/** Gets BuildGunState depending on the enum passed */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	FORCEINLINE class UFGBuildGunState* GetBuildGunStateFor( EBuildGunState gunState ) const { return mStates[ (uint8)gunState ]; }

	/** Gets the build gun delay progress from current state as a percentage between 0-1 */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	float GetCurrentBuildGunDelayPercentage() const;

	/** Gets the build gun delay message from current state */
	UFUNCTION( BlueprintPure, Category = "BuildGun|State" )
	FText GetCurrentBuildGunDelayMessage() const;

	/** @return true if the produce the same buildable; false if not. */
	UFUNCTION( BlueprintCallable, Category = "BuildGun|Recipe" )
	bool CompareActiveRecipeTo( TSubclassOf< class UFGRecipe > recipe );

	/** @return true if current customizatio recipe is the same as the given recipe. If both are nullptr it also returns true */
	bool CompareActiveCustomizationRecipeTo( TSubclassOf< class UFGCustomizationRecipe > recipe );

	/** @return true if the given blueprint descriptor is active and the blueprint recipe is active as well */
	bool IsBlueprintDescriptorActive( class UFGBlueprintDescriptor* blueprintDescriptor  ) const;

	/** Checks if the buildgun is in the state we send in  */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	bool IsInState( EBuildGunState inState );

	/** Gets the current state of the buildgun. */
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	FORCEINLINE UFGBuildGunState* GetCurrentState() const { return mCurrentState; }

	// <FL> [PuschkeN] keeping track of the previous build gun state allows us to detect e.g. when returning to the build menu directly from building, in which case we want to set the focus on that recipe
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	FORCEINLINE EBuildGunState GetPreviousStateEnum() const { return mPreviousStateEnum; }
	// </FL>

	/**
	 * Only the server is allowed to build stuff so all the actions are executed on the server but may be simulated on the client.
	 * Simulations may be sounds and the brrrrrrrring progress bar when selling.
	 *****************************************************************************/
	void OnPrimaryFirePressed();
	void OnPrimaryFireReleased();
	void OnSecondaryFirePressed();
	void OnSecondaryFireReleased();
	void OnModeSelectPressed();
	void OnModeSelectReleased();
	void OnBuildSamplePressed();
	void OnBuildSampleReleased();

	UFUNCTION( Server, Reliable )
	void Server_Scroll( int32 delta );
	void Scroll( int32 delta );

	/** Input Action Bindings */
	void Input_PrimaryFire( const FInputActionValue& actionValue );
	void Input_SecondaryFire( const FInputActionValue& actionValue );
	void Input_ModeSelect( const FInputActionValue& actionValue );
	void Input_ScrollAxis( const FInputActionValue& actionValue );
	void Input_BuildSample( const FInputActionValue& actionValue );

	/**
	 * Only the client handles categories, recipes.
	 * This enables faster menu feedback and that the menus can be completely separated from the build gun implementation.
	 * The client knows about every recipe available and their category and may organize them however it wants to.
	 * When it want to set a recipe to active it tells the server to change the active recipe, hence no need for the server to handle the categories.
	 *****************************************************************************/

	/**
	 * (Simulated)
	 * Set the build gun in menu mode.
	 * @note Must be called on the local player.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoMenuState();

	/**
	 * (Simulated)
	 * Set the build gun in building mode and activates the given recipe.
	 * @note Must be called on the local player.
	 *
	 * @param recipe The recipe to set as active. This may be nullptr, e.g. to hide hologram.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoBuildState( TSubclassOf< class UFGRecipe > recipe );
	
	/**
	 * (Simulated)
	 * Set the build gun in painting mode with the specific paint params
	 * @note Must be called on the local player.
	 * @param customizationRecipe The Descriptor to apply
	 * @param clearCache If true, remove all existing customizations before adding those passed in via customizationDescriptors
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoPaintState( TSubclassOf< class UFGCustomizationRecipe > customizationRecipe, bool clearCache = false );

	/**
	 * (Simulated)
	 * Set the build gun in dismantling mode.
	 * @note Must be called on the local player.
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void GotoDismantleState();

	/**
	 * (Simulated)
	 * Sets the blueprint desc to use when setting a blueprint recipe on the build state.
	 * This will fail if the desc is not found by name. Potentially could happen if a client has blueprints the server doesn't
	 * @note Must be called on the local player.
	 *
	 * @param blueprintName string name of the descriptor that is to be used
	 */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void SetDesiredBlueprint( const FString& blueprintName );
	
	/** Updates the gamestate slot data for a given index */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|BuildGunPaint" )
	void SetCustomizationDataForSlot( uint8 slotIndex, FFactoryCustomizationColorSlot slotData );

	/** Server call for clients to set the slot data */
	UFUNCTION( Server, Reliable )
	void Server_SetCustomizationDataForSlot( uint8 slotIndex, FFactoryCustomizationColorSlot slotData );

	void SetAllowRayClearanceHit( bool allow );
	void SetAllowRayBlueprintProxyHit( bool allow );
	void SetAllowRayWireMeshHit( bool allow );

	bool IsRayClearanceHitAllowed() const { return mAllowCleranceRayHits; }
	bool IsRayBlueprintProxyHitAllowed() const { return mAllowBlueprintProxyRayHits; }
	bool IsRayWireMeshHitAllowed() const { return mAllowWireMeshRayHits; }

	/** Gets the default range of the build gun. **/
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	float GetDefaultBuildGunRange() const { return mBuildDistanceMax; }

	/** Set the state to enter on the next equip */
	void SetPendingEntryState( EBuildGunState state );

	/** Set the menu section for the build menu */
	UFUNCTION( BlueprintCallable, Category = "BuildGun" )
	void SetMenuStateSection( EMenuStateSection desiredSection, bool broadcastUpdate = true );

	/** Gets the current menu state section. */
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	EMenuStateSection GetMenuStateSection() { return mMenuStateSection; }

	/** Updates cached hit result and simulate building sample pressed */
	UFUNCTION()
	void TryBuildSample();

	/** Set the current mode on the build gun. */
	UFUNCTION( BlueprintCallable, Category = "BuildGunModeSelect" )
	void SetCurrentBuildGunMode( TSubclassOf< UFGBuildGunModeDescriptor > mode );

	/** Gets the currently active buildgun mode. */
	UFUNCTION( BlueprintPure, Category = "BuildGunModeSelect" )
	FORCEINLINE TSubclassOf< UFGBuildGunModeDescriptor > GetCurrentBuildGunMode() const { return mCurrentBuildGunMode; }

	/** Checks if the build gun's current mode is the one specified. */
	UFUNCTION( BlueprintPure, Category = "BuildGunModeSelect" )
	bool IsCurrentBuildGunMode( TSubclassOf< UFGBuildGunModeDescriptor > buildMode ) const;

	UFUNCTION( BlueprintCallable, Category = "BuildGunModeSelect" )
	FORCEINLINE bool IsWaitingForBuildGunModeSelectUI() const { return mIsWaitingForSelectionUI; }

	UFUNCTION( BlueprintCallable, Category = "BuildGunModeSelect" )
	void CycleBuildMode( int32 deltaIndex );
	
	UFUNCTION( BlueprintPure, Category = "BuildGun" )
	float GetBuildGunRange() const;

	void GotoNoneState() { GotoState(EBuildGunState::BGS_NONE); } // i am not feeling good about this :( but it seems necessary in order to switch back to the build menu state after shortcut radial menu closes

protected:
	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;

	/** Show the  mode selection UI */
	UFUNCTION( BlueprintImplementableEvent, Category = "BuildModeSelect" )
	void ShowBuildGunModeSelectUI();

	/** Close the  mode selection UI */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "BuildModeSelect" )
	void CloseBuildGunModeSelectUI();
private:
	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_PrimaryFire();

	/** Lets the server handle the action. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_SecondaryFire();

	/** Lets the server switch to build state. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_GotoBuildState( TSubclassOf< class UFGRecipe > recipe );

	/** Inform the server of which blueprint file we are using (in the event that the blueprint hologram is set on the build state) */
	UFUNCTION( Server, Reliable )
	void Server_SetDesiredBlueprint( const FString& blueprintName );
	
	/** Lets the server switch to paint state. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_GotoPaintState( TSubclassOf< class UFGCustomizationRecipe > customizationRecipe );

	UFUNCTION( Server, Reliable )
	void Server_SetCurrentBuildGunMode( TSubclassOf< UFGBuildGunModeDescriptor > mode );

	/**
	 * (Simulated)
	 * Set the build gun in the given state.
	 * Some states may require additional parameters so use the GotoXyzState helper functions.
	 * @note Must be called on the local player.
	 */
	void GotoState( EBuildGunState state );

	/** Lets the server switch state. */
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_GotoState( EBuildGunState state );

	/** Switch the current state */
	void GotoStateInternal( EBuildGunState state );

	UFUNCTION()
	void OnRep_CurrentBuildGunMode();

private:
	FORCEINLINE UFGBuildGunState* GetState( EBuildGunState state ) const { return mStates[ ( uint8 )state ]; }
	template< class C > FORCEINLINE C* GetState( EBuildGunState state ) const { return CastChecked< C >( GetState( state ) ); }

	void CreateBuildGunState( EBuildGunState state, FName StateName, TSubclassOf<UFGBuildGunState> stateClass );
public:
	/** Called when the build gun state changes. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|State" )
	FOnBuildGunStateChanged mOnStateChanged;
	
	/** Called when the build gun menu state changes. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|State" )
	FOnBuildGunMenuStateChanged mOnMenuStateChanged;

	/** Called when the build gun build state receives a new recipe. This May be called prior to OnStateChanged. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Recipe" )
	FOnBuildGunRecipeChanged mOnRecipeChanged;

	/** Called when the build gun have sampled a new recipe. */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Recipe" )
	FOnRecipeSampled mOnRecipeSampled;

	/** Called when the build gun have sampled customizations */
	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Paint" )
	FOnCustomizationsSampled mOnCustomizationsSampled;

	UPROPERTY( BlueprintAssignable, Category = "BuildGun|Mode", DisplayName = "OnBuildGunModeChanged" )
	FBuildGunModeChanged mOnBuildGunModeChanged;

protected:
	/** Trace distance for this build gun when building and dismantling. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun" )
	float mBuildDistanceMax;

	/** The state to use when operating the menus. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunState > mMenuStateClass;

	/** The state to use when building. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunStateBuild > mBuildStateClass;

	/** The state to use when dismantling. */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunStateDismantle > mDismantleStateClass;

	/** The state to use when painting (applying color, patterns, etc.) */
	UPROPERTY( EditDefaultsOnly, Category = "BuildGun|State" )
	TSubclassOf< class UFGBuildGunStatePaint > mPaintStateClass;

	bool mAllowCleranceRayHits = false;

	bool mAllowBlueprintProxyRayHits = false;
	
	bool mAllowWireMeshRayHits = false;

private:
	/** All the states. */
	UPROPERTY( Replicated )
	UFGBuildGunState* mStates[ ( uint8 )EBuildGunState::BGS_MAX ] {};

	/** Current mode on the buildgun. */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentBuildGunMode )
	TSubclassOf< UFGBuildGunModeDescriptor > mCurrentBuildGunMode;

	/** State to enter on the next equip. */
	EBuildGunState mPendingEntryState;

	/** Current menu section of the build gun. */
	EMenuStateSection mMenuStateSection;

	/** Result of the latest trace. */
	UPROPERTY()
	FHitResult mHitResult;

	/**
	 * (Simulated)
	 * Current build gun state.
	 * The client sets this locally and tells the server I want this state.
	 */
	UPROPERTY()
	EBuildGunState mCurrentStateEnum;

	// <FL> [PuschkeN] keeping track of the previous build gun state allows us to detect e.g. when returning to the build menu directly from building, in which case we want to set the focus on that recipe
	UPROPERTY()
	EBuildGunState mPreviousStateEnum;
	// </FL>

	/** @see mCurrentStateIndex. */
	UPROPERTY()
	UFGBuildGunState* mCurrentState;

	/** wait for primary fire release event before re-initiating another build gun fire. Does not affect click+hold. */
	bool mWaitingForPrimaryFireRelease;

	bool mHasHookedUpBuildStateUserSettings = false; //[DavalliusA:Thu/23-01-2020] not happy with this, but didn't find a function that is only called once and where we know we have a local instagator or not

	/** True if we are waiting for the selection UI */
	UPROPERTY()
	bool mIsWaitingForSelectionUI = false;
	
	/** stores a time we have held the mode select button for. Used so we can detect if it's a hold or tap, to show the menu or not*/
	float mBuildModeSelectHoldTime = -1; //@TODO:[DavalliusA:Thu/28-11-2019] consider using a game time stamp instead so we don't have to rely on tick to update this

	/** Time needed to hold down the key to show the selection UI */
	UPROPERTY( EditDefaultsOnly, Category = "BuildModeSelect" )
	float mBuildModeSelectHoldDownDurationForUI = 0.18f;

	/** Build gun item descriptor to use for looking up build gun as a recipe producer */
    UPROPERTY( EditDefaultsOnly, Category = "BuildGun" )
    TSoftClassPtr<UFGItemDescriptor> mBuildGunEquipmentDescriptor;
};

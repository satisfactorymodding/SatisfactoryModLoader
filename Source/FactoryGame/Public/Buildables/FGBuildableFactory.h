// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGSignificanceInterface.h"
#include "FGBuildableFactory.generated.h"

enum class EPowerShardType : uint8;
enum class EVisibilityBasedAnimTickOption : uint8;
struct FInstanceHandle;

/** Delegate for when some binary state has changed */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBuildingStateChanged, bool, state );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildingProductionBoostChanged, float, newProductionBoost );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildingPotentialChanged, float, newProductionBoost );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnBuildingProductivityChanged, float, newProductivity );
DECLARE_MULTICAST_DELEGATE_OneParam( FBuildingCurrentPotentialChanged, float );

/**
 * Base class for factory machines like miners, conveyors, assemblers, storages etc.
 * @todorefactor Comments about the Factory_ and non factory code.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFactory : public AFGBuildable, public IFGSignificanceInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	AFGBuildableFactory();

	// Begin UObject interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End UObject interface
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual void UpdateSignificanceTickRate_Implementation(float NewTickRate, bool bTickEnabled) override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual	void SetupForSignificance() override;
	virtual void SetInitialState(bool bState) override { mIsSignificant = bState; }
	virtual bool DoesReduceTick() const override;
	virtual int32 NumTickLevels() const override;
	virtual float GetTickExponent() const override { return mTickExponent; }
	//End IFGSignificanceInterface

	//~ Begin IFGUseableInterface
	virtual void RegisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	virtual void UnregisterInteractingPlayer_Implementation( class AFGCharacterPlayer* player ) override;
	//~ End IFGUseableInterface

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface
	
	// Begin FGBuildable
	virtual void OnBuildEffectFinished() override;
	virtual void OnBuildEffectActorFinished() override;
	virtual void Dismantle_Implementation() override;
	// End FGBuildable

	/** Get the connections to this factory. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Factory" )
	TArray< UFGFactoryConnectionComponent* > GetConnectionComponents() const;

	/**
	 * Visual "HasPower" used to update emmisive data float on customprimdata / PIC
	 */
	virtual float GetEmissivePower() override;

	virtual bool ShouldShowCenterGuidelinesForHologram( const AFGHologram* hologram ) const override;

	/**
	 * Check if we have power.
	 * @return true if we have power; false if we do not have power or does not run on power.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	bool HasPower() const { return mHasPower; }

	UFUNCTION(BlueprintPure,Category="FactoryGame|Factory")
	bool CanChangeProductionBoost() const { return mCanChangeProductionBoost; }
	/**
	 * Check if this machine runs on power.
	 * @return - true if this machine runs on power; false if it does not.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	bool RunsOnPower() const { return mPowerConsumption > 0.f; }

	/**
	 * Get the power info for this factory.
	 * @return The power info for this factory; nullptr if this factory does not run on power.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	FORCEINLINE class UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/** Get the power consumption for production. */
	virtual float GetIdlePowerConsumption() const;

	/** Get the current producing consumption before overclocking is applied. */
	virtual float GetProducingPowerConsumptionBase() const { return mPowerConsumption; }

	/** The power consumption when producing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	float GetProducingPowerConsumption() const;

	/** The unmodified power consumption when producing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	float GetDefaultProducingPowerConsumption() const;

	/** Calculates power consumption for overclocking */
	static float CalcOverclockPowerConsumption( float power, float overclock, float exponent );

	/** Calculates power consumption for production boost */
	static float CalcProductionBoostPowerConsumption( float power, float productionBoost, float exponent );
	
	/** Helper to get the power consumption for production at a certain potential. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	float CalcProducingPowerConsumptionForPotential( float potential ) const;

	/**
	 * Check if this building has been configured by the player, has recipe set etc.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual bool IsConfigured() const;

	/**
	 * Are we producing?
	 *
	 * @return - true if producing; otherwise false.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	bool IsProducing() const
	{
		return Factory_IsProducing();
	}

	/* Native version of IsProducing */
	FORCEINLINE virtual bool Factory_IsProducing() const
	{
		return mIsProducing;
	}

	/** Returns true if this building is alien overclocked (has production boost > 100%). Returns correct value on the client even if the UI is not open */
	UFUNCTION( BlueprintPure, Category = "Alien Overclocking" )
	FORCEINLINE bool IsAlienOverclocked() const { return mIsAlienOverclocked; }

	/** Returns true if this building is overclocked (has potential > 100%). Returns correct value on the client even if the UI is not open */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE bool IsOverclocked() const { return mIsOverclocked; }

	/**
	 * Can we start production i.e. do we have the items needed for assembly etc.
	 *
	 * @return - true if we can start production; otherwise false.
	 */
	UFUNCTION( BlueprintPure, BlueprintNativeEvent, CustomEventUsing=mHasCanProduce, Category = "FactoryGame|Factory|Production" )
	bool CanProduce() const;

	/** Set if this factory should pause it's production or not. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Production" )
	virtual void SetIsProductionPaused( bool isPaused );

	/** Is this factory's production manually paused. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Production" )
	FORCEINLINE bool IsProductionPaused() const { return mIsProductionPaused; }

	//@todomods This should be moddable without performance impact.
	/** @return The status to display on the production indicator, valid on server and client. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual EProductionStatus GetProductionIndicatorStatus() const;

	/** Returns the current progress of the production. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float GetProductionProgress() const;

	/** The current production cycle time for the current recipe, with potential multiplier applied */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float GetProductionCycleTime() const;

	/** The production cycle time for the recipe, not including the current potential multiplier */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float GetDefaultProductionCycleTime() const;

	/** Calculates the production cycle time of this factory with a certain recipe without modifiers. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float GetProductionCycleTimeForRecipe( TSubclassOf< UFGRecipe > recipe ) const;

	/** Calculates the production cycle time of this factory with a certain potential */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float CalcProductionCycleTimeForPotential( float potential ) const;
	
	/** A measure of how productive this factory is. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Productivity" )
	virtual float GetProductivity() const;

	/** How long is the measurement for the buildings productivity. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Productivity" )
	float GetProductivityMeasurementDuration() const;

	/** Get the inventory that we place crystal in to unlock the slider of potential */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE UFGInventoryComponent* GetPotentialInventory() const { return mInventoryPotential; }

	/** Gets you the current potential */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetCurrentPotential() const { return mCurrentPotential; }

	/** Gets you the pending potential */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetPendingPotential() const { return mPendingPotential; }

	/** Set a new pending potential, the current one will be changed to this when we finish a production cycle */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	virtual void SetPendingPotential( float newPendingPotential );
	
	/** Get the minimum potential possible */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	virtual float GetCurrentMinPotential() const;
	
	/** Get the default maximum potential possible */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetMaxPotential() const { return mMaxPotential; }

	/** Get the maximum potential possible depending on the num crystals in inventories */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	virtual float GetCurrentMaxPotential() const;
	
	/** Get mCanChangePotential */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE bool GetCanChangePotential() const { return mCanChangePotential; }

	/** Get the stack size scalar for fluid types on this buildable ( this is only relevant to fluid inventories ) */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Inventory" )
	FORCEINLINE float GetFluidInventoryStackSizeScalar() const { return mFluidStackSizeMultiplier; }

	/** Get the override stack size scaled for fluid types. Specified in class / BP defaults */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Inventory" )
	FORCEINLINE int32 GetScaledFluidStackSize( ) const { return mCachedFluidStackSize * mFluidStackSizeMultiplier; }

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Significance" )
	FORCEINLINE bool GetIsSignificant() { return mIsSignificant || !mAddToSignificanceManager; }

	/** Called when we want the looping SFX/VFX for production to start
	  * @param didStartProducing - true if factory just started producing
	  */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Factory|Effects" )
	void StartProductionLoopEffects( bool didStartProducing );

	/** Called when we want the looping SFX/VFX for production to stop 
	  * @param didStopProducing - true if the production stopped 
	  */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Factory|Effects" )
	void StopProductionLoopEffects( bool didStopProducing );

	/** Called when we want the looping SFX/VFX for idling ( power but no production ) to start 
	 * @param didGainPower - true if factory just got power
	  */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Factory|Effects" )
	void StartIdlingLoopEffects( bool didGainPower );

	/** Called when we want the looping SFX/VFX for idling ( power but no production ) to stop 
	 * @param didLosePower - true if factory just lost power
	  */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Factory|Effects" )
	void StopIdlingLoopEffects( bool didLosePower );

	/** Called when we want the looping SFX/VFX for idling ( power but no production ) to stop. Will prevent StopIdlingLoopEffects to be called twice in a row 
	 * @param didLosePower - true if factory just got power
	  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Effects" )
	void TryStopIdlingLoopEffects( bool didLosePower );

	/** Called when we want the looping SFX/VFX for idling ( power but no production ) to start. Will prevent StartIdlingLoopEffects to be called twice in a row 
	 * @param didGainPower - true if factory just got power
	  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Effects" )
	void TryStartIdlingLoopEffects( bool didGainPower );

	/** Called when we want the looping SFX/VFX for production to stop. Will prevent StartProductionLoopEffects to be called twice in a row
	  * @param didStopProducing - true if the production stopped
	  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Effects" )
	void TryStartProductionLoopEffects( bool didStartProducing );

	/** Called when we want the looping SFX/VFX for production to stop. Will prevent StopProductionLoopEffects to be called twice in a row
	  * @param didStopProducing - true if the production stopped
	  */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Effects" )
	void TryStopProductionLoopEffects( bool didStopProducing );

	/** Updates  EVisibilityBasedAnimTickOption on all cached skel meshes */
	void UpdateAnimTickOption( EVisibilityBasedAnimTickOption newOption );

	/** Gets you the current production boost multiplier */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetCurrentProductionBoost() const { return mCurrentProductionBoost; }

	/** Gets you the pending production boost */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetPendingProductionBoost() const { return mPendingProductionBoost; }

	/** Set a new pending production boost multiplier, the current one will be changed to this when we finish a production cycle */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	virtual void SetPendingProductionBoost( float newPendingProductionBoost );

	/** Get the minimum production boost multiplier possible, e.g. the base one */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetMinProductionBoost() const { return mBaseProductionBoost; }

	/** Get the maximum production boost multiplier possible without using the shards, e.g. the base one */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE float GetMaxProductionBoost() const { return mBaseProductionBoost; }

	/** Get the maximum production boost multiplier depending on the amount of shards in the inventory */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	float GetCurrentMaxProductionBoost() const;
	
	/** Tries to fill up the potential inventory from the given players inventory so we can use the target potential. Doesn't apply target potential
	 *	Returns the pair of potential and production boost we were able to apply based on the amount of shards we have by type
	 */
	virtual bool TryFillPotentialInventory( AFGCharacterPlayer* player, const TMap<EPowerShardType, TPair<TSubclassOf<class UFGPowerShardDescriptor>, float>>& potentialValues, TMap<EPowerShardType, float>& out_reachedPotentialValues, bool simulate = false);

	/**
	 * Attempts to move all items out of the inventory to the player inventory, if it cannot it drops them
	 * on the ground instead around the player
	 */
	static void MoveOrDropInventory( UFGInventoryComponent* inventory, AFGCharacterPlayer* player );
protected:
	/** Helper function to fill the potential inventory slots from the player inventory with the shards of the particular type, aiming to reach a target amount of shards in slots. Once this function returns, the ref parameter contains amount of slots the inventory was unable to accomodate */
	void FillPotentialSlotsInternal( UFGInventoryComponent* playerInventory, EPowerShardType powerShardType, TSubclassOf<UFGPowerShardDescriptor> shardItemDescriptor, int32& ref_targetAmountOfShardsInSlots, TArray<FInventoryStack>& out_itemsToDrop ) const;
	
	/** Helper function to calculate maximum production, can be used for Custom shard types */
	float GetCurrentMaxPotentialForType(EPowerShardType powerShardType, float minValue, float maxValue, float boostPerShardMultiplier = 1.0f) const;
	
	/** Called whenever HasPower has changed, exposed here for cleaner/more optimized ways of changing state when the factory has power */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasOnHasPowerChanged, Category="FactoryGame|Factory|Power")
	void OnHasPowerChanged( bool newHasPower );

	/** Called whenever IsProducing has changed, exposed here for cleaner/more optimized ways of changing state when the factory is producing */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasOnIsProducingChanged, Category = "FactoryGame|Factory|Production" )
	void OnIsProducingChanged( bool newIsProducing );

	/** Native version of OnIsProducingChanged */
	UFUNCTION( )
	void OnIsProducingChanged_Native( bool newIsProducing );

	/** Native version of OnHasPowerChanged */
	UFUNCTION()
	void OnHasPowerChanged_Native( bool newHasPower );

	/** Set a new current potential, used to catch all changes of current potential and broadcast an event */
	void SetCurrentPotential( float newCurrentPotential );

	/** Event for when current potential is changed*/
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Factory|Productivity" )
    void OnCurrentPotentialChanged( float newCurrentPotential );

	/** Set a new value of the current production boost and fire the event */
	virtual void SetCurrentProductionBoost( float newProductionBoost );

	/** Event for when current potential is changed */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Factory|Productivity" )
	void OnCurrentProductionBoostChanged( float newCurrentProductionBoost );

	/** Called to check if this building has power, result is cached in Factory_Tick, use HasPower() instead. */
	virtual bool Factory_HasPower() const;
	
	/** Call this when we finished a production cycle, like produced a recipe or extracted an ore. */
	UFUNCTION(BlueprintCallable, Category = "FactoryGame|Factory|Productivity")
	virtual void Factory_ProductionCycleCompleted( float overProductionRate );

	/** Try to collect input from connected buildings. */
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing = mHasFactory_CollectInput, Category = "FactoryGame|Factory|Production" )
	void Factory_CollectInput();

	/** Try to collect input from connected pipes */
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing = mHasFactory_PullPipeInput, Category = "FactoryGame|Factory|Production" )
	void Factory_PullPipeInput( float dt );

	/** Try to push fluid inventory to connected pipes 
	*	This is contrary to always pulling like FactoryConnections. Pipes are handled very differently from buildings
	*	so a push occurs so that each pipe doesn't need to differentiate between objects its connected to.
	*/
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing = mHasFactory_PushPipeOutput, Category = "FactoryGame|Factory|Production" )
	void Factory_PushPipeOutput( float dt );

	/** Start the production, client get this call replicated after the server. You must call Super if overriding this. */
	virtual void Factory_StartProducing();

	/** Calls blueprint when we start producing. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing=mHasFactory_StartProducing, Category = "FactoryGame|Factory|Production", meta = (DisplayName = "Factory_StartProducingAuthorative") )
	void Factory_ReceiveStartProducing();

	/** Tick the production. */
	virtual void Factory_TickProducing( float dt );

	/** Tick the fact that we are not producing. Used for productivity calculations. */
	void Factory_TickProductivity( float dt );

	/** Calls blueprint when we tick production. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasFactory_TickProducing, Category = "FactoryGame|Factory|Production", meta=(DisplayName="Factory_TickProducingAuthorative") )
	void Factory_ReceiveTickProducing( float deltaTime );

	/** Stops the production, client get this call replicated after the server. You must call Super if overriding this. */
	virtual void Factory_StopProducing();

	/** Calls blueprint when we stop producing. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasFactory_StopProducing, Category = "FactoryGame|Factory|Production", meta = (DisplayName = "Factory_StopProducingAuthorative") )
	void Factory_ReceiveStopProducing();

	/** Function for updating sfx/vfx at intervals */
	virtual void NativeUpdateEffects( float DeltaSeconds );

	/** Calls blueprint when we update effects. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasUpdateEffects, Category = "FactoryGame|Factory|Effects", meta = ( DisplayName = "UpdateEffects" ) )
	void ReceiveUpdateEffects( float DeltaSeconds );

	/* Spawns all particles found through GetAlienOverClockingEffectLocations(). */
	UFUNCTION( BlueprintNativeEvent, Category = "Alien Overclocking" )
	void TrySpawnAlienOverClockingEffects( const TArray<UNiagaraSystem*>& ParticlesToSpawn, const TArray<FTransform>& LocationsForParticlesToSpawn );

	/* Destroys all particle and sound effects that are spawned through TrySpawnAlienOverClockingEffects*/
	UFUNCTION( BlueprintNativeEvent, Category = "Alien Overclocking" )
	void TryCleanupAlienOverClockingEffects();

	void GetAlienOverClockingEffectLocations(UStaticMesh* SourceMesh, FTransform SourceTransform, TArray<UNiagaraSystem*>& ParticlesToSpawn, TArray<FTransform>& LocationsForParticlesToSpawn);

	/** Utility function for scheduling a task to run on the next tick of the main thread */
	void ScheduleTaskOnMainThread( const TDelegate<void()>& inDelegate ) const;

	UFUNCTION()
	virtual void OnRep_CurrentPotential();
	UFUNCTION()
	virtual void OnRep_IsProductionPaused();
	UFUNCTION()
	virtual void OnRep_CurrentProductionBoost();
	UFUNCTION()
	virtual void OnRep_PendingPotential();
	UFUNCTION()
	virtual void OnRep_PendingProductionBoost();
	UFUNCTION()
	virtual void OnRep_CurrentProductivity();
private:
	/** Calls Start/Stop Producing on client */
	UFUNCTION()
	virtual void OnRep_IsProducing();
	UFUNCTION()
	virtual void OnRep_IsAlienOverclocked();

	UFUNCTION()
	virtual void OnPotentialInventoryItemChanged( TSubclassOf< UFGItemDescriptor > itemClass, const int32 numChanged, UFGInventoryComponent* sourceOrTargetInventory = nullptr );
	
	/** Filters what item can be used in the potential inventory slots. We use it to check if overclock have been unlocked */
	UFUNCTION()
	virtual bool FilterPotentialInventoryClasses( TSubclassOf< UObject > object, int32 idx ) const;

	virtual bool IsPowerShardTypeAllowed(EPowerShardType PowerShardType) const;

	//////////////////////////////////////////////////////////////////////////
	/// Push Model Replication Setters
	void SetIsProducing( uint8 isProducing );
	void SetHasPower( uint8 hasPower );
	void SetCurrentProductivity( uint8 productivity );
	void SetIsAlienOverclocked( bool isAlienOverclocked );
	void SetIsOverclocked( bool isOverclocked );

	/**
	 * Toggle productivity monitoring.
	 * When turned off, the productivity is reset to 0. 
	 */
	void SetProductivityMonitorEnabled( bool enabled );

	/** Handles the migration of the potential inventory when it has been loaded with the smaller capacity */
	static void MigratePotentialInventorySlots( UFGInventoryComponent* inventory, int32 oldSize, int32 newSize );

	/** Determines whenever the alien overclocking effects should be visible now, and depending on that calls Start/Stop alien overclocking effects */
	void UpdateAlienOverclockingEffects();
	
	void StopAlienOverclockingEffects();
	void StartAlienOverclockingEffects();
protected:
	void GetSlotsForPowerShardType( EPowerShardType powerShardType, TArray< int32 >& out_slotIndices ) const;
	EPowerShardType GetPowerShardTypeForSlot( int32 slotIdx ) const;

	void RecalculateProducingPowerConsumption();
	
public:
	/** Power consumption of this factory. */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = "0.0" ) )
	float mPowerConsumption;

	/**
	 * Exponent used in power consumption calculations.
	 * To calculate maximum consumption: max = overclock ^ exponent
	 * Example: 2.5 ^ 1.6 = 4.33      An exponent of 1.6 gives a maximum consumption of 433% at 2.5x overclock.
	 * If exponent is 1.0 the function becomes linear.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = "1.0", ClampMax = 2 ) )
	float mPowerConsumptionExponent;

	UPROPERTY( EditDefaultsOnly, Category = "Power", meta = ( ClampMin = "1.0", ClampMax = 4 ) )
	float mProductionBoostPowerConsumptionExponent;

	UPROPERTY( EditDefaultsOnly, Category = "Animation" )
	bool mDoesHaveShutdownAnimation;

	FORCEINLINE EProductionStatus GetCachedProductionState() const { return mCachedProductionStatus; }
	
	/** So that you can listen for when power has changed */
	UPROPERTY(BlueprintAssignable)
	FBuildingStateChanged mOnHasPowerChanged;

	/** So that you can listen for when production has changed */
	UPROPERTY( BlueprintAssignable )
	FBuildingStateChanged mOnHasProductionChanged;

	/** So that you can listen for when standby is toggled. True == Standby is active False == Standby was disabled */
	UPROPERTY( BlueprintAssignable )
	FBuildingStateChanged mOnHasStandbyChanged;

	/** So that you can listen for when current potential is changed. */
	FBuildingCurrentPotentialChanged mOnCurrentPotentialChanged;

	/** Called when the pending potential value on this buildable changes. Called on the client as well. */
	UPROPERTY( BlueprintAssignable )
	FOnBuildingPotentialChanged mOnPendingPotentialChanged;

	/** Called when the pending production boost value on this buildable changes. Called on the client as well. */
	UPROPERTY( BlueprintAssignable )
	FOnBuildingProductionBoostChanged mOnPendingProductionBoostChanged;

	/** Called when the productivity of the buildable changes. This is to be used in conjunction with GetProductivity */
	UPROPERTY( BlueprintAssignable )
	FOnBuildingProductivityChanged mOnCurrentProductivityChanged;
protected:
	/** Transient struct handling the conditional replication of the buildable properties */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;

	/** Power simulation info */
	UPROPERTY( SaveGame )
	class UFGPowerInfoComponent* mPowerInfo;
		
	/**
	 * The minimum time one production cycle must take.
	 * If the part is finished earlier the machine remains in the producing state until the minimum time has passed.
	 * If the required input for the next part is available during this time, it starts producing again, thus remaining in the production state.
	 * TickProducing is not called during the wait.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Production" )
	float mMinimumProducingTime;

	/**
	 * The minimum time that must pass from when the production is stopped until it can start up again.
	 * If the machine has stopped and new parts are available within the delay, the machine will wait until the minimum time has passed.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Production" )
	float mMinimumStoppedTime;

	/**
	 * This is reset every time the production is changed, i.e. StartProducing/StopProducing.
	 */
	UPROPERTY( SaveGame, Meta = (NoAutoJson = true) )
	float mTimeSinceStartStopProducing;

	/** Keeps track if we produced this tick or not */
	bool mDidProduceThisTick;
	
	/** Should this building ever be able to have productivity monitoring? */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	bool mCanEverMonitorProductivity;

	/** Set this to true if we want this building to be able to change the production rate potential with the "Slider of Potential" */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	bool mCanChangePotential;
	
	/** True if we allow changing the production boost multiplier and inserting production boost shards */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	bool mCanChangeProductionBoost;

	/** When ever a production cycle is completed we set the current potential to this value */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_PendingPotential ) )
	float mPendingPotential;

	/** When ever a production cycle is completed we set the current production boost to this value */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_PendingProductionBoost ) )
	float mPendingProductionBoost;

	/** You can never set the potential to less than this when playing */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mMinPotential;
	
	/** Default maximum potential on the buildable, not accounting for the installed power shards */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mMaxPotential;

	/** Default max production boost multiplier on a buildable, normally 1.0 */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mBaseProductionBoost;
	
	/** Number of slots used for potential/overclocking shards */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity", meta = (EditCondition = "mOverridePotentialShardSlots", EditConditionHides) )
	int32 mPotentialShardSlots;
	
	/** Slot size for the production boost power shards */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity", meta = (EditCondition = "mOverrideProductionShardSlotSize", EditConditionHides) )
	int32 mProductionShardSlotSize;

	/** Multiplier to apply to the production boost value from the production boost shards in this buildable */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mProductionShardBoostMultiplier;
	
	/** Item stack size Enum to use as base for how much fluid a Liquid / Gas Item descriptor can be stored on an index in an inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	EStackSize mFluidStackSizeDefault;

	/** Scalar for multiplying the default Stack Size for Fluid Inventory Slots ( 1 is default. 2 == 2 * FluidStackSize )*/
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mFluidStackSizeMultiplier;

	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	bool mHasInventoryPotential;
	
	/** The player is able to toggle if production should be paused or not */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsProductionPaused, Meta = (NoAutoJson = true) )
	bool mIsProductionPaused;

	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	bool mIsTickRateManaged = true;
	
private:
	/** The input we place a crystal in to unlock the potential */
	UPROPERTY( EditDefaultsOnly, SaveGame, Category = "Productivity" )
	class UFGInventoryComponent* mInventoryPotential;
	
	/** This is the current potential (overclock, overcharge) of this factory [0..N]
	* [FreiholtzK:Fri/4-12-2020]  encapsulated to make sure we catch changes of this value and can broadcast them
	*/
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_CurrentPotential ) )
	float mCurrentPotential;

	/** The current production boost multiplier set on the buildable */
	UPROPERTY( SaveGame, Meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_CurrentProductionBoost ) )
	float mCurrentProductionBoost;

	/** How often effect update should update */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mEffectUpdateInterval;

	/** Accumulator for the effect update interval */
	float mEffectUpdateAccumulator;

	/** Cached value of Fluid Resource Stack Size ( set in begin play from the default stack enum ) */
	int32 mCachedFluidStackSize;

	/** The cached production status, evaluated once every tick. */
	EProductionStatus mCachedProductionStatus;

	/**
	 * For how long do the building calculate and average of the productivity. [seconds]
	 * Due to a simplified implementation the real average for the mCurrentProductivity will be over [default, default * 2] seconds.
	 */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mDefaultProductivityMeasurementDuration = 300.f;
	
	/**
	 * Calculate and average over time by using two averages, we save one average from the past and update the current one.
	 * When the current one gets above the specified measured time, save it to the last and start over on the current one.
	 */
	UPROPERTY( SaveGame )
	float mLastProductivityMeasurementProduceDuration;
	UPROPERTY( SaveGame )
	float mLastProductivityMeasurementDuration;
	UPROPERTY( SaveGame )
	float mCurrentProductivityMeasurementProduceDuration;
	UPROPERTY( SaveGame )
	float mCurrentProductivityMeasurementDuration;
	
	/** A replicated compressed version of the productivity, where a value of 0-255 is 0-100 percent. */
	UPROPERTY( Meta = ( NoAutoJson = true, FGReplicatedUsing = OnRep_CurrentProductivity ) )
	uint8 mCurrentProductivity;
	
	/** Should this building calculate its productivity, buildings do not tick productivity when newly built or in standby. */
	UPROPERTY( SaveGame )
	uint8 mProductivityMonitorEnabled : 1;
	
	/** Are we producing? Do not set this manually, some delegates and other stuff might not get triggered then. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsProducing, Meta = (NoAutoJson = true) )
	uint8 mIsProducing : 1;

	/** if true, then blueprint has implemented CanProduce */
	uint8 mHasCanProduce : 1;

	/** If building has power, for more details about the circuitry see mPowerInfo. */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	uint8 mHasPower : 1;

	/** Last frame's has power */
	uint8 mLastHasPower : 1;

	/** Last frame's is producing */
	uint8 mLastIsProducing : 1;

	/** if true, then blueprint has implemented Factory_CollectInput */
	uint8 mHasFactory_CollectInput : 1;

	/** if true, then the blueprint has implemented Factory_PullPipeInput */
	uint8 mHasFactory_PullPipeInput : 1;

	/** if true, then the blueprint has implemented Factory_PushPipeOutput */
	uint8 mHasFactory_PushPipeOutput : 1;

	/** if true, then blueprint has implemented OnHasPowerChanged */
	uint8 mHasOnHasPowerChanged : 1;

	/** if true, then blueprint has implemented OnHasProducingChanged */
	uint8 mHasOnIsProducingChanged : 1;

	/** if true, then blueprint has implemented Factory_StartProducing */
	uint8 mHasFactory_StartProducing : 1;

	/** if true, then blueprint has implemented Factory_TickProducing */
	uint8 mHasFactory_TickProducing : 1;

	/** if true, then blueprint has implemented Factory_StopProducing */
	uint8 mHasFactory_StopProducing : 1;

	/** if true, then blueprint has implemented UpdateEffects */
	uint8 mHasUpdateEffects : 1;

	/** Indicates if the factory is within significance distance */
	uint8 mIsSignificant : 1;

	/** Indicates if we have already started the idling effects */
	uint8 mDidStartIdlingEffects : 1;

	/** Indicates if we have already started the production effects effects */
	uint8 mDidStartProductionEffects : 1;

	/** True if the building is currently overclocked. Updated on BeginPlay and when overclocking potential changes */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	uint8 mIsOverclocked : 1;
	/** True if the building is currently alien overclocked. Updated on BeginPlay and when alien overclocking potential changes */
	UPROPERTY( ReplicatedUsing = OnRep_IsAlienOverclocked, Meta = (NoAutoJson = true) )
	uint8 mIsAlienOverclocked : 1;

	/** True if we are currently playing alien overclocking effects */
	uint8 mIsPlayingAlienOverclockingEffects : 1;
protected:
	/* Determines if we should Factory_PullPipeInput in factory tick.*/
	uint8 mHasPipeInput : 1;

	/* Determines if we should Factory_PushPipeOutput in factory tick.*/
	uint8 mHasPipeOutput : 1;

	/* Determines if we should collect inputs in factory tick.*/
	uint8 mHasSolidInput : 1;

	/** Whenever this buildable has a custom value for Potential Shard Slots */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	uint8 mOverridePotentialShardSlots : 1;

	/** Whenever this buildable has a custom value for Production Shard Slot Size */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	uint8 mOverrideProductionShardSlotSize : 1;
	
	/** Indicates if the factory should be handled by significance manager */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	uint8 mAddToSignificanceManager : 1;
	
	/** Particle effects currently playing for the alien overclocking */
	UPROPERTY( BlueprintReadWrite, Category = "Alien Overclocking" )
	TArray<UNiagaraComponent*> mAlienOverClockingParticleEffects;

	/** Audio component playing the alien overclocking audio */
	UPROPERTY( BlueprintReadWrite, Category = "Alien Overclocking" )
	UAkComponent* mAlienOverClockingLayerSFXComponent;
private:	
	/** Caching all skeletal meshes so that we can set tick optimizations later from significance manager */
	UPROPERTY()
	TArray< USkeletalMeshComponent* > mCachedSkeletalMeshes;
protected:
	/** The range to keep the factory in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;

	UPROPERTY( EditDefaultsOnly,Category= "Significance")
	float mTickExponent = 5;
};

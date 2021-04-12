// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGRecipeProducerInterface.h"
#include "FGSignificanceInterface.h"
#include "Replication/FGReplicationDetailInventoryComponent.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGBuildableFactory.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnReplicationDetailActorCreated, class AActor*, replicationDetailActorOwner );

/**
 * Production status of the factory, i.e. displayed on the indicator.
 */
UENUM( BlueprintType )
enum class EProductionStatus : uint8
{
	IS_NONE,
	IS_PRODUCING,
	IS_PRODUCING_WITH_CRYSTAL, //We have a crystal in the potential slot and are producing
	IS_STANDBY,
	IS_ERROR,
	IS_MAX
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FProductionStatusChanged, EProductionStatus, status );

/** Delegate for when some binary state has changed */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FBuildingStateChanged, bool, state );

/**
 * Base class for factory machines like miners, conveyors, assemblers, storages etc.
 * @todorefactor Comments about the Factory_ and non factory code.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFactory : public AFGBuildable, public IFGSignificanceInterface, public IFGReplicationDetailActorOwnerInterface
{
	GENERATED_BODY()
public:
	AFGBuildableFactory();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;
	virtual bool GetNetDormancy( const FVector& ViewPos, const FVector& ViewDir, class AActor* Viewer, AActor* ViewTarget, UActorChannel* InChannel, float Time, bool bLowBandwidth ) override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason );
	virtual void Tick( float dt ) override;
	virtual void Destroyed() override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	//Begin IFGSignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual	void LostSignificance_Implementation() override;
	virtual float GetSignificanceRange() override { return mSignificanceRange; }
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual	void SetupForSignificance() override;
	//End IFGSignificanceInterface

	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin IFGUseableInterface
	virtual void OnUse_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual void OnUseStop_Implementation( class AFGCharacterPlayer* byCharacter, const FUseState& state ) override;
	virtual bool IsUseable_Implementation() const override;
	// End IFGUseableInterface

	// Begin IFGDismantleInterface
	virtual void GetDismantleRefund_Implementation( TArray< FInventoryStack >& out_refund ) const override;
	// End IFGDismantleInterface

	// Begin IFGReplicationDetailActorOwnerInterface
	virtual AFGReplicationDetailActor* GetReplicationDetailActor( bool tryCreate = false ) override 
	{
		if( tryCreate )
		{
			return GetOrCreateReplicationDetailActor(); 
		}
		else
		{
			return mReplicationDetailActor;
		}
	};
	virtual void OnBuildableReplicationDetailStateChange( bool newStateIsActive ) override;
	virtual void OnReplicationDetailActorCreated() override;
	virtual void OnReplicationDetailActorRemoved() override;
	virtual UClass* GetReplicationDetailActorClass() const override { return AFGReplicationDetailActor_BuildableFactory::StaticClass(); };
	// End IFGReplicationDetailActorOwnerInterface

	/** Returns true if caller is server ( no replication detail actor is required ) or if the detail actor has been replicated to the client */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Replication" )
	FORCEINLINE bool HasValidReplicationDetailActor() const { return HasAuthority() || IsValid( mReplicationDetailActor ); }

	// Begin FGBuildable
	virtual bool ShouldSkipBuildEffect() override;
	// End FGBuildable

	/** Get the connections to this factory. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Factory" )
	TArray< UFGFactoryConnectionComponent* > GetConnectionComponents() const;

	/**
	 * Check if we have power.
	 * @return true if we have power; false if we do not have power or does not run on power.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	bool HasPower() const
	{
		return Factory_HasPower();
	}

	/* Native only version of RunsOnPower for inlining. */
	FORCEINLINE virtual bool Factory_HasPower() const
	{
		return mHasPower;
	}
	
	/**
	 * Check if this machine runs on power.
	 * @return - true if this machine runs on power; false if it does not.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	bool RunsOnPower() const { return Factory_RunsOnPower(); }

	/* Native only version of RunsOnPower for inlining. */
	FORCEINLINE virtual bool Factory_RunsOnPower() const
	{
		return mPowerInfo && mPowerConsumption > 0.0f;
	}

	/**
	 * Get the power info for this factory.
	 * @return The power info for this factory; nullptr if this factory does not run on power.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	FORCEINLINE class UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/** Get the power consumption for production. */
	float GetIdlePowerConsumption() const;

	/** Get the current producing consumption before overclocking is applied. */
	virtual float GetProducingPowerConsumptionBase() const { return mPowerConsumption; }

	/** The power consumption when producing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	float GetProducingPowerConsumption() const;

	/** The unmodified power consumption when producing. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Power" )
	float GetDefaultProducingPowerConsumption() const;

	static float CalcPowerConsumption( float power, float overclock, float exponent );

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

	/** The current production cycle time for the current recipe with modifiers. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Production" )
	virtual float GetProductionCycleTime() const;

	/** The unmodified production cycle time for the current recipe. */
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
	float GetProductivity();

	/** Get the inventory that we place crystal in to unlock the slider of potential */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|Productivity" )
	FORCEINLINE UFGInventoryComponent* GetPotentialInventory() const { return mInventoryPotentialHandler->GetActiveInventoryComponent(); }

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
	FORCEINLINE float GetMinPotential() const { return mMinPotential; }

	/** Get the maximum potential possible depending on the num crystals in inventories */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	float GetCurrentMaxPotential() const;

	/** Get the max potential, as if you had all slots filled with crystals */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|Productivity" )
	float GetMaxPossiblePotential() const;

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
protected:
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

	// Begin AFGBuildable interface
	virtual void OnReplicatingDetailsChanged() override;
	// End AFGBuildable interface

	/** Call this when we finished a production cycle, like produced a recipe or extracted an ore. */
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
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing=mHasFactory_StartProducing, Category = "FactoryGame|Factory|Production", meta = (DisplayName = "Factory_StartProducing") )
	void Factory_ReceiveStartProducing();

	/** Tick the production. */
	virtual void Factory_TickProducing( float dt );

	/** Tick the fact that we are not producing. Used for productivity calculations. */
	virtual void Factory_TickProductivity( float dt );

	/** Calls blueprint when we tick production. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasFactory_TickProducing, Category = "FactoryGame|Factory|Production", meta=(DisplayName="Factory_TickProducing") )
	void Factory_ReceiveTickProducing( float deltaTime );

	/** Stops the production, client get this call replicated after the server. You must call Super if overriding this. */
	virtual void Factory_StopProducing();

	/** Calls blueprint when we stop producing. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasFactory_StopProducing, Category = "FactoryGame|Factory|Production", meta = (DisplayName = "Factory_StopProducing") )
	void Factory_ReceiveStopProducing();

	/** Function for updating sfx/vfx at intervals */
	virtual void NativeUpdateEffects( float DeltaSeconds );

	/** Calls blueprint when we update effects. */
	UFUNCTION( BlueprintImplementableEvent, CustomEventUsing = mHasUpdateEffects, Category = "FactoryGame|Factory|Effects", meta = ( DisplayName = "UpdateEffects" ) )
	void ReceiveUpdateEffects( float DeltaSeconds );

	UFUNCTION()
	virtual void OnRep_ReplicationDetailActor();

	virtual class AFGReplicationDetailActor* GetOrCreateReplicationDetailActor();

	UFUNCTION()
	virtual void OnRep_CurrentPotential();

private:
	/** Calls Start/Stop Producing on client */
	UFUNCTION()
	virtual void OnRep_IsProducing();

	UFUNCTION()
	void OnPotentialInventoryItemRemoved( TSubclassOf< class UFGItemDescriptor > itemClass, int32 numRemoved );

	class AFGReplicationDetailActor_BuildableFactory* GetCastRepDetailsActor() const { return Cast<AFGReplicationDetailActor_BuildableFactory>( mReplicationDetailActor ); } // @todo: make this a static function instead

	//////////////////////////////////////////////////////////////////////////
	/// Push Model Replication Setters
	void SetIsProducing( uint8 isProducing );
	void SetHasPower( uint8 hasPower );
	void SetCurrentProductivity( uint8 productivity );

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

	/** Class to use for the power simulation on this factory, this is only used if the building has any FGPowerConnectionComponent attached. */
	UPROPERTY( EditDefaultsOnly, Category = "Power" ) //@todo Replicated
	TSubclassOf< class UFGPowerInfoComponent > mPowerInfoClass;

	/** Callback for when the production indicator state changes. Called locally on both server and client. */
	UPROPERTY( BlueprintAssignable )
	FProductionStatusChanged mOnProductionStatusChanged;

protected:
	friend class AFGReplicationDetailActor_BuildableFactory;

	/** Power simulation info */
	UPROPERTY( SaveGame, Replicated )
	class UFGPowerInfoComponent* mPowerInfo;

	/** So that you can listen for when power has changed */
	UPROPERTY(BlueprintAssignable)
	FBuildingStateChanged mOnHasPowerChanged;

	/** So that you can listen for when production has changed */
	UPROPERTY( BlueprintAssignable )
	FBuildingStateChanged mOnHasProductionChanged;

	/** So that you can listen for when standby is toggled. True == Standby is active False == Standby was disabled */
	UPROPERTY( BlueprintAssignable )
	FBuildingStateChanged mOnHasStandbyChanged;

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

	/** How many cycles back do we base the productivity on */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	int32 mNumCyclesForProductivity;

	/** These are a list of timestamps for the most recently completed production cycles, used to calculate productivity */
	TArray< float > mCompletedCycleTimeStamps;

	/** An estimation on when the current cycle will be done. If we didn't produce for a frame we add delta to this */
	float mCurrentProductionCycleETA;

	/** Keeps track if we produced this tick or not */
	bool mDidProduceThisTick;

	/** Set this to true if we want this building to be able to change the production rate potential with the "Slider of Potential" */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	bool mCanChangePotential;

	/** When ever a production cycle is completed we set the current potential to this value */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	float mPendingPotential;

	/** You can never set the potential to less than this when playing */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mMinPotential;
	
	/** You can never set the potential to more than this when playing */
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mMaxPotential;

	/** When the player adds another crystal in the inventory we unlock even more potential*/
	UPROPERTY( EditDefaultsOnly, Category = "Productivity" )
	float mMaxPotentialIncreasePerCrystal;

	/** Item stack size Enum to use as base for how much fluid a Liquid / Gas Item descriptor can be stored on an index in an inventory */
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	EStackSize mFluidStackSizeDefault;

	/** Scalar for multiplying the default Stack Size for Fluid Inventory Slots ( 1 is default. 2 == 2 * FluidStackSize )*/
	UPROPERTY( EditDefaultsOnly, Category = "Inventory" )
	int32 mFluidStackSizeMultiplier;

	/** The player is able to toggle if production should be paused or not */
	UPROPERTY( SaveGame, Replicated, Meta = (NoAutoJson = true) )
	bool mIsProductionPaused;

	UPROPERTY( Replicated, Transient, ReplicatedUsing = OnRep_ReplicationDetailActor )
	class AFGReplicationDetailActor* mReplicationDetailActor;

	/** Event for when ReplicationDetailActors are created. Will only be dispatched if this buildable inherits from the ReplicationDetailActorOwnerInterface. */
	UPROPERTY( BlueprintAssignable, Category = "Replication Detail Actor Owner Interface" )
	FOnReplicationDetailActorCreated OnReplicationDetailActorCreatedEvent;

private:
	/** The input we place a crystal in to unlock the potential */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mInventoryPotential;

	UPROPERTY()
	class UFGReplicationDetailInventoryComponent* mInventoryPotentialHandler;

	/** This is the current potential (overclock, overcharge) of this factory [0..N]
	* [FreiholtzK:Fri/4-12-2020]  encapsulated to make sure we catch changes of this value and can broadcast them
	*/
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_CurrentPotential, Meta = (NoAutoJson = true) )
	float mCurrentPotential;

	/** How often effect update should update */
	UPROPERTY( EditDefaultsOnly, Category = "Anim" )
	float mEffectUpdateInterval;

	/** Accumulator for the effect update interval */
	float mEffectUpdateAccumulator;

	/** Cached value of Fluid Resource Stack Size ( set in begin play from the default stack enum ) */
	int32 mCachedFluidStackSize;

	/** The cached production status, evaluated once every tick. */
	EProductionStatus mCachedProductionStatus;

	/** A replicated compressed version of the productivity */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	uint8 mCurrentProductivity;

	/** Are we producing? Do not set this manually, some delegates and other stuff might not get triggered then. */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_IsProducing, Meta = (NoAutoJson = true) )
	uint8 mIsProducing:1;

	/** if true, then blueprint has implemented CanProduce */
	uint8 mHasCanProduce:1;

	/** If building has power, for more details about the circuitry see mPowerInfo. */
	UPROPERTY( Replicated, Meta = (NoAutoJson = true) )
	uint8 mHasPower:1;

	/** Last frame's has power */
	uint8 mLastHasPower:1;

	/** Last frame's is producing */
	uint8 mLastIsProducing : 1;

	/** if true, then blueprint has implemented Factory_CollectInput */
	uint8 mHasFactory_CollectInput:1;

	/** if true, then the blueprint has implemented Factory_PullPipeInput */
	uint8 mHasFactory_PullPipeInput : 1;

	/** if true, then the blueprint has implemented Factory_PushPipeOutput */
	uint8 mHasFactory_PushPipeOutput : 1;

	/** if true, then blueprint has implemented OnHasPowerChanged */
	uint8 mHasOnHasPowerChanged :1;

	/** if true, then blueprint has implemented OnHasProducingChanged */
	uint8 mHasOnIsProducingChanged :1;

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

	/** Caching all skel meshes so that we can set tick optimizations later from significance manager */
	UPROPERTY()
	TArray< USkeletalMeshComponent* > mCachedSkeletalMeshes;
protected:
	/** Indicates if the factory should be handled by significance manager */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	uint8 mAddToSignificanceManager : 1;

	/** The range to keep the factory in significance */
	UPROPERTY( EditDefaultsOnly, Category = "Significance" )
	float mSignificanceRange;
};

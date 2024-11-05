// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Replication/FGConditionalPropertyReplicator.h"
#include "Replication/FGConditionalReplicationInterface.h"
#include "Components/ActorComponent.h"
#include "FGSaveInterface.h"
#include "FGPowerInfoComponent.generated.h"

UCLASS()
class FACTORYGAME_API UFGBatteryInfo : public UObject
{
	GENERATED_BODY()
public:
	FORCEINLINE void SetActive( bool isActive ) { mIsActive = isActive; }
	FORCEINLINE bool IsActive() const { return mIsActive; }
	FORCEINLINE float GetPowerStore() const { return mPowerStore; }
	FORCEINLINE void SetPowerStore( float powerStore ) { mPowerStore = powerStore; }
	FORCEINLINE float GetPowerInput() const { return mPowerInput; }
	
	FORCEINLINE float GetPowerStoreCapacity() const { return mPowerStoreCapacity; }
	FORCEINLINE float GetPowerInputCapacity() const { return mPowerInputCapacity; }

private:
	friend class UFGPowerInfoComponent;
	friend class UFGPowerCircuitGroup;

	bool mIsActive;

	float mPowerStoreCapacity;
	float mPowerInputCapacity;

	float mPowerStore;
	float mPowerInput;
};

/**
 * A power info is a component on buildings that lets them interact with the power circuit.
 *
 * The power info on a building must be registered with one of the building's power connections.
 * 
 * A building with a power info can for example:
 *   Request power from it.
 *   Produce power to it.
 *   See that status of the fuse.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPowerInfoComponent : public UActorComponent, public IFGSaveInterface, public IFGConditionalReplicationInterface
{
	GENERATED_BODY()
public:
	UFGPowerInfoComponent();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin IFGConditionalReplicationInterface
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;
	virtual bool IsPropertyRelevantForConnection(UNetConnection* netConnection, const FProperty* property) const override;
	// End IFGConditionalReplicationInterface

	/**
	 * @return The power circuit this is connected to; nullptr if not connected.
	 * @note This can be changed/removed at any time so do not save copies to it.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	class UFGPowerCircuit* GetPowerCircuit() const;

	/**
	 * @return true if the connected to a circuit.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	FORCEINLINE bool IsConnected() const { return mCircuitID != INDEX_NONE; }

	/**
	 * @return true if we have power; false if we do not have power.
	 * @note This is updated once per frame so if setting target consumption the result is available next frame.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	FORCEINLINE bool HasPower() const { return mHasPower; }

	/** @return true if the grid is overloaded and the fuse has been triggered; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	FORCEINLINE bool IsFuseTriggered() const { return mIsFuseTriggered; }

	/**
	 * Set the power we want from the circuit.
	 * This is only a request, use GetActualConsumption to see what is actually consumed.
	 * @note This call is asynchronous and the result is available next frame.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetTargetConsumption( float newConsumption );
	/** Get the target power consumption. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetTargetConsumption() const;
	
	/**
	 * Set the maximum power we might want from the circuit under normal conditions, i.e. no potential set.
	 * @note This is an informative value for the subsystem and is not used in any of the power calculations.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetMaximumTargetConsumption( float maxConsumption );
	
	/** Get the maximum target power consumption under normal conditions, i.e. no potential set. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetMaximumTargetConsumption() const;

	/**
	 * Get the power we actually got for this frame.
	 * @note This is updated once per frame when the power subsystem is ticked.
	 * @return The actual power consumed.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetActualConsumption() const;

	/**
	 * Set the power we always provide to the circuit. This can not be regulated.
	 * E.g. A wind turbine always generate power when there's wind.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetBaseProduction( float newProduction );
	/** Get the base power production. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetBaseProduction() const;

	/**
	 * Set the maximum dynamic power production we can provide to the circuit.
	 * Use GetRegulatedDynamicProduction to see the actual production needed.
	 * @note Asynchronous.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetDynamicProductionCapacity( float newProduction );
	/** Get the maximum dynamic power production. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetDynamicProductionCapacity() const;

	/**
	 * Get how much of the max output a dynamic producer needs to produce.
	 * This is in the range [0,1+] and if >1 the demand is greater than the available production, i.e. the circuit is overloaded.
	 * @return Dynamic demand factor.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetDynamicProductionDemandFactor() const;

	/** Get the dynamic power production we provide to the circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetRegulatedDynamicProduction() const;

	/** Set production boost factor. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetProductionBoostFactor( float newFactor );

	/** Get the production boost factor. [%] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetProductionBoostFactor() const;
	/** Get the actual production boost provided by this building. [MW] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	float GetActualProductionBoost() const;
	
	/**
	 * @param isFullBlast set to true if the generator should always produce at full capacity; to false if it should only produce on-demand
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerInfo" )
	void SetFullBlast( bool isFullBlast );
	/**
	 * @return true if the generator always produces at full capacity; false if it only produces on-demand
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerInfo" )
	bool IsFullBlast() const;

	/**
	 * @note Do not call this unless you know what you're doing.
	 * @param circuitID The new circuit id, INDEX_NONE if disconnected.
	 */
	void SetCircuitID( int32 circuitID );

	/**
	 * Create and attach a battery to this power-circuit node
	 */
	void InitializeBatteryInfo( float powerStoreCapacity, float powerInputCapacity );

	UFGBatteryInfo* GetBatteryInfo() { return mBatteryInfo; }

	/** Debug */
	void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

	/** Updates the relevancy owner for this item. This component will only replicate it's data when the relevancy owner allows it to */
	void SetReplicationRelevancyOwner( UObject* relevancyOwner );

protected:
	/** Updates simulation data on this component. Called from the power circuit ticking logic directly. */
	virtual void UpdateSimulationData( float dynamicProductionDemandFactor, float actualConsumption, bool isFuseTriggered, bool hasPower, float actualProductionBoost );

public:
	/** Delegate that will fire whenever mHasPower has changed */
	DECLARE_DELEGATE_OneParam( FOnHasPowerChanged, UFGPowerInfoComponent* )
    FOnHasPowerChanged OnHasPowerChanged;

protected:
	/** The owner of this component that dictates when it becomes relevant */
	UPROPERTY()
	TScriptInterface<IFGConditionalReplicationInterface> mReplicationRelevancyOwner;
	
	/** Property replicator for conditionally replicating details */
	UPROPERTY( Replicated, Transient, meta = ( FGPropertyReplicator ) )
	FFGConditionalPropertyReplicator mPropertyReplicator;
private:
	friend class UFGPowerCircuit;
	friend class UFGPowerCircuitGroup;

	void OnRelevancyOwnerInvalidatedRelevantPropertiesCache();
	
	/**
	 * The circuit we're connected to.
	 * @note - This ID may change at any time when changes occurs in the circuitry. Do not save copies of it!
	 */
	UPROPERTY( Replicated )
	int32 mCircuitID;

	/** Power to draw from the circuit. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mTargetConsumption;

	/** Maximum power consumption under normal conditions. */
	UPROPERTY( meta = ( FGReplicated ) )
	float mMaximumTargetConsumption;

	/** The actual power we got from the circuit (updated each frame). */
	UPROPERTY( meta = ( FGReplicated ) )
	float mActualConsumption;

	/** Power to always provide to the circuit. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mBaseProduction;

	/** Power to optionally provide to the circuit. */
	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	float mDynamicProductionCapacity;

	/** The demand for dynamic power (updated each frame). */
	UPROPERTY( meta = ( FGReplicated ) )
	float mDynamicProductionDemandFactor;

	/** How much is this producer boosting the power production. [%] */
	UPROPERTY( meta = ( FGReplicated ) )
	float mProductionBoostFactor;

	/** How much did we produce. [MW] */
	UPROPERTY( meta = ( FGReplicated ) );
	float mActualProductionBoost;

	UPROPERTY()
	UFGBatteryInfo* mBatteryInfo;

	/** Do we have enough of the requested power. Do not set this directly, use SetHasPower. */
	UPROPERTY( meta = ( FGReplicated ) )
	uint8 mHasPower:1;

	/** true if the circuit is overloaded and the fuse has been triggered. */
	UPROPERTY( meta = ( FGReplicated ) )
	uint8 mIsFuseTriggered:1;

	UPROPERTY( SaveGame, meta = ( FGReplicated ) )
	uint8 mIsFullBlast:1;
};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FGSaveInterface.h"
#include "FGPowerInfoComponent.generated.h"


/**
 * Default implementation for a powered building.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class UFGPowerInfoComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()

public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	/** If we should replicate detailed information, use this to optimize replication of inventories not actively used by client. */
	FORCEINLINE void SetReplicateDetails( bool replicateDetails ) { mReplicateDetails = replicateDetails; }

	/** Ctor */
	UFGPowerInfoComponent();

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/**
	 * @return The power circuit this is connected to; nullptr if not connected.
	 * @note This can be changed/removed at any time so do not save copies to it.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	class UFGPowerCircuit* GetPowerCircuit() const;

	/**
	 * @return true if the connected to a circuit.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	FORCEINLINE bool IsConnected() const { return mCircuitID != INDEX_NONE; }

	/**
	 * @return true if we have power; false if we do not have power.
	 * @note This is updated once per frame so if setting target consumption the result is available next frame.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool HasPower() const { return mHasPower; }

	/** @return true if the grid is overloaded and the fuse has been triggered; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsFuseTriggered() const { return mIsFuseTriggered; }

	/**
	 * Set the power we want from the circuit.
	 * This is only a request, use GetActualConsumption to see what is actually consumed.
	 * @note This call is asynchronous and the result is available next frame.
	 */
	UFUNCTION( BlueprintCallable, Category = "Power" )
	void SetTargetConsumption( float newConsumption );
	/** Get the target power consumption. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetTargetConsumption() const;

	/**
	 * Get the power we actually got for this frame.
	 * @note This is updated once per frame when the power subsystem is ticked.
	 * @return The actual power consumed.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetActualConsumption() const;

	/**
	 * Set the power we always provide to the circuit. This can not be regulated.
	 * E.g. A wind turbine always generate power when there's wind.
	 */
	UFUNCTION( BlueprintCallable, Category = "Power" )
	void SetBaseProduction( float newProduction );
	/** Get the base power production. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetBaseProduction() const;

	/**
	 * Set the maximum dynamic power production we can provide to the circuit.
	 * Use GetRegulatedDynamicProduction to see the actual production needed.
	 * @note Asynchronous.
	 */
	UFUNCTION( BlueprintCallable, Category = "Power" )
	void SetDynamicProductionCapacity( float newProduction );
	/** Get the maximum dynamic power production. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetDynamicProductionCapacity() const;

	/**
	 * Get how much of the max output a dynamic producer needs to produce.
	 * This is in the range [0,1+] and if >1 the demand is greater than the available production, i.e. the circuit is overloaded.
	 * @return Dynamic demand factor.
	 */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetDynamicProductionDemandFactor() const;

	/** Get the dynamic power production we provide to the circuit. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetRegulatedDynamicProduction() const;

	/**
	 * @note Do not call this unless you know what you're doing.
	 * @param circuitID The new circuit id, INDEX_NONE if disconnected.
	 */
	void SetCircuitID( int32 circuitID );

	/** Debug */
	void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

private:
	/** If we should replicate detailed information. */
	bool IsReplicatingDetails() const { return mReplicateDetails; }

private:
	friend class UFGPowerCircuit;

	/** If we should replicate detailed information, use this to optimize replication of power info not actively used by client. */
	bool mReplicateDetails;

	/**
	 * The circuit we're connected to.
	 * @note - This ID may change at any time when changes occurs in the circuitry. Do not save copies of it!
	 */
	UPROPERTY( Replicated )
	int32 mCircuitID;

	/** Power to draw from the circuit. */
	UPROPERTY( SaveGame, Replicated )
	float mTargetConsumption;

	/** The actual power we got from the circuit (updated each frame). */
	UPROPERTY( Replicated )
	float mActualConsumption;

	/** Power to always provide to the circuit. */
	UPROPERTY( SaveGame, Replicated )
	float mBaseProduction;

	/** Power to optionally provide to the circuit. */
	UPROPERTY( SaveGame, Replicated )
	float mDynamicProductionCapacity;

	/** The demand for dynamic power (updated each frame). */
	UPROPERTY( Replicated )
	float mDynamicProductionDemandFactor;

	/** Do we have enough of the requested power. */
	uint8 mHasPower:1;

	/** true if the circuit is overloaded and the fuse has been triggered. */
	UPROPERTY( Replicated )
	uint8 mIsFuseTriggered:1;
};

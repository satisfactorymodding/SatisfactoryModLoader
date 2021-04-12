// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCircuit.h"
#include "FGNetSerialization.h"
#include "FGPowerCircuit.generated.h"

/**
 * A point on the power curve.
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPowerGraphPoint
{
	GENERATED_BODY()
public:
	FPowerGraphPoint();
	bool NetSerialize( FArchive& ar, class UPackageMap* map, bool& out_success );

	/** Data for this point. */
	UPROPERTY( BlueprintReadOnly )
	float Consumed;

	UPROPERTY( BlueprintReadOnly )
	float Produced;

	UPROPERTY( BlueprintReadOnly )
	float ProductionCapacity;

	UPROPERTY( BlueprintReadOnly )
	float MaximumConsumption;

	UPROPERTY( BlueprintReadOnly )
	float BatteryPowerInput;
};

template<>
struct TStructOpsTypeTraits< FPowerGraphPoint > : public TStructOpsTypeTraitsBase2< FPowerGraphPoint >
{
	enum
	{
		WithNetSerializer = true
	};
};


/**
 * Stats for a power circuit, refreshed once every second. Implemented as a ring buffer, so that we don't have to re-replicate all the time
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FPowerCircuitStats
{
	GENERATED_BODY()
public:
	FPowerCircuitStats();
	bool NetSerialize( FArchive& ar, class UPackageMap* map, bool& out_success );

	/** Helper to make a new graph point. */
	FPowerGraphPoint& MakeAndAddGraphPoint();

	/** Helper to make a new graph point from current time */
	FORCEINLINE void MakeGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const;

	/** Get the last graph point in the stats */
	FORCEINLINE void GetLastGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const;

	/** Advances the graph and gets the next graph point we want to write to. */
	FPowerGraphPoint& AdvanceToNextGraphPoint();

	/** Get the number of points in our graph */
	FORCEINLINE int32 GetNumGraphPoints() const{ return Items.Num(); }

	/** Get item of index in our graph @return false if the index is invalid */
	FORCEINLINE bool GetGraphPointAtIndex( int32 idx, FPowerGraphPoint& out_graphPoint ) const;

	template< float FPowerGraphPoint::*Member >
	void GetPoints( TArray< float >& out_points, bool clampToZero = false, bool invert = false ) const;

public:
	/** The duration between each stat. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float StatIntervalTime;

	/** For how long do we keep the stats. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float StatHistoryTime;

	/** Last time we collected stats. */
	float LastStatTime;
	/** Last time the fuse was triggered. */
	float LastFuseTriggeredTime;

	/** How much power can be produced. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float PowerProductionCapacity;

	/** How much power is produced. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float PowerProduced;

	/** How much power is consumed. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float PowerConsumed;

	/** How much power can hypothetically be consumed at once. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float MaximumPowerConsumption;

	/** The sum of the power inputs to batteries. A negative value denotes power output. */
	UPROPERTY( BlueprintReadOnly, NotReplicated )
	float BatteryPowerInput;

	/** Freeze the stats until the next stat. */
	bool HasPinnedGraphPoint;
	FPowerGraphPoint PinnedGraphPoint;

private:
	/** All the points on the graph. */
	UPROPERTY()
	TArray< FPowerGraphPoint > Items;

	/** The index we count as the first index in our ring buffer */
	UPROPERTY()
	int8 FirstIndex;

	/** Maximum number of points in the graph. */
	int32 NumGraphPointsMax;
};

template<>
struct TStructOpsTypeTraits< FPowerCircuitStats > : public TStructOpsTypeTraitsBase2< FPowerCircuitStats >
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * Implementation of a power circuit.
 */
UCLASS()
class FACTORYGAME_API UFGPowerCircuit : public UFGCircuit
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void PreReplication( IRepChangedPropertyTracker& ChangedPropertyTracker ) override;

	UFGPowerCircuit();

	/** Resets the fuse. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerCircuit" )
	void ResetFuse();

	/** @return true if the fuse is triggered; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	bool IsFuseTriggered() { return mIsFuseTriggered; }

	/** Get the power production capacity of this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetPowerProductionCapacity() const { return mPowerProductionCapacity; }

	/** Get the stats for this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	void GetStats( FPowerCircuitStats& out_stats ) const { out_stats = mPowerStats; }

	/** Get the graph point from the index in our stats,  @return false if the index is invalid */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" ) // meta = ( DeprecatedFunction, DeprecationMessage = "Invoke server call on Remote Call Object instead." ) )
	static bool GetGraphPointAtIndex( const FPowerCircuitStats& stats, int32 idx, FPowerGraphPoint& out_item ){ return stats.GetGraphPointAtIndex( idx, out_item ); }

	/** Get how many graph points there is in our stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static int32 GetNumGraphPoint( const FPowerCircuitStats& stats ){ return stats.GetNumGraphPoints(); }

	/** Get consumed points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetConsumedPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::Consumed >( out_points ); }

	/** Get produced points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetProducedPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::Produced >( out_points ); }

	/** Get production-capacity points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetProductionCapacityPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::ProductionCapacity >( out_points ); }
	
	/** Get maximum-consumed points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetMaximumConsumptionPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::MaximumConsumption >( out_points ); }

	/** Get battery power input points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetBatteryPowerInputPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::BatteryPowerInput >( out_points, true ); }

	/** Get battery power output points from stats */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	static void GetBatteryPowerOutputPoints( const FPowerCircuitStats& stats, TArray< float >& out_points ) { stats.GetPoints< &FPowerGraphPoint::BatteryPowerInput >( out_points, true, true ); }

	/** @return true if there are any batteries connected to this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	bool HasBatteries() const { return mHasBatteries; }

	/** @return the combined power stored in the active batteries currently connected to this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetBatterySumPowerStore() const { return mBatterySumPowerStore; }

	/** @return the combined maximum power-store capacity of all the active batteries currently connected to this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetBatterySumPowerStoreCapacity() const { return mBatterySumPowerStoreCapacity; }

	/** @return the combined power store as percentage of the combined power-store capacity of all the active batteries connected to this circuit. In the range [0.0, 1.0]. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetBatterySumPowerStorePercent() const { return mBatterySumPowerStore / mBatterySumPowerStoreCapacity; }
	
	/** @return the combined power input to all the batteries connected to this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetBatterySumPowerInput() const { return FMath::Max( mBatterySumPowerInput, 0.0f ); }

	/** @return the combined power output from all the batteries connected to this circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetBatterySumPowerOutput() const { return FMath::Max( -mBatterySumPowerInput, 0.0f ); }

	/** @returns the time in seconds to when all batteries are empty if GetBatterySumPowerOutput() returns > 0, otherwise returns 0. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetTimeToBatteriesEmpty() const { return mBatterySumPowerInput < 0.0f ? mTimeToBatteriesEmpty : 0.0f; }

	/** @returns the time in seconds to when all batteries are full if GetBatterySumPowerInput() returns > 0, otherwise returns 0. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	float GetTimeToBatteriesFull() const { return mBatterySumPowerInput > 0.0f ? mTimeToBatteriesFull : 0.0f; }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent ) override;

	bool IsNoPowerCheatOn() const;
	
	/** @returns true if the power production is this circuit is above zero, false otherwise. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerCircuit" )
	bool HasPower() const { return mHasPower; }

	/** Event that will fire whenever mHasPower has changed */
	DECLARE_EVENT_OneParam( UFGPowerCircuit, FOnHasPowerChanged, bool )
	FOnHasPowerChanged OnHasPowerChanged;

protected:
	// Begin UFGCircuit interface
	virtual void OnCircuitChanged() override;
	virtual bool IsTrivial() const override;
	virtual void OnRemoved() override;
	// End UFGCircuit interface

private:
	/** Update the power stats. */
	void UpdateStatsGeneral();
	void UpdateStatsGraph();
	/** Pin the current stats until the next interval. */
	void PinStatsGraphPoint();
	/** Let the stats now the fuse got triggered. */
	void StatFuseTriggered();

	/** @return a newly created circuit of this class, preserving some of the state of this circuit */
	virtual UFGCircuit* SplitCircuit( AFGCircuitSubsystem* subsystem ) const override;

	virtual UFGCircuitGroup* CreateCircuitGroup( AFGCircuitSubsystem* subsystem ) const override;
	
	void SetHasPower( bool hasPower );

private:
	/** All power infos in this circuit, in the order they should be updated. */
	TArray< class UFGPowerInfoComponent* > mPowerInfos;

	/** Total amount of power that can be produced in the circuit. Used for stats. */
	UPROPERTY()
	float mPowerProductionCapacity;

	/** Total amount of power produced in the circuit. */
	UPROPERTY()
	float mPowerProduced;

	/** Total amount of power consumed in the circuit. */
	UPROPERTY()
	float mPowerConsumed;

	/** The maximum power that can be demanded by all connected infos. */
	UPROPERTY( Replicated )
	float mMaximumPowerConsumption;
	
	/** true if the power production is this circuit is above zero, false otherwise. */
	UPROPERTY( Replicated )
	bool mHasPower;

	/** true if there are any batteries connected to this circuit. */
	UPROPERTY( Replicated )
	bool mHasBatteries;

	/** The combined power stored in the batteries currently connected to this circuit. */
	UPROPERTY( Replicated )
	float mBatterySumPowerStore;

	/** The combined maximum power-store capacity of all the batteries currently connected to this circuit. */
	UPROPERTY( Replicated )
	float mBatterySumPowerStoreCapacity;

	/** The combined power input to all the batteries connected to this circuit. Negative values denote power output. */
	UPROPERTY( Replicated )
	float mBatterySumPowerInput;

	/** The time in seconds to when all batteries are empty on current power output. Recalculated when mBatterySumPowerInput < 0. */
	UPROPERTY( Replicated )
	float mTimeToBatteriesEmpty;

	/** The time in seconds to when all batteries are full on current power input. Recalculated when mBatterySumPowerInput > 0. */
	UPROPERTY( Replicated )
	float mTimeToBatteriesFull;

	//@optimize This should preferably not be replicated always.
	/** true if the fuse was triggered. */
	UPROPERTY( Replicated )
	bool mIsFuseTriggered;

	/** The power consumption/production over time. Used for feedback. */
	UPROPERTY( Replicated )
	FPowerCircuitStats mPowerStats;

	/** The sum battery power store at the time when the latest non-stop depletion of batteries started. 0.0f when uninitialized. */
	UPROPERTY()
	float mPowerStoreAtBatteryDepletionStart;

	/** The time that has passed since the last critical battery depletion warning. */
	UPROPERTY()
	float mTimeSinceLastWarning;

	friend class UFGPowerCircuitGroup;
};

UCLASS()
class FACTORYGAME_API UFGPowerCircuitGroup : public UFGCircuitGroup
{
	GENERATED_BODY()
public:

	void ResetFuses();
	void RegisterPrioritySwitch( class AFGBuildablePriorityPowerSwitch* circuitSwitch );

private:
	// Begin UFGCircuitGroup interface
	virtual void Reset() override { mCircuits.Reset(); }
	virtual void PushCircuit( UFGCircuit* circuit ) override;
	virtual bool PreTickCircuitGroup( float dt, bool hasAuthority ) override;
	virtual void TickCircuitGroup( float dt, bool hasAuthority ) override;
	virtual void VisitCircuitBridge( class AFGBuildableCircuitBridge* circuitBridge ) override;
	// End UFGCircuitGroup interface

	/**
	* Ticks a group of power circuits, making calculations as to power produced, power consumed, and if the fuse is blown.
	*/
	void TickPowerCircuitGroup( float deltaTime, bool hasAuthority, bool isNoPowerCheatOn );

	/** Specifically ticks the batteries connected to the power-circuit group, calculating the power input, output and charge increment to the batteries. */
	float TickBatteries( float deltaTime, const float netPowerProduction, bool isFuseTriggered );

	/** If a valid-numbered priority switch that is turned on is found, it will be turned off. @returns true if such a switch was found, false otherwise. */
	bool TryTurnOffPrioritySwitch();

	/** Called when the fuse is set/reset in the circuit. */
	void OnFuseSet();
	void OnFuseReset();

private:
	UPROPERTY()
	TArray< UFGPowerCircuit* > mCircuits;

	TSet< TWeakObjectPtr< class AFGBuildablePriorityPowerSwitch > > mPrioritySwitches;
};

void FPowerCircuitStats::MakeGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const
{
	out_newGraphPoint.Consumed = PowerConsumed;
	out_newGraphPoint.Produced = PowerProduced;
	out_newGraphPoint.ProductionCapacity = PowerProductionCapacity;
	out_newGraphPoint.MaximumConsumption = MaximumPowerConsumption;
	out_newGraphPoint.BatteryPowerInput = BatteryPowerInput;
}

bool FPowerCircuitStats::GetGraphPointAtIndex( int32 idx, FPowerGraphPoint& out_graphPoint ) const
{
	if( idx < 0 || idx >= Items.Num() )
	{
		out_graphPoint.Consumed = 0.0f;
		out_graphPoint.Produced = 0.0f;
		out_graphPoint.ProductionCapacity = 0.0f;
		out_graphPoint.MaximumConsumption = 0.0f;
		out_graphPoint.BatteryPowerInput = 0.0f;

		return false;
	}

	const int32 nextIdx = ( FirstIndex + 1 + idx ) % NumGraphPointsMax;

	out_graphPoint = Items[ nextIdx ];

	return true;
}

template< float FPowerGraphPoint::*Member >
void FPowerCircuitStats::GetPoints( TArray< float >& out_points, bool clampToZero /*= false*/, bool invert /*= false */ ) const
{
	const int32 count = Items.Num();
	out_points.SetNum( count );
	for( int32 i = 0; i < count; ++i )
	{
		const int32 nextIdx = ( FirstIndex + 1 + i ) % count;
		float value = Items[ nextIdx ].*Member;
		if( invert && value != 0.0f )
		{
			value = -value;
		}
		if( clampToZero && value < 0.0f )
		{
			value = 0.0f;
		}
		out_points[ i ] = value;
	}
}

void FPowerCircuitStats::GetLastGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const
{
	GetGraphPointAtIndex( NumGraphPointsMax - 1, out_newGraphPoint );
}

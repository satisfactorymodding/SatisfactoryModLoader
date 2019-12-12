// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/CoreNet.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGCircuit.h"
#include "FGNetSerialization.h"
#include "FGPowerCircuit.generated.h"

/**
 * A point on the power curve.
 */
USTRUCT( BlueprintType )
struct FPowerGraphPoint
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
struct FPowerCircuitStats
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
	UFUNCTION( BlueprintCallable, Category = "Power" )
	void ResetFuse();

	/** @return true if the fuse is triggered; false otherwise. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	bool IsFuseTriggered() { return mIsFuseTriggered; }

	/** Get the stats for this circuit. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	void GetStats( FPowerCircuitStats& out_stats ) const { out_stats = mPowerStats; }

	/** Get the graph point from the index in our stats,  @return false if the index is invalid */
	UFUNCTION( BlueprintPure, Category = "Power" )
	static bool GetGraphPointAtIndex( const FPowerCircuitStats& stats, int32 idx, FPowerGraphPoint& out_item ){ return stats.GetGraphPointAtIndex( idx, out_item ); }

	/** Get how many graph points there is in our stats */
	UFUNCTION( BlueprintPure, Category = "Power" )
	static int32 GetNumGraphPoint( const FPowerCircuitStats& stats ){ return stats.GetNumGraphPoints(); }

	/** Debug */
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos, float indent ) override;

protected:
	// Begin UFGCircuit interface
	virtual void TickCircuit( float dt ) override;
	virtual void OnCircuitChanged() override;
	// End UFGCircuit interface

private:
	/** Update the power stats. */
	void UpdateStatsGeneral();
	void UpdateStatsGraph();
	/** Pin the current stats until the next interval. */
	void PinStatsGraphPoint();
	/** Let the stats now the fuse got triggered. */
	void StatFuseTriggered();

	/** Called when the fuse is set/reset in the circuit. */
	void OnFuseSet();
	void OnFuseReset();

private:
	/** All power infos in this circuit, in the order they should be updated. */
	TArray< class UFGPowerInfoComponent* > mPowerInfos;

	/** Total amount of energy that can be produced in the circuit. Used for stats. */
	UPROPERTY()
	float mPowerProductionCapacity;

	/** Total amount of energy produced in the circuit. */
	UPROPERTY()
	float mPowerProduced;

	/** Total amount of energy consumed in the circuit. */
	UPROPERTY()
	float mPowerConsumed;

	//@optimize This should preferably not be replicated always.
	/** true if the fuse was triggered. */
	UPROPERTY( Replicated )
	bool mIsFuseTriggered;

	/** The power consumption/production over time. Used for feedback. */
	UPROPERTY( Replicated )
	FPowerCircuitStats mPowerStats;
};

void FPowerCircuitStats::MakeGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const
{
	out_newGraphPoint.Consumed = PowerConsumed;
	out_newGraphPoint.Produced = PowerProduced;
	out_newGraphPoint.ProductionCapacity = PowerProductionCapacity;
}

bool FPowerCircuitStats::GetGraphPointAtIndex( int32 idx, FPowerGraphPoint& out_graphPoint ) const
{
	if( idx < 0 || idx >= Items.Num() )
	{
		out_graphPoint.Consumed = 0;
		out_graphPoint.Produced = 0;
		out_graphPoint.ProductionCapacity = 0;

		return false;
	}

	const int32 nextIdx = ( FirstIndex + 1 + idx ) % NumGraphPointsMax;

	out_graphPoint = Items[ nextIdx ];

	return true;
}

void FPowerCircuitStats::GetLastGraphPoint( FPowerGraphPoint& out_newGraphPoint ) const
{
	GetGraphPointAtIndex( NumGraphPointsMax - 1, out_newGraphPoint );
}

// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"

#include "Buildables/FGBuildable.h"
#include "FGVehicle.h"
#include "ItemAmount.h"

struct FACTORYGAME_API FFactoryStats
{
public:
	/**
	 * All length measurements are in cm.
	 * All area measurements are in cm2.
	 */

	int32 NumBuildables;
	TMap< TSubclassOf< AFGBuildable >, int32 > NumBuildablesByClass;

	int32 NumVehicles;
	TMap< TSubclassOf< AFGVehicle >, int32 > NumVehiclesByClass;

	float TotalConveyorLength = 0.f;
	float TotalConveyorLiftHeight = 0.f;
	float TotalPipelineLength = 0.f;
	float TotalRailroadTrackLength = 0.f;
	float TotalRoadLength = 0.f;
	float TotalWireLength = 0.f;
	float TotalHyperTubeLength = 0.f;

	TArray< FItemAmount > SpentOnBuilding;
	TArray< FItemAmount > StockInventory;

	int32 NumRemovedFoliageInstances = 0;
	//int32 NumCircuits;
	//int32 NumTrains;
	//int32 NumSelfDrivingTrucks;

public:
	FORCEINLINE ~FFactoryStats() = default;
};

/**
 * Functions for gathering stats about the factory.
 * This does not collect any stats, it just summarizes stats from other systems.
 */
struct FACTORYGAME_API FFactoryStatHelpers
{
	static void GetFactoryStats( class UWorld* world, FFactoryStats& out_stats );

public:
	FORCEINLINE ~FFactoryStatHelpers() = default;
};

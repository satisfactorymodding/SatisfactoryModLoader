// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "SubclassOf.h"

#include "Buildables/FGBuildable.h"
#include "FGVehicle.h"
#include "ItemAmount.h"

struct FFactoryStats
{
public:
	FFactoryStats();

public:
	/**
	 * All length measurements are in cm.
	 * All area measurements are in cm2.
	 */

	int32 NumBuildables;
	TMap< TSubclassOf< AFGBuildable >, int32 > NumBuildablesByClass;

	int32 NumVehicles;
	TMap< TSubclassOf< AFGVehicle >, int32 > NumVehiclesByClass;

	float TotalConveyorLength;
	float TotalRailroadTrackLength;
	float TotalRoadLength;
	float TotalWireLength;

	TArray< FItemAmount > SpentOnBuilding;
	TArray< FItemAmount > StockInventory;

	int32 NumRemovedFoliageInstances;
	//int32 NumCircuits;
	//int32 NumTrains;
	//int32 NumSelfDrivingTrucks;
};

/**
 * Functions for gathering stats about the factory.
 * This does not collect any stats, it just summarizes stats from other systems.
 */
struct FFactoryStatHelpers
{
	static void GetFactoryStats( class UWorld* world, FFactoryStats& out_stats );
};

// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

/**
 * Custom serialization version for save games.
 * If a custom version is no longer supported and has been cleaned up, add the prefix DROPPED_.
 */
struct FSaveCustomVersion
{
	enum Type
	{
		/** 2016/12/20 - Initial version of the save system, saves some character stuff like inventory and health */
		BeforeCustomVersionWasAdded = 0,

		/** 2017/01/23 - Now storing transform for all saved actors */
		DROPPED_StoreTransform,

		/** 2017/01/25 - Change object header, stops storing map name in savefile. Breaks all backward compability */
		DROPPED_ChangeObjectHeader,

		/** 2017/01/30 - Changed serialization of property names to strings instead of ints. Breaks all backward compability  */
		DROPPED_PropertyTagsAsStrings,

		/** 2017/01/31 - Now store the body state of all vehicles */
		DROPPED_StoreVehiclesBodyState,

		/** 2017/02/13 - Store if a actor was stored in the level in the actor TOC */
		DROPPED_ActorPlacedInLevelSaved,

		/** 2017/05/02 - Removed outer from save in actor header, now it's saved as a part of the actors property set */
		DROPPED_MovedActorOuter,

		/** 2017/05/23 - Rewrote power connections to use actor components. */
		DROPPED_PowerConnectionComponents,

		// 2017-10-09: Serialize train timetable
		DROPPED_SerializeTrainTimetable,

		// 2017-10-27: FactoryConnection transform converted from World to local
		DROPPED_FactoryConnectionWorldToLocal,

		// 2017-11-03: Circuits are now objects and not structs.
		DROPPED_CircuitObjects,

		// 2018-02-12: DockingStations now only have one inventory
		DROPPED_DockingStationSingleInventory,

		// 2018-03-06: Saving build shortcuts
		SavingBuildShortcuts,

		// 2018-04-05 Game Phase manager has been added and functionality has been moved from GameState.
		DROPPED_GamePhaseManagerAdded,

		// 2018-10-25 No longer save relative transforms for UFGConnectionComponent.
		RemovedRelativeTransformsFromConnectionComponents,

		// 2018-11-19 OnlineSubsystemMCP - Restore a lost pawn since we didn't have peoples EpicID
		MCP_RestoreLostPawn,

		// 2018-11-19 Wires no longer save locations, they span between connection components instead
		WireSpanFromConnnectionComponents,

		// 2019-01-30 Renamed SaveSessionId
		RenamedSaveSessionId,

		// 2019-06-20 GeoThermal generators didn't save resource nodes prior to this which results with issues when being dismantled
		ChangedGeoThermalGeneratorSaved,

		// 2019-06-24 NewRailroadSerialization to overwrite old railroad data
		OverwriteOldRailroadData,

		// 2019-07-24 Due to a bug in the network optimizations the legs data where trashed, reseting the legs to zero is the best option.
		ResetFactoryLegs,

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};

	// The GUID for this custom version number
	const static FGuid GUID;

	const static Type MinSupportedVersion;

private:
	FSaveCustomVersion() {}
};

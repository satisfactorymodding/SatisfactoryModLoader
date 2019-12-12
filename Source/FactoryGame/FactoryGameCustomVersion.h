#pragma once
#include "CoreTypes.h"
#include "Misc/Guid.h"

// Custom serialization version for changes made in Dev-Framework stream
struct FFactoryGameCustomVersion
{
	enum Type
	{
		// Before any version changes were made
		BeforeCustomVersionWasAdded = 0,

		// 2017-06-02: Moved mNumItems and mPickupClass into mPickupItems in FGItemPickup
		ItemPickupGotInventoryStack,

		// 2017-06-17: Added persistant serialization to inventory items
		InventoryItemGotPersistantSeralization,

		// 2017-08-23: Moved mPreviewDistance from Vehicle and Buildable to FGItemDescriptor
		MovedPreviewDistanceToDescriptor,

		// 2017-08-29: Moved mPreviewDistance into FItemView
		MovedPreviewDistanceToItemView,

		// 2017-09-08: Moved mBuildCategory from FGBuildingDescriptor to new base FGBuildDescriptor
		MovedBuildCategory,

		// 2017-11-09: In FGSchematic renamed mTechOnionRingIndex to mTechTier
		RenamedTechOnionRingIndexToTechTier,

		// 2017-11-14: Removed alternative costs that are randomized.
		RemovedRandomizedSchematicCosts,

		// 2017-12-12: Renamed ArmsAnimClass in equipment
		RenamedArmsAnimClass,

		// 2018-02-23: FItemView changed FocalZOffset to FocalOffset
		ChangedItemViewFocus,

		// 2018-09-17: Added support for large icons
		AddedLargeIcons,

		// 2019-04-08: Changed ExcludedInBuild to IncludedInBuild with research recipes
		CookResearchRecipes,

		// 2019-04-24: Changed so that fuel classes default values are separated from what's replicated to clients
		ChangedFuelClassesStorage,

		// -----<new versions can be added above this line>-------------------------------------------------
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1
	};

	// The GUID for this custom version number
	const static FGuid GUID;

private:
	FFactoryGameCustomVersion() {}
};

#pragma once
#include "UObject/Class.h"

static const FName INCLUDE_IN_BUILD_ASSET_TAG( TEXT( "mIncludeInBuilds" ) );
static const FName TECH_TIER_ASSET_TAG( TEXT( "mTechTier" ) );

// Where this schematic should be included. Cooker strips away builds that's marked for different build types
UENUM( BlueprintType )
enum class EIncludeInBuilds : uint8
{
	IIB_Never			UMETA( DisplayName = "Never", ToolTip="The schematic will never show up anywhere" ),
	IIB_Development		UMETA( DisplayName = "Development", ToolTip="The schematic will show up in standalone and PIE" ),
	IIB_PrivateBuilds	UMETA( DisplayName = "PrivateBuilds", ToolTip="The schematic will show up in builds marked as private (ie, local builds, and not builds sent to staging/main)" ),
	IIB_PublicBuilds	UMETA( DisplayName = "PublicBuilds", ToolTip="The schematic will always be included" )
};

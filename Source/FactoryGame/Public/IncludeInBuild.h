// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

static const FName INCLUDE_IN_BUILD_ASSET_TAG( TEXT( "mIncludeInBuilds" ) );
static const FName TECH_TIER_ASSET_TAG( TEXT( "mTechTier" ) );

// Used to determine when something should be included. Used for schematics, research and options for example. When used with cooker it strips away builds that's marked for different build types
UENUM( BlueprintType )
enum class EIncludeInBuilds : uint8
{
	IIB_Never			UMETA( DisplayName = "Never", ToolTip="Will never show up anywhere" ),
	IIB_Development		UMETA( DisplayName = "Development", ToolTip="Will show up in standalone and PIE" ),
	IIB_PrivateBuilds	UMETA( DisplayName = "PrivateBuilds", ToolTip="Will show up in standalone, PIE and builds marked as private (ie, local builds, and not builds sent to staging/main)" ),
	IIB_PublicBuilds	UMETA( DisplayName = "PublicBuilds", ToolTip="Will always be included" )
};

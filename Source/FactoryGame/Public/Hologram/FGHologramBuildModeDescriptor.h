// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGBuildGunModeDescriptor.h"
#include "FGHologramBuildModeDescriptor.generated.h"

/**
 * Used to define a Build Mode for holograms. Which changes how the hologram behaves.
 */
UCLASS( Blueprintable, Abstract,HideCategories=(Icon, Preview),meta=(AutoJSON=true) )
class FACTORYGAME_API UFGHologramBuildModeDescriptor : public UFGBuildGunModeDescriptor
{
	GENERATED_BODY()
};

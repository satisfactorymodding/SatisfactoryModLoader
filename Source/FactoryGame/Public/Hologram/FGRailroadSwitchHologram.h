// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGRailroadHologram.h"
#include "FGRailroadSwitchHologram.generated.h"

/**
 * Hologram for railroad switch controls.
 */
UCLASS()
class FACTORYGAME_API AFGRailroadSwitchHologram : public AFGRailroadHologram
{
	GENERATED_BODY()

	//@todotrains These are built implicitly, use this or remove it when making a composite hologram for switches/tracks.
};

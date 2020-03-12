// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "Buildables/FGBuildable.h"
#include "FGBuildableFactory.h"
#include "FGBuildableRailroadSignal.generated.h"

/**
 * A signal for the railroad, these are placed on connection points and separate access to tracks by block signaling.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRailroadSignal : public AFGBuildable
{
	GENERATED_BODY()
public:
	//@todo Implement

public:
	FORCEINLINE ~AFGBuildableRailroadSignal() = default;
};

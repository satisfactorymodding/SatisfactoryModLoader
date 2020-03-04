// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableFoundation.h"
#include "FGBuildableRamp.generated.h"

/**
 * Base class for all kinds of ramps.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableRamp : public AFGBuildableFoundation
{
	GENERATED_BODY()
public:
	
	//@todo You should not be able to snap on top of this, but on all other sides.

public:
	FORCEINLINE ~AFGBuildableRamp() = default;
};

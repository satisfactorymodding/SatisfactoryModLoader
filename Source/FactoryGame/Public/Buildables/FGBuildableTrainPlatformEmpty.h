// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableTrainPlatform.h"
#include "Buildables/FGBuildableFactory.h"
#include "FGBuildableFactory.h"
#include "FGBuildableTrainPlatformEmpty.generated.h"

/**
 * Its an empty platform, no logic, just visuals.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableTrainPlatformEmpty : public AFGBuildableTrainPlatform
{
	GENERATED_BODY()

public:
	FORCEINLINE ~AFGBuildableTrainPlatformEmpty() = default;
};

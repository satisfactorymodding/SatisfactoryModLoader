// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableFloor.generated.h"

/**
 * DEPRECATED - We only want foundations for now.
 * A floor, must be placed on a foundation.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFloor : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableFloor();

public:
	/** Size of the floor, width and depth. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mSize;
};

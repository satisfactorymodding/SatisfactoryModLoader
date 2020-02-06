// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableWalkway.generated.h"

/**
 * Base class for walkways.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableWalkway : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
public:
	AFGBuildableWalkway();

public:
	/** Size of the walkway (size of one side of the square part). */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Walkway" )
	float mSize;

	/** Height of this walkway if ramp, assumes -x to be lower and +x to be higher. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Walkway" )
	float mElevation;

	/** Disable snapping on specific sides. */
	UPROPERTY( EditDefaultsOnly, Category = "Walkway" )
	FFoundationSideSelectionFlags mDisableSnapOn;
};

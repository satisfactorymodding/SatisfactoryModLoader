// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGBuildableFactoryBuilding.h"
#include "FGBuildableFoundation.generated.h"

/**
 * A foundation to build your factory walls and floors on.
 */
UCLASS(Abstract)
class FACTORYGAME_API AFGBuildableFoundation : public AFGBuildableFactoryBuilding
{
	GENERATED_BODY()
protected:
	AFGBuildableFoundation();

public:
	/** Size of the foundation (size of one side of the square). */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mSize;

	/** Height of the foundation. Origo is assumed to be half way between. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Foundation" )
	float mHeight;

	/** Disable snapping on specific sides. */
	UPROPERTY( EditDefaultsOnly, Category = "Foundation" )
	FFoundationSideSelectionFlags mDisableSnapOn;
};

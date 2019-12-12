// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFactoryBuildingHologram.h"
#include "FGWalkwayHologram.generated.h"

/**
 * Hologram for walkways.
 */
UCLASS()
class FACTORYGAME_API AFGWalkwayHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGWalkwayHologram();

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	virtual void BeginPlay() override;

private:
	float mSize;
	float mElevation;
	FFoundationSideSelectionFlags mDisableSnapOn;
};

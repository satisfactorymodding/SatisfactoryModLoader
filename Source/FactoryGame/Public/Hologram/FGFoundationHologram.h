// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGFactoryBuildingHologram.h"
#include "FGFoundationHologram.generated.h"

/**
 * Base hologram for foundation type buildables.
 */
UCLASS()
class FACTORYGAME_API AFGFoundationHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGFoundationHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void ConfigureSnappedBuilding( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidFloor() override;
	// End AFGBuildableHologram interface

protected:
	/** Size of the foundation, from the default buildable. */
	float mSize;

	/** Height of the foundation, from the default buildable. */
	float mHeight;

	/** Disable snapping on specific sides. */
	FFoundationSideSelectionFlags mDisableSnapOn;
};

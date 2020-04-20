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
	bool CanSnapVertically( class AFGBuildableFoundation* toFoundation, float dirZ ) const;

protected:
	/** Defaults from the default buildable. */
	float mSize;
	float mHeight;
	float mElevation;
	FFoundationSideSelectionFlags mDisableSnapOn;

	/** Ratios for the snapping zones, how much of the wall to hit for snap to either direction. */
	float mSnapVerticalHitZoneRatio = 0.25f;
	float mSnapCenterHitZoneRatio = 0.33f; // This ratio is measured from the center.

public:
	FORCEINLINE ~AFGFoundationHologram() = default;
};

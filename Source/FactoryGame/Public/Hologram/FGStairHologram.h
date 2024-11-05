// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FGFoundationHologram.h"
#include "FGStairHologram.generated.h"

/**
 * Hologram for stairs.
 */
UCLASS()
class FACTORYGAME_API AFGStairHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGStairHologram();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FVector& hologramLocationOffset ) const override;
	// End AFGBuildableHologram Interface

protected:
	// Stair direction enum, from default buildable.
	uint8 mStairDirection;

	// Height of the staircase, from default buildable.
	float mHeight;

	// Size of the staircase, from default buildable.
	float mSize;
};

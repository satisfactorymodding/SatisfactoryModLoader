// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFoundationHologram.h"
#include "FGStairHologram.generated.h"

/**
 * Hologram for stairs.
 */
UCLASS()
class FACTORYGAME_API AFGStairHologram : public AFGFoundationHologram
{
	GENERATED_BODY()
public:
	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

public:
	FORCEINLINE ~AFGStairHologram() = default;
};

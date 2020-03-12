// Copyright 2017 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGPipeReservoirHologram.generated.h"

/**
 * Hologram for stackable pipe reservoirs
 */
UCLASS()
class FACTORYGAME_API AFGPipeReservoirHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGPipeReservoirHologram();
	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

private:
	FORCEINLINE bool CanStack() const { return mStackingHeight > KINDA_SMALL_NUMBER; }

private:
	float mStackingHeight;

public:
	FORCEINLINE ~AFGPipeReservoirHologram() = default;
};

// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGStackableStorageHologram.generated.h"

/**
 * Hologram for stackable storage boxes.
 */
UCLASS()
class FACTORYGAME_API AFGStackableStorageHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
public:
	AFGStackableStorageHologram();
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
};

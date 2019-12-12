// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGFactoryBuildingHologram.h"
#include "FGWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGWallHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGWallHologram();

	/** Begin */
	virtual void BeginPlay() override;

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

private:
	/** Width of the wall, from the default buildable. */
	float mWidth;

	/** Height of the wall, from the default buildable. */
	float mHeight;
};

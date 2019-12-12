// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGWallHologram.h"
#include "FGPoweredWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPoweredWallHologram : public AFGWallHologram
{
	GENERATED_BODY()
public:	
	// Begin AFGBuildableHologram interface
	virtual void ConfigureSnappedPower( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram interface
};

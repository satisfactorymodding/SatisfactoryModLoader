// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGResourceExtractorHologram.h"
#include "FGGeoThermalGeneratorHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGGeoThermalGeneratorHologram : public AFGResourceExtractorHologram
{
	GENERATED_BODY()
protected:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

public:
	FORCEINLINE ~AFGGeoThermalGeneratorHologram() = default;
};

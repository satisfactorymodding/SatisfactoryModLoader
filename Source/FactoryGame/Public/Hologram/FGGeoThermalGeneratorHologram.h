// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Hologram/FGResourceExtractorHologram.h"
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

	// Begin AFGResourceExtractorHologram Interface
	virtual bool CanOccupyResource( const TScriptInterface< class IFGExtractableResourceInterface >& resource ) const override;
	// End AFGResourceExtractorHologram Interface
};

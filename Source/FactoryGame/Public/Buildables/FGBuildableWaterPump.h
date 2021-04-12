// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableResourceExtractor.h"
#include "FGBuildableWaterPump.generated.h"

/**
 * 
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableWaterPump : public AFGBuildableResourceExtractor
{
	GENERATED_BODY()

public:
	/** Ctor */
	AFGBuildableWaterPump();

protected:	
	// Begin AFGBuildableResourceExtractorBase Interface
	virtual AActor* TryFindMissingResource() override;
	// End AFGBuildableResourceExtractorBase Interface

protected:
	friend class AFGWaterPumpHologram;
	
	/** (For Hologram) Minimum depth to collision this extractor requires to be placed ( tex. Water Pumps need to be at least X distance above floor ) */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	float mMinimumDepthForPlacement;

	/** Offset from hologram origin to begin and end traces When performing minimum depth checks ( if enabled for this buildable ) during placement */
	UPROPERTY( EditDefaultsOnly, Category = "Extraction" )
	FVector mDepthTraceOriginOffset;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableResourceExtractor.h"
#include "Resources/FGResourceNodeFrackingSatellite.h"
#include "FGBuildableFrackingExtractor.generated.h"

/**
 * Resource extractor that can only extract resources from an AFGResourceNodeFrackingSatellite node.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableFrackingExtractor : public AFGBuildableResourceExtractor
{
	GENERATED_BODY()

public:
	//~ Begin AFGBuildableFactory interface
	virtual bool Factory_HasPower() const override;
	virtual bool CanProduce_Implementation() const override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_ProductionCycleCompleted( float overProductionRate );
	//~ End AFGBuildableFactory interface

	/** Invoked when the resource node that this extractor is extracting from has had a state change */
	UFUNCTION( BlueprintImplementableEvent, Category="Fracking" )
	void OnNodeStateChanged( EFrackingSatelliteState state );

	/** Called when the resource node that this extractor is extracting from has had a state change, native handler */
	void OnNodeStateChanged_Native( EFrackingSatelliteState state );

protected:
	// Begin AFGBuildableResourceExtractorBase interface
	virtual void OnExtractableResourceSet() override;
	// End AFGBuildableResourceExtractorBase interface

private:
	void CalculatePendingPotential();

private:
	TWeakObjectPtr< AFGResourceNodeFrackingSatellite > mSatelliteNode;

	bool mIsPotentialChanged = false;
};

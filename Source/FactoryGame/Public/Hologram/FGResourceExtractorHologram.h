// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Resources/FGResourceDescriptor.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGResourceExtractorHologram.generated.h"

/**
 * Hologram for buildings that can only be placed (snapped) on resource nodes.
 */
UCLASS()
class FACTORYGAME_API AFGResourceExtractorHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	AFGResourceExtractorHologram();
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool TryUpgrade( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual AActor* GetUpgradedActor() const override;
	// End AFGHologram Interface

protected:
	// Begin AFGHologram Interface
	virtual void CheckValidPlacement() override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

	/**
	 * Helper to check if there's resources available for IsValidPlacement.
	 */
	void CheckResourcesAvailable();

	virtual void TrySnapToExtractableResource( const FHitResult& hitResult, FVector& newHitLocation );

	/** Can this extractor occupy a resource node? */
	virtual bool CanOccupyResource( const TScriptInterface< class IFGExtractableResourceInterface >& resource ) const;

	/** Can this extractor occupy a resource node, given that it is not already occupied? */
	virtual bool IsAllowedOnResource( const TScriptInterface< class IFGExtractableResourceInterface >& resource ) const;

protected:
	UPROPERTY()
	const class AFGBuildableResourceExtractorBase* mDefaultExtractor = nullptr;

	/** The resource node we snapped to. */
	UPROPERTY()
	TScriptInterface< class IFGExtractableResourceInterface > mSnappedExtractableResource;

	UPROPERTY( )
	class AFGBuildableResourceExtractorBase* mUpgradeTarget = nullptr;

};

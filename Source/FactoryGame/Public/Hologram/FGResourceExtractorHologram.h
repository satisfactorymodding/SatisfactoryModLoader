// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "../Resources/FGItemDescriptor.h"
#include "FGFactoryHologram.h"
#include "FGResourceExtractorHologram.generated.h"

/**
 * Hologram for buildings that can only be placed (snapped) on resource nodes.
 */
UCLASS()
class FACTORYGAME_API AFGResourceExtractorHologram : public AFGFactoryHologram
{
	GENERATED_BODY()
	
public:
	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
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

protected:
	/** What form can the overlapping resources be in. */
	UPROPERTY()
	TArray< EResourceForm > mAllowedResourceForms;

	/** The resource node we snapped to. */
	UPROPERTY()
	class AFGResourceNode* mSnappedResourceNode;
};

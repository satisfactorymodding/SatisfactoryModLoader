// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Resources/FGResourceDescriptor.h"
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
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	// End AFGBuildableHologram Interface

	/**
	 * Helper to check if there's resources available for IsValidPlacement.
	 */
	void CheckResourcesAvailable();

	/**
	 * Check if this hologram meets minimum depth requirements.
	 */
	void CheckMinimumDepth();

protected:
	/** What form can the overlapping resources be in. */
	UPROPERTY()
	TArray< EResourceForm > mAllowedResourceForms;

	/** Only allow certain specified resources ( set on the buildable ) */
	bool mOnlyAllowCertainResources;

	/** Class of disqualifier to display when not snapped to a resource ( copied from buildable ) */
	UPROPERTY()
	TSubclassOf< class UFGConstructDisqualifier > mMustPlaceOnResourceDisqualifier;

	/** If this buildable only allows certain resources for placement, this is the list of those taken from the buildable */
	UPROPERTY()
	TArray< TSubclassOf< UFGResourceDescriptor > > mAllowedResources;

	/** The resource node we snapped to. */
	UPROPERTY()
	TScriptInterface< class IFGExtractableResourceInterface > mSnappedExtractableResource;

	UPROPERTY( )
	class AFGBuildableResourceExtractor* mUpgradeTarget = nullptr;

	/** name used to mathc types of extractros for compatiblility when upgrading */
	FName mExtractorTypeName = "";

	/** Minimum depth for placement assigned from the Buildable */
	float mMinimumDepthForPlacement;

	/** Require collision with the resource class at all minimum depth points? Assigned from the buildable */
	bool mRequireResourceAtMinimumDepthChecks;

	/** Origin Offset when performing minimum depth traces. Assigned from the buildable */
	FVector mDepthTraceOriginOffset;


public:
	FORCEINLINE ~AFGResourceExtractorHologram() = default;
};

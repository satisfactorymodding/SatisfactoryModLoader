// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Hologram/FGBuildableHologram.h"
#include "Hologram/FGBuildGuide.h"
#include "FGFactoryConnectionComponent.h"
#include "FGFactoryHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGFactoryHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

public:
	/** Ctor */
	AFGFactoryHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual void SetupClearance( class UBoxComponent* boxComponent ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	virtual void Destroyed() override;
	virtual FVector GetGuideLinesBaseLocation();

	// @todo: Move clearance mesh thingies to BuildableHologram
	/** Mesh component used to display the clearance mesh */
	UPROPERTY()
	class UStaticMeshComponent* mClearanceMeshComponent;

	/** Mesh we want to use in the component */
	UPROPERTY()
	class UStaticMesh* mClearanceMesh;

	/** Material to use on the clearance component */
	UPROPERTY()
	class UMaterialInterface* mClearanceMaterial;

	/** Should this building also use the TC_BuildGuide when sweeping for aligned buildings? */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Hologram" )
	bool mIncludeBuildGuideTraceChannel;

	TMap<class UObject*, class AFGBuildGuide*> mGuideLineBuildings;
};

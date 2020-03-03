// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGBuildableHologram.h"
#include "FGBuildGuide.h"
#include "../FGFactoryConnectionComponent.h"
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

	TMap<class UObject*, class AFGBuildGuide*> mGuideLineBuildings;

public:
	FORCEINLINE ~AFGFactoryHologram() = default;
};

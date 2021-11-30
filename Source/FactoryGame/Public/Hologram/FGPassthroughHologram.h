// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGPassthroughHologram.generated.h"


/**
 * 
 */
UCLASS()
class AFGPassthroughHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

public:
	
	AFGPassthroughHologram();

	// Begin Actory Interface
	virtual void BeginPlay() override;
	// End AActor Interface


	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void ConfigureActor( class AFGBuildable* inBuildable ) const override;
	// End AFGHologram interface

protected:
	void BuildMeshes();
	void UpdateClearance();

private:
	UPROPERTY()
	FVector mAlignDirection;

	// The foundation this passthrough has snapped to
	UPROPERTY()
	AFGBuildableFoundation* mSnappedFoundation;

	// Depending on what we snap to this can be the wall thickness or foundation height
	UPROPERTY()
	float mSnappedBuildingThickness;

	// The length of the mesh used for tiling the mid section
	UPROPERTY()
	float mMidMeshLength;

	UPROPERTY()
	class UStaticMesh* mCapMesh;

	UPROPERTY()
	class UStaticMesh* mMidMesh;

	UPROPERTY()
	FRotator mEndCapRotation;

	UPROPERTY()
	FRotator mMidMeshRotation;

	UPROPERTY()
	FVector mEndCapTranslation;

	UPROPERTY()
	float mClearanceHeightMin;

	UPROPERTY()
	float mClearanceThickness;

	UPROPERTY()
	TArray< class UStaticMeshComponent* > mMeshComponents;

	UPROPERTY()
	TSubclassOf< class UFGConnectionComponent > mConnectionClass;
};

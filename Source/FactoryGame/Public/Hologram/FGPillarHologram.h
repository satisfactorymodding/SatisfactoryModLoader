// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGPillarHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPillarHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGPillarHologram();

	// Begin Actor interface
	virtual void BeginPlay() override;
	// End Actor interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void AdjustForGround( FVector& out_adjustedLocation, FRotator& out_adjustedRotation ) override;
	// End AFGHologram interface

	// Begin AFGBuildableHologram interface
	virtual void SetZoopFromHitresult( const FHitResult& hitResult ) override;
	virtual void CreateZoopInstances( const FIntVector& DesiredZoop ) override;
	virtual void FilterAttachmentPoints( TArray< const FFGAttachmentPoint* >& Points, AFGBuildable* pBuildable, const FHitResult& HitResult ) const override;
	virtual void CreateAttachmentPointTransform( FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint ) override;
	// End AFGBuildableHologram interface
protected:
	// Begin AFGHologram Interface
	virtual bool CanIntersectWithDesigner( class AFGBuildableBlueprintDesigner* designer ) const override;
	// End AFGHologram Interface
	
	// Begin AFGBuildableHologram interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FTransform& hologramTransform ) const override;
	// End AFGBuildableHologram interface
	
private:
	UPROPERTY( EditDefaultsOnly, Category = "Hologram" )
	float mForceVerticalSnapThreshold;
	
	FVector mSize;

	FVector mSnappedLocation;
};

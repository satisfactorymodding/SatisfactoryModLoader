// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGStorageBoxHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGStorageBoxHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

public:
	AFGStorageBoxHologram();

	// Begin AFGHologram Interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGBuildableHologram Interface
	virtual void CreateAttachmentPointTransform( FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint ) override;
	// End AFGBuildableHologram Interface

private:
	bool mFlipSnappedDirection;
};

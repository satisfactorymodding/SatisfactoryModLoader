// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "Hologram/FGFoundationHologram.h"
#include "FGRampHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGRampHologram : public AFGFoundationHologram
{
	GENERATED_BODY()

public:
	AFGRampHologram();

protected:

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool IsHologramIdenticalToActor( AActor* actor, const FTransform& hologramTransform ) const override;
	// End AFGHologram interface
	
	// Begin AFGBuildableHologram interface
	virtual void CreateZoopInstances( const FIntVector& DesiredZoop ) override;
	// End AFGBuildableHologram interface

	// Begin AFGFoundationHologram interface
	virtual void SetZoopFromHitresult( const FHitResult& hitResult ) override;
	// End AFGFoundationHologram interface

protected:
	bool mIsRoof;
};

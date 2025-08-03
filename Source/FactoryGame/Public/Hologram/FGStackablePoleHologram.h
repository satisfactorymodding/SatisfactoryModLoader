// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryBuildingHologram.h"
#include "FGStackablePoleHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGStackablePoleHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()

public:
	AFGStackablePoleHologram();

	virtual void BeginPlay() override;
	
	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

	// Begin AFGFactoryBuildingHologram interface
	virtual void SetZoopFromHitresult( const FHitResult& hitResult );
	virtual void CreateZoopInstances() override;
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
	// End AFGFactoryBuildingHologram interface
	
private:
	float mStackHeight;
};

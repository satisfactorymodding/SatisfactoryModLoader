// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryBuildingHologram.h"
#include "FGBarrierCornerHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBarrierCornerHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()

public:
	AFGBarrierCornerHologram();

	virtual void BeginPlay() override;

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGFactoryBuildingHologram Interface
	virtual void CreateZoopInstances() override;
	virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
	// End AFGFactoryBuildingHologram Interface

private:
	FVector mSize;
};

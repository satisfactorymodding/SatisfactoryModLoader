// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGFactoryBuildingHologram.h"
#include "FGStackableShelfHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGStackableShelfHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()

public:
	AFGStackableShelfHologram();

	virtual void BeginPlay() override;

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGBuildableHologram interface
    virtual void CreateZoopInstances( const FIntVector& DesiredZoop ) override;
    virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
    // End AFGBuildableHologram interface

	void SetZoopFromHitResult( const FHitResult& hitResult );
	
private:
	FVector mSize;
};

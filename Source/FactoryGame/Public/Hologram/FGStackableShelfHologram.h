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
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGFactoryBuildingHologram interface
    virtual void CreateZoopInstances() override;
    virtual FVector ConvertZoopToWorldLocation( const FIntVector& zoop ) const override;
    // End AFGFactoryBuildingHologram interface

	void SetZoopFromHitResult( const FHitResult& hitResult );
	
private:
	FVector mSize;
};

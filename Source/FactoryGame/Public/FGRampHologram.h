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
	
	// Begin AFGFactoryBuildingHologram interface
	virtual void UpdateZoop() override;
	virtual void ConstructZoop( TArray<AActor*>& out_children ) override;
	// End AFGFactoryBuildingHologram interface

	// Begin AFGFoundationHologram interface
	virtual void SetZoopFromHitresult( const FHitResult& hitResult ) override;
	// End AFGFoundationHologram interface
};

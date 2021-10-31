// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGFactoryBuildingHologram.h"
#include "FGCornerWallHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGCornerWallHologram : public AFGFactoryBuildingHologram
{
	GENERATED_BODY()
public:
	AFGCornerWallHologram();

	// Begin AActor Interface
	virtual void BeginPlay() override;
	// End AActor Interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram interface

protected:
	/** Size of the wall corner, grabbed from default buildable */
	float mSize;

	/** Height of the wall corner, grabbed from default buildable */
	float mHeight;
};

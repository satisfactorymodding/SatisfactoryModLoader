// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGFactoryConnectionComponent.h"
#include "FGFactoryHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGFactoryHologram : public AFGBuildableHologram
{
	GENERATED_BODY()

public:
	/** Ctor */
	AFGFactoryHologram();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram interface
};

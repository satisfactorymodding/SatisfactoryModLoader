// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Hologram/FGPoleHologram.h"
#include "FGSignPoleHologram.generated.h"

/**
 * Hologram for sign poles.
 */
UCLASS()
class FACTORYGAME_API AFGSignPoleHologram : public AFGPoleHologram
{
	GENERATED_BODY()
public:
	AFGSignPoleHologram();
	virtual void BeginPlay() override;

	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

	// Set to indicated whether this was attached to a cieling or a floor
	FORCEINLINE float GetDirectionZ() { return zDir; }

private:
	float zDir;
};

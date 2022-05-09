// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Hologram/FGVehicleHologram.h"
#include "FGWheeledVehicleHologram.generated.h"

/**
 * The base class for wheeled vehicle holograms.
 */
UCLASS()
class FACTORYGAME_API AFGWheeledVehicleHologram : public AFGVehicleHologram
{
	GENERATED_BODY()
	
public:

protected:
	// Begin AFGHologram interface
	virtual void HandleClearanceOverlap( const FOverlapResult& overlap, const FVector& locationOffset, bool HologramHasSoftClearance ) override;
	// End of AFGHologram interface
};

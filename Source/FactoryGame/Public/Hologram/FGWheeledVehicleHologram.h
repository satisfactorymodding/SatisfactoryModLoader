// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGVehicleHologram.h"
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
	virtual void SetHologramLocationAndRotation(const FHitResult& hitResult) override;
	virtual AFGVehicle* ConstructVehicle(FNetConstructionID netConstructionID) const override;
	// End of AFGHologram interface
};

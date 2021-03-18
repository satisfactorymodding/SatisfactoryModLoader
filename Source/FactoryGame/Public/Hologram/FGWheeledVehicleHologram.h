// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

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
	// Begin AFGHologram interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End of AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	// End of AFGHologram interface

	/** @copydoc AFGVehicleHologram::ConstructVehicle */
	virtual class AFGVehicle* ConstructVehicle( FNetConstructionID netConstructionID ) const override;
};

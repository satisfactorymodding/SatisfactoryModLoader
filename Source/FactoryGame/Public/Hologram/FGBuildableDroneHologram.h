// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"


#include "Hologram/FGVehicleHologram.h"
#include "FGBuildableDroneHologram.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableDroneHologram : public AFGVehicleHologram
{
	GENERATED_BODY()

public:
	AFGBuildableDroneHologram();
	
	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End of AFGHologram interface

protected:

	// Begin AFGVehicleHologram Interface
	virtual class AFGVehicle* ConstructVehicle( FNetConstructionID netConstructionID ) const override;
	// End AFGVehicleHologram Interface

protected:
	/** The pipeline we snapped to. */
	UPROPERTY( Replicated )
	class AFGBuildableDroneStation* mSnappedStation;
};

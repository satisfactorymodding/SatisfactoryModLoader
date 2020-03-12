// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGHologram.h"
#include "FGVehicleHologram.generated.h"

/**
* The base class for vehicle holograms such as trucks, trains etc.
*/
UCLASS()
class FACTORYGAME_API AFGVehicleHologram : public AFGHologram
{
	GENERATED_BODY()

public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End of AFGHologram interface
protected:
	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	// End of AFGHologram interface

	/**
	 * Construct the actual thing from this hologram (the vehicle).
	 * @return - The constructed vehicle on success; nullptr on failure.
	 */
	virtual class AFGVehicle* ConstructVehicle( FNetConstructionID netConstructionID ) const;

public:
	FORCEINLINE ~AFGVehicleHologram() = default;
};

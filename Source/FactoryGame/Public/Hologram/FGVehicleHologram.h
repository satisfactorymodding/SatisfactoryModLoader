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

	/** Set the vehicle class for this hologram. */
	void SetVehicleClass( TSubclassOf< class AFGVehicle > vehicleClass );

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual AActor* Construct( TArray< AActor* >& out_children ) override;
	// End of AFGHologram interface

protected:
	// Begin AFHHologram interface
	virtual TSubclassOf< AActor > GetActorClass() const override;
	// End of AFGHologram interface

	/**
	 * Construct the actual thing from this hologram (the vehicle).
	 * @return - The constructed vehicle on success; nullptr on failure.
	 */
	virtual class AFGVehicle* ConstructVehicle() const;

protected:
	/** The vehicle class that this hologram constructs. */
	UPROPERTY( Replicated )
	TSubclassOf< class AFGVehicle > mVehicleClass;
};

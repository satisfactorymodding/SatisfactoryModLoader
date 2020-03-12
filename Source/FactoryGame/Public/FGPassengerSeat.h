#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGDriveablePawn.h"
#include "FGPassengerSeat.generated.h"


/**
* Passenger seat used in FGVehicle
*/
UCLASS()
class FACTORYGAME_API AFGPassengerSeat : public AFGDriveablePawn
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	AFGPassengerSeat();

	// Begin AActor interface
	virtual void Tick( float dt ) override;
	// End AActor interface

	/** Gets the actual vehicle this passenger seat belongs to */
	UFUNCTION( BlueprintPure, Category = "Vehicle" )
	FORCEINLINE class AFGVehicle* GetOuterVehicle() { return mOuterVehicle; }

protected:
	/** Called every frame when we have a local driver in the vehicle */
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void UpdateCamera();
	
public:
	/** Instance of the vehicle this passenger seat belongs to */
	UPROPERTY( SaveGame, Replicated )
	class AFGVehicle* mOuterVehicle; 

public:
	FORCEINLINE ~AFGPassengerSeat() = default;
};

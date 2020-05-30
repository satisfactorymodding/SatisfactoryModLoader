// Copyright 2016-2020 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGVehicleSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGVehicleSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGVehicleSubsystem();

	// Begin AActor interface
	virtual void Tick( float dt ) override;

	// End AActor interface

	/** Get the vehicle subsystem, this should always return something unless you call it really early. */
	static AFGVehicleSubsystem* Get( UWorld* world );

	/** Get the vehicle subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Vehicle", DisplayName = "GetVehicleSubsystem", Meta = (DefaultToSelf = "worldContext") )
	static AFGVehicleSubsystem* Get( UObject* worldContext );

	void TickVehicleSimulation( float dt );

	/** Find the closest player sq for a creature */
	float FindClosestPlayerSq( class AActor* actor ) const;

	/**
	 * Adds the  vehicle to the subsystem
	 */
	void AddVehicle( class AFGVehicle* vehicle );

	/**
	 * Removes the  vehicle from the subsystem
	 */
	void RemoveVehicle( class AFGVehicle* vehicle );
private:
	/** How many vehicles can we iterate over per tick */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle" )
	int32 mMaxVehicleIterationsPerTick;

	/** Iterator for current index in the vehicle array */
	int32 mVehicleIterator;

	/** All the vehicles in the world. */
	UPROPERTY()
	TArray< class AFGVehicle* > mVehicles;

public:
	FORCEINLINE ~AFGVehicleSubsystem() = default;
};

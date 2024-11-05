// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Containers/List.h"

#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGDroneStationInfo.h"
#include "FGDroneSubsystem.generated.h"

USTRUCT( BlueprintType )
struct FDroneStationData
{
	GENERATED_BODY()

	/**  */
	UPROPERTY( BlueprintReadOnly )
	TObjectPtr<AFGDroneStationInfo> Station = nullptr;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsOrigin = false;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsPairedToOrigin = false;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsPairedFromOrigin = false;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	float Distance = false;
};

/**
 * 
 */
UCLASS( Blueprintable, abstract, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick", LOD, Cooking ) )
class FACTORYGAME_API AFGDroneSubsystem : public AFGSubsystem
{
	GENERATED_BODY()
public:
	AFGDroneSubsystem();

	/** Get the drone subsystem, this should always return something unless you call it really early. */
	static AFGDroneSubsystem* Get( UWorld* world );

	/** Get the vehicle subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Drones", DisplayName = "GetDroneSubsystem", Meta = (DefaultToSelf = "worldContext") )
	static AFGDroneSubsystem* Get( UObject* worldContext );

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void Tick( float DeltaSeconds ) override;
	// End AActor interface

	FORCEINLINE const TArray< class AFGDroneVehicle* >& GetAllDrones() const { return mDrones; }
	FORCEINLINE const TArray< class AFGDroneStationInfo* >& GetAllStations() const { return mStations; }

	/**
	 * Adds a drone station to the subsystem
	 */
	void AddStation( class AFGBuildableDroneStation* station );

	/**
	 * Removes a drone station from the subsystem
	 */
	void RemoveStation( class AFGBuildableDroneStation* station );

	/**
	 * Registers a drone to the subsystem
	 */
	void RegisterDrone( class AFGDroneVehicle* drone );

	/**
	 * Unregisters a drone from the subsystem
	 */
	void UnregisterDrone( class AFGDroneVehicle* drone );

	/**
	 * Registers a drone movement to the subsystem for ticking
	 */
	void RegisterDroneMovement( class UFGDroneMovementComponent* droneMovement );

	/**
	 * Unregisters a drone movement from the subsystem for ticking
	 */
	void UnregisterDroneMovement( class UFGDroneMovementComponent* droneMovement );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Drones" )
	void SearchStations( AFGDroneStationInfo* originStation, AFGDroneStationInfo* hostStation, FString filter, bool connectionsOnly, bool excludeOrigin, bool pairedFirst, bool includeEmptyStation, TArray< FDroneStationData >& result );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Drones" )
	void Server_PairStations( AFGDroneStationInfo* origin, AFGDroneStationInfo* target );

	/** Give this station an initial name. */
	void SetInitialStationName( AFGDroneStationInfo* stationInfo );

	/** Set the name of this station. */
	void SetStationName( AFGDroneStationInfo* stationInfo, const FString& newName );
	
	/** Generates a new name for a drone station. */
	FText GenerateStationName() const;

	/** @return If the station name is available; false if another station with this name already exists. */
	bool IsStationNameAvailable( const FString& name ) const;
	
private:
	void InitializeStationNames();

	void UpdatePhysics( FPhysScene* physScene, float dt );
	void TickDroneMovement( float DeltaSeconds );

private:
	FDelegateHandle OnPhysSceneStepHandle;
	
	/** All the drone stations in the world */
	UPROPERTY( Replicated )
	TArray< class AFGDroneStationInfo* > mStations;

	/** All the drones in the world */
	UPROPERTY( Replicated )
	TArray< class AFGDroneVehicle* > mDrones;

	/** All the drone movement components which need ticking. */
	UPROPERTY()
	TArray< class UFGDroneMovementComponent* > mTickingMovementComponents;

	/** A random name is picked from here when placing a stop. */
	UPROPERTY()
	TArray< FString > mStationNames;
};

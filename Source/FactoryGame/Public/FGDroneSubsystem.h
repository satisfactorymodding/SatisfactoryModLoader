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
	class AFGDroneStationInfo* Station;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsOrigin;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsPairedToOrigin;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	bool IsPairedFromOrigin;

	/**  */
	UPROPERTY( BlueprintReadOnly )
	float Distance;
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
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	// End AActor interface

	/**
	 * Adds a drone station to the subsystem
	 */
	void AddStation( class AFGBuildableDroneStation* station );

	/**
	 * Removes a drone station from the subsystem
	 */
	void RemoveStation( class AFGBuildableDroneStation* station );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Drones" )
	void SearchStations( AFGDroneStationInfo* originStation, AFGDroneStationInfo* hostStation, FString filter, bool connectionsOnly, bool excludeOrigin, bool pairedFirst, bool includeEmptyStation, TArray< FDroneStationData >& result );

	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Drones" )
	void Server_PairStations( AFGDroneStationInfo* origin, AFGDroneStationInfo* target );

	void SetUniqueStationName( AFGDroneStationInfo* stationInfo, const FString& prefix ) const;

private:
	bool TrySetStationName( AFGDroneStationInfo* stationInfo, const FString& name ) const;

private:
	/** All the drone stations in the world */
	UPROPERTY( Replicated )
	TArray< AFGDroneStationInfo* > mStations;

	/** What new drone stations should be called by default excluding unique number. */
	UPROPERTY( EditDefaultsOnly, Category = "Drone Station" )
	FString mDroneStationDefaultNamePrefix = "Drone Port";

};

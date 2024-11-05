// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableRailroadTrack.h"
#include "GameFramework/Actor.h"
#include "FGTrainReplicationActor.generated.h"

class AFGRailroadVehicle;


/**
 * Replicated simulation state used for client prediction and correction.
 */
USTRUCT()
struct FTrainReplicatedSimulationData
{
	GENERATED_BODY()
public:
	/**
	 * Custom as we need this struct to have replication atomicity.
	 * Note: The track can still be invalid on client if it is not relevant.
	 */
	bool NetSerialize( FArchive& ar, UPackageMap* map, bool& out_success );
	
	/** @return true if the replicated state is valid. */
	bool IsValid() const;
	
public:
	/** When this state was received. */
	double TimeStamp = 0.f;

	/** Server's first vehicle, this is dependent on the direction of travel. */
	UPROPERTY()
	AFGRailroadVehicle* FirstVehicle = nullptr;
	
	/** Server position at the time. */
	UPROPERTY()
	FRailroadTrackPosition FirstVehiclePosition = FRailroadTrackPosition::InvalidTrackPosition;

	/** Servers velocity at the time, so we can predict our new position. */
	float Velocity = 0.f;
};

template<>
struct TStructOpsTypeTraits<FTrainReplicatedSimulationData> : public TStructOpsTypeTraitsBase2<FTrainReplicatedSimulationData>
{
	enum
	{
		WithNetSerializer = true
	};
};

/**
 * Base class for an actor that helps replicate a train.
 *
 * It replicates the train by adding all vehicles as a dependency to itself so that the entire consist is replicated at once.
 * This ensures that we can simulate the physics of a train on the client.
 * 
 * Subclasses are derived for specific lengths of trains (can be seen as buckets) so that train that are longer have a longer replication distance.
 *
 * This class is also responsible for replicating simulation data for the train. Used to run client side prediction and correction.
 */
UCLASS( notplaceable )
class AFGTrainReplicationActor : public AActor
{
	GENERATED_BODY()
public:
	AFGTrainReplicationActor();
	
	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type endPlayReason) override;
	// End AActor Interface
	
	/**
	 * Determine which replication class to use based on the length of the train.
	 */
	static UClass* GetConcreteClassForTrainSize( int32 numVehicles );
	
	/**
	 * Initialize all vehicles in this replication actor.
	 * 
	 * Note: Must be called before BeginPlay and it is only valid to call once.
	 */
	void SetVehicles( TArray< AFGRailroadVehicle* > vehicles );

	/**
	 * Get all the vehicles in the train, valid to call on server and client.
	 */
	const TArray< class AFGRailroadVehicle* >& GetVehicles() const;

	/**
	 * Called on server to update the clients state.
	 *
	 * Note: Not valid to call on the client.
	 */
	void SetServerSimulationState( FTrainReplicatedSimulationData& state );
	
	/**
	 * Get the last received server simulation state, we base our predictions on it.
	 */
	const FTrainReplicatedSimulationData& GetLastServerSimulationState() const;

private:
	UFUNCTION()
	void OnRep_Vehicles();

	UFUNCTION()
	void OnRep_LastServerSimulationState();

public:
	/** Called whenever the vehicles gets replicated. */
	DECLARE_MULTICAST_DELEGATE( FOnVehiclesReplicated );
	
	FOnVehiclesReplicated mOnVehiclesReplicated;

	/** Delegates for the replication graph so it can setup dependencies. */
	DECLARE_MULTICAST_DELEGATE_OneParam( FOnTrainReplicationActorAdded, AFGTrainReplicationActor* );
	DECLARE_MULTICAST_DELEGATE_OneParam( FOnTrainReplicationActorRemoved, AFGTrainReplicationActor* );
	
	static FOnTrainReplicationActorAdded OnTrainReplicationActorAdded;
	static FOnTrainReplicationActorRemoved OnTrainReplicationActorRemoved;
private:
	/** Array of all vehicles in the train, in the order they appear in the consist. */
	UPROPERTY( ReplicatedUsing = OnRep_Vehicles )
	TArray< AFGRailroadVehicle* > mVehicles;
	
	/** Last known server state. */
	UPROPERTY( ReplicatedUsing = OnRep_LastServerSimulationState )
	FTrainReplicatedSimulationData mLastServerSimulationState;
};

UCLASS( notplaceable )
class AFGTrainReplicationActorShort : public AFGTrainReplicationActor
{
	GENERATED_BODY()
public:
	static constexpr int32 MAX_TRAIN_SIZE = 10;
	static constexpr float REPLICATION_CULL_DISTANCE = 80000.f + MAX_TRAIN_SIZE * 1600.f; // A train car is 16 m long.
};

UCLASS( notplaceable )
class AFGTrainReplicationActorMedium : public AFGTrainReplicationActor
{
	GENERATED_BODY()
public:
	static constexpr int32 MAX_TRAIN_SIZE = 20;
	static constexpr float REPLICATION_CULL_DISTANCE = 80000.f + MAX_TRAIN_SIZE * 1600.f;
};

UCLASS( notplaceable )
class AFGTrainReplicationActorLong : public AFGTrainReplicationActor
{
	GENERATED_BODY()
public:
	static constexpr int32 MAX_TRAIN_SIZE = 30;
	static constexpr float REPLICATION_CULL_DISTANCE = 80000.f + MAX_TRAIN_SIZE * 1600.f;
};

UCLASS( notplaceable )
class AFGTrainReplicationActorVeryLong : public AFGTrainReplicationActor
{
	GENERATED_BODY()
public:
	static constexpr int32 MAX_TRAIN_SIZE = 100; //@todo-trains-client This should match the maximum allowed train length
	static constexpr float REPLICATION_CULL_DISTANCE = 80000.f + MAX_TRAIN_SIZE * 1600.f;
};

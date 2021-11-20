// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGRailroadVehicle.h"
#include "FGRailroadSignalBlock.h"
#include "FGRailroadSubsystem.generated.h"


// Group for the detailed stats for this subsystem.
DECLARE_STATS_GROUP( TEXT( "RailroadSubsystem" ), STATGROUP_RailroadSubsystem, STATCAT_Advanced );


UCLASS()
class FACTORYGAME_API UFGRailroadRemoteCallObject : public UFGRemoteCallObject
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	UFUNCTION( Server, Reliable, WithValidation )
	void Server_RerailTrain( class AFGTrain* train );
	
private:
	UPROPERTY( Replicated, Meta = ( NoAutoJson ) )
	bool mForceNetField_UFGRailroadRemoteCallObject = false;
};

/**
 * Struct representing a set of interconnected tracks.
 */
USTRUCT()
struct FACTORYGAME_API FTrackGraph
{
	GENERATED_BODY()
public:
	FTrackGraph();

public:
	/** All the tracks that are connected (nodes in the graph) */
	UPROPERTY()
	TArray< class AFGBuildableRailroadTrack* > Tracks;
	
	/** All the signal blocks managed by this graph. */
	TArray< TSharedPtr< FFGRailroadSignalBlock > > SignalBlocks;

	/** This is the third rail the locomotives and stations connect to. */
	UPROPERTY()
	class UFGPowerConnectionComponent* ThirdRail;

	/** Do this track graph need to be rebuilt, e.g. tracks have been removed. */
	uint8 NeedFullRebuild:1;
	
	/** Has this track graph changed, tracks connected, rolling stock added or removed, signals added or removed. */
	uint8 HasChanged:1;
};


/**
 * Struct for storing collisions to trigger at a later point when the world is loaded in.
 */
USTRUCT()
struct FACTORYGAME_API FPendingTrainCollisionEvent
{
	GENERATED_BODY()
public:
	FVector Location = FVector::ZeroVector;
	
	TWeakObjectPtr< AFGRailroadVehicle > FirstHitVehicle = nullptr;
	TWeakObjectPtr< AFGRailroadVehicle > SecondHitVehicle = nullptr;

	//@todo-trains Add this when we need to save and reapply this on load.
	float FirstTrainVelocity = 0.f;
	float SecondTrainVelocity = 0.f;
};

/**
 * Actor for handling the railroad network and the trains on it.
 */
UCLASS( abstract, Blueprintable, hidecategories = ( Actor, Input, Replication, Rendering, "Actor Tick" ) )
class FACTORYGAME_API AFGRailroadSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGRailroadSubsystem();

	/** Called after this is spawned for additional setup prior to begin play. */
	void Init();
	
	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void Serialize( FArchive& ar ) override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	virtual void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface
	
	/** Get the railroad subsystem, this should always return something unless you call it really early. */
	static AFGRailroadSubsystem* Get( UWorld* world );

	/** Get the railroad subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad", DisplayName = "GetRailroadSubsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGRailroadSubsystem* Get( UObject* worldContext );



	/***************************************************************************************************
	 * Functions to handle Trains
	 */

	/** How should the train (name, time table etc) be handled when a consist is split up, i.e. uncoupling occurs. */
	enum class EDecouplingPolicy : uint8
	{
		UP_Auto,
		UP_KeepTrainOnFirst,	// When the split occurs, keep the existing train on the first vehicle.
		UP_KeepTrainOnSecond,	// When the split occurs, keep the existing train on the second vehicle.
	};

	/**
	 * Adds the railroad vehicle to the subsystem, and gives it a train if it does not have one already.
	 */
	void AddRailroadVehicle( AFGRailroadVehicle* vehicle );

	/**
	 * Removes the railroad vehicle from it's train and the subsystem, handles decoupling.
	 */
	void RemoveRailroadVehicle( AFGRailroadVehicle* vehicle );

	/**
	 * Couples two trains together.
	 * @param parentVehicle		This is the attach parent, this is not moved during the snap.
	 * @param otherVehicle		This train is nudged and attached to parent. @note This may be a newly spawned unregistered vehicle.
	 */
	void CoupleTrains( AFGRailroadVehicle* parentVehicle, AFGRailroadVehicle* otherVehicle );

	/**
	 * De-couples two vehicles in a train.
	 * To decouple a vehicle completely you need to run this for booth ends of the vehicle.
	 */
	void DecoupleTrains( AFGRailroadVehicle* firstVehicle, AFGRailroadVehicle* secondVehicle, EDecouplingPolicy decouplePolicy );

	/**
	 * Get the distance between two train vehicles.
	 */
	FORCEINLINE static float GetCouplingDistance( float firstVehicleLength, float secondVehicleLength )
	{
		return firstVehicleLength * 0.5f + secondVehicleLength * 0.5f;
	}

	/** Get all trains on the specified track. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad" )
	void GetTrains( int32 trackID, TArray< class AFGTrain* >& out_trains ) const;

	/** Get all trains. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad" )
	void GetAllTrains( TArray< class AFGTrain* >& out_trains ) const;



	/***************************************************************************************************
	 * Functions to handle Train Stations.
	 */

	/** Generates a new name for a train station. */
	FText GenerateTrainStationName() const;

	/** @return If the station name is available; false if another station with this name already exists. */
	bool IsTrainStationNameAvailable( const FString& name ) const;

	/** Add, update and remove train stations for use in time tables. */
	void AddTrainStation( class AFGBuildableRailroadStation* station );
	void UpdateTrainStation( class AFGBuildableRailroadStation* station );
	void RemoveTrainStation( class AFGBuildableRailroadStation* station );

	/** Get all stations for the specified track. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad" )
	void GetTrainStations( int32 trackID, TArray< class AFGTrainStationIdentifier* >& out_stations ) const;

	/** Get all stations. */
	UFUNCTION( BlueprintCallable, BlueprintPure = false, Category = "FactoryGame|Railroad" )
	void GetAllTrainStations( TArray< class AFGTrainStationIdentifier* >& out_stations ) const;

	/** Called to externally update a platforms power connection to use its tracks third rail */
	void UpdateCargoPlatformPowerConnection( int32 trackGraphID, class AFGBuildableTrainPlatformCargo* cargoPlatform );



	/***************************************************************************************************
	 * Functions to keep track of the Tracks.
	 */

	/**
	 * Move a position along a track, leaving the current segment and entering a new if needed.
	 * @return true on success, false if we did not move the whole distance.
	 */
	static bool MoveTrackPosition( struct FRailroadTrackPosition& position, float delta, float& out_movedDelta, float endStopDistance = 0.f );

	/**
	 * Add a new track segment.
	 * @note Track must have its connections set up.
	 */
	void AddTrack( class AFGBuildableRailroadTrack* track );

	/** Remove a track segment. Called on dismantle. */
	void RemoveTrack( class AFGBuildableRailroadTrack* track );

	/**
	 * Get the power connection that the locomotives power shoe connects to (the third rail).
	 * 
	 * Only valid to call on server.
	 * 
	 * @return The third rail power connection for the given track, nullptr if the track is not valid or not part of a valid graph.
	 */
	class UFGPowerConnectionComponent* GetThirdRailForTrack( const class AFGBuildableRailroadTrack* track ) const;

	/**
	 * Get the power connection that the locomotives power shoe connects to (the third rail).
	 * 
	 * Only valid to call on server.
	 * 
	 * @return The third rail power connection for the given track graph, nullptr if the track graph is not valid.
	 */
	class UFGPowerConnectionComponent* GetThirdRailForTrackGraph( int32 trackGraphID ) const;

	/***************************************************************************************************
	 * Functions to handle signals.
	 */

	/**
	 * Called when a signal is built or loaded so necessary structures can be rebuilt.
	 */
	void AddSignal( class AFGBuildableRailroadSignal* signal );

	/**
	 * Called when a signal is dismantled so necessary structures can be rebuilt.
	 */
	void RemoveSignal( class AFGBuildableRailroadSignal* signal );

	/**
	 * Get the active train scheduler.
	 */
	class AFGTrainScheduler* GetTrainScheduler() const;

	/***************************************************************************************************
	 * Iterator for train sets.
	 * Used to iterate over all the vehicles in a train
	 *
	 * @usage    for( TTrainIterator it( FirstVehicle ); it; ++it )
	 */
	class TTrainIterator
	{
	public:
		TTrainIterator( AFGRailroadVehicle* vehicle ) :
			mCurrentVehicle( vehicle )
		{
		}

		/** Advances iterator to the next vehicle in the train. */
		FORCEINLINE TTrainIterator& operator++()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_FRONT :  ERailroadVehicleCoupler::RVC_BACK );
			}
			return *this;
		}

		/** Moves iterator to the previous vehicle in the train. */
		FORCEINLINE TTrainIterator& operator--()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_BACK :  ERailroadVehicleCoupler::RVC_FRONT );
			}
			return *this;
		}

		/** Compare if two iterator points to the same vehicle. */
		FORCEINLINE friend bool operator==( const TTrainIterator& lhs, const TTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle == rhs.mCurrentVehicle;
		}
		FORCEINLINE friend bool operator!=( const TTrainIterator& lhs, const TTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle != rhs.mCurrentVehicle;
		}

		/** Conversion to "bool" returning true if the iterator is valid. */
		FORCEINLINE explicit operator bool() const
		{
			return !!mCurrentVehicle;
		}

		/** inverse of the "bool" operator */
		FORCEINLINE bool operator !() const
		{
			return !( bool )*this;
		}

		/** Vehicle access */
		FORCEINLINE AFGRailroadVehicle* operator*() const
		{
			return mCurrentVehicle;
		}
		FORCEINLINE AFGRailroadVehicle* operator->() const
		{
			return mCurrentVehicle;
		}

	private:
		UPROPERTY()
		AFGRailroadVehicle* mCurrentVehicle;
	};

	/**
	 * Const version of the above.
	 */
	class TConstTrainIterator
	{
	public:
		TConstTrainIterator( const AFGRailroadVehicle* vehicle ) :
			mCurrentVehicle( vehicle )
		{
		}

		/** Advances iterator to the next vehicle in the train. */
		FORCEINLINE TConstTrainIterator& operator++()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_FRONT : ERailroadVehicleCoupler::RVC_BACK );
			}
			return *this;
		}

		/** Moves iterator to the previous vehicle in the train. */
		FORCEINLINE TConstTrainIterator& operator--()
		{
			if( LIKELY( mCurrentVehicle ) )
			{
				mCurrentVehicle = mCurrentVehicle->GetCoupledVehicleAt( mCurrentVehicle->IsOrientationReversed() ? ERailroadVehicleCoupler::RVC_BACK : ERailroadVehicleCoupler::RVC_FRONT );
			}
			return *this;
		}

		/** Compare if two iterator points to the same vehicle. */
		FORCEINLINE friend bool operator==( const TConstTrainIterator& lhs, const TConstTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle == rhs.mCurrentVehicle;
		}
		FORCEINLINE friend bool operator!=( const TConstTrainIterator& lhs, const TConstTrainIterator& rhs )
		{
			return lhs.mCurrentVehicle != rhs.mCurrentVehicle;
		}

		/** Conversion to "bool" returning true if the iterator is valid. */
		FORCEINLINE explicit operator bool() const
		{
			return !!mCurrentVehicle;
		}

		/** inverse of the "bool" operator */
		FORCEINLINE bool operator !() const
		{
			return !( bool )*this;
		}

		/** Vehicle access */
		FORCEINLINE const AFGRailroadVehicle* operator*() const
		{
			return mCurrentVehicle;
		}
		FORCEINLINE const AFGRailroadVehicle* operator->() const
		{
			return mCurrentVehicle;
		}

	private:
		UPROPERTY()
		const AFGRailroadVehicle* mCurrentVehicle;
	};

	/***************************************************************************************************
	 * Block visualization
	 */
	void ToggleBlockVisualization( bool enabled );
	void ToggleBlockVisualizationAlways( bool enabled );
	FLinearColor GetBlockVisualizationColor( int32 forSignalBlockID );

	/***************************************************************************************************
	 * Debug functions
	 */
	void Debug_MarkAllGraphsAsChanged();
	void Debug_MarkAllGraphsForFullRebuild();
	
protected:
	/** Called when two trains collide, only called once. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Railroad" )
	void OnTrainsCollided( class AFGTrain* first, class AFGTrain* second );
	
private:
	void TickTrackGraphs( float dt );
	void TickPendingCollisions( float dt );
	void TickBlockVisualization();

	void PurgeInvalidStationsFromTimeTables();

	/** Simple hit result struct for the custom train collisions. */
	struct FRailroadHitResult
	{
		/** Hit time, 1 means no hit < 1 mean a hit along the sweep, 0 means initial overlap. */
		float Time = 1.f;
		/** Vehicle that has been hit. */
		AFGRailroadVehicle* Vehicle = nullptr;
	};

	/**
	 * Solves the collisions for a vehicle in a train along its moved distance.
	 */
	FRailroadHitResult SolveVehicleCollisions(
		class AFGTrain* forTrain,
		class AFGRailroadVehicle* forVehicle,
		FRailroadTrackPosition oldTrackPosition,
		FRailroadTrackPosition newTrackPosition,
		float moveDelta );

	/**
	 * Helper to do a simple capsule against capsule hit detection for the trains.
	 * One of the capsules are moving and the other one is stationary.
	 * 
	 * @param capsuleSize		Size of the sweeping capsule, X is length, Y is radius.
	 * @param startPos			Start position of the sweeping capsule.
	 * @param startOrientation	Direction of the vehicle relative to the start positions direction.
	 * @param endPos			End position of the sweeping capsule.
	 * @param otherCapsuleSize	Size of the capsule we're sweeping against.
	 * @param otherPos			Position of the capsule we're sweeping against.
	 * 
	 * @return Hit time, 1 means no hit < 1 mean a hit along the sweep, 0 means initial overlap.
	 */
	float SweepRailroadPositions(
		FVector2D capsuleSize,
		FRailroadTrackPosition startPos,
		float startOrientation,
		FRailroadTrackPosition endPos,
		FVector2D otherCapsuleSize,
		FRailroadTrackPosition otherPos );
	
	/**
	 * Internal helper to rebuild a graph.
	 * Note: This function might split, remove or otherwise change the graph so it is not safe to assume anything about the graph afterwards.
	 */
	void RebuildTrackGraph( int32 graphID );

	/**
	 * Internal helper to rebuild the signal blocks.
	 */
	void RebuildSignalBlocks( int32 graphID );

	/** Call when updating a stations hidden power connection to update all platforms attached to that station */
	void RefreshPlatformPowerConnectionsFromStation( class AFGBuildableRailroadStation* station, class UFGCircuitConnectionComponent* connectTo );

	/** Initializes all auto generated station names. */
	void InitializeStationNames();

	/** Creates a new train with vehicle as the first vehicle. */
	class AFGTrain* CreateTrain( AFGRailroadVehicle* vehicle ) const;

	/** Remove a train and destroy the actor. */
	void RemoveTrain( class AFGTrain* train );

	/** Reconnects all vehicles in this train to the third rail. */
	void ReconnectTrainToThirdRail( AFGTrain* train );

	/** The physics is driven by the physics scene. */
	void PreTickPhysics( FPhysScene* physScene, float dt );
	void UpdatePhysics( FPhysScene* physScene, float dt );

	void UpdateSimulationData( class AFGTrain* train, struct FTrainSimulationData& simData );

	/** Merge two track graphs to one. */
	void MergeTrackGraphs( int32 first, int32 second );
	/** Create a new track graph. */
	int32 CreateTrackGraph();
	/** Remove track graph. */
	void RemoveTrackGraph( int32 graphID );

	/** Adds a track to a graph, performs a merge if the track is connected to another graph. */
	void AddTrackToGraph( class AFGBuildableRailroadTrack* track, int32 graphID );
	/** Tries to remove a track from it's current graph, if not part of a graph this does nothing. */
	void RemoveTrackFromGraph( class AFGBuildableRailroadTrack* track );

	/** Helpers to mark graphs dirty. */
	void MarkGraphAsChanged( int32 graphID );
	void MarkGraphForFullRebuild( int32 graphID );

	/** Get a new UID for a track graph. */
	int32 GenerateUniqueTrackGraphID();
	
public:
	/**
	 * How far apart can trains connect to each other.
	 * Can be used as the actor distance or track distance.
	 * (note that the track distance will be slightly longer than the actor distance in curved sections)
	 */
	UPROPERTY( EditDefaultsOnly )
	float mConnectDistance;

	/** Default switch control to place when building switches. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGBuildableRailroadSwitchControl > mSwitchControlClass;

	/** Default train class to use when spawning trains. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class AFGTrain > mTrainClass;

	/** How far away are the blocks visible. [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Signal Block Visualization" )
	float mBlockVisualizationDistance;
	
	/** Default block visualization colors. */
	UPROPERTY( EditDefaultsOnly, Category = "Signal Block Visualization" )
	TArray< FLinearColor > mBlockVisualizationColors;

private:
	FDelegateHandle OnPhysScenePreTickHandle;
	FDelegateHandle OnPhysSceneStepHandle;

	/** Counters for generating UIDs. */
	int32 mTrackGraphIDCounter;

	/** A random name is picked from here when placing a stop. */
	UPROPERTY()
	TArray< FString > mStationNames;

	/** All tracks in the world, valid on server and client (only relevant tracks). */
	TArray< TWeakObjectPtr< AFGBuildableRailroadTrack > > mTracks;
	
	/** All the train tracks in the world, separated by connectivity. */
	UPROPERTY()
	TMap< int32, FTrackGraph > mTrackGraphs;

	/** All station identifiers in the world. */
	UPROPERTY( SaveGame, Replicated )
	TArray< class AFGTrainStationIdentifier* > mTrainStationIdentifiers;

	//@todoG2 does this need to be saved? HannaS 28/4 -19
	/** All the trains in the world. */
	UPROPERTY( SaveGame, Replicated )
	TArray< class AFGTrain* > mTrains;

	/** Pending collision events for trains that collide outside of the loaded world. */
	TArray< FPendingTrainCollisionEvent > mPendingTrainCollisions;

private:
	/** Handles all the trains and their reservations inside the blocks. Only valid on server. */
	UPROPERTY()
	class AFGTrainScheduler* mTrainScheduler;
	
	/** True if we are actively showing block visualization. */
	bool mIsBlockVisualizationEnabled;
	bool mIsBlockVisualizationAlwaysEnabled;
};

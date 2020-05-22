// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGRailroadVehicle.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "GraphAStar.h"
#include "RailroadNavigation.h"
#include "FGRailroadSubsystem.generated.h"



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

	/** This is the third rail the locomotives and stations connect to. */
	UPROPERTY()
	class UFGPowerConnectionComponent* ThirdRail;

	/** Do this track graph need to be rebuilt, e.g. tracks have been removed. */
	uint8 NeedFullRebuild:1;

	//@todotrains Signaling, consider if this and mHasTrackGraphsChanged is needed.
	/** Has this track graph changed, tracks connected, rolling stock added or removed. */
	uint8 HasChanged:1;

public:
	FORCEINLINE ~FTrackGraph() = default;
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
	void DecoupleTrains( AFGRailroadVehicle* firstVehicle, AFGRailroadVehicle* secondVehicle );

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
	static bool MoveTrackPosition( struct FRailroadTrackPosition& position, float delta, float& out_movedDelta );

	/**
	 * Add a new track segment.
	 * @note Track must have its connections set up.
	 */
	void AddTrack( class AFGBuildableRailroadTrack* track );

	/** Remove a track segment. Called on dismantle. */
	void RemoveTrack( class AFGBuildableRailroadTrack* track );



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

private:
	void TickTrackGraphs( float dt );
	
	/**
	 * Internal helper to rebuild a graph.
	 * Note: This function might split, remove or otherwise change the graph so it is not safe to assume anything about the graph afterwards.
	 */
	void RebuildTrackGraph( int32 graphID );

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

	/** Called when the vehicles in a train changes, i.e. rolling stock is (de)coupled. */
	void OnTrainOrderChanged( class AFGTrain* trainID );

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

	/** This is sound component used to play sounds on trains. */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UFGRailroadVehicleSoundComponent > mVehicleSoundComponentClass;

private:
	FDelegateHandle OnPhysScenePreTickHandle;
	FDelegateHandle OnPhysSceneStepHandle;

	/** Counters for generating UIDs. */
	int32 mTrackGraphIDCounter;

	/** A random name is picked from here when placing a stop. */
	UPROPERTY()
	TArray< FString > mStationNames;

	/** All the train tracks in the world, separated by connectivity. */
	UPROPERTY()
	TMap< int32, FTrackGraph > mTrackGraphs;

	/** If the track graphs has changed and dependent data needs an update. */
	bool mHasTrackGraphsChanged;

	/** All station identifiers in the world. */
	UPROPERTY( SaveGame, Replicated )
	TArray< class AFGTrainStationIdentifier* > mTrainStationIdentifiers;

	//@todoG2 does this need to be saved? HannaS 28/4 -19
	/** All the trains in the world. */
	UPROPERTY( SaveGame, Replicated )
	TArray< class AFGTrain* > mTrains;

public:
	FORCEINLINE ~AFGRailroadSubsystem() = default;
};

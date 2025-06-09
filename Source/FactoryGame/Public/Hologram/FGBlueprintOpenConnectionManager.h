// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGConveyorBeltHologram.h"
#include "FGPipelineHologram.h"
#include "FGRailroadTrackHologram.h"

#include "FGFactoryConnectionComponent.h"
#include "FGPipeConnectionComponent.h"
#include "FGRailroadTrackConnectionComponent.h"

DECLARE_MULTICAST_DELEGATE_FourParams( FOnConnectionStateChanged, const TArray< class UFGConnectionComponent* >&, class UFGConnectionComponent*, class UFGConnectionComponent*, bool );

DECLARE_CYCLE_STAT( TEXT( "FGBlueprintOpenConnectionManagerBase - Update Automatic Connections" ), STAT_BlueprintOpenConnectionManager_UpdateAutomaticConnections, STATGROUP_Hologram );
DECLARE_CYCLE_STAT( TEXT( "FGBlueprintOpenConnectionManagerBase - Update OpenConnection State" ), STAT_BlueprintOpenConnectionManager_UpdateOpenConnectionState, STATGROUP_Hologram );

/**
 * Base class for FGBlueprintOpenConnectionManager, used by the BlueprintHologram to interface with the FGBlueprintOpenConnectionManagers without using templated functions.
 */
class FACTORYGAME_API FGBlueprintOpenConnectionManagerBase
{
public:
	FGBlueprintOpenConnectionManagerBase( class AFGBlueprintHologram* BlueprintHologram ) :
		mHologram( BlueprintHologram )
	{
	}

	virtual ~FGBlueprintOpenConnectionManagerBase() = default;

	virtual void RegisterNearbyActor( class AActor* Actor ) = 0;
	virtual void UnregisterNearbyActor( class AActor* Actor ) = 0;
	
	class AFGBlueprintHologram* GetHologram() const { return mHologram; }

	virtual void UpdateAutomaticConnections( const FHitResult& hitResult, bool& out_PlaySnapEffects ) = 0;

	virtual void HandleBuildableConnectionRemapping( class AFGBuildable* Buildable, int32 BlueprintBuildableIndex ) = 0;

	virtual void Initialize( TArray< class AFGBuildable* > buildables ) = 0;

	virtual bool AttemptConnectionStateSnap() = 0;

	virtual bool CanSnapConnectionStates() const = 0;

	virtual void Construct( TArray< class AFGBuildable* >& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID ) = 0;

	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) = 0;
	virtual void PostConstructMessageDeserialization() = 0;

	virtual void ResetAutomaticConnections() = 0;

public:
	FOnConnectionStateChanged mOnConnectionStateChanged;

private:
	class AFGBlueprintHologram* mHologram;
};

/** Class responsible for connecting open ended connections on a blueprint to buildables in the world. This is the base manager class containing some basic functionality and boilerplate functions for managing connections of a certain type. */
template<class ConnectionClass, class BridgeHologramClass>
class FGBlueprintOpenConnectionManager : public FGBlueprintOpenConnectionManagerBase
{
public:
	/** Struct representing a single open connection on the blueprint hologram. */
	struct OpenConnection
	{
		OpenConnection() :
			Buildable( nullptr ),
			Connection( nullptr ),

			BlueprintBuildableIndex( INDEX_NONE ),
			ConnectionIndex( INDEX_NONE )
		{
		}
			
		const class AFGBuildable* Buildable;
		ConnectionClass* Connection;
			
		// Blueprint Buildable Index and Connection Index will be used for remapping between spawned blueprints, as the blueprint will always spawn the buildables in the same order
		int32 BlueprintBuildableIndex;
		int32 ConnectionIndex;
	};
	
	/** An open connection state manages connecting one or several open connections to a target connection. */
	struct OpenConnectionState
	{
		OpenConnectionState() :
			TargetConnection( nullptr ),
			PreviousTargetConnection( nullptr ),

			BridgeHologram( nullptr ),

			HasSnappedTargetConnection( false ),

			CanDirectlyConnect( false ),
		
			IsValid( false ),
			PreviousIsValid( false )
		{
		}

		friend FArchive& operator<<( FArchive& ar, OpenConnectionState& item )
		{
			ar << item.TargetConnection;
			ar << item.HasSnappedTargetConnection;
			ar << item.BridgeHologram;
			ar << item.CanDirectlyConnect;
			
			return ar;
		}

		TArray< const OpenConnection* > OpenConnections;

		ConnectionClass* TargetConnection;
		ConnectionClass* PreviousTargetConnection;
	
		BridgeHologramClass* BridgeHologram;

		bool HasSnappedTargetConnection;

		bool CanDirectlyConnect;

		bool IsValid;
		bool PreviousIsValid;
	};

	/** Struct containing information about a nearby connection. */
	struct NearbyConnectionData
	{
		NearbyConnectionData( class AActor* actor, TArray< ConnectionClass* > connections ) :
			Actor( actor ),
			Connections( MoveTemp( connections ) )
		{
		}
		
		class AActor* Actor;
		TArray< ConnectionClass* > Connections;
	};
	
	/** Data for a potential connection between an OpenConnectionState and a target connection */
	struct PotentialConnectionPair
	{
		PotentialConnectionPair() :
			OpenConnectionState( nullptr ),
			TargetConnection( nullptr ),
			Score( 0.0f )
		{}
		
		OpenConnectionState* OpenConnectionState;
		ConnectionClass* TargetConnection;

		float Score;
	};
	
	FGBlueprintOpenConnectionManager( class AFGBlueprintHologram* BlueprintHologram ) : FGBlueprintOpenConnectionManagerBase( BlueprintHologram )
	{
		static_assert( std::is_base_of_v< class UFGConnectionComponent, ConnectionClass >, "FGBlueprintOpenConnectionStateManager ConnectionClass must inherit from UFGConnectionComponent." );
	}

	virtual ~FGBlueprintOpenConnectionManager() override = default;

	const TArray< OpenConnection >& GetOpenConnections() const { return mOpenConnections; }
	const TArray< OpenConnectionState >& GetOpenConnectionStates() const { return mOpenConnectionStates; }

	/** Registers an actor and its components as a nearby actor. */
	virtual void RegisterNearbyActor( class AActor* Actor ) override final;

	/** Unregisters an actor and its components as a nearby actor. */
	virtual void UnregisterNearbyActor( class AActor* Actor ) override final;

	/** Called by the blueprinthologram in order to update all automatic connection functionality, including bridge holograms. This is essentially the main updating function for the system. */
	virtual void UpdateAutomaticConnections( const FHitResult& hitResult, bool& out_PlaySnapEffects ) override final;

	/** Generates open connections for a loaded blueprint buildable. */
	virtual void GenerateOpenConnections( class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex ) = 0;

	/** Remaps open connections for the specified blueprint buildable index to the specified buildable. This is needed in order to connect our open ended connections to the newly constructed buildable. */
	virtual void HandleBuildableConnectionRemapping( class AFGBuildable* Buildable, int32 BlueprintBuildableIndex ) override final;

	/** Initializes the open connection manager for the specified buildables. */
	virtual void Initialize( TArray< class AFGBuildable* > buildables ) override final;

	/** Will connect all open ended connection states with their target connections. */
	virtual void Construct( TArray< class AFGBuildable* >& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID ) override;

	virtual void SerializeConstructMessage( FArchive& ar, FNetConstructionID id ) override;

	virtual void PostConstructMessageDeserialization() override;
	
	/** Will reset all open connection states. */
	virtual void ResetAutomaticConnections() override;

	/** Attempts to "snap" the open connection states to their target connection, locking it from being changed. Returns true if a state was snapped. */
	virtual bool AttemptConnectionStateSnap() override;

	virtual bool CanSnapConnectionStates() const override;
	
protected:
	/** Remaps connections for the specified bridge hologram to the new buildable and its connections. */
	virtual void RemapConnectionsForState( OpenConnectionState& State, const TArray< OpenConnection* >& ConnectionsToRemap, const TArray<ConnectionClass*>& NewConnections ) = 0;

	/** Whether or not the specified state can be connected directly, usually when the connections are right on top of eachother. Will disable the bridge hologram and call ConnectStateDirectly on construction instead. */
	virtual bool CanDirectlyConnectOpenState( const OpenConnectionState& State ) const = 0;

	/** Used to directly connect an OpenConnectionState to its target connection without a bridge hologram. */
	virtual void ConnectStateDirectly( OpenConnectionState& State ) = 0;

	/** Generates a list of Open Connection States based on the open connections on the blueprint. One state can be responsible for multiple Open Connections (Open ended train track junctions will only have one state, for example) */
	virtual void GenerateOpenConnectionStates();

	/** Updates the specified state, used for generating / updating bridge holograms among other things. */
	virtual void UpdateOpenConnectionState( OpenConnectionState& State, const FHitResult& hitResult ) = 0;

	/** Generates a list of potential connections. The state will set its target connection to whichever potential connection has the lowest score. (Lowest instead of highest because we usually base it on distance, lower distance is better.) */
	virtual TArray< PotentialConnectionPair > GeneratePotentialConnections( const OpenConnectionState& State, const TSet<ConnectionClass*>& ClaimedConnections ) = 0;

	/** Whether or not the specified bridge hologram is invalid. Will disable it if the open connection state it belongs to is not snapped. */
	virtual bool IsBridgeHologramInvalid( BridgeHologramClass* BridgeHologram ) const;

	OpenConnection& CreateOpenConnection();
	OpenConnectionState& CreateOpenConnectionState();

	const TArray< NearbyConnectionData >& GetNearbyConnections() { return mNearbyConnections; }
	NearbyConnectionData* GetNearbyConnectionDataForActor( const AActor* Actor );

private:
	/** List of open connections on the blueprint hologram. */
	TArray< OpenConnection > mOpenConnections;

	/** List of open connection states. One state can manage and connect multiple open connections. */
	TArray< OpenConnectionState > mOpenConnectionStates;

	/** Nearby connections that we're able to connect our open connection states to. */
	TArray< NearbyConnectionData > mNearbyConnections;
};

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::GenerateOpenConnectionStates()
{
	// Default behavior is to create one open connection state per open connection
	for( const OpenConnection& OpenConnection : mOpenConnections )
	{
		OpenConnectionState& NewState = CreateOpenConnectionState();
		NewState.OpenConnections.Add( &OpenConnection );
	}
}

template<class ConnectionClass, class BridgeHologramClass>
bool FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::IsBridgeHologramInvalid(
	BridgeHologramClass* BridgeHologram ) const
{
	return !BridgeHologram->CanConstruct();
}

template<class ConnectionClass, class BridgeHologramClass>
typename FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::OpenConnection& FGBlueprintOpenConnectionManager<
ConnectionClass, BridgeHologramClass>::CreateOpenConnection()
{
	return mOpenConnections.AddDefaulted_GetRef();
}

template<class ConnectionClass, class BridgeHologramClass>
typename FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::OpenConnectionState& FGBlueprintOpenConnectionManager<
ConnectionClass, BridgeHologramClass>::CreateOpenConnectionState()
{
	return mOpenConnectionStates.AddDefaulted_GetRef();
}

template<class ConnectionClass, class BridgeHologramClass>
typename FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::NearbyConnectionData* FGBlueprintOpenConnectionManager<
ConnectionClass, BridgeHologramClass>::GetNearbyConnectionDataForActor( const AActor* Actor )
{
	return mNearbyConnections.FindByPredicate( [Actor](const NearbyConnectionData& data ){ return data.Actor == Actor; } );
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::RegisterNearbyActor( AActor* Actor )
{
	if( !GetNearbyConnectionDataForActor( Actor ) )
	{
		TArray< ConnectionClass* > Connections;
		Actor->GetComponents< ConnectionClass >( Connections );
		
		mNearbyConnections.Emplace( Actor, MoveTemp( Connections ) );
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::UnregisterNearbyActor( AActor* Actor )
{
	mNearbyConnections.RemoveAllSwap( [Actor]( const NearbyConnectionData& Data ) { return Data.Actor == Actor; } );
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::UpdateAutomaticConnections( const FHitResult& hitResult, bool& out_PlaySnapEffects )
{
	SCOPE_CYCLE_COUNTER( STAT_BlueprintOpenConnectionManager_UpdateAutomaticConnections )
	
	TSet<ConnectionClass*> ClaimedConnections;
	
	// Clear out the target connections for all states, this needs to be done beforehand so we can properly filter and "claim" one connection each for the open connections
	for( OpenConnectionState& openConnectionState : mOpenConnectionStates )
	{
		// Update previous connection
		openConnectionState.PreviousTargetConnection = openConnectionState.TargetConnection;
			
		if( IsValid( openConnectionState.TargetConnection ) )
		{
			// If this connection state has snapped the target connection, then add it as a claimed connection, otherwise clear it
			if( openConnectionState.HasSnappedTargetConnection )
			{
				ClaimedConnections.Add( openConnectionState.TargetConnection );
			}
			else
			{
				openConnectionState.TargetConnection = nullptr;
			}
		}
		else
		{
			// Reset just in case the target connection goes invalid when we're snapped to it
			openConnectionState.HasSnappedTargetConnection = false;
		}
	}

	// Generate a list of potential connections
	static TArray< PotentialConnectionPair > PotentialConnections;
	PotentialConnections.Reset();
	
	for( OpenConnectionState& openConnectionState : mOpenConnectionStates )
	{
		if( openConnectionState.HasSnappedTargetConnection )
		{
			continue;
		}
		
		TArray< PotentialConnectionPair > NewPotentialConnections = GeneratePotentialConnections( openConnectionState, ClaimedConnections );

		for( const PotentialConnectionPair& newPotentialConnection : NewPotentialConnections )
		{
			// Check if there's an existing pair already trying to connect to this connection
			if( PotentialConnectionPair* existingPair = PotentialConnections.FindByPredicate( [newPotentialConnection]( const PotentialConnectionPair& existingPotentialConnection ) { return existingPotentialConnection.TargetConnection == newPotentialConnection.TargetConnection; } ) )
			{
				// Replace it if our score is lower, since lower score is better
				if( newPotentialConnection.Score < existingPair->Score )
				{
					existingPair->Score = newPotentialConnection.Score;
					existingPair->OpenConnectionState = newPotentialConnection.OpenConnectionState;
				}
			}
			else
			{
				PotentialConnections.Emplace( newPotentialConnection );
			}
		}
	}

	// Figure out the lowest scoring potential connection pairs for all open connection state
	TMap< OpenConnectionState*, const PotentialConnectionPair* > LowestScoringConnectionPairs;
	for( const PotentialConnectionPair& PotentialConnection : PotentialConnections )
	{
		if( !LowestScoringConnectionPairs.Contains( PotentialConnection.OpenConnectionState ) )
		{
			LowestScoringConnectionPairs.Add( PotentialConnection.OpenConnectionState, &PotentialConnection );
		}
		else
		{
			if( PotentialConnection.Score < LowestScoringConnectionPairs[PotentialConnection.OpenConnectionState]->Score )
			{
				LowestScoringConnectionPairs[PotentialConnection.OpenConnectionState] = &PotentialConnection;
			}
		}
	}

	// Connect the highest scoring connection pairs
	TArray< OpenConnectionState* > StatesToConnect;
	LowestScoringConnectionPairs.GenerateKeyArray( StatesToConnect );

	for( OpenConnectionState* State : StatesToConnect )
	{
		State->TargetConnection = LowestScoringConnectionPairs[State]->TargetConnection;
	}

	// Update open connection states
	TMap< AFGBlueprintProxy*, TArray< OpenConnectionState* > > ProxyConnectionStateMap;
	
	for( OpenConnectionState& State : mOpenConnectionStates )
	{
		SCOPE_CYCLE_COUNTER( STAT_BlueprintOpenConnectionManager_UpdateOpenConnectionState )

		if( IsValid( State.TargetConnection ) )
		{
			State.CanDirectlyConnect = CanDirectlyConnectOpenState( State );
		}
		else
		{
			State.CanDirectlyConnect = false;
		}

		UpdateOpenConnectionState( State, hitResult );
		
		if( IsValid( State.BridgeHologram ) )
		{
			bool bShouldEnableBridgeHologram = true;

			if( State.CanDirectlyConnect )
			{
				bShouldEnableBridgeHologram = false;
			}
			else
			{
				if( IsValid( State.TargetConnection ) )
				{				
					// Disable invalid bridge holograms if the target connection isn't snapped
					if( !State.HasSnappedTargetConnection )
					{
						if( IsBridgeHologramInvalid( State.BridgeHologram ) )
						{
							bShouldEnableBridgeHologram = false;
						}
					}
				}
				else
				{
					// Make sure to reset this in case we lose our target connection
					State.HasSnappedTargetConnection = false;
				
					// Disable bridge hologram if we don't have a target connection
					bShouldEnableBridgeHologram = false;
				}
			}
			
			if( bShouldEnableBridgeHologram )
			{				
				// Play snap effect if we're enabling a bridge hologram or the target connection has changed
				bool connectionChanged = false;

				if( State.PreviousTargetConnection != State.TargetConnection )
				{
					if( IsValid( State.PreviousTargetConnection ) && IsValid( State.TargetConnection ) )
					{
						// In some cases (train tracks), we might be snapped to an open ended junction with multiple connections, they are different connections but all are in the same location.

						// We check the distance between the old and new connection to avoid playing snap effects if we're still connected to that same junction
						const float DistSqr = FVector::DistSquared( State.PreviousTargetConnection->GetComponentLocation(), State.TargetConnection->GetComponentLocation() );

						if( !FMath::IsNearlyZero( DistSqr, 1.0f ) )
						{
							connectionChanged = true;
						}
					}
					else
					{
						connectionChanged = true;
					}
				}
				
				if( State.BridgeHologram->IsDisabled() || connectionChanged)
				{
					out_PlaySnapEffects = true;
				}
			}
				
			State.BridgeHologram->SetDisabled( !bShouldEnableBridgeHologram );
		}

		State.IsValid = State.CanDirectlyConnect || ( IsValid( State.BridgeHologram ) && !State.BridgeHologram->IsDisabled() );

		if( State.IsValid != State.PreviousIsValid || State.PreviousTargetConnection != State.TargetConnection )
		{
			TArray< class UFGConnectionComponent* > connections;
			connections.Reserve( State.OpenConnections.Num() );
			
			for( const OpenConnection* Connection : State.OpenConnections )
			{
				connections.Add( Connection->Connection );
			}
			
			mOnConnectionStateChanged.Broadcast( connections, State.PreviousTargetConnection, State.TargetConnection, State.IsValid );
		}

		State.PreviousIsValid = State.IsValid;
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::HandleBuildableConnectionRemapping( AFGBuildable* Buildable, int32 BlueprintBuildableIndex )
{
	TArray<ConnectionClass*> NewConnections;
    Buildable->GetComponents<ConnectionClass>(NewConnections);
    			
	for( OpenConnectionState& State : mOpenConnectionStates )
	{
		// Check if any of the connections contain the specified buildable
		TArray< OpenConnection* > ConnectionsToRemap;
		ConnectionsToRemap.Reserve( State.OpenConnections.Num() );
		
		for( const OpenConnection* Connection : State.OpenConnections )
		{
			if( Connection->BlueprintBuildableIndex == BlueprintBuildableIndex )
			{
				ConnectionsToRemap.Add( const_cast< OpenConnection* >( Connection ) );
			}
		}

		if( ConnectionsToRemap.Num() > 0 )
		{
			// Start by remapping the bridge hologram connections, in case it references our open connections
			if( IsValid( State.BridgeHologram ) )
			{
				RemapConnectionsForState( State, ConnectionsToRemap, NewConnections );
			}

			// Remap open connections
			for( OpenConnection* Connection : ConnectionsToRemap )
			{
				Connection->Buildable = Buildable;
				
				if( NewConnections.IsValidIndex( Connection->ConnectionIndex ) )
				{
					Connection->Connection = NewConnections[ Connection->ConnectionIndex ];
				}
				else
				{
					ensureAlwaysMsgf( false, TEXT("FGBlueprintOpenConnectionManager::HandleBuildableConnectionRemapping - Could not remap open connection. Invalid index.") );
				}
			}
		}
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::Initialize( TArray< AFGBuildable* > buildables )
{
	mOpenConnections.Reset();
	mOpenConnectionStates.Reset();

	int32 buildableIndex = 0;
	for( AFGBuildable* buildable : buildables )
	{
		GenerateOpenConnections( buildable, buildableIndex++ );
	}

	GenerateOpenConnectionStates();
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::Construct( TArray<AFGBuildable*>& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID )
{
	for( OpenConnectionState& State : mOpenConnectionStates )
	{
		// Attempt direct connection
		if( State.CanDirectlyConnect )
		{
			ConnectStateDirectly( State );
		}
		else
		{
			// Try to construct the bridge hologram
			if( IsValid( State.BridgeHologram ) )
			{
				if( !State.BridgeHologram->IsDisabled() && State.BridgeHologram->CanConstruct() )
				{
					TArray< AActor* > constructedChildren;
					AFGBuildable* newBridgeBuildable = CastChecked< AFGBuildable >( State.BridgeHologram->Construct( constructedChildren, NetConstructionID ) );

					out_ConstructedBridgeBuildables.Add( newBridgeBuildable );
				}
			}
		}
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::SerializeConstructMessage( FArchive& ar, FNetConstructionID id )
{	
	for( OpenConnectionState& openConnectionState : mOpenConnectionStates )
	{
		ar << openConnectionState;
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::PostConstructMessageDeserialization()
{
	for( OpenConnectionState& openConnectionState : mOpenConnectionStates )
	{
		FHitResult dummy;
		UpdateOpenConnectionState( openConnectionState, dummy );
	}
}

template<class ConnectionClass, class BridgeHologramClass>
void FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::ResetAutomaticConnections()
{
	for( OpenConnectionState& State : mOpenConnectionStates )
	{
		const bool ShouldBroadcast = State.IsValid || IsValid( State.TargetConnection );
		
		State.TargetConnection = nullptr;
		
		State.HasSnappedTargetConnection = false;
		State.CanDirectlyConnect = false;

		State.IsValid = false;

		if( IsValid( State.BridgeHologram ) )
		{
			State.BridgeHologram->SetDisabled( true );
		}

		if( ShouldBroadcast )
		{
			TArray< class UFGConnectionComponent* > connections;
			connections.Reserve( State.OpenConnections.Num() );
			
			for( const OpenConnection* Connection : State.OpenConnections )
			{
				connections.Add( Connection->Connection );
			}
			
			mOnConnectionStateChanged.Broadcast( connections, State.PreviousTargetConnection, State.TargetConnection, State.IsValid );
		}

		State.PreviousTargetConnection = nullptr;
		State.PreviousIsValid = false;
	}
}

template<class ConnectionClass, class BridgeHologramClass>
bool FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::AttemptConnectionStateSnap()
{
	bool bFoundUnsnappedTargetConnection = false;
	
	for( OpenConnectionState& State : mOpenConnectionStates )
	{
		if( IsValid( State.TargetConnection ) && State.IsValid && !State.HasSnappedTargetConnection )
		{
			bFoundUnsnappedTargetConnection = true;
			State.HasSnappedTargetConnection = true;
		}
	}

	return bFoundUnsnappedTargetConnection;
}

template<class ConnectionClass, class BridgeHologramClass>
bool FGBlueprintOpenConnectionManager<ConnectionClass, BridgeHologramClass>::CanSnapConnectionStates() const
{
	// Can take next build step if we're trying to snap an open connection to a target connection
	for( const OpenConnectionState& State : mOpenConnectionStates )
	{
		if( IsValid( State.TargetConnection ) && State.IsValid && !State.HasSnappedTargetConnection )
		{
			return true;
		}
	}

	return false;
}

// Factory Connections
class FACTORYGAME_API FGBlueprintOpenFactoryConnectionManager final : FGBlueprintOpenConnectionManager< UFGFactoryConnectionComponent, AFGConveyorBeltHologram >
{
public:
	explicit FGBlueprintOpenFactoryConnectionManager( class AFGBlueprintHologram* BlueprintHologram ) : FGBlueprintOpenConnectionManager( BlueprintHologram )
	{
	}

	virtual void GenerateOpenConnections( class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex ) override;
	virtual void RemapConnectionsForState( OpenConnectionState& State, const TArray< OpenConnection* >& ConnectionsToRemap, const TArray<UFGFactoryConnectionComponent*>& NewConnections ) override;

protected:
	virtual void UpdateOpenConnectionState( OpenConnectionState& State, const FHitResult& hitResult ) override;
	virtual TArray<PotentialConnectionPair> GeneratePotentialConnections( const OpenConnectionState& State, const TSet<UFGFactoryConnectionComponent*>& ClaimedConnections ) override;

protected:
	virtual bool CanDirectlyConnectOpenState( const OpenConnectionState& State ) const override;
	virtual void ConnectStateDirectly( OpenConnectionState& State ) override;
};

// Pipe Connections
class FACTORYGAME_API FGBlueprintOpenPipeConnectionManager final : FGBlueprintOpenConnectionManager< UFGPipeConnectionComponentBase, AFGPipelineHologram >
{
public:
	explicit FGBlueprintOpenPipeConnectionManager( class AFGBlueprintHologram* BlueprintHologram ) : FGBlueprintOpenConnectionManager( BlueprintHologram )
	{
	}

	virtual void GenerateOpenConnections( class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex ) override;
	virtual void RemapConnectionsForState( OpenConnectionState& State, const TArray< OpenConnection* >& ConnectionsToRemap, const TArray<UFGPipeConnectionComponentBase*>& NewConnections ) override;

protected:
	virtual void UpdateOpenConnectionState( OpenConnectionState& State, const FHitResult& hitResult ) override;
	virtual TArray<PotentialConnectionPair> GeneratePotentialConnections( const OpenConnectionState& State, const TSet<UFGPipeConnectionComponentBase*>& ClaimedConnections ) override;

protected:
	virtual bool CanDirectlyConnectOpenState( const OpenConnectionState& State ) const override;
	virtual void ConnectStateDirectly( OpenConnectionState& State ) override;
};

// Railroad Connections
class FACTORYGAME_API FGBlueprintOpenRailroadConnectionManager final : FGBlueprintOpenConnectionManager< UFGRailroadTrackConnectionComponent, AFGRailroadTrackHologram >
{
public:
	explicit FGBlueprintOpenRailroadConnectionManager( class AFGBlueprintHologram* BlueprintHologram ) : FGBlueprintOpenConnectionManager( BlueprintHologram )
	{
	}

	virtual void GenerateOpenConnections( class AFGBuildable* BlueprintBuildable, int32 BlueprintBuildableIndex ) override;
	virtual void Construct( TArray< class AFGBuildable* >& out_ConstructedBridgeBuildables, FNetConstructionID NetConstructionID ) override;

protected:
	virtual void GenerateOpenConnectionStates() override;
	virtual void UpdateOpenConnectionState( OpenConnectionState& State, const FHitResult& hitResult ) override;
	virtual bool IsBridgeHologramInvalid( AFGRailroadTrackHologram* BridgeHologram ) const override;
	
	virtual TArray<PotentialConnectionPair> GeneratePotentialConnections( const OpenConnectionState& State, const TSet<UFGRailroadTrackConnectionComponent*>& ClaimedConnections ) override;

public:
	virtual void RemapConnectionsForState( OpenConnectionState& State, const TArray< OpenConnection* >& ConnectionsToRemap, const TArray<UFGRailroadTrackConnectionComponent*>& NewConnections ) override;

protected:
	virtual bool CanDirectlyConnectOpenState( const OpenConnectionState& State ) const override;
	virtual void ConnectStateDirectly( OpenConnectionState& State ) override;

private:
	/** Cached list of duplicated connection components for all open ended railroad track connections in the blueprint. */
	TArray< class UFGRailroadTrackConnectionComponent* > mGeneratedConnectionComponents;

	/** Switch holograms used when directly connecting the blueprint to a railroad track without a bridge hologram inbetween. */
	TMap< const OpenConnectionState*, TArray< class AFGRailroadSwitchControlHologram* > > mDirectConnectionSwitchHolograms;
};
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGConnectionComponent.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadTrackConnectionComponent.generated.h"


/**
 * The actual track connection placed in the editor.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGRailroadTrackConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
	constexpr static int32 MAX_NUM_SWITCH_POSITIONS = 3;
	
	UFGRailroadTrackConnectionComponent();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin ActorComponent interface
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	// End ActorComponent interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface

	/** Return the connectors world location. */
	FORCEINLINE FVector GetConnectorLocation() const { return GetComponentTransform().GetLocation(); }
	/** Return the connectors world normal. */
	FORCEINLINE FVector GetConnectorNormal() const { return GetComponentRotation().Vector(); }

	bool CanConnectTo( const UFGRailroadTrackConnectionComponent* toComponent ) const;
	
	/**
	 * Add a connected component.
	 * @note Sets both ends of the connection.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Track" )
	void AddConnection( UFGRailroadTrackConnectionComponent* toComponent );

	/**
	 * @return The connected connection at switch position; nullptr if not connected or bad index.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE UFGRailroadTrackConnectionComponent* GetConnection( int32 position ) const { return mConnectedComponents.IsValidIndex( position ) ? mConnectedComponents[ position ] : nullptr; }

	/**
	 * @note If this is called on a component with multiple connections (switch/turnout) the result is depends on the switch's position.
	 * @return The connected connection; nullptr if not connected.
	 */
	UFGRailroadTrackConnectionComponent* GetConnection() const;
	
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	UFGRailroadTrackConnectionComponent* GetConnectionAtSwitchPosition() const;

	/**
	 * @return All connections; empty if not connected. If more than one this is a switch.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE TArray< UFGRailroadTrackConnectionComponent* > GetConnections() const { return mConnectedComponents; }

	/**
	 * Remove a connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 * @note This resets the switch's position to 0 or INDEX_NONE.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Track" )
	void RemoveConnection( UFGRailroadTrackConnectionComponent* toComponent );

	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE bool IsConnected() const { return mConnectedComponents.Num() > 0; }

	/** @return The track position of this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE FRailroadTrackPosition GetTrackPosition() const { return mTrackPosition; }

	/** @return Owning track for this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE class AFGBuildableRailroadTrack* GetTrack() const { return mTrackPosition.Track.Get(); }

	/** @return true if this connection is occupied by rolling stock. */
	bool IsOccupied( float distance, AFGTrain* ignored ) const { return GetTrack()->IsConnectionOccupied( this, distance, ignored ); }
	
	/**
	 * @return what part of a switch this connection is.
	 */
	bool IsFacingSwitch() const;
	bool IsTrailingSwitch() const;

	/**
	 *  0: Not connected.
	 *  1: Connected.
	 * >1: Turnout.
	 *
	 * @return The number of connections, i.e. switch positions.
	 */
	int32 GetNumSwitchPositions() const;

	/**
	 * @return The current switch position [0,n]; 0 if not a switch, INDEX_NONE if track is not connected.
	 */
	int32 GetSwitchPosition() const;

	/**
	 * Look up at which position a given track is.
	 * 
	 * @param track The track we want to look up, must be connected directly to the switch.
	 *
	 * @return The switch position for the given track, INDEX_NONE if not connected to the switch.
	 */
	int32 GetSwitchPositionForTrack( class AFGBuildableRailroadTrack* track ) const;

	/** @return true if the switch is clear of rolling stock, otherwise false. */
	bool IsSwitchClear() const;
	bool IsSwitchClear( AFGTrain* ignored ) const;
	
	/**
	 * Set the current switch position, not valid to call on client.
	 * @param position Will be clamped to the valid range [0,n].
	 *
	 * Note: On client use the switch control instead.
	 */
	void SetSwitchPosition( int32 position );

	/** @return The switch control, if any. Valid on client. */
	class AFGBuildableRailroadSwitchControl* GetSwitchControl() const { return mSwitchControl; }

	/** @return The station at the connection, if any. */
	class AFGBuildableRailroadStation* GetStation() const { return mStation; }

	/** @return The facing signal at the connection, if any. */
	class AFGBuildableRailroadSignal* GetFacingSignal() const { return mFacingSignal; }
	/** @return The trailing signal at the connection, if any. */
	class AFGBuildableRailroadSignal* GetTrailingSignal() const { return mTrailingSignal; }

	/** @return The signal block this connection belongs to, if any. */
	TWeakPtr< FFGRailroadSignalBlock > GetSignalBlock() const;
	
	/** Get the connection opposite to this one on the track segment. */
	UFGRailroadTrackConnectionComponent* GetOpposite() const;

	/** Get the next connection along the track from this one, considering switches position. */
	UFGRailroadTrackConnectionComponent* GetNext() const;

	/** Find the closest overlapping connection matching all search criteria. */
	static UFGRailroadTrackConnectionComponent* FindClosestOverlappingConnection(
		const class UFGRailroadTrackConnectionComponent* component,
		const FVector& location,
		float radius,
		const TSet< class UFGRailroadTrackConnectionComponent* >& ignoredConnections = {} );

	/** Finds all connections within a specified radius which are opposite / neighbouring our connection. */
	static TArray< UFGRailroadTrackConnectionComponent* > FindAlignedConnections(
		const class UFGRailroadTrackConnectionComponent* component,
		float radius,
		bool neighbouring = false );

	/** Returns a filtered list of the specified connections based on whether or not they're aligned with the specified connection. */
	static TArray< UFGRailroadTrackConnectionComponent* > FilterAlignedConnections(
		const class UFGRailroadTrackConnectionComponent* component,
		const TArray< UFGRailroadTrackConnectionComponent* >& connections,
		float radius,
		bool neighbouring = false );
	
	/** Find probable client connection. */
	static UFGRailroadTrackConnectionComponent* FindProbableClientConnection(
		const class UFGRailroadTrackConnectionComponent* connection );

	/**
	 * Functions used by buildings that are built on a track, do not call them unless you know what you're doing.
	 * Note that these can be called multiple times with the same input.
	 */
	void SetSwitchControl( class AFGBuildableRailroadSwitchControl* control );
	void SetStation( class AFGBuildableRailroadStation* station ) { mStation = station; }
	void SetFacingSignal( class AFGBuildableRailroadSignal* signal ) { mFacingSignal = signal; }
	void SetTrailingSignal( class AFGBuildableRailroadSignal* signal ) { mTrailingSignal = signal; }
	void SetTrackPosition( const FRailroadTrackPosition& position );

	/**
	 * Sort the connections in the visual order, from left to right when facing the track in the forward direction.
	 * Note that this does not change the current switch position if the connections are reordered.
	 */
	void SortConnections();

	/**
	 * Clears out any connections that are considered "invalid"
	 */
	void ClearInvalidConnections();

	/** Whether or not the specified connection is considered "valid" for us. */
	bool IsConnectionValid( UFGRailroadTrackConnectionComponent* toComponent );
	
private:
	/** Internal helper functions to add/remove connection. */
	void AddConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );
	void RemoveConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );
	void OnConnectionsChangedInternal();

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnConnectionsChanged, UFGRailroadTrackConnectionComponent*, connectionComponent );
	FOnConnectionsChanged mOnConnectionsChanged;

	/** LEGACY: This is now saved inside the switch control, this is here for migration from pre 1.1 saves. */
	UPROPERTY( SaveGame )
	int32 mSwitchPosition_DEPRECATED;
	
private:
	/** Position of this connection component on the track. */
	UPROPERTY( Replicated )
	FRailroadTrackPosition mTrackPosition;

	/** The components we're connected to. If >1 this is a switch. */
	UPROPERTY( SaveGame, Replicated )
	TArray< UFGRailroadTrackConnectionComponent* > mConnectedComponents;

	/** The switch control associated with this connection, if any. */
	UPROPERTY( Replicated )
	class AFGBuildableRailroadSwitchControl* mSwitchControl;

	/** The station associated with this connection, if any. */
	UPROPERTY()
	class AFGBuildableRailroadStation* mStation;

	/**
	 * The facing signal associated with this connection, if any.
	 * This is the signal a train cares about when traversing this connection.
	 */
	UPROPERTY()
	class AFGBuildableRailroadSignal* mFacingSignal;
	
	/**
	 * The trailing signals associated with this connection, if any.
	 * This is here for the subsystem to keep track of.
	 * This is the facing signal of the connected connections.
	 * If this is set but the facing signal is null, traversing is disallowed based on the one-way rule of signalling.
	 */
	UPROPERTY()
	class AFGBuildableRailroadSignal* mTrailingSignal;
};

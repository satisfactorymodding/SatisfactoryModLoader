// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGConnectionComponent.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadTrackConnectionComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnRailRoadConnectionSwitched, int32, newSwitch );

/**
 * The actual track connection placed in the editor.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGRailroadTrackConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
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

	/**
	 * Add a connected component.
	 * @note Sets both ends of the connection.
	 */
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
	FORCEINLINE UFGRailroadTrackConnectionComponent* GetConnection() const { return GetConnection( mSwitchPosition ); }

	/**
	 * @return All connections; empty if not connected. If more than one this is a switch.
	 */
	FORCEINLINE TArray< UFGRailroadTrackConnectionComponent* > GetConnections() const { return mConnectedComponents; }

	/**
	 * Remove a connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 * @note This resets the switch's position to 0 or INDEX_NONE.
	 */
	void RemoveConnection( UFGRailroadTrackConnectionComponent* toComponent );

	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram.
	 */
	FORCEINLINE bool IsConnected() const { return mConnectedComponents.Num() > 0; }

	/** @return The track position of this connection. */
	FORCEINLINE FRailroadTrackPosition GetTrackPosition() const { return mTrackPosition; }

	/** @return Owning track for this connection. */
	FORCEINLINE class AFGBuildableRailroadTrack* GetTrack() const { return mTrackPosition.Track.Get(); }

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
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE int32 GetNumSwitchPositions() const { return mConnectedComponents.Num(); }

	/**
	 * @return The current switch position [0,n]; 0 if not a switch.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Railroad|Track" )
	FORCEINLINE int32 GetSwitchPosition() const { return mSwitchPosition; }

	/**
	 * Set the current switch position.
	 * @param position Will be clamped to the valid range [0,n].
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Track" )
	void SetSwitchPosition( int32 position );

	/**
	 * Set the current switch position to match the given connections track.
	 */
	void SetSwitchPosition( class AFGBuildableRailroadTrack* track );

	/** @return The switch control, if any. */
	class AFGBuildableRailroadSwitchControl* GetSwitchControl() const { return mSwitchControl; }

	/** @return The station at the connection, if any. */
	class AFGBuildableRailroadStation* GetStation() const { return mStation; }

	/** @return The signal at the connection, if any. */
	class AFGBuildableRailroadSignal* GetSignal() const { return mSignal; }

	/** Get the connection opposite to this one on the track segment. */
	UFGRailroadTrackConnectionComponent* GetOpposite() const;

	/** Get the next connection along the track from this one, considering switches position. */
	UFGRailroadTrackConnectionComponent* GetNext() const;

	/** Find the closest overlapping connection matching all search criteria. */
	static UFGRailroadTrackConnectionComponent* FindOverlappingConnections(
		class UFGRailroadTrackConnectionComponent* component,
		const FVector& location,
		float radius,
		bool allowPlatformTracks = false );

	/** Functions used by buildings that are built on a track, do not call them unless you know what you're doing. */
	void SetSwitchControl( class AFGBuildableRailroadSwitchControl* control ) { mSwitchControl = control; }
	void SetStation( class AFGBuildableRailroadStation* station ) { mStation = station; }
	void SetSignal( class AFGBuildableRailroadSignal* signal ) { mSignal = signal; }
	void SetTrackPosition( const FRailroadTrackPosition& position );

	/**
	 * Sort the connections in the visual order, from left to right when facing the track in the forward direction.
	 * Note that this does not change the current switch position if the connections are reordered.
	 */
	void SortConnections();
private:
	//@todotrains Verify building switches at both sides of a connection, the weird bug some people report.
	/** Internal helper functions to add/remove connection. */
	void AddConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );
	void RemoveConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );

	void ClampSwitchPosition();

public:
	/** Delegate to fire when changing switch on a track */
	UPROPERTY()
	FOnRailRoadConnectionSwitched mRailRoadSwitchDelegate;
private:
	/** Position of this connection component on the track. */
	FRailroadTrackPosition mTrackPosition;

	/** The components we're connected to. If >1 this is a switch. */
	UPROPERTY( SaveGame, Replicated )
	TArray< UFGRailroadTrackConnectionComponent* > mConnectedComponents;

	/** If this is a switch, this is the switch position. */
	UPROPERTY( SaveGame, Replicated )
	int32 mSwitchPosition;

	/** The switch control associated with this connection, if any. */
	UPROPERTY()
	class AFGBuildableRailroadSwitchControl* mSwitchControl;

	/** The station associated with this connection, if any. */
	UPROPERTY()
	class AFGBuildableRailroadStation* mStation;

	/** The signal associated with this connection, if any. */
	UPROPERTY()
	class AFGBuildableRailroadSignal* mSignal; //@todotrains

public:
	FORCEINLINE ~UFGRailroadTrackConnectionComponent() = default;
};

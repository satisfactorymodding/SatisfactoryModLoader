// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FGConnectionComponent.h"
#include "FGRailroadInterface.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "FGRailroadTrackConnectionComponent.generated.h"


/**
 * The actual track connection placed in the editor.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGRailroadTrackConnectionComponent : public UFGConnectionComponent, public IFGRailroadInterface
{
	GENERATED_BODY()

public:	
	UFGRailroadTrackConnectionComponent();

	// Begin ActorComponent interface
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	// End ActorComponent interface

	// Begin IFGRailroadInterface
	virtual void RegisteredOnTrack_Implementation( const FRailroadTrackPosition& position ) override;
	virtual void UnregisteredFromTrack_Implementation() override;
	virtual FRailroadTrackPosition GetTrackPosition_Implementation() const override;
	// End IFGRailroadInterface

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

	/**
	 * Set the track position of this component.
	 * @note Cannot be called after component registration.
	 */
	void SetTrackPosition( const FRailroadTrackPosition& position );

	/**
	 * @return Owning track for this connection.
	 */
	FORCEINLINE class AFGBuildableRailroadTrack* GetTrack() const { return mTrackPosition.Track.Get(); }

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
	 * @param position Clamped to the valid range [0,n].
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Railroad|Track" )
	void SetSwitchPosition( int32 position );

	/**
	 * Gets the attached switch control, if any.
	 * @note Loops through all attach children, use with care!
	 */
	class AFGBuildableRailroadSwitchControl* GetAttachedSwitchControl() const;

	/**
	 * Get the connection opposite to this one on the track segment.
	 */
	UFGRailroadTrackConnectionComponent* GetOpposite() const;

	/** Find the closest overlapping connection matching all search criteria. */
	static UFGRailroadTrackConnectionComponent* FindOverlappingConnections(
		class UFGRailroadTrackConnectionComponent* component,
		const FVector& location,
		float radius,
		bool allowPlatformTracks = false );

private:
	/** Internal helper functions to add/remove connection. */
	void AddConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );
	void RemoveConnectionInternal( UFGRailroadTrackConnectionComponent* toComponent );

private:
	/** Position of this connection component on the track. */
	FRailroadTrackPosition mTrackPosition;

	/** The components we're connected to. If >1 this is a switch. */
	UPROPERTY( SaveGame )
	TArray< UFGRailroadTrackConnectionComponent* > mConnectedComponents;

	/** If this is a switch, this is the switch position. */
	UPROPERTY( SaveGame )
	int32 mSwitchPosition;
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"
#include "Array.h"
#include "UObject/Class.h"
#include "GameFramework/Actor.h"
#include "FGConnectionComponent.h"
#include "FGSaveInterface.h"
#include "FGCircuitConnectionComponent.generated.h"

#define IS_PUBLIC_BUILD 1

DECLARE_MULTICAST_DELEGATE_OneParam( FConnectionChanged, class UFGCircuitConnectionComponent* );

/**
 * A scene component used for adding circuit connectors to a building.
 * A wire can be connected between two connectors, making it a circuit in the circuit subsystem.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGCircuitConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
	UFGCircuitConnectionComponent();

	// Begin UActorComponent interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	// End UActorComponent interface

	// Begin IFGSaveInterface interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End IFGSaveInterface interface

	/** Set if this connection is hidden. */
	void SetIsHidden( bool isHidden ) { mIsHiddenConnection = isHidden; }

	/** Get the number of connections to this connection, excluding hidden. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	int32 GetNumConnections() const;

	/** Get the number of hidden connections to this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE int32 GetNumHiddenConnections() const { return mHiddenConnections.Num(); }

	/** Get the maximum allowed connections to this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE int32 GetMaxNumConnections() const { return mMaxNumConnectionLinks; }

	/** Get How many free connections this connection has. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE int32 GetNumFreeConnections() const { return GetMaxNumConnections() - GetNumConnections(); }

	/**
	 * Get all the connections, excluding hidden connections. Use GetHiddenConnections for that.
	 * @param out_connections Array to append all the connections.
	 */
	void GetConnections( TArray< class UFGCircuitConnectionComponent* >& out_connections ) const;

	/**
	 * Get all the hidden connections.
	 * @param out_connections Array to append all the hidden connections.
	 */
	FORCEINLINE void GetHiddenConnections( TArray< class UFGCircuitConnectionComponent* >& out_connections ) const { out_connections.Append( mHiddenConnections ); }

	/**
	 * Get all the wires connected to this connection.
	 * @param out_wires Array to append all the wires.
	 */
	FORCEINLINE void GetWires( TArray< class AFGBuildableWire* >& out_wires ) const { out_wires.Append( mWires ); }
	FORCEINLINE void GetWires( TInlineComponentArray< class AFGBuildableWire* >& out_wires ) const { out_wires.Append( mWires ); }

	/**
	 * Add a connection to another component.
	 * Note: Connections are the wires responsibility, this call only makes it known to us that a connection exists.
	 * Note: Do not call this unless you know what you're doing.
	 */
	void AddConnection( class AFGBuildableWire* wire );

	/**
	 * Remove connection using this wire.
	 * Note: Connections are the wires responsibility, this call only makes it known to us that a connection exists.
	 * Note: Do not call this unless you know what you're doing.
	 */
	void RemoveConnection( class AFGBuildableWire* wire );

	/**
	 * Add a hidden connection to another connection component. One of the connections must be hidden for this to be valid.
	 * Connects both ends of the connection and the circuits.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|Connection" )
	void AddHiddenConnection( class UFGCircuitConnectionComponent* other );

	/**
	 * Remove a hidden connection to another connection component.
	 * Disconnects both ends of the connection and the circuits.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|Connection" )
	void RemoveHiddenConnection( class UFGCircuitConnectionComponent* other );

	/** Clear all hidden connections. */
	void ClearHiddenConnections();

	/** Is this a hidden connection, you cannot connect a wire to it but connect it through code. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE bool IsHidden() const { return mIsHiddenConnection; }

	/** @return true if this is connected to a circuit; false if not connected. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE int32 IsConnected() const { return mCircuitID != INDEX_NONE; }

	/** Get the circuit this is connected to; -1 if not connected to a circuit. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Connection" )
	FORCEINLINE int32 GetCircuitID() const { return mCircuitID; }

	/** Used by the circuits and circuit subsystem to update the circuit this is connected to. */
	void SetCircuitID( int32 circuitID );

	/** Debug */
	void DisplayDebug( class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );
	FString GetDebugName() const;

protected:
	/** Called when the circuit ID changes, this can happen at any time when the circuitry is changed, e.g. when circuits are split or merged. */
	virtual void OnCircuitIDChanged();

	/** Called when the circuit changes, this can happen at any time when the circuitry is changed, e.g. when circuits are split or merged. */
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Circuits|Connection", Meta = ( DisplayName = "OnCircuitIDChanged" ) )
	void ReceiveOnCircuitIDChanged();

private:
	/** Tracks replication changes to mCircuitID */
	UFUNCTION()
	void OnRep_CircuitIDChanged();

public:
	/** Callback when connection was removed or added */
	FConnectionChanged OnConnectionChanged;

private:
	/** How many connections this component can have connected. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	int32 mMaxNumConnectionLinks;

	/** This connection is hidden and can only be connected through the code. E.g. powered walls have a hidden connection all machines connect to. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	bool mIsHiddenConnection;

	/** The wired connections to this. */
	UPROPERTY( VisibleAnywhere, SaveGame, Replicated, Category = "Connection" )
	TArray< AFGBuildableWire* > mWires;

	/** The wired connections to this. */
	UPROPERTY( VisibleAnywhere, Replicated, Category = "Connection" )
	uint8 mNumWiresConnected;

	/** The non-wired (if this or the other is hidden) connections to this. */
	UPROPERTY( VisibleAnywhere, SaveGame )
	TArray< UFGCircuitConnectionComponent* > mHiddenConnections;

	/**
	 * The circuit this connection is connected to. INDEX_NONE if not connected.
	 * @note - This ID may change at any time when changes occurs in the circuitry. Do not save copies of it!
	 */
	UPROPERTY( VisibleAnywhere, ReplicatedUsing = OnRep_CircuitIDChanged, Category = "Connection" )
	int32 mCircuitID;

public:
	FORCEINLINE ~UFGCircuitConnectionComponent() = default;
};

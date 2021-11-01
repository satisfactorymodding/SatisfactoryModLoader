// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGConnectionComponent.h"
#include "FGInventoryComponent.h"
#include "FGFactoryConnectionComponent.generated.h"

// For lazy people. This is used in nearly every BeginPlay of Proxies.
#define FOR_EACH_FACTORY_INLINE_COMPONENTS( COMPONENT_NAME ) \
	TInlineComponentArray<UFGFactoryConnectionComponent*> connections; \
	GetComponents( connections ); \
	for( UFGFactoryConnectionComponent* COMPONENT_NAME : connections )

// If you need the components sorted by index at end of name
#define FOR_EACH_ORDERED_FACTORY_INLINE_COMPONENTS( COMPONENT_NAME ) \
	TInlineComponentArray<UFGFactoryConnectionComponent*> connections; \
	GetComponents( connections ); \
	UFGFactoryConnectionComponent::SortComponentList( connections ); \
	for( UFGFactoryConnectionComponent* COMPONENT_NAME : connections )

//@todo This is unused and is only confusing, remove it later -G2 2020-05-29
/**
 * Type of connections in the game.
 * @todo-Pipes - This is old, we're shifting to a different connection component type for pipes as they don't need most of the special logic in the factory connection
 */
UENUM( BlueprintType )
enum class EFactoryConnectionConnector : uint8
{
	FCC_CONVEYOR	UMETA( DisplayName = "Conveyor" ),
	FCC_PIPE		UMETA( DisplayName = "Pipe" ),
	FCC_MAX			UMETA( Hidden )
};

/**
 * Type of connections in the game.
 */
UENUM( BlueprintType )
enum class EFactoryConnectionDirection : uint8
{
	FCD_INPUT		UMETA( DisplayName = "Input" ),
	FCD_OUTPUT		UMETA( DisplayName = "Output" ),
	FCD_ANY			UMETA( DisplayName = "Any" ),
	FCD_SNAP_ONLY	UMETA( DisplayName = "Snap Only" ), // Special case for conveyor poles, may need refactor later.
	FCD_MAX			UMETA( Hidden )
};

/**
 * This component is used on factories to connect to.
 */
UCLASS( ClassGroup = ( Custom ), meta = (BlueprintSpawnableComponent) )
class FACTORYGAME_API UFGFactoryConnectionComponent : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
	UFGFactoryConnectionComponent();

	/** Replication */
	void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const;

	// Begin ActorComponent interface
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	// End ActorComponent interface

	// Begin save interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End save interface

	/** Set our direction after creation time */
	FORCEINLINE void SetDirection( EFactoryConnectionDirection newDirection ){ mDirection = newDirection; }

	/** Set the conveyor clearance for this connection. */
	FORCEINLINE void SetConnectorClearance( float clearance ){ mConnectorClearance = clearance; }

	/**
	 * Set the inventory associated with this connection
	 */
	void SetInventory( class UFGInventoryComponent* inventory );

	/**
	* Sets a specified index for the component to access on its assigned inventory
	*/
	void SetInventoryAccessIndex( int32 index );

	/**
	* Gets the inventory access index specified for this factory connection
	*/
	int32 GetInventoryAccessIndex() const { return mInventoryAccessIndex; }

	/**
	 * Set which connection this is connected to.
	 * @note Sets both ends of the connection.
	 * If there already a connection made we assert.
	 */
	void SetConnection( class UFGFactoryConnectionComponent* toComponent );

	/**
	 * Get which connection this is connected to.
	 */
	FORCEINLINE class UFGFactoryConnectionComponent* GetConnection() const { return mConnectedComponent; }

	/**
	 * Clear the connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 */
	void ClearConnection();

	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram, snap only or bad index configuration.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|FactoryConnection" )
	FORCEINLINE bool IsConnected() const
	{
		return mHasConnectedComponent;
	}

	/** Return the inventory associated with this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|FactoryConnection" )
	FORCEINLINE class UFGInventoryComponent* GetInventory() const { return mConnectionInventory; }

	/** Return the direction for this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|FactoryConnection" )
	FORCEINLINE EFactoryConnectionDirection GetDirection() const { return mDirection; }

	/** Get the direction needed to be able to connect to this connection, ANY if anything is valid. */
	EFactoryConnectionDirection GetCompatibleSnapDirection() const;

	/** Return the connector used for this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|FactoryConnection" )
	FORCEINLINE EFactoryConnectionConnector GetConnector() const { return mConnector; }
	
	/** Check if the given connection can snap to this. */
	bool CanSnapTo( UFGFactoryConnectionComponent* otherConnection ) const;
	
	/** Check if the given connection can connect to this. */
	bool CanConnectTo( UFGFactoryConnectionComponent* otherConnection ) const;

	/** Accessor for c++ constructors */
	FORCEINLINE void SetForwardPeekAndGrabToBuildable( bool forwardPeekAndGrab ){ mForwardPeekAndGrabToBuildable = forwardPeekAndGrab; }

	/** Return the clearance needed when routing a conveyor belt from this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Factory|FactoryConnection" )
	FORCEINLINE float GetConnectorClearance() const { return mConnectorClearance; }

	/** Return the connectors world location with or without considering the clearance. */
	FVector GetConnectorLocation( bool withClearance = false ) const;
	/** Return the connectors world normal. */
	FVector GetConnectorNormal() const { return GetComponentRotation().Vector(); }

	/**
	 * Check this connection has a output
	 * @param type - Optionally check the type of the output, nullptr for any.
	 * @return true if it has output; false if no output or
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|FactoryConnection" )
	bool Factory_PeekOutput( TArray< FInventoryItem >& out_items, TSubclassOf< class UFGItemDescriptor > type = nullptr ) const;

	/**
	 * Grab the output on a connection (Grabs 1 resource).
	 * @param type - Type to grab if output has multiple types, nullptr for any.
	 * @param offset - if we are grabbing from a belt the item might have an offset beyond the belt's length
	 * @return valid resource descriptor on success; nullptr if no output of given type exists.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|FactoryConnection" )
	bool Factory_GrabOutput( FInventoryItem& out_item, float& out_OffsetBeyond, TSubclassOf< UFGItemDescriptor > type = nullptr );

	/**
	 * Internal function, for when overloading how to handle a peek, peeks our output from a inventory
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|FactoryConnection" )
	bool Factory_Internal_PeekOutputInventory( TArray< FInventoryItem >& out_items, TSubclassOf< class UFGItemDescriptor > type ) const;

	/**
	 * Internal function, for when overloading how to handle a grab, grabs our output from a inventory
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Factory|FactoryConnection" )
	bool Factory_Internal_GrabOutputInventory( FInventoryItem& out_item, TSubclassOf< UFGItemDescriptor > type );

	/** Debug */
	void DisplayDebug( int32 connectionIndex, class UCanvas* canvas, const class FDebugDisplayInfo& debugDisplay, float& YL, float& YPos );

	class AFGBuildable* GetOuterBuildable() const { return mOuterBuildable; }

	/**
	 * Sort the components by name
	 * 
	 * @param io_components - List to be sorted
	 */
	static void SortComponentList( TInlineComponentArray< UFGFactoryConnectionComponent* >& io_components );

	/**
	 * This function tells us the maximum amounts of grabs this building can make this frame
	 */
	virtual uint8 MaxNumGrab( float delta ) const;

	/** Same as FindOverlappingConnections but finds a connection compatible with the passed connection. */
	static UFGFactoryConnectionComponent* FindCompatibleOverlappingConnections(
		class UFGFactoryConnectionComponent* component,
		const FVector& location,
		float radius,
		UFGFactoryConnectionComponent* lowPrioConnection = nullptr );

	/** Find the closest overlapping connection matching all search criteria. */
	static UFGFactoryConnectionComponent* FindOverlappingConnections(
		UWorld* world,
		const FVector& location,
		float radius,
		EFactoryConnectionConnector connector,
		EFactoryConnectionDirection direction,
		UFGFactoryConnectionComponent* lowPrioConnection = nullptr );

	/**
	 * Find all overlapping connections and returns them in a list.
	 * Filters to not include blocked connections or incompatible connections.
	 */
	static int32 FindAllOverlappingConnections(
		TArray< UFGFactoryConnectionComponent* > out_Connection,
		UWorld* world,
		const FVector& location,
		float radius,
		EFactoryConnectionConnector connector,
		EFactoryConnectionDirection direction );

private:
	/**
	 * Checks if a connection is blocked by another connection in a list of building overlaps.
	 * If not blocked it returns null, if blocked it returns the blocking connection.
	 */
	static UFGFactoryConnectionComponent* CheckIfSnapOnlyIsBlockedByOtherConnection(
		UFGFactoryConnectionComponent* connectionToCheck,
		TArray< FOverlapResult > potentialBlockers );

protected:
	/** Physical type of connector used for this connection. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	EFactoryConnectionConnector mConnector;

	/** Direction for this connection. */
	UPROPERTY( EditDefaultsOnly, SaveGame, Category = "Connection" )
	EFactoryConnectionDirection mDirection;

	/** How long the connector is extending, indicates where the connected conveyor may start turning. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	float mConnectorClearance;

	/** Connection to another component. If this is set we're connected. */
	UPROPERTY( SaveGame )
	class UFGFactoryConnectionComponent* mConnectedComponent;

	/** Light-weight connected indication for clients. */
	UPROPERTY( Replicated )
	bool mHasConnectedComponent;

	/** The inventory of this connection */
	UPROPERTY( SaveGame )
	class UFGInventoryComponent* mConnectionInventory;

	/** The inventory index utilized by this connection ( -1 for none specified ) */
	UPROPERTY( SaveGame )
	int32 mInventoryAccessIndex;

	/** Buildable owning us, cached for performance */
	UPROPERTY()
	class AFGBuildable* mOuterBuildable;

	/** Forward implementation details to our owner. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	bool mForwardPeekAndGrabToBuildable;
};

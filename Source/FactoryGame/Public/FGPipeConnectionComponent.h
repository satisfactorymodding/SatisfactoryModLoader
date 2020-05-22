// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGConnectionComponent.h"
#include "FGInventoryComponent.h"
#include "FGPipeConnectionComponent.generated.h"


#define FOR_EACH_PIPE_INLINE_COMPONENTS( COMPONENT_NAME ) \
	TInlineComponentArray<UFGPipeConnectionComponent*> pipeConnections; \
	GetComponents( pipeConnections ); \
	for( UFGPipeConnectionComponent* COMPONENT_NAME : pipeConnections )

/**
 * Type of pipe connections
 */
UENUM( BlueprintType )
enum class EPipeConnectionType : uint8
{
	PCT_ANY			UMETA( DisplayName = "Any" ),
	PCT_CONSUMER	UMETA( DisplayName = "Consumer" ),
	PCT_PRODUCER	UMETA( DisplayName = "Producer" ),
	PCT_SNAP_ONLY	UMETA( DisplayName = "Snap Only" ), // How its handled for factories, which also mentions it may need a refactor
	PCT_MAX			UMETA( Hidden )
};



//@todoPipes Move the base to its own header file

/**
 * Connection base used to link generic pipes together
 */
UCLASS( EditInlineNew, Blueprintable, ClassGroup = ( Custom ), Category = "Pipe" )
class FACTORYGAME_API UFGPipeConnectionComponentBase : public UFGConnectionComponent
{
	GENERATED_BODY()
public:
	UFGPipeConnectionComponentBase();

	// Begin ActorComponent interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void OnComponentDestroyed( bool isDestroyingHierarchy ) override;
	virtual void OnRegister() override;
	virtual void OnUnregister() override;
	// End ActorComponent interface

	// Begin save interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End save interface

	/** Set the conveyor clearance for this connection. */
	FORCEINLINE void SetConnectorClearance( float clearance ){ mConnectorClearance = clearance; }

	/** Return the clearance needed when routing a pipe from this connection. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Connection" )
	FORCEINLINE float GetConnectorClearance() const { return mConnectorClearance; }

	/**
	 * Set which connection this is connected to.
	 * @note Sets both ends of the connection.
	 * If there already a connection made we assert.
	 */
	virtual void SetConnection( class UFGPipeConnectionComponentBase* toComponent );

	/**
	 * Get which connection this is connected to.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Connection" )
	FORCEINLINE class UFGPipeConnectionComponentBase* GetConnection() const 
	{
		if( IsValid( mConnectedComponent ) ) 			
		{
			return mConnectedComponent;
		}
		else 	
		{
			return nullptr;
		}
	}

	/**
	 * Clear the connection on this component
	 * @note Clears both ends of the connection.
	 * If nothing is connected this does nothing.
	 */
	virtual void ClearConnection();


	/**
	 * Is this connection connected to anything.
	 * @return - true if connected; otherwise false. Always false if attached to hologram, snap only or bad index configuration.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Connection" )
	bool IsConnected() const;

	/** Check if the given connection can snap to this. */
	bool CanSnapTo( UFGPipeConnectionComponentBase* otherConnection ) const;
	/** Check if the given connection can connect to this. */
	bool CanConnectTo( UFGPipeConnectionComponentBase* otherConnection ) const;

	
	/** CheckCompatibility
	 * Checks the connection types and general compatibility of the connections. If the hologram is given it can report more specific issues as well, but otherwise the return value will tell weather the connections are compatible.
	 * This is not necessarily for connecting two connections, but rather to make sure that they can belong to the same system.
	 *
	 * @param	otherConnection - the connection to check against
	 * @param	buildStepOwner - [OPTIONAL] The hologram to report errors with construction disqualifiers to.
	 * 
	 * @return	bool - returns true if compatible and no errors reported
	 */
	 virtual bool CheckCompatibility( UFGPipeConnectionComponentBase* otherConnection, class AFGHologram* buildStepOwner ); 

	/** Set the connection type for this connection */
	void SetPipeConnectionType( EPipeConnectionType connectionType ) { mPipeConnectionType = connectionType; }

	/** Get the Pipe Connection type for this connection */
	EPipeConnectionType GetPipeConnectionType() const { return mPipeConnectionType; }

	/** Return the connectors world location with or without considering the clearance. */
	FVector GetConnectorLocation( bool withClearance = false ) const;

	/** Return the connectors world normal. */
	FVector GetConnectorNormal() const { return GetComponentRotation().Vector(); }

	/**
	 * Find overlapping connections that are compatible with this one.
	 */
	static UFGPipeConnectionComponentBase* FindCompatibleOverlappingConnection( class UFGPipeConnectionComponentBase* component, const FVector& location, float radius, UFGPipeConnectionComponentBase* lowPriorityConnection = nullptr);

	/**
	 * Returns an overlapped pipe connection. Does not take into account if it is a valid connection only if the connection is in the radius of the one passed in
	 */
	static UFGPipeConnectionComponentBase* FindOverlappingConnection( class UFGPipeConnectionComponentBase* component, const FVector& location, float radius, UFGPipeConnectionComponentBase* lowPriorityConnection = nullptr );

	void UpdateClientCachedConnection();
protected:
	/** Specifies the type of connection this is, used to determine attachment potential */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	EPipeConnectionType mPipeConnectionType;

	/** How long the connector is extending, indicates where the connected pipe may start turning. */
	UPROPERTY( EditDefaultsOnly, Category = "Connection" )
	float mConnectorClearance;

protected:
	UPROPERTY( EditDefaultsOnly )
	FName mPipeType = "Base"; //used to find matching types for snapping and so on

	/** Connection to another component. If this is set we're connected. */
	UPROPERTY( SaveGame )
	class UFGPipeConnectionComponentBase* mConnectedComponent;

	/** Light-weight connected indication for clients. */
	UPROPERTY( Replicated )
	bool mHasConnectedComponent = false;

public:
	FORCEINLINE ~UFGPipeConnectionComponentBase() = default;
};




/**
 * Connection used to link pipelines together
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPipeConnectionComponent : public UFGPipeConnectionComponentBase
{
	GENERATED_BODY()
public:
	UFGPipeConnectionComponent();

	// Begin ActorComponent Interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	// End ActorComponent Interface

	virtual bool CheckCompatibility( UFGPipeConnectionComponentBase* otherConnection, class AFGHologram* buildStepOwner ) override;

	// Begin Connection Interface
	virtual void ClearConnection() override;
	// End Connection Interface

	/** Get which pipe connection this is connected to. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Connection" )
	UFGPipeConnectionComponent* GetPipeConnection() const;

	/** Used by the pipe subsystem to update the network this is connected to. */
	int32 GetPipeNetworkID() const { return mPipeNetworkID; }

	/**
	* Called from begin play for buildables that implement the fluid integrant interface
	*/
	void SetFluidIntegrant( class IFGFluidIntegrantInterface* fluidIntegrant ) { mFluidIntegrant = fluidIntegrant; }

	/** 
	* @return The FluidIntegrant interface that this connection potentially belongs to. Can be null.
	*/
	class IFGFluidIntegrantInterface* GetFluidIntegrant() { return mFluidIntegrant; }

	/** 
	* Does this connection belong to a buildable that implements the Fluid Integrant Interface?
	*/
	bool HasFluidIntegrant() const { return mFluidIntegrant != nullptr; }

	/**
	* Set the item descriptor for this connection ( is defined by the network this connection belongs to )
	*/
	void SetFluidDescriptor( TSubclassOf< class UFGItemDescriptor > itemDescriptor );

	/**
	* Get item descriptor for this connections ( can be null )
	*/
	TSubclassOf< class UFGItemDescriptor > GetFluidDescriptor() const;

	/**
	 * Set the inventory associated with this connection
	 */
	void SetInventory( class UFGInventoryComponent* inventory );

	/**
	* Sets a specified index for the component to access on its assigned inventory, if it has one
	*/
	void SetInventoryAccessIndex( int32 index );

	/**
	* Get the specified index for a component to access its assigned inventory
	*/
	int32 GetInventoryAccessIndex() { return mInventoryAccessIndex; }

	/** Functions to move Items from and to an inventory component and a fluid integrant
	*	These must be called by owning buildables. I.e. The manufacturer informs its components to act
	*	Acts on an Inventory component and fluid integrant. This is independent of the Pipe Network fluid updates
	*	Calls the internal implementation after determining if it is the component on the destination buildable
	*/
	int32 Factory_PushPipeOutput( float dt, const FInventoryStack& stack );
	bool Factory_PullPipeInput( float dt, FInventoryStack& out_stack, TSubclassOf< UFGItemDescriptor > type, int32 maxQuantity = -1 );

	/** Actual implementation of PushPipeOutput */
	int32 Factory_Internal_PushPipeOutput( float dt, const FInventoryStack& stack );

	/** Actual implementation of PullPipeInput */
	bool Factory_Internal_PullPipeInput( float dt, FInventoryStack& out_stack, TSubclassOf< UFGItemDescriptor > type, int32 maxQuantity = -1 );


private:
	/** Used by the pipe subsystem to update the network this is connected to. */
	void SetPipeNetworkID( int32 networkID );

	/** OnRep to track changes and notify outer actors of changes 
	*@todoPipes This is a rather ugly necessity of the fluid descriptor residing on connections and being needed by pipelines
	*			The way its set up there is no reliable way for client pipelines to know when their fluid descriptor has been set				
	*/
	UFUNCTION()
	void OnRep_FluidDescriptor();

public: // MODDING EDIT: protected -> public
	/** The inventory of this connection. This can be null in many cases. */
    // MODDING EDIT VERY Experimental most buildings handle this on their own. Writing to it maybe crashes.
	UPROPERTY( BlueprintReadWrite, SaveGame )
	class UFGInventoryComponent* mConnectionInventory;

	/**
	 * The inventory index utilized by this connection ( -1 for none specified ). Only relevant if an inventory is set
	 * Unlike the Factory Connections this access index is also used to determine if a connection should be pushed to from manufacturing
	 * buildables. This is because fluids should belong to a single stack in an inventory and if none is specified then a pipe should
	 * not be eligible to receive liquid. There may be a better way to handle this but that is how its operating.
	 */
    //MODDING EDIT Experimental !!! Writing to it maybe crashes
	UPROPERTY( BlueprintReadWrite, SaveGame )
	int32 mInventoryAccessIndex;

	/**
	 * The network this connection is connected to. INDEX_NONE if not connected.
	 * @note - This ID may change at any time when changes occurs in the network. Do not save copies of it!
	 */
    // MODDING EDIT: BPReadOnly
	UPROPERTY( SaveGame, BlueprintReadOnly, VisibleAnywhere, Replicated, Category = "Connection" )
	int32 mPipeNetworkID;

	/**
	 * The Fluid Descriptor class this connection has. This is defined network wide. This is merely a cached value to save frequent lookups when pushing and pulling liquids
	 */
	//@todoPipes This is ugly and bad for performance.
	//           But on the server the descriptor is pushed from the subsystem when it changes.
	//           We cannot do that on the client cause it does not have a graph built.
	//           And the pipe network id gets wonky on the client as well... and
	//           we need this to work for the play test so for now lets go with ugly.
	// MODDING EDIT: BPReadOnly, VisibleAnywhere
    UPROPERTY( BlueprintReadOnly, VisibleAnywhere, ReplicatedUsing = OnRep_FluidDescriptor )
	TSubclassOf< class UFGItemDescriptor > mFluidDescriptor;

protected: // MODDING EDIT
	/**
	 * The fluid integrant this connection belongs to ( interface on the outer buildable ). Assigned in begin play if one exists.
	 * Can be null. Tex. For production buildings
	 */
	class IFGFluidIntegrantInterface* mFluidIntegrant;

private:
	friend class AFGPipeNetwork;

	/** Time debt since last push or pull ( only tracks unused quantities, does not act as a timer and thus will not increment while nothing is attempting to push or pull ) */
	float mPushOrPullTimeDebt;

	/** Cached value of mFluidToInventoryStackRate defined on the PipeSubsystem */
	int32 mCachedFluidToInventoryStackRate;

	/** Cached value of mInventoryStackToFluidRate defined on the PipeSubsystem */
	int32 mCachedInventoryStackToFluidRate;

	/** Cached Owner. Valid if owner is a pipeline. Null otherwise (Not a UPROPERTY because this component must have an owner and null is okay )*/
	class AFGBuildablePipeline* mCachedPipelineOwner;

public:
	FORCEINLINE ~UFGPipeConnectionComponent() = default;
};

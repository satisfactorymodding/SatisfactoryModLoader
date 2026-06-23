// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "Buildables/FGBuildable.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGVehiclePathNode.generated.h"

class USphereComponent;
struct FVehiclePathNavigationGraph;
struct FVehiclePathPointNavigationData;
class AFGVehiclePathSegment;
class UStaticMeshComponent;
class UBoxComponent;
class AFGVehicleSubsystem;

/** Vehicle path Nodes connect multiple path segments together */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGVehiclePathNode : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGVehiclePathNode();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin AFGBuildable interface
	virtual TSoftClassPtr<UFGMaterialEffect_Build> GetDismantleEffectTemplate_Implementation() const override { return nullptr; }
	virtual void PostSerializedFromBlueprint(bool isBlueprintWorld) override;
	// End AFGBuildable interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	// Begin IFGDismantleInterface
	virtual void GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const override;
	// End IFGDismantleInterface

	/** Returns the GUID of this path node. GUID uniquely identifies the path node on the client */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	FORCEINLINE FGuid GetPathNodeGUID() const { return mPathNodeGUID; }

	/** Returns the connections this connection is connected to */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	const TArray<AFGVehiclePathSegment*>& GetArrivingConnections() const { return ObjectPtrDecay( mArrivingConnections ); }

	/** Returns the connections this connection is connected to */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	const TArray<AFGVehiclePathSegment*>& GetLeavingConnections() const { return ObjectPtrDecay( mLeavingConnections ); }

	/** Returns true if this node has a connection that arrives to other node */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	bool HasConnectionArrivingToNode( const AFGVehiclePathNode* endNode ) const;

	/** Returns forward direction for this node as forced by the connections, returns empty optional when node has no connections */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	TOptional<FVector> GetNodeForcedForwardDirection() const;

	/** Utility function to gather all vehicle path nodes connected to this node (in either direction) */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	void GetConnectedNodes( TArray<AFGVehiclePathNode*>& out_connectedNodes ) const;

	/** Returns a connection starting at this node and ending at the target node, or nullptr */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	AFGVehiclePathSegment* FindConnectionArrivingToNode( const AFGVehiclePathNode* endNode ) const;

	/** Returns true if this path node is trivial, e.g. has only one (or no) arriving segment and only one (or no) leaving segments */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Node" )
	FORCEINLINE bool IsTrivialPathNode() const { return GetArrivingConnections().Num() <= 1 && GetLeavingConnections().Num() <= 1; } 

	/**
	 * Returns the ID of the path network this segment belongs to.
	 * Network IDs should not be used on the client as they are volatile and change with the network topology.
	 */
	FORCEINLINE int32 GetPathNetworkID() const { return mPathNetworkID; }

	/** Migrate connections from this node to a new node. This node will be removed */
	void MoveConnectionsToNode( AFGVehiclePathNode* newPathNode );

	// Internal functions used by vehicle path segments to attach themselves to path nodes. Do not call manually.
	void AddArrivingConnection( AFGVehiclePathSegment* pathSegment );
	void AddLeavingConnection( AFGVehiclePathSegment* pathSegment );
	void RemoveArrivingConnection( AFGVehiclePathSegment* pathSegment, bool bAllowNodeCleanup = true );
	void RemoveLeavingConnection( AFGVehiclePathSegment* pathSegment, bool bAllowNodeCleanup = true );
	
	// Internal functions used by the vehicle subsystem to manage the path network associations and visualization state for the vehicle nodes
	void SetPathNetworkID(int32 newPathNetworkID);
protected:
	/** Returns true if this node is persistent (should not be removed when it has no connections) */
	virtual bool IsPersistentNode() const { return false; }
	/** Called on the server and the client when node connections change */
	virtual void OnNodeConnectionsChanged();

	void OnVehicleSubsystemValid();
	UFUNCTION()
	void OnRep_NodeConnections();
	
	void UpdateOrCleanupConnectionNode( bool bAllowNodeCleanup );

	/** GUID of this path node, does not change once the path node is constructed */
	UPROPERTY( SaveGame, Replicated )
	FGuid mPathNodeGUID;

	/** ID of the path network this path segment belongs to, on the server */
	UPROPERTY( SaveGame, Replicated )
	int32 mPathNetworkID{INDEX_NONE};

	/** Path segments entering this node */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_NodeConnections )
	TArray<TObjectPtr<AFGVehiclePathSegment>> mArrivingConnections;

	/** Path segments leaving this node */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_NodeConnections )
	TArray<TObjectPtr<AFGVehiclePathSegment>> mLeavingConnections;
};

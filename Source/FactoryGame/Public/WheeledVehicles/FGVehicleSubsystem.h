// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSubsystem.h"
#include "FGSaveInterface.h"
#include "FGVehiclePathSegment.h"
#include "FGVehicleSubsystem.generated.h"

class UFGVehicleDetectionComponent;
class AFGStandaloneVehiclePathNode;
class UFGVehiclePathPreset;
class AFGWheeledVehicleIdentifier;
class UFGVehicleSubsystemReplicationComponent;
class AFGDockingStationIdentifier;
struct FVehiclePathVisualizationHandle;
class UFGVehicleDescriptor;
struct FVehiclePathNavigationGraph;
class USplineMeshComponent;
class AFGVehiclePathNode;
class AFGVehiclePathSegment;

/** Represents information about a path node actor that might not be available on the client in the world */
USTRUCT( BlueprintType )
struct FVehiclePathNetworkNodeData
{
	GENERATED_BODY()
	
	/** GUID of this vehicle path node */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Node" )
	FGuid PathNodeGuid;

	/** Location of this vehicle path node in the world */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Node" )
	FVector PathNodeLocation{ForceInit};

	friend FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkNodeData& NodeData);
};

/** Represents information about a path segment actor that might not be available on the client in the world */
USTRUCT( BlueprintType )
struct FVehiclePathNetworkSegmentData
{
	GENERATED_BODY()

	/** Index of the node from which this segment starts */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	int32 FromNodeIndex{INDEX_NONE};

	/** Index of the path node to which this segment arrives */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	int32 ToNodeIndex{INDEX_NONE};

	/** Length of this vehicle path segment */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	float SegmentLength{0.0f};

	/** Spline points for this path segment in world space */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	TArray<FSplinePointData> SplinePoints;

	/** Mask that determines whenever this segment can be traversed by the given vehicle type. Use FGVehiclePathNetwork::CanVehicleTraverseSegment to evaluate this mask */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	int64 VehicleTraversabilityMask{0};

	/** Virtual length of the segment (length with additional multiplier applied based on the average climb angle) for fuel consumption calculation */
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Vehicle Path Segment" )
	TArray<float> VehicleSegmentVirtualLength;

	friend FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkSegmentData& SegmentData);
};

/** Replication data used to replication path networks from the server to the client */
struct FVehiclePathNetworkReplicationData
{
	int32 PathNetworkID{INDEX_NONE};
	TArray<UFGVehiclePathPreset*> VehicleTypes;
	TArray<FVehiclePathNetworkNodeData> PathNodes;
	TArray<FVehiclePathNetworkSegmentData> PathSegments;

	friend FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkReplicationData& ReplicationData);
};

/** Replication data used to update the traversability of the vehicle path network on the client */
struct FVehiclePathNetworkTraversabilityReplicationData
{
	int32 PathNetworkID{INDEX_NONE};
	FGuid FromNodeGuid;
	FGuid ToNodeGuid;
	uint64 NewVehicleTraversabilityMask{0};
	TArray<float> VehicleSegmentVirtualLength;

	friend FArchive& operator<<(FArchive& Ar, FVehiclePathNetworkTraversabilityReplicationData& ReplicationData);
};

/**
 * Path network represents a collection of path nodes interconnected with vehicle path segments
 * Path networks are created on the server and re-created when network topology changes
 * Path networks and their topology are replicated to the clients in compact form through Reliable Messaging even when their individual actors are not
 */
UCLASS( BlueprintType, Within = FGVehicleSubsystem )
class FACTORYGAME_API UFGVehiclePathNetwork : public UObject, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	// Begin IFGSaveInterface interface
	virtual bool ShouldSave_Implementation() const override { return true; }
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface interface
	
	/**
	 * Returns the ID of this path network.
	 * Network IDs should not be used on the client as they are volatile and change with the network topology.
	 */
	FORCEINLINE int32 GetNetworkID() const { return mNetworkID; }

	/** Returns path nodes contained within the network. Returns valid results on both the server and the clients */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	const TArray<FVehiclePathNetworkNodeData>& GetPathNodes() const { return mPathNodeData; }

	/** Returns path segments contained within the network. Returns valid results on both the server and the clients */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	const TArray<FVehiclePathNetworkSegmentData>& GetPathSegments() const { return mPathSegmentData; }

	/** Returns path node at the particular index */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	FVehiclePathNetworkNodeData GetPathNodeAtIndex( int32 pathNodeIndex ) const;

	/** Returns path segment at the particular index */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	FVehiclePathNetworkSegmentData GetPathSegmentAtIndex( int32 pathSegmentIndex ) const;

	/** Attempts to find the path node with the given Guid and returns its index if it is found. Returns -1 if not found */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	int32 FindPathNodeIndexByGuid( const FGuid& pathNodeGuid ) const;

	/** Attempts to find an index of the path between two path nodes. Returns -1 if not found */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	int32 FindPathIndexBetweenPathNodes( const int32 fromNodeIndex, const int32 toNodeIndex ) const;

	/** Returns true if the given vehicle can traverse the node with the provided path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	bool CanVehicleTraverseSegment( const FVehiclePathNetworkSegmentData& segmentData, const UFGVehiclePathPreset* vehiclePathPreset ) const;

	/** Calculates fuel consumption in MW necessary for the vehicle of the given type to pass the given segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	float GetVehicleFuelConsumptionForSegment( const FVehiclePathNetworkSegmentData& segmentData, const TSubclassOf<AFGWheeledVehicle>& vehicleType ) const;

	/** Returns the changelist of the traversability status of this network. This is incremented every time network traversability changes */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	FORCEINLINE int32 GetNetworkPathTraversabilityChangelist() const { return mPathNetworkTraversabilityChangelist; }

	/** Attempts to find a path for the given vehicle type from the given node to another node. Returns true and the nodes that lead to that path if found, and false otherwise */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Path Network" )
	bool FindVehiclePath( const FGuid& fromNodeGuid, const FGuid& toNodeGuid, const UFGVehiclePathPreset* vehicleType, TArray<FGuid>& out_vehiclePath ) const;

	/** Resolves all docking stations contained within this path network. This function is not constant time, so use with caution (although it is very fast) */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Path Network" )
	void PopulateNetworkStations( TArray<AFGDockingStationIdentifier*>& out_dockingStations ) const;

	/** Resolves all vehicles currently part of the path network. This function is not constant time, so use with caution (although it is very fast) */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Path Network" )
	void PopulateNetworkVehicles( TArray<AFGWheeledVehicleIdentifier*>& out_vehicles ) const;
	
	/**
	 * Returns all the nodes contained in this network on server. Will return empty list on client.
	 * Note that this can contain invalid elements if the network is pending a rebuild.
	 */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path Network" )
	const TArray<AFGVehiclePathNode*>& GetNetworkElementsOnServer() const { return ObjectPtrDecay( mNetworkNodes ); }
protected:
	friend class AFGVehicleSubsystem;

	/** Marks this network as structurally modified. It will be rebuilt on the end of the frame. Must only be called on the server */
	FORCEINLINE void MarkNetworkStructurallyModified() { mNetworkTopologyNeedsRebuild = true; }
	FORCEINLINE bool NeedsNetworkTopologyRebuild() const { return mNetworkTopologyNeedsRebuild; }
	bool IsNetworkEmptyOnServer() const;

	/** Initializes this network with a network ID and a list of elements */
	void InitializeNewNetwork( int32 newNetworkID, const TArray<AFGVehiclePathNode*>& newNetworkElements );
	/** Initializes this network from the replication data */
	void InitializeFromReplicationData( const FVehiclePathNetworkReplicationData& replicationData );
	/** Updates path network traversability directly */
	bool UpdatePathTraversabilityDirectly( const FGuid& fromNode, const FGuid& toNode, uint64 newTraversabilityMask, const TArray<float>& vehicleSegmentVirtualLength );

	/** Resets network ID on this network. Network must be empty before this function can be called */
	void ResetNetworkID();
	/** Removes the node from the network and immediately marks it as structurally modified */
	void RemoveNetworkElement( AFGVehiclePathNode* networkElement );
	void BulkRemoveNetworkElements( const TSet<AFGVehiclePathNode*>& networkElements );
	/** Updates the traversability of the path segment and returns the update data */
	bool UpdateNetworkPathTraversability( const AFGVehiclePathSegment* networkPathSegment, FVehiclePathNetworkTraversabilityReplicationData& out_traversabilityUpdateData );
	
	/** Populates replication data with the data from this path network */
	FVehiclePathNetworkReplicationData ToReplicationData() const;
	
	/** Called to regenerate the cached data from the path nodes and segments contained in this network */
	void RegenerateCachedDataOnServer();

	/** Called to regenerate the navigation graph for this network. Will be called upon network creation and when the network is loaded from a save game */
	void RegenerateNavigationGraph();
	/** Calculates the traversability mask from the given path segment */
	uint64 CalculateTraversabilityMask( const AFGVehiclePathSegment* networkPathSegment, TArray<float>& out_vehicleSegmentVirtualLength ) const;
	
	/** ID of this path network. Does not change over the lifespan of the network */
	UPROPERTY( SaveGame )
	int32 mNetworkID{INDEX_NONE};
	
	/** All the nodes contained in this path network. Does not change over the lifespan of the network */
	UPROPERTY( SaveGame )
	TArray<TObjectPtr<AFGVehiclePathNode>> mNetworkNodes;

	/** Navigation graph for this path network. The graph is immutable and can be used off the game thread freely */
	TSharedPtr<FVehiclePathNavigationGraph> mNavigationGraph;

	/** Bumped up each time traversal status of any path in the network changes, to force the vehicles to rebuild their active paths when network traversability changes, but the topology does not */
	UPROPERTY( SaveGame )
	int32 mPathNetworkTraversabilityChangelist{0};

	/** True if network topology rebuild is needed and will be done at the end of the frame */
	UPROPERTY( SaveGame )
	bool mNetworkTopologyNeedsRebuild{false};

	/** Order of bits in the vehicle path traversability masks of this path network */
	UPROPERTY()
	TArray<TObjectPtr<UFGVehiclePathPreset>> mPathTraversabilityVehicleOrder;
	/** Lookup of vehicle type index by vehicle type */
	UPROPERTY()
	TMap<TObjectPtr<UFGVehiclePathPreset>, int32> mVehicleTypeIndexLookup;

	/** Path node data cached from the path nodes contained within the network */
	TArray<FVehiclePathNetworkNodeData> mPathNodeData;
	/** Lookup of the vehicle path index by the node GUID */
	TMap<FGuid, int32> mPathNodeIndexLookup;
	
	/** Path segment data cached from the path segments contained within the network */
	TArray<FVehiclePathNetworkSegmentData> mPathSegmentData;
	/** Lookup of the vehicle path segment index by the IDs of the from and to nodes */
	TMap<TPair<int32, int32>, int32> mPathSegmentIndexLookup;
};

// No initializers to keep it a plain old data type
struct FVehicleTriggerBoxOctreeElement
{
	FBoxCenterAndExtent BoundingBox;
	TWeakObjectPtr<UFGVehicleDetectionComponent> Object;
};

struct FVehicleTriggerBoxSemantics
{
	// When a leaf gets more than this number of elements, it will split itself into a node with multiple child leaves
	enum { MaxElementsPerLeaf = 16 };
	enum { MinInclusiveElementsPerNode = 7 };
	enum { MaxNodeDepth = 20 };

	using FOctree = TOctree2<FVehicleTriggerBoxOctreeElement, FVehicleTriggerBoxSemantics>;
	typedef TInlineAllocator<MaxElementsPerLeaf> ElementAllocator;

	static const FBoxCenterAndExtent& GetBoundingBox(const FVehicleTriggerBoxOctreeElement& Element) { return Element.BoundingBox; }
	static bool AreElementsEqual(const FVehicleTriggerBoxOctreeElement& A, const FVehicleTriggerBoxOctreeElement& B) { return A.Object == B.Object; }
	static void SetElementId(FOctree& Octree, const FVehicleTriggerBoxOctreeElement& Element, FOctreeElementId2 OctreeElementID);
};

struct FVehicleTriggerBoxOctree : TOctree2<FVehicleTriggerBoxOctreeElement, FVehicleTriggerBoxSemantics>
{
	FVehicleTriggerBoxOctree() = default;
	FVehicleTriggerBoxOctree(const FVector& InOrigin, const FVector::FReal InExtent) : TOctree2(InOrigin, InExtent) {};
};

/**
 * Subsystem for all vehicles, mainly used for wheeled vehicles.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGVehicleSubsystem : public AFGSubsystem, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGVehicleSubsystem();

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor interface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override { return true; }
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFSaveInterface

	/** Get the vehicle subsystem */
	static AFGVehicleSubsystem* Get( const UWorld* world );

	/** Get the vehicle subsystem from a world context, this should always return something unless you call it really early. */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem", DisplayName = "Get Vehicle Subsystem", Meta = ( DefaultToSelf = "worldContext" ) )
	static AFGVehicleSubsystem* Get( const UObject* worldContext );

	/** Allocates a new default vehicle path node. Actor will not be automatically connected to any segments */
	AFGVehiclePathNode* CreateNewVehiclePathNode( const FVector& pointLocation, const AFGBuildable* sourceBuildable ) const;

	/** Returns a list of all vehicle path networks currently present */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem" )
	const TArray<UFGVehiclePathNetwork*>& GetAllPathNetworks() const { return ObjectPtrDecay( mPathNetworks ); }

	/**
	 * Returns the network with the given ID, or nullptr if it is not found
	 * Network IDs should not be used on the client as they are volatile and change with the network topology.
	 */
	UFGVehiclePathNetwork* FindNetworkByID( int32 networkID ) const;

	/** Attempts to find a path network by the GUID of the given path node. This functionality iterates over networks so try to use not too frequently (it is still very fast though, but not "free") */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Subsystem" )
	UFGVehiclePathNetwork* FindNetworkByPathNodeGuid( const FGuid& pathNodeGuid ) const;

	/** Returns all docking stations currently present in the world */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem" )
	const TArray<AFGDockingStationIdentifier*>& GetDockingStations() const { return ObjectPtrDecay( mAllDockingStations ); }

	/** Returns all wheeled vehicles currently present in the world */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem" )
	const TArray<AFGWheeledVehicleIdentifier*>& GetAllVehicles() const { return ObjectPtrDecay( mAllVehicles ); }

	/** Attempts to find the path node actor by the given GUID if it has been replicated. Returns nullptr if the actor has not been replicated to the client yet or does not exist */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem" )
	AFGVehiclePathNode* FindReplicatedPathNodeByGuid( const FGuid& pathNodeGuid ) const;

	/** If the given vehicle path node GUID represents a docking station, returns the information about that docking station */
	UFUNCTION( BlueprintPure, Category = "Vehicle Subsystem" )
	AFGDockingStationIdentifier* FindDockingStationIdentifierForPathNodeGuid( const FGuid& pathNodeGuid ) const;

	/** Invalidates all vehicle paths in the given volume, forcing their re-validation */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Subsystem" )
	void InvalidateVehiclePathsInVolume( const FBox& invalidationVolume );

	/** Like InvalidateVehiclePathsInVolume, but does processing in bulk */
	UFUNCTION( BlueprintCallable, Category = "Vehicle Subsystem" )
	void InvalidateVehiclePathsInVolumeList( const TArray<FBox>& invalidationVolumeList );

	/** Adds path visualization request to the active list */
	void RequestVehiclePathVisualization( const TSharedPtr<FVehiclePathVisualizationHandle>& pathVisualizationInfo );
	/** Removes path visualization info from the active list */
	void RemoveVehiclePathVisualization( const TSharedPtr<FVehiclePathVisualizationHandle>& pathVisualizationInfo );
	/** Requests vehicle path segment visualization to be refreshed */
	void RequestPathSegmentVisualizationUpdate( AFGVehiclePathSegment* pathSegment );
	/** Requests vehicle path node visualization to be refreshed */
	void RequestPathNodeVisualizationUpdate( AFGStandaloneVehiclePathNode* pathNode );
	/** Requests full visualization updates across all vehicle path segments and nodes */
	void RequestFullVisualizationUpdate();

	// Called by path nodes and path segment when their topology or traversability status changes
	void NotifyNodeTopologyChanged( AFGVehiclePathNode* networkElement );
	void NotifyPathTraversabilityChanged( const AFGVehiclePathSegment* networkSegment );

	// Functions called by various vehicle subsystem-managed actors on BeginPlay to register themselves with the system
	void AddPathSegment( AFGVehiclePathSegment* pathSegment );
	void RemovePathSegment( AFGVehiclePathSegment* pathSegment );
	void InvalidateVehiclePathSegment( AFGVehiclePathSegment* pathSegment );
	void AddPathNode( AFGVehiclePathNode* pathNode );
	void RemovePathNode( AFGVehiclePathNode* pathNode );
	void AddDockingStation( AFGDockingStationIdentifier* stationIdentifier );
	void RemoveDockingStation( AFGDockingStationIdentifier* stationIdentifier );
	void AddVehicle( AFGWheeledVehicleIdentifier* vehicleIdentifier );
	void RemoveVehicle( AFGWheeledVehicleIdentifier* vehicleIdentifier );
	void AddReplicationComponent( UFGVehicleSubsystemReplicationComponent* replicationComponent );
	void RemoveReplicationComponent( UFGVehicleSubsystemReplicationComponent* replicationComponent );
	void AddGenericVehicle( AFGVehicle* vehicle );
	void RemoveGenericVehicle( AFGVehicle* vehicle );
	void AddVehicleTriggerBox( UFGVehicleDetectionComponent* vehicleTriggerBox );
	void RemoveVehicleTriggerBox( UFGVehicleDetectionComponent* vehicleTriggerBox );

	// Internal replication related functions
	void PopulateInitialNetworkReplicationData( TArray<FVehiclePathNetworkReplicationData>& out_replicationData ) const;
	void InitializeNetworksFromReplicationData( const TArray<FVehiclePathNetworkReplicationData>& replicationData );
	void RemoveNetworkFromReplicationData( int32 networkID );
	void AddNetworkFromReplicationData( const FVehiclePathNetworkReplicationData& replicationData );
	void UpdateNetworkTraversabilityFromReplicationData( const FVehiclePathNetworkTraversabilityReplicationData& replicationData );

	TSubclassOf<AFGVehiclePathSegment> FindPathTypeForLegacyPath( const UFGVehiclePathPreset* pathPreset ) const;
protected:
	static TArray<AFGVehiclePathNode*> ExplodeNode( AFGVehiclePathNode* seedElement, TSet<AFGVehiclePathNode*>& exploredNodeSet );

	void AddNetworkElement( AFGVehiclePathNode* networkElement );
	void RemoveNetworkElement( AFGVehiclePathNode* networkElement ) const;
	void CleanNetworkIDOnElements( const TArray<AFGVehiclePathNode*>& networkElements );
	void CreateNewNetworkOnServer( const TArray<AFGVehiclePathNode*>& newNetworkElements );
    void RemoveNetworkOnServer( UFGVehiclePathNetwork* network );
	void RebuildDirtyNetworks();
	void UpdateVehiclePathVisualization();
	void RebuildInvalidatedPathSegments();
	void UpdateVehiclePlayerProximity();
	void TickPendingVehicleVisualizationUpdates();
	void TickVehicleAutopilot( float deltaTime );

	/** Class of the default vehicle path node created for vehicle path segments */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Subsystem" )
	TSubclassOf<AFGVehiclePathNode> mDefaultVehiclePathNodeClass;

	/** Class of the legacy target nodes used in save games. Here to force it to be cooked since it is used in old save games */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Subsystem" )
	TSubclassOf<class AFGTargetPoint> mLegacyTargetNodeClass;

	/** Given a path preset, returns a class of the vehicle path that should be created from a legacy path using that path preset */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Subsystem" )
	TMap<TObjectPtr<UFGVehiclePathPreset>, TSubclassOf<AFGVehiclePathSegment>> mLegacyPathConversionMap;

	/** Maximum amount of vehicle proximity checks to handle per frame */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Subsystem" )
	int32 mMaxVehicleProximityChecksPerFrame{10};

	/** All path nods registered to the system, used for visualization. Valid on the client as well */
	UPROPERTY()
	TSet<TObjectPtr<AFGVehiclePathNode>> mAllPathNodes;

	/** All path segments currently registered to the vehicle subsystem. Valid on the client as well */
	UPROPERTY()
	TSet<TObjectPtr<AFGVehiclePathSegment>> mAllPathSegments;
	
	UPROPERTY()
	TArray<TObjectPtr<AFGDockingStationIdentifier>> mAllDockingStations;

	UPROPERTY()
	TArray<TObjectPtr<AFGWheeledVehicleIdentifier>> mAllVehicles;

	TSharedPtr<FVehiclePathVisualizationHandle> mActiveVisualizationInfo;
	TArray<TSharedPtr<FVehiclePathVisualizationHandle>> mRegisteredVisualizationInfoList;
	bool mNeedsVisualizationInfoUpdate{false};
	bool mForceVisualizationInfoUpdate{false};

	/** ID for the next path network to be created */
	UPROPERTY( SaveGame )
	int32 mCurrentNetworkID{0};

	/** All path networks currently existing */
	UPROPERTY( SaveGame )
	TArray<TObjectPtr<UFGVehiclePathNetwork>> mPathNetworks;

	/** Lookup of path network by integer ID */
	UPROPERTY()
	TMap<int32, TObjectPtr<UFGVehiclePathNetwork>> mPathNetworkByIDLookup;

	/** Newly created path nodes that have not had their network assigned yet. List is processed next tick */
	UPROPERTY()
	TArray<TObjectPtr<AFGVehiclePathNode>> mPendingNetworkElements;

	/** Lookup of vehicle path nodes by their ID */
	UPROPERTY()
	TMap<FGuid, TObjectPtr<AFGVehiclePathNode>> mPathNodeByIDLookup;

	/** Lookup of the docking stations associated with the given node GUID */
	UPROPERTY()
	TMap<FGuid, TObjectPtr<AFGDockingStationIdentifier>> mDockingStationByIDLookup;

	/** Registered replication components to notify of network creations and removal */
	UPROPERTY()
	TArray<TObjectPtr<UFGVehicleSubsystemReplicationComponent>> mReplicationComponents;

	/** Path segments that were invalidated this frame and will be rebuilt next frame */
	UPROPERTY()
	TSet<TObjectPtr<AFGVehiclePathSegment>> mInvalidatedPathSegments;

	bool mReceivedInitialNetworkReplicationData{false};

	/** True if we should do a sanitization pass on the vehicle route tables next tick */
	bool mNeedsToSanitizeVehicleRouteTables{false};

	/** True if we have handled legacy path conversion already */
	UPROPERTY( SaveGame )
	bool mConvertedLegacyPaths{false};

	/** All vehicles registered for player proximity updates */
	UPROPERTY()
	TArray<TObjectPtr<AFGVehicle>> mGenericVehicles;
	int32 mCurrentGenericVehicleIndex{0};

	/** Octree for all vehicle trigger boxes relevant for current vehicles */
	FVehicleTriggerBoxOctree mVehicleTriggerBoxOctree;
	UPROPERTY()
	TSet<TObjectPtr<UFGVehicleDetectionComponent>> mCurrentlyActiveTriggerBoxTemplates;
	uint64 mTriggerBoxUpdateFrameCounter{0};

	TSharedPtr<FVehiclePathVisualizationHandle> mPendingUpdateVisualizationInfo;
	bool mDispatchingFullVisualizationUpdate{false};
	UPROPERTY()
	TArray<TObjectPtr<AFGVehiclePathSegment>> mVehiclePathSegmentsPendingUpdate;
	UPROPERTY()
	TArray<TObjectPtr<AFGStandaloneVehiclePathNode>> mVehiclePathNodesPendingUpdate;
};

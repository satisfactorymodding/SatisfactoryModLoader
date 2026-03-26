// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGNetSignificanceInterface.h"
#include "Buildables/FGBuildable.h"
#include "FGSignificanceInterface.h"
#include "FGVehiclePathValidation.h"
#include "Components/SplineComponent.h"
#include "FGVehiclePathSegment.generated.h"

class UFGVehiclePathPreset;
class AFGCharacterPlayer;
class UFGVehicleDescriptor;
class AFGVehicleSubsystem;
class USplineMeshComponent;
class UBoxComponent;
class AFGVehiclePathNode;
class AFGWheeledVehicle;
class AFGVehiclePathSegment;

USTRUCT()
struct FACTORYGAME_API FVehiclePathSegmentValidationData
{
	GENERATED_BODY()

	UPROPERTY( SaveGame )
	TObjectPtr<UFGVehiclePathPreset> PathPreset;

	UPROPERTY( SaveGame )
	int32 PathPresetVersionNumber{0};

	UPROPERTY( SaveGame )
	FVehiclePathValidationInfo ValidationInfo;
};

struct FACTORYGAME_API FVehiclePathVisualizationHandle final : FGCObject
{
	/** Info with the highest priority is used for visualization */
	int32 Priority{0};

	/** Types of vehicles to validate paths for. Only used when vehicle class override is not set */
	TArray<TObjectPtr<UFGVehiclePathPreset>> VisualizationPresets;

	/** True if this visualization info has been changed since its registration and needs the visualization to be updated */
	bool bNeedsVisualizationInfoUpdate{false};

	// Begin FGCObject interface
	virtual FString GetReferencerName() const override;
	virtual void AddReferencedObjects(FReferenceCollector& Collector) override;
	// End FGCObject interface
};

struct FVehiclePathVisualizationInfo
{
	/** Path validation info to be visualized (empty if not visualizing path validation) */
	TOptional<FVehiclePathValidationInfo> PathValidationInfo;

	/** Only used when there is no path validation config or info. True if the path is traversable for the current visualization preset, false otherwise */
	bool bIsSegmentRelevant{true};

	/** True if this segment is a dead end and should show as a warning */
	bool bIsSegmentDeadEnd{false};

	/** True if this segment intersects with other segments of the path */
	bool bIsSegmentAnIntersection{false};

	/** True if the segment is highlighted for dismantle with the dismantle outline */
	bool bIsSegmentHighlightedForDismantle{false};

	/** True if the node this path is leaving from a junction node, e.g. a node with more than one connection */
	bool bIsLeavingNodeJunctionOrDeadEnd{false};
	/** True if the node this path is arriving to is a junction node, e.g. a node with more than one connection */
	bool bIsArrivingNodeJunctionOrDeadEnd{false};

	/** True if this is a legacy path segment */
	bool bIsLegacyPathSegment{false};
	/** Maximum path visualization distance as currently configured in the settings. -1.0f = infinite */
	float MaxPathVisualizationDistance{-1.0f};

	friend bool operator==( const FVehiclePathVisualizationInfo& A, const FVehiclePathVisualizationInfo& B )
	{
		return A.PathValidationInfo == B.PathValidationInfo && A.bIsSegmentRelevant == B.bIsSegmentRelevant &&
			A.bIsSegmentDeadEnd == B.bIsSegmentDeadEnd && A.bIsSegmentAnIntersection == B.bIsSegmentAnIntersection &&
			A.bIsSegmentHighlightedForDismantle == B.bIsSegmentHighlightedForDismantle &&
			A.bIsLeavingNodeJunctionOrDeadEnd == B.bIsLeavingNodeJunctionOrDeadEnd && A.bIsArrivingNodeJunctionOrDeadEnd == B.bIsArrivingNodeJunctionOrDeadEnd &&
			A.bIsLegacyPathSegment == B.bIsLegacyPathSegment &&
			A.MaxPathVisualizationDistance == B.MaxPathVisualizationDistance;
	}
};

/** Represent a single shared reservation of the path block */
struct FACTORYGAME_API FVehiclePathBlockSharedReservation : TSharedFromThis<FVehiclePathBlockSharedReservation>
{
	TWeakObjectPtr<AFGVehiclePathSegment> ReservedSegment;
	int32 ReservedPathBlockIndex{INDEX_NONE};
	TWeakPtr<struct FVehiclePathBlockExclusiveReservation> OwnerReservation;
};

/** Represent a single unique reservation of the path block */
struct FACTORYGAME_API FVehiclePathBlockExclusiveReservation : TSharedFromThis<FVehiclePathBlockExclusiveReservation>
{
	TWeakObjectPtr<AFGVehiclePathSegment> ReservedSegment;
	int32 ReservedPathBlockIndex{INDEX_NONE};
	TWeakObjectPtr<const AFGWheeledVehicle> OwnerVehicle;
	TArray<TSharedPtr<FVehiclePathBlockSharedReservation>> SharedReservations;

	/** Releases all shared reservations owned by this exclusive reservation */
	void ReleaseAllSharedReservations_ThreadSafe();

	/** Releases this exclusive reservation */
	void ReleaseExclusiveReservation_ThreadSafe();
};

USTRUCT()
struct FACTORYGAME_API FVehiclePathBlockReference
{
	GENERATED_BODY()

	/** Segment that owns the given path block */
	UPROPERTY( SaveGame )
	TObjectPtr<AFGVehiclePathSegment> Segment;

	/** Index of the path block on the given segment */
	UPROPERTY( SaveGame )
	int32 PathBlockIndex{INDEX_NONE};

	friend bool operator==( const FVehiclePathBlockReference& A, const FVehiclePathBlockReference& B )
	{
		return A.Segment == B.Segment && A.PathBlockIndex == B.PathBlockIndex;
	}

	friend uint32 GetTypeHash( const FVehiclePathBlockReference& Value )
	{
		return HashCombineFast( GetTypeHash( Value.Segment ), GetTypeHash( Value.PathBlockIndex ) );
	}

	/** Resolved a reference to the block, returns nullptr if the reference is not valid */
	const struct FVehiclePathBlock* ResolveConst() const;
};

/** Represents a vehicle path block, a unit of path reservation */
USTRUCT()
struct FACTORYGAME_API FVehiclePathBlock
{
	GENERATED_BODY()

	/** All blocks that are overlapping this block */
	UPROPERTY( SaveGame )
	TArray<FVehiclePathBlockReference> OverlappingBlocks;

	/** Shared reservations that currently exist on this block */
	TArray<TSharedPtr<FVehiclePathBlockSharedReservation>> SharedReservations;
	/** Exclusive reservations that currently exist on this block */
	TArray<TSharedPtr<FVehiclePathBlockExclusiveReservation>> ExclusiveReservations;
};

UCLASS( Blueprintable )
class FACTORYGAME_API AFGVehiclePathSegment : public AFGBuildable, public IFGSignificanceInterface, public IFGNetSignificanceInterface
{
	GENERATED_BODY()
public:
	AFGVehiclePathSegment();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Begin AActor interface
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
#if WITH_EDITOR
	virtual bool CanVisualizeBlueprintAsset() const override;
#endif
	// End AActor interface

	// Begin AFGBuildable interface
	virtual void PostSerializedFromBlueprint(bool isBlueprintWorld = false) override;
	virtual TSoftClassPtr<UFGMaterialEffect_Build> GetDismantleEffectTemplate_Implementation() const override { return nullptr; }
	virtual FBox CalculateBounds() const override;
	// End AFGBuildable interface

	// Begin IFGSaveInterface
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	// End IFGSaveInterface

	// Begin IFGDismantleInterface
	virtual void GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const override;
	virtual void TogglePendingDismantleMaterial(bool enabled) override;
	// End IFGDismantleInterface

	// Begin IFGClearanceInterface
	virtual void GetClearanceData_Implementation( TArray<FFGClearanceData>& out_data ) const override;
	// End IFGClearanceInterface

	// Begin IFGSignificanceInterface
	virtual float GetSignificanceRange_Implementation() const override;
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	// End IFGSignificanceInterface

	// Begin IFGNetSignificanceInterface
	virtual float GetNetSignificanceRange_Implementation() const override;
	virtual void GainedNetSignificance_Implementation() override;
	virtual void LostNetSignificance_Implementation() override;
	// End IFGNetSignificanceInterface

	/** Returns the spline component for this path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE USplineComponent* GetSplineComponent() const { return mSplineComponent; }

	/** Returns true if the segment is significant to any player in the session */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE bool GetIsNetSignificant() const { return mIsNetSignificant; }

	/** Returns true if the segment is significant to the local player */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE bool GetIsSignificantToLocalPlayer() const { return mIsSignificantForLocalPlayer; }

	/** Returns the path validation data for the given vehicle type for this path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	bool GetValidationDataForPreset( const UFGVehiclePathPreset* pathPreset, FVehiclePathValidationInfo& out_validationInfo ) const;

	/** Returns true if this path is valid for the given vehicle type */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	bool IsPathValidForPreset( const UFGVehiclePathPreset* pathPreset ) const;

	/** Returns raw validation data for this segment */
	FORCEINLINE const TArray<FVehiclePathSegmentValidationData>& GetPathSegmentValidationData() const { return mValidationData; }

	/** Returns the path node used as an entry point to this path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE AFGVehiclePathNode* GetStartNode() const { return mStartNode; }

	/** Returns the path node used as an exit point from this path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE AFGVehiclePathNode* GetEndNode() const { return mEndNode; }

	/** Returns the GUID of the path start node for this segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE FGuid GetStartPathNodeGuid() const { return mStartPathNodeGuid; }

	/** Returns the extent of the collision around the spline. Collision is virtualized, there are no colliders for path segment unless visualization mode is requested */
	FORCEINLINE float GetCollisionExtent() const { return mCollisionExtent; }

	/** Vehicle types that are allowed to traverse this path segment */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FORCEINLINE TArray<UFGVehiclePathPreset*> GetAllowedVehicleTypes() const { return ObjectPtrDecay( mAllowedVehicleTypes ); }

	/** Returns the vehicles currently traversing this path segment */
	const TArray<AFGWheeledVehicle*>& GetVehicles() const { return ObjectPtrDecay( mVehicles ); }

	/** Returns the extents of the largest vehicle allowed on this path */
	UFUNCTION( BlueprintPure, Category = "Vehicle Path" )
	FVector CalculateLargestAllowedVehicleExtents() const;

	/**
	 * Rebuilds the path validation data for this segment immediately.
	 * Expensive function to call. Prefer AFGVehicleSubsystem::InvalidateVehiclePathsInVolume which does bath processing and splits the work over multiple frames instead
	 * Note that this function only performs work if the actor is significant, as it relies on the collision data around the path being streamed in.
	 */
	void ImmediateRebuildPathValidationData();

	// Called by the vehicles that traverse this path segment to register them to the segment
	void AddVehicle( AFGWheeledVehicle* newVehicle );
	void RemoveVehicle( AFGWheeledVehicle* vehicle );

	/** Returns true if this path segment is considered a junction (e.g. it has overlapping segments) */
	FORCEINLINE bool IsJunctionBlock() const { return mHasOverlappingSegments; }

	/** Returns all vehicle path blocks for the segment */
	const TArray<FVehiclePathBlock>& GetVehiclePathBlocks() const { return mPathBlocks; }

	/** Returns the index of the vehicle path block at the provided distance along the spline */
	int32 FindVehiclePathBlockIndexAtDistance( float distanceAlongSpline ) const;

	float GetVehiclePathBlockSize() const;
	float GetVehiclePathBlockStartDistance( int32 pathBlockIndex ) const;
	float GetVehiclePathBlockEndDistance( int32 pathBlockIndex ) const;

	/** Checks if exclusive path block reservation can be created for the given block segment */
	bool CanCreateExclusiveBlockReservation_ThreadSafe( int32 pathBlockIndex ) const;

	/** Creates an exclusive reservation of the given path block for the given vehicle. Never fails, reserves even in cases where it is normally forbidden */
	TSharedPtr<FVehiclePathBlockExclusiveReservation> CreateExclusiveReservationUnchecked_ThreadSafe( const AFGWheeledVehicle* ownerVehicle, int32 pathBlockIndex );

	/** Releases the given exclusive path reservation */
	void ReleaseExclusiveReservation_ThreadSafe( const TSharedPtr<FVehiclePathBlockExclusiveReservation>& exclusiveReservation );

	/** Releases the given shared path reservation. Internal function, not to be used directly in user code */
	void ReleaseSharedReservation_ThreadSafe( const TSharedPtr<FVehiclePathBlockSharedReservation>& sharedReservation );

	/** Initializes this segment's spline from spline points (in local space). Must be called before BeginPlay. Will automatically cache validation data */
	void SetSplinePointsAndValidatePath( const TArray<FSplinePointData>& splinePointData );
	/** Initializes this segment's connections. Must be called before BeginPlay. Null connections will be automatically initialized to fresh nodes */
	void SetNodeConnections( AFGVehiclePathNode* newStartNode, AFGVehiclePathNode* newEndNode );
	/** Marks the path as legacy path converted to new system. Path validation is disabled, and intersections are not calculated for legacy paths */
	void SetLegacyConvertedPath();

	/** Splits this path segment in two and returns the node created between them. The current segment is automatically destroyed */
	AFGVehiclePathNode* Split( float splitAtDistanceAlongSpline );

	/** Splits this path segment at the location of the given node, and automatically connects the segments to the node */
	void SplitAtNode( AFGVehiclePathNode* splitAtPathNode );

	/** Moves this connection to new nodes, and destroys the old connection */
	AFGVehiclePathSegment* MoveConnectionToNodes( AFGVehiclePathNode* newStartNode, AFGVehiclePathNode* newEndNode );

	/** Creates spline mesh components for visualization of path segment */
	void CreateSplineMeshComponents( const USplineComponent* splineComponent, const FVehiclePathVisualizationInfo& visualizationInfo,
		TArray<TObjectPtr<USplineMeshComponent>>& out_splineMeshComponents, const TFunctionRef<USplineMeshComponent*(UStaticMesh* staticMesh)>& componentConstructor ) const;
	/** Creates clearance data for the path segment */
	void CreateClearanceData( const USplineComponent* splineComponent, TArray<FFGClearanceData>& out_clearanceData ) const;

	/** Returns true if this path segment is currently being visualized */
	FORCEINLINE bool IsVisualizationEnabled() const { return mIsVisualizationEnabled; }
	void SetVisualizationEnabled( const FVehiclePathVisualizationHandle& visualizationHandle );
	void SetVisualizationDisabled();

	FORCEINLINE bool IsVisualizationDirty() const { return mIsVisualizationDirty; }
	void MarkVisualizationDirty() { mIsVisualizationDirty = true; }
protected:
	/** Internal function to split the segment using the pre-spawned path node at the given distance */
	void SplitInternal( AFGVehiclePathNode* splitPathNode, float splitAtDistanceAlongSpline );

	/** Clears the rotation on the root component and applies it to the spline instead */
	void UnrotateForBlueprintPlaced();
	
	FVehiclePathVisualizationInfo GetPathVisualizationInfo( const FVehiclePathVisualizationHandle& visualizationHandle ) const;

	void CleanupOverlappingPathSegments();
	void RecalculateHasOverlappingPathSegments();
	void InitializeOverlappingPathSegments();

	void CreateCollisionComponents( TArray<TObjectPtr<UBoxComponent>>& out_collisionComponents, bool bIsEditorVisualization = false );
	void DestroyCollisionComponents();
	void DestroyVisualizationComponents();

#if WITH_EDITOR
	void CreateEditorVisualization();
#endif

	void OnVehicleSubsystemValid();

	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	TObjectPtr<USplineComponent> mSplineComponent;

	/** Static mesh used for visualization of this path segment */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	TObjectPtr<UStaticMesh> mVisualizationMesh;

	/** Vehicle types that are allowed to traverse this path segment */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	TArray<TObjectPtr<UFGVehiclePathPreset>> mAllowedVehicleTypes;

	/** Segment size for the visualization mesh */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mVisualizationMeshLength{100.0f};

	/** Extent of the collision when aiming at the path segment with build gun */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mCollisionExtent{120.0f};

	/** Granularity of the vehicle path overlap check, in centimeters per checked segment */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mPathOverlapCheckGranularity{50.0f};

	/** Z Offset of the collision and visualization meshes from the spline (since the base spline is on the ground) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mVisualizationZOffset{100.0f};
	
	/** The range in which path segments are considered significant to the player, and will be visualized */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mSignificanceRange{15000.0f};

	/** The range in which the path segments will be allowed to be re-validated and will assume that terrain data (such as collision) is available */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mNetSignificanceRange{15000.0f};

	/** Size of a single vehicle path block relative to the size of the largest vehicle on the path. This must be at least 2 to be able to accomodate the largest vehicle on path */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mPathBlockRelativeSize{2.0f};

	/** Minimum spacing between vehicles traversing on paths that are close to each other. This will be added to the size of the vehicle for overlap detection */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Path Segment" )
	float mPathOverlapVehicleSpacing{25.0f};

#if WITH_EDITORONLY_DATA
	/** True if path validation visualization should be shown */
	UPROPERTY( EditAnywhere, Category = "Vehicle Path Segment | Visualization" )
	bool mVisualizeVehiclePathValidation{false};
	
	/** Path validation info to visualize */
	UPROPERTY( EditAnywhere, Category = "Vehicle Path Segment | Visualization" )
	FVehiclePathValidationInfo mVisualizationPathValidationInfo;
#endif

	UPROPERTY( Transient )
	TArray<TObjectPtr<UBoxComponent>> mCollisionComponents;

	UPROPERTY( Transient )
	TArray<TObjectPtr<USplineMeshComponent>> mVisualizationComponents;

	TOptional<FVehiclePathVisualizationInfo> mCurrentPathVisualizationInfo;

	bool mIsVisualizationEnabled{false};
	bool mIsVisualizationDirty{false};

	/** Saved spline points data for the path segment. Used to rebuild spline across save game reloads & replication */
	UPROPERTY( SaveGame, Replicated )
	TArray<FSplinePointData> mSplinePoints;

	/** Cached validation data for this path segment */
	UPROPERTY( SaveGame, Replicated )
	TArray<FVehiclePathSegmentValidationData> mValidationData;

	/** Vehicle path node used to enter this path segment */
	UPROPERTY( SaveGame, Replicated )
	TObjectPtr<AFGVehiclePathNode> mStartNode;

	/** Vehicle path node used to exit this path segment */
	UPROPERTY( SaveGame, Replicated )
	TObjectPtr<AFGVehiclePathNode> mEndNode;

	/** Path blocks for this vehicle path, the size of the block being defined by the size of the largest vehicle on the path */
	UPROPERTY( SaveGame )
	TArray<FVehiclePathBlock> mPathBlocks;

	/** Critical section for path blocks (since vehicles can book path blocks in parallel) */
	mutable FRWLock mPathBlocksLock;

	/** Value that can be used on the client to tell if this segment acts as an intersection */
	UPROPERTY( Replicated )
	bool mHasOverlappingSegments{false};

	/** ID of the start path node for this path segment. This is replicated separately in case mStartNode/mEndNode are not replicated to the client yet */
	UPROPERTY( Replicated )
	FGuid mStartPathNodeGuid;

	/** Vehicles currently traversing this path segment */
	UPROPERTY( Replicated )
	TArray<TObjectPtr<AFGWheeledVehicle>> mVehicles;

	/** True if this object is currently significant to the local player or any other player in multiplayer session when playing as a host */
	bool mIsNetSignificant{false};
	/** True if this object is currently significant to the local player */
	bool mIsSignificantForLocalPlayer{false};

	/** Ignore significance, update path validation data and overlaps regardless of what significance says */
	bool mForceUpdateOnBeginPlayRegardlessOfSignificance{false};

	/** True if path validation data for this path segment is dirty, e.g. it is outdated or there are new path presets not yet validated. Will force the path re-validation on significance gain */
	UPROPERTY( SaveGame )
	bool mPathValidationDataDirty{false};

	/** True if we need to perform check for overlapping segments when the collision data is available */
	UPROPERTY( SaveGame )
	bool mOverlappingPathSegmentsDirty{false};

	/** True if this is a legacy vehicle path converted to a new path system. Path validation and overlapping segment check are disabled for legacy paths */
	UPROPERTY( SaveGame, Replicated )
	bool mIsLegacyPath{false};

#if WITH_EDITORONLY_DATA
	/** Temporary visualization components spawned in editor worlds */
	UPROPERTY( Transient )
	TArray<TObjectPtr<UActorComponent>> mEditorVisualizationComponents;
#endif

	/** Clearance data cached on the segment */
	mutable TArray<FFGClearanceData> mCachedClearanceData;
};

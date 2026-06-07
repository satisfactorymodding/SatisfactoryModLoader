// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGBuildableHologram.h"
#include "FGHologram.h"
#include "Components/SplineComponent.h"
#include "WheeledVehicles/FGVehiclePathValidation.h"
#include "FGVehiclePathSegmentHologram.generated.h"

class UFGVehiclePathPreset;
struct FVehiclePathVisualizationHandle;
struct FVehiclePathVisualizationInfo;
class USplineMeshComponent;
class AFGVehiclePathSegment;
class AFGWheeledVehicle;
class AFGVehiclePathNode;
class USplineComponent;

UENUM()
enum class EVehiclePathBuildStep : uint8
{
	StartPoint,
	EndPoint,
};

UCLASS()
class FACTORYGAME_API AFGVehiclePathSegmentHologram : public AFGBuildableHologram
{
	GENERATED_BODY()
public:
	AFGVehiclePathSegmentHologram();

	// Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End AActor interface

	// Begin AFGHologram interface
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void PreConfigureActor(class AFGBuildable* inBuildable) override;
	virtual bool TrySnapToActor(const FHitResult& hitResult) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual void SetHologramNudgeLocation() override;
	virtual int32 GetRotationStep() const override;
	virtual void ScrollRotate(int32 delta, int32 step) override;
	virtual bool ShouldBuildGunHitVehiclePaths() const override;
	virtual void GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const override;
	virtual void ReplaceHologram(AFGHologram* hologram, bool snapTransform) override;
	virtual void PostConstructMessageDeserialization() override;
	virtual bool CanNudgeHologram() const override;
	virtual ENudgeFailReason NudgeTowardsWorldDirection(const FVector& Direction) override;
	virtual void GetClearanceData(TArray<const FFGClearanceData*>& out_ClearanceData) const override;
	virtual bool IsHologramIdenticalToActor(AActor* actor, const FTransform& hologramTransform) const override;
	virtual void GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const override;
	virtual TSubclassOf<class UFGConstructDisqualifier> GetConstructDisqualifierFromClearanceOverlap(const EClearanceOverlapResult& overlapResult, AActor* otherActor) const override;
	// End of AFGHologram interface

	void SetupBridgeHologram( bool bIsSegmentReversed );
	/** Used by vehicle path open connection manager to create bridge vehicle path holograms between two connections */
	void UpdateBridgeHologramLocation( const FVector& startLocation, const FVector& startForwardDirection, AFGVehiclePathNode* endPathNode );
	/** Used by vehicle path open connection manager to populate the bridge hologram with the newly constructed blueprint path node */
	void SetBridgeHologramStartPathNode( AFGVehiclePathNode* startPathNode );

	static void AddIgnoredActorsFromPathNode( AFGVehiclePathNode* pathNode, TSet<AActor*>& ignoredActors );
	static void AddIgnoredActorsFromPathSegment( AFGVehiclePathSegment* pathSegment, TSet<AActor*>& ignoredActors );

	/** Attempts to overlap path segments to find the path node closest to the given location. This will not find path nodes not connected to any path segments */
	static AFGVehiclePathNode* OverlapPathNode( const UWorld* world, const FVector& worldLocation, float overlapRadius );
protected:
	AFGVehiclePathNode* GetPathNodeFromHitResult( const FHitResult& hitResult ) const;

	bool CheckPathCompatibility( const AFGVehiclePathSegment* pathSegment ) const;
	bool CheckNodeCompatibility( const AFGVehiclePathNode* pathNode, bool bIsArrivingConnection ) const;
	bool TrySnapToPathNode( AFGVehiclePathNode* pathNode );
	bool TrySnapToPathSegment( AFGVehiclePathSegment* pathSegment, const float snapDistance );
	void RouteHologramSpline();

	/** Updates current path validation data from the spline component. Called during CheckValidPlacement */
	void UpdatePathValidationInfoFromSplineComponent();
	/** Updates visual state of the hologram */
	void UpdateHologramVisualState();
	void GetActiveVehicleTypes( TArray<UFGVehiclePathPreset*>& out_activeVehicleTypes ) const;
	void UpdatePathVisualizationHandle();

	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	virtual void CheckBlueprintCommingling() override;
	virtual void OnHologramLockStateChanged() override;
	// End of AFGHologram interface

	UFUNCTION()
	void OnRep_SplineData();
	UFUNCTION()
	void OnRep_HologramState();

	/** Maps path validation result to a specific disqualifier for it. If no entry is found, generic disqualifier will be used */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TMap<EVehiclePathValidationResult, TSubclassOf<UFGConstructDisqualifier>> mPathValidationResultToDisqualifier;

	/** Disqualifier for when the path is too short */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TSubclassOf<UFGConstructDisqualifier> mPathTooShortDisqualifier;

	/** Disqualifier for when the path is too long */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TSubclassOf<UFGConstructDisqualifier> mPathTooLongDisqualifier;

	/** Disqualifier for when the connection between two nodes already exists */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TSubclassOf<UFGConstructDisqualifier> mConnectionAlreadyExistsDisqualifier;

	/** Disqualifier for when the vehicle path shape is invalid for the current build mode */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TSubclassOf<UFGConstructDisqualifier> mInvalidVehiclePathShapeDisqualifier;

	/** Maximum distance to search for the floor when projecting the spline to the surface */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mMaxFloorTraceSearchDistance{2000.0f};

	/** How far above the terrain the path should be elevated before it is projected to the terrain? */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mPathFloorTraceElevation{200.0f};

	/** Distance along which we should project the spline to the surface. Lower numbers result in more accurate projection but considerably more expensive splines */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mPathSplineQuantizationLength{100.0f};

	/** Minimum length of a single vehicle path segment spline */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mMinPathLength{100.0f};

	/** Maximum length of a single vehicle path segment spline */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mMaxPathLength{10000.0f};

	/** Snap distance at which the connection will be snapped to the end or the start of the path segment, as opposed to splitting the segment */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mSegmentEndPointSnapDistance{800.0f};

	/** Path nodes in this radius around the hit position will be snapped to the newly built path segment */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	float mPathNodeOverlapRadius{300.0f};

	/** Straight path segment build mode */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TSubclassOf<UFGHologramBuildModeDescriptor> mBuildModeStraight;

	/** Spline data points for replication & hologram construction message serialization */
	UPROPERTY( ReplicatedUsing = OnRep_SplineData )
	TArray<FSplinePointData> mSplineData;

	UPROPERTY()
	TObjectPtr<USplineComponent> mTempSplineComponent;

	UPROPERTY()
	TObjectPtr<USplineComponent> mPathSplineComponent;

	/** Directional arrow mesh shown in the first build step */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TObjectPtr<UStaticMeshComponent> mDirectionalArrowComponent;

	/** Placement orientation visualization mesh shown in both the first and the second build step */
	UPROPERTY( EditDefaultsOnly, Category = "Path Segment" )
	TObjectPtr<UStaticMeshComponent> mPlacementVisualizationComponent;

	UPROPERTY()
	TArray<TObjectPtr<USplineMeshComponent>> mSplineMeshComponents;

	/** Current build step for the hologram. This information needs to be replicated because visualization behavior differs between the build steps */
	UPROPERTY( Replicated, CustomSerialization )
	EVehiclePathBuildStep mBuildStep{EVehiclePathBuildStep::StartPoint};

	/** Vehicle path nodes that we have been snapped to. nullptr means that particular node is not snapped */
	UPROPERTY( CustomSerialization )
	TObjectPtr<AFGVehiclePathNode> mSnappedPathNodes[2];

	/** Path segments that we want to slice to create junctions */
	UPROPERTY( CustomSerialization )
	TObjectPtr<AFGVehiclePathSegment> mSnappedPathSegments[2];

	/** When slicing an existing path segment, this is a position at which a junction will be created */
	UPROPERTY( CustomSerialization )
	float mSnappedPathSegmentSlicePositions[2] {};

	/** True if this segment is reversed, e.g. start point is the arriving connection and not an exit connection */
	UPROPERTY( CustomSerialization )
	bool mIsSegmentReversed{false};

	/** True if path segment shape is considered invalid due to the current build mode constraints */
	UPROPERTY( Replicated )
	bool mIsPathSegmentShapeInvalid{false};

	/** Vehicle type to which current path validation info belongs */
	UPROPERTY( ReplicatedUsing = OnRep_HologramState )
	TObjectPtr<UFGVehiclePathPreset> mCurrentPathValidationVehicleClass;

	/** Path validation info cached during placement */
	UPROPERTY( ReplicatedUsing = OnRep_HologramState )
	FVehiclePathValidationInfo mCurrentPathValidationInfo;

	/** Active handle to the path visualization, valid only for locally instigated holograms */
	TSharedPtr<FVehiclePathVisualizationHandle> mActivePathVisualizationHandle;

	UPROPERTY( CustomSerialization )
	FVector mStartLocation{ForceInit};
	UPROPERTY( CustomSerialization )
	FVector mStartPointExitDirection{ForceInit};
	UPROPERTY( CustomSerialization )
	FVector mEndLocation{ForceInit};
	UPROPERTY( CustomSerialization )
	FVector mEndPointEntryDirection{ForceInit};
	UPROPERTY( CustomSerialization )
	bool mUseCustomEndRotation{false};
	UPROPERTY( CustomSerialization )
	bool mStraightMode{false};

	int32 mSelectedConnectionPointIndex{0};
	bool mUseCustomConnectionPointIndex{false};

	/** True if first point must behave as it is snapped even if it does not have a snapped segment or node (used by blueprint open connection manager) */
	UPROPERTY( CustomSerialization )
	bool mForceSnapFirstPoint{false};

	/** True if we are a blueprint open connection bridge hologram and should not project or validate the path until it is built */
	UPROPERTY( CustomSerialization )
	bool mBlueprintBridgeHologramMode{false};

	/** Used to store original start and end locations when nudging */
	FVector mInitialStartLocation{ForceInit};
	FVector mInitialEndLocation{ForceInit};

	/** Cached clearance data for the path */
	TArray<FFGClearanceData> mPathClearanceData;
};

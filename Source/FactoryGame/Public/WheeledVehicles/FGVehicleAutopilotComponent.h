// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveInterface.h"
#include "FGVehiclePathSegment.h"
#include "FGWheeledVehicleAnimationInstance.h"
#include "FGWheeledVehicleVFXHandler.h"
#include "Components/ActorComponent.h"
#include "Curves/CurveFloat.h"
#include "FGVehicleAutopilotComponent.generated.h"

enum class EVehicleAutopilotErrorStatus : uint8;
class UCurveFloat;
class AFGVehiclePathNode;
class AFGWheeledVehicle;
class AFGVehiclePathSegment;
class AFGDockingStationIdentifier;

USTRUCT()
struct FVehicleStopTarget
{
	GENERATED_BODY()
	
	UPROPERTY()
	uint64 StopTargetIdentifier{0};

	UPROPERTY()
	float DistanceToStopTarget{0.0f};

	UPROPERTY()
	TOptional<float> TargetMovementSpeed;

	FVehicleStopTarget() = default;
	explicit FVehicleStopTarget( const uint64 stopTargetIdentifier, const float distanceToStopTarget ) : StopTargetIdentifier( stopTargetIdentifier ), DistanceToStopTarget( distanceToStopTarget ) {}
	FVehicleStopTarget( const uint64 stopTargetIdentifier, const float distanceToStopTarget, const TOptional<float>& targetMovementSpeed ) : StopTargetIdentifier( stopTargetIdentifier ),
		DistanceToStopTarget( distanceToStopTarget ), TargetMovementSpeed( targetMovementSpeed ) {}
};

struct FVehicleCommonInputs
{
	float VehicleHalfLength{0.0f};
	float VehicleForwardSpeed{0.0f};
	float VehicleDistanceAlongSpline{0.0f};
	float VehicleSplineLength{0.0f};
	FVector VehicleForwardDirection{ForceInit};
	bool bIsCurrentlyDockingStation{false};
};

struct FVehicleAutopilotEstimate
{
	float DistanceToStopTarget{0.0f};
	float MinimumAirBrakingTime{0.0f};
	float EstimatedEngineBrakingTime{0.0f};
	float TotalDecelerationTime{0.0f};	
};

struct FVehicleAutopilotInputs
{
	FVehicleCommonInputs CommonInputs;
	float SpeedLimit{0.0f};
	TOptional<FVehicleStopTarget> StopTarget;
};

struct FVehicleAutopilotState
{
	TOptional<FVehicleStopTarget> CurrentStopTarget;
	bool bApproachingStopTarget{false};
	bool bStartedReleasingAirBrakes{false};
	bool bSlowedDownToMinimumSpeedForStopTarget{false};
	bool bStartedSpeedMatchingStopTarget{false};
	float CurrentThrottleInput{0.0f};
	float CurrentAirbrakeInput{0.0f};
	bool bCurrentEngineBrakeInput{false};
	bool bCurrentHandbrakeInput{false};
};

struct FVehicleMovementOutputs
{
	struct FVehicleMovementForces
	{
		float Weight{0.0f};
		float Drag{0.0f};
		float RollingResistance{0.0f};
		float AirBraking{0.0f};
		float DynamicBraking{0.0f};
		float Traction{0.0f};
		float Handbrake{0.0f};
	} Forces;
	float TotalForce{0.0f};
	float Acceleration{0.0f};
};

USTRUCT()
struct FVehicleAutopilotBlockReservationContainer
{
	GENERATED_BODY()

	TSharedPtr<FVehiclePathBlockExclusiveReservation> Reservation;
};

struct FVehicleAutopilotBlockReference
{
	int32 PathNodeIndex{INDEX_NONE};
	int32 PathBlockIndex{INDEX_NONE};

	friend bool operator==( const FVehicleAutopilotBlockReference& A, const FVehicleAutopilotBlockReference& B )
	{
		return A.PathNodeIndex == B.PathNodeIndex && A.PathBlockIndex == B.PathBlockIndex;
	}

	friend uint32 GetTypeHash( const FVehicleAutopilotBlockReference& Value )
	{
		return HashCombine( GetTypeHash( Value.PathNodeIndex ), GetTypeHash( Value.PathBlockIndex ) );
	}
};

// Note: this type is assumed to be trivially constructible by zero-initialization (vehicle subsystem makes that assumption during Tick)
struct FVehicleAutopilotComponentSimData
{
	TOptional<FTransform> SharedVehicleTransform;
	float SimulatedAdjustedServerVehicleSplinePosition{0.0f};
	bool bServerNeedToUpdateCurrentPathSegmentOnVehicle{false};
	int32 ServerCurrentTargetWaypointIndex{0};
	bool bServerNeedToUpdateTargetWaypointIndex{false};
	class AFGBuildableDockingStation* ServerDockingStationToDock{};
	FVehicleAutopilotInputs ServerAutopilotInputs;
	FVehicleMovementOutputs ServerMovementOutputs;
	EVehicleAutopilotErrorStatus ServerCurrentAutopilotErrorStatus;
	bool bServerShouldUpdateAutopilotErrorStatus{false};
	bool bServerShouldDisableAutopilot{false};
};

UCLASS(Within = FGWheeledVehicle)
class FACTORYGAME_API UFGVehicleAutopilotComponent : public UActorComponent, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	UFGVehicleAutopilotComponent();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** Returns true if this autopilot component should be ticked this frame */
	bool ShouldTickAutopilotComponent() const;
	/** Will be called to update this autopilot off the game thread, in parallel with other autopilot updates. Writing to shared state (e.g. vehicle or world) is unsafe here! */
	void TickAutopilotComponent_Parallel( float deltaTime, FVehicleAutopilotComponentSimData& simData );
	/** Will be called on game thread after all autopilots have been ticked in parallel to apply the calculated data to the game state */
	void PostTickAutopilotComponent_GameThread( const FVehicleAutopilotComponentSimData& simData );

	// Begin UActorComponent interface
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	// End UActorComponent interface

	// Begin IFGSaveInterface
	virtual bool ShouldSave_Implementation() const override;
	// End IFGSaveInterface

	FORCEINLINE float GetCurrentForwardSpeed() const { return mCurrentServerVehicleForwardSpeed; }
	FORCEINLINE TArray<FWheelAnimationData> GetWheelAnimationData() const { return mCachedWheelAnimationData; }
	FORCEINLINE float GetLastTickVirtualMovementDelta() const { return mLastTickVirtualMovementDelta; }
	FORCEINLINE FVector GetLastVehicleLocation() const { return mLastVehicleLocation; }
	FORCEINLINE FRotator GetLastVehicleRotation() const { return mLastVehicleRotation; }
	FORCEINLINE bool HasAuthoritativeVehicleLocation() const { return mHasAuthoritativeVehicleLocation; }

	/** Populates visual state of the vehicle when using the vehicle autopilot component */
	void PopulateVehicleVisualState( FFGVehicleVFXData& vehicleVisualState ) const;

	/** Completely resets the state of the autopilot (status, speed and position) on server */
	void ResetAutopilotStateOnServer();

	/** Returns the maximum movement speed for this autopilot component. Caches the value after first computation on the instance */
	float GetMaxVehicleMovementSpeed() const;
protected:
	void TickVehicleMovementServer_Parallel( float deltaTime, FVehicleAutopilotComponentSimData& simData );
	void PostTickVehicleMovementServer_GameThread( const FVehicleAutopilotComponentSimData& simData );

	void TickVehicleMovementSimulated_Parallel( float deltaTime, FVehicleAutopilotComponentSimData& simData );
	void PostTickVehicleMovementSimulated_GameThread( const FVehicleAutopilotComponentSimData& simData );

	/** Recalculates the current vehicle route to the next target waypoint */
	void RecalculateVehicleRoute_Parallel( FVehicleAutopilotComponentSimData& simData );
	/** Invalidates current vehicle route, causing it to be recalculated next frame */
	void InvalidateVehicleRoute_ThreadSafe();
	/** Updates the pointer to the next path segment that the vehicle will be taking */
	void UpdateNextVehiclePathSegment_ThreadSafe();
	/** Updates current autopilot state on the server regardless of the current frame time */
	bool UpdateVehicleAutopilotStateOnServer( FVehicleAutopilotComponentSimData& simData );
	/** Moves the vehicle along the path spline on the server, also handles docking to stations */
	void MoveVehicleAlongSplineOnServer_Parallel( float deltaTime, FVehicleAutopilotComponentSimData& simData );
	/** Moves vehicle along the path spline on the client */
	void MoveVehicleAlongSplineOnClient_Parallel( float deltaTime, FVehicleAutopilotComponentSimData& simData );
	/** Calculates the maximum movement speed of the vehicle given the movement parameters of the autopilot */
	float CalculateMaxVehicleMovementSpeed() const;
	/** Releases all vehicle path block reservations held by the autopilot */
	void ReleaseVehiclePathBlockReservations_Parallel();
	/** Cleans up all path block reservations that are not referenced from the given set */
	void CleanupOldVehiclePathBlockReservations_Parallel( const TSet<FVehiclePathBlockReference>& referencedPathBlockReservations );

	/** Caches new vehicle position from the given path segment and input parameters to be applied later with ApplyCachedVehiclePosition_GameThread */
	void UpdateVehiclePositionFromPathSplineAndDistance_Parallel( const AFGVehiclePathSegment* currentPathSegment, float distanceAlongSpline, float vehicleForwardSpeed, float deltaTime, FVehicleAutopilotComponentSimData& simData );
	/** Applies position previously cached with CacheVehiclePositionFromPathSplineAndDistance_Parallel to the vehicle */
	void PostUpdateVehiclePosition_GameThread( const FVehicleAutopilotComponentSimData& simData );
	
	/** Calculates vehicle half-length from the vehicle */
	static float CalculateVehicleHalfLength( const AFGWheeledVehicle* wheeledVehicle );
	/** Calculates common vehicle inputs from the vehicle and the provided data */
	FVehicleCommonInputs CalculateCommonVehicleInputs( const AFGVehiclePathSegment* currentPathSegment, float currentDistanceAlongSpline, float currentVehicleSpeed ) const;
	/** Calculates the estimates based on the vehicle inputs and distance to stop target */
	FVehicleAutopilotEstimate CalculateAutopilotEstimate( float currentVehicleSpeed, float desiredVehicleSpeed ) const;
	/** Updates current autopilot state based on the autopilot inputs and delta time */
	void UpdateVehicleAutopilot_ThreadSafe( const FVehicleAutopilotInputs& autopilotInputs, FVehicleAutopilotState& autopilotState, float deltaTime ) const;
	/** Calculates the acceleration that should be applied to the vehicle */
	FVehicleMovementOutputs CalculateVehicleMovementParameters( const FVehicleCommonInputs& commonInputs, const FVehicleAutopilotState& autopilotState ) const;

	/** Finds the block reference at the given position along the spline, relative to the vehicle current path segment */
	bool FindPathBlockFromVehiclePosition( float vehicleSplinePosition, FVehicleAutopilotBlockReference& out_autopilotBlockReference, float& out_distanceToEndOfPathBlock ) const;
	/** Calculates a sequence of path blocks that should be reserved as a single unit. Path block sequence is a collection of intersection path blocks ending with a single non-intersection path block */
	bool CalculatePathBlockSequence( FVehicleAutopilotBlockReference& currentBlockReference, TArray<FVehicleAutopilotBlockReference>& pathBlockSequence ) const;
	/** Calculates the total distance between the given path node + path block index pairs */
	float CalculateTotalDistanceBetweenPathBlocks( const FVehicleAutopilotBlockReference& startBlockReference, const FVehicleAutopilotBlockReference& endBlockReference ) const;
	/** Given a reference to the path block, returns a reference to the path block that precedes it. Returns the reference to the passed block if there is no preceding block */
	FVehicleAutopilotBlockReference GetPreviousPathBlockReference( const FVehicleAutopilotBlockReference& pathBlockReference ) const;
	/** Given a reference to the path block, returns a reference to a path block after it. Returns the reference to the passed block if there is no next block */
	FVehicleAutopilotBlockReference GetNextPathBlockReference( const FVehicleAutopilotBlockReference& pathBlockReference ) const;
	/** Books any given vehicle path blocks that have not been booked yet */
	void ReserveVehiclePathBlocks_Parallel( const TArray<FVehicleAutopilotBlockReference>& pathBlocks, TSet<FVehiclePathBlockReference>& referencedPathBlocks );
	/** Updates deadlock status of the vehicle based on the next free block reference and delta time */
	bool UpdateVehicleDeadlockStatus_Parallel( const FVehicleCommonInputs& commonInputs, const TArray<FVehicleAutopilotBlockReference>& currentVehicleBlocks, float deltaTime, FVehicleAutopilotComponentSimData& simData );
	/** Updates vehicle path reservations for vehicle paths in a way of the vehicle */
	bool UpdateVehiclePathReservations_Parallel( const FVehicleCommonInputs& commonInputs, float deltaTime, FVehicleAutopilotComponentSimData& simData );

	/** Updates path reservations within the given lookahead distance. Returns false if we are clear to continue movement at full speed within lookahead distance, or true and the distance after which we will need to stop */
	void CalculatePathReservationStopTarget( float maxLookaheadDistance, float vehicleHalfLength, TArray<FVehicleStopTarget>& out_stopTargets ) const;
	/** Checks if the docking destination is within the lookahead distance. Returns false if we are clear of the docking destination, or true and the distance which we have until we hit the docking destination */
	void CalculateDestinationStopTarget( float maxLookaheadDistance, TArray<FVehicleStopTarget>& out_stopTargets ) const;
	/** Checks if there are any vehicles ahead of us that we should avoid by slowing down to their own speed (or waiting for them if they are completely still). Returns false if the path is clear, or true and the distance to vehicle plus vehicle speed */
	void CalculateVehicleAvoidanceTarget( float maxLookaheadDistance, float vehicleHalfLength, TArray<FVehicleStopTarget>& out_stopTargets ) const;
	/** Calculates the most significant stop target for the vehicle autopilot */
	TOptional<FVehicleStopTarget> CalculateClosestStopTarget( const FVehicleCommonInputs& commonInputs, const FVehicleAutopilotState& autopilotState ) const;
	/** Calculates the vehicle speed limit based on the path curvature */
	float CalculatePathCurvatureSpeedLimit( const FVehicleCommonInputs& commonInputs ) const;

	/** Called to update the last server replication timestamp on the client */
	UFUNCTION()
	void OnRep_CurrentServerTimestamp();

	/** Mass of the vehicle. Acts as a scale on all the forces except for the vehicle weight. Speaking simply, larger mass results in weight making more contribution to the vehicle speed and vehicle having more inertia [kg] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	float mVehicleMass{6000.0f};

	/** Cross-sectional area of the vehicle for drag force calculation. For passenger cars this is 0.7 square meters, for large trucks this is 7.5 to 10 square meters */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	float mVehicleCrossSectionalArea{7.5f};

	/** Drag coefficient for the vehicle. For passenger cars this is about 0.3, for large trucks it is about 0.7. Good values are within 0.2-0.9 range */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	float mDragCoefficient{0.7f};

	/** Wheel rolling resistance coefficient. For passenger cars this is about 0.0065, for large trucks it is 0.0045 to 0.0080. Good values are within 0.01-0.005 range */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	float mRollingResistanceCoefficient{0.0045f};

	/** The maximum air braking force that can be delivered from the vehicle brakes [kN] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	float mMaxAirBrakingEffort{20.0f};

	/** Dynamic/engine braking curve for this vehicle. Maps current vehicle speed [m/s] to the effort of the engine braking [kN] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	FRuntimeFloatCurve mDynamicBrakingEffortCurve;

	/** Tractive effort curve for this vehicle. Maps current vehicle speed [m/s] to the tractive effort of the vehicle engine [kN] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Movement" )
	FRuntimeFloatCurve mTractiveEffortCurve;

	/** Curvature speed limit curve for the vehicle. Maps path curvature [deg/cm] to the maximum vehicle speed [m/s] that the vehicle must have to traverse the path */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	FRuntimeFloatCurve mCurvatureSpeedLimitCurve;
 
	/** How much the vehicle throttle can change per second (throttle input is from 0 to 1.0). Used to avoid quick jumps in throttle given by the autopilot [s^-1] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotThrottleChangeRate{0.2f};

	/** Over how many seconds the air brakes are fully released [s^-1] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotAirbrakeReleaseRate{1.0f};

	/** Speed to which vehicles will slow down when approaching their target [cm/s] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotTargetApproachSpeed{250.0f};

	/** Stop at this distance from the target, or closer to the target [cm] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotTargetStopDistanceTolerance{10.0f};

	/** The rate at which the speed limit is adjusted when the path curvature changes. [cm/s] */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotSpeedLimitChangeRate{500.0f};

	/** Amount of space to leave between vehicles that are following each other */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotVehicleAvoidanceSpacing{400.0f};

	/** The factor by which the minimum braking distance must be multiplied to check for speed limit of vehicles moving ahead of this vehicle */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotSpeedMatchingDistanceFactor{2.0f};

	/** The amount of time in seconds it takes waiting on a block reservation for the autopilot to mark the vehicle deadlocked */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Autopilot" )
	float mAutopilotWaitTimeToDeadlock{120.0f};

	/** Scales wheel steering magnitude (visual only) */
	UPROPERTY( EditDefaultsOnly, Category = "Vehicle Wheel Animation" )
	float mWheelSteeringMagnitudeScale{1.0f};

	/** Current path segment the vehicle is following on the server */
	UPROPERTY( Replicated, SaveGame )
	TObjectPtr<AFGVehiclePathSegment> mCurrentServerPathSegment;

	/** Next path segment the vehicle will follow on the server */
	UPROPERTY( Replicated )
	TObjectPtr<AFGVehiclePathSegment> mNextServerPathSegment;

	/** Position of the vehicle on the current path segment from the perspective of the server */
	UPROPERTY( Replicated, SaveGame )
	float mCurrentServerVehicleSplinePosition{0.0f};

	/** Distance that the vehicle travelled last tick for the purposes of fuel consumption calculation */
	float mLastTickVirtualMovementDelta{0.0f};

	/** Current speed of the vehicle, in meters per second, as reported by the server. This value is not smoothed or locally simulated by the clients */
	UPROPERTY( Replicated, SaveGame )
	float mCurrentServerVehicleForwardSpeed{0.0f};

	/** Speed limit based on the path curvature calculated on the server */
	UPROPERTY( Replicated )
	float mServerPathCurvatureSpeedLimit{0.0f};
	/** Stop target closest to the vehicle on the server. Replicated to the client because client is not capable of stop target calculation on its own */
	UPROPERTY( Replicated )
	bool mServerClosestStopTargetIsSet{false};
	UPROPERTY( Replicated )
	FVehicleStopTarget mServerClosestStopTarget;

	/** Current timestamp of the vehicle movement data replicated from the server. Used to interpolate the client data when the replication is not as frequent or is delayed due to high ping */
	UPROPERTY( ReplicatedUsing = OnRep_CurrentServerTimestamp )
	float mCurrentServerTimestamp{0.0f};
	/** Client time seconds timestamp of the last replication data from the server */
	float mLastServerReplicationClientTimestamp{0.0f};

	/** Current state of the autopilot on the server */
	FVehicleAutopilotState mServerAutopilotState{};

	/** ID of the current path network this vehicle is following on the server */
	int32 mCurrentPathNetworkID{INDEX_NONE};
	/** Current changelist number of the vehicle route. Used to detect changes in the vehicle route configuration */
	int32 mCurrentRouteChangelist{INDEX_NONE};
	/** Current changelist of the path network traversability */
	int32 mCurrentPathNetworkChangelist{INDEX_NONE};

	/** Last result for autopilot vehicle route calculation */
	EVehicleAutopilotErrorStatus mVehicleRouteErrorStatus{};
	/** Cached vehicle route from the current location to the next target waypoint */
	TArray<FGuid> mCurrentVehicleRoute;
	/** Current target waypoint index in the vehicle route */
	int32 mCurrentPathNodeIndex{0};

	/** Route segments for the current vehicle route. Segment at index i starts at node (i - 1) and ends at node i */
	UPROPERTY()
	TArray<TObjectPtr<AFGVehiclePathSegment>> mCurrentVehicleRouteSegments;

	/** Reservations for junctions in the vehicle path */
	UPROPERTY()
	TMap<FVehiclePathBlockReference, FVehicleAutopilotBlockReservationContainer> mPathBlockReservations;
	/** Reference to the next free block on which we can park if no further path reservations are possible */
	TOptional<FVehicleAutopilotBlockReference> mNextFreeBlockReference;
	TOptional<TArray<FVehicleAutopilotBlockReference>> mNextBlockSequenceReference;

	/** Time we have spent waiting for the path block reservation on the current free block */
	UPROPERTY( SaveGame )
	float mTimeSpentWaitingOnCurrentFreeBlock{0.0f};

	// NOTE: mLastVehicleLocation, mLastVehicleRotation and mHasAuthoritativeVehicleLocation are NOT safe to modify during parallel vehicle tick since it leaks outside the autopilot component state

	/** Last location and rotation of the vehicle when moving with autopilot. Cached to snap the vehicle to the destination position when exiting self driving mode */
	UPROPERTY( SaveGame )
	FVector mLastVehicleLocation{ForceInit};
	UPROPERTY( SaveGame )
	FRotator mLastVehicleRotation{ForceInit};
	/** True if autopilot is currently the authoritative source of location data (autopilot can be enabled but not performed a single move, in which case it has no location data) */
	UPROPERTY( SaveGame )
	bool mHasAuthoritativeVehicleLocation{false};

	/** Current vehicle path segment on the simulated client */
	UPROPERTY()
	TObjectPtr<AFGVehiclePathSegment> mCurrentSimulatedPathSegment;

	/** Position of the vehicle on the current spline */
	float mCurrentSimulatedVehicleSplinePosition{0.0f};
	/** Forward speed of the vehicle simulated locally on the client */
	float mCurrentSimulatedVehicleForwardSpeed{0.0f};

	/** Autopilot state simulated locally on the client */
	FVehicleAutopilotState mSimulatedAutopilotState{};

	TArray<FWheelAnimationData> mCachedWheelAnimationData;
	TArray<FFGVehicleWheelVFXData> mCachedWheelVisualData;
	float mCachedEngineRPM{0.0f};
	TArray<float> mCurrentWheelsRotationRadians;
	mutable TOptional<float> mCachedMaxVehicleMovementSpeed;
};

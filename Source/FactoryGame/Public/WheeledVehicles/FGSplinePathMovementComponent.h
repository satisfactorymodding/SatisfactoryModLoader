// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "GameFramework/MovementComponent.h"
#include "FGVehicleSubsystem.h"
#include "FGSplinePathMovementComponent.generated.h"

UCLASS()
class FACTORYGAME_API UFGSplinePathMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
public:
	UFGSplinePathMovementComponent();

	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	//Begin UActorComponent Interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void TickComponent( float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	//End UActorComponent Interface

	void TicTac( float DeltaTime );

	void OnBecameTheChosenWheeledVehicle();

	void RestoreEssentialClaims();

	void DestroyPath_Server();

#if DEBUG_SELF_DRIVING
	void DrawDebug( int debugLevel ) const;
#endif

	void AddDynamicStops_Server( const TArray< FVector >& stops );

	/**
	 * Starts movement on the spline path. Called on server and then multicast.
	 */
	void StartSplinePathMovement_Server( class AFGTargetPoint* target );

	/**
	 * Starts movement on the spline path.
	 */
	UFUNCTION( Reliable, NetMulticast )
	void StartSplinePathMovement_Multi( class AFGTargetPoint* target );

	/**
	 * Called when a vehicle goes from physical to simulated, to create smooth transition. Called on server and then multicast.
	 */
	void TransitionToSimulation();

	DECLARE_DELEGATE_OneParam( FTargetReached, class AFGTargetPoint* );
	FTargetReached mTargetReachedDelegate;

	void SetPaused( bool isPaused );
	bool IsPaused() const { return mIsPaused; }

	bool HasValidPosition() const { return mHasValidPosition; }

	const FVector& GetSimulatedLocation();
	const FRotator& GetSimulatedRotation();

	bool IsDocked() const { return mIsDocked; }
	void SetIsDocked( bool isDocked );

	bool IsBlocked() const { return mIsBlocked; }
	void SetIsBlocked( class AFGWheeledVehicleInfo* blockingVehicle );
	void ResetIsBlocked();

	void DrawTargetDebug( bool drawSearchPoints ) const;

	void ResetIsDeadlocked( bool removeDeadlock );
	void SetDeadlockId( int deadlockId, bool isInHardDeadlock );
	int GetDeadlockId() { return mDeadlockId; }
	bool IsDeadlocked() const { return mDeadlockId != -1; }

	float GetTimeSpentOnPath() const { return mTimeSpentOnPath; }
	float GetTimeSpentOnRegularPath() const;

	void ResetTarget( bool resetStatus );

	const TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > >& GetBlockingVehicles() const { return mBlockingVehicles; }
	TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > >& GetDeadlockedVehicles() { return mDeadlockingVehicles; }
	void ResetDeadlockedVehicles() { mDeadlockingVehicles.Reset(); }

	const TArray< FVector >& GetSearchPoints() const;

	bool TryClaim( class AFGTargetPoint* target, bool essentialsOnly );

	bool IsMoving() const { return mIsMoving; }

	FVector GetVelocityVector() const { return mVelocityVector; }

	float GetTargetTimeFulfilment() const { return mTargetTimeFulfilment; }

	FVector GetDeadlockSegmentCenter() const { return mDeadlockSegmentCenter; }
	void SetDeadlockSegmentCenter( FVector deadlockSegmentCenter ) { mDeadlockSegmentCenter = deadlockSegmentCenter; }

	class AFGTargetPoint* GetTarget() const { return mTarget; }
	void SetTarget( class AFGTargetPoint* target ) { mTarget = target; }

	class AFGTargetPoint* GetPreviousTarget() const { return mPreviousTarget; }
	void SetPreviousTarget( class AFGTargetPoint* previousTarget ) { mPreviousTarget = previousTarget; }

	FVector GetSimulatedLocationOffset() const { return mSimulatedLocationOffset; }
	void IncrementSimulatedLocationOffset( FVector increment ) { mSimulatedLocationOffset += increment; }
	void ResetSimulatedLocationOffset() { mSimulatedLocationOffset = FVector::ZeroVector; }

	void SetTargetList( class AFGDrivingTargetList* targetList ) { mTargetList = targetList; }

private:
	static void GetShortestRotation( FRotator& rotation );

	bool HasData() const;

	void CalculateSimulatedPosition( float clientCorrection );

	float GetServerTime() const;
	
	UFUNCTION()
	void OnRep_PauseTarget();

	UFUNCTION()
	void OnRep_ServerStartTime();

	UFUNCTION()
	void OnRep_IsMoving();

	bool TickSplinePathMovement( double deltaTime );

	FVector GetSimulationLocation();

#if DEBUG_SELF_DRIVING
	void DrawDebugVehicle( int visualDebugLevel, int textualDebugLevel );
#endif

	void AdvanceOnSplinePath();

	void TryClaimTarget();

	void SetTarget( class AFGTargetPoint* newTarget, bool resetStatus );

	float GetStartTime( float adjustment );

	void SetStartTime( float startTime );

	bool ShouldAdjustClient() const;

private:
	friend class AFGWheeledVehicleInfo;

	UPROPERTY( Replicated )
	class AFGWheeledVehicleInfo* mVehicle;

	bool mIsServer = false;

	class AFGVehicleSubsystem* mSubsystem = nullptr;

	UPROPERTY( Replicated )
	class AFGDrivingTargetList* mTargetList;

	UPROPERTY( ReplicatedUsing = OnRep_PauseTarget )
	class AFGTargetPoint* mPauseTarget;

	UPROPERTY( Transient )
	class AFGTargetPoint* mTarget;

	UPROPERTY( Transient )
	class AFGTargetPoint* mPreviousTarget;

	/**
	 * Server only. Stops to make a physical vehicle take a route around an obstacle.
	 */
	TArray< FVector > mDynamicStops;

	/**
	* How much the simulated vehicle deviates from the spline path, replicated.
	* Used for "lifting" vehicles out of other objects before they are physical.
	*/
	UPROPERTY( Replicated )
	FVector mSimulatedLocationOffset = FVector::ZeroVector;

	/**
	* How much the simulated vehicle deviates from the spline path, non-replicated (independently calculated on server and client).
	* Used to create smooth transitions from physical to simulated vehicles.
	*/
	FVector mLocalLocationOffset = FVector::ZeroVector;
	FRotator mLocalRotationOffset = FRotator::ZeroRotator;
	
	FVector mVelocityVector = FVector::ZeroVector;

	/**
	 * Has reached the end of the road? Only for non-circular paths.
	 */
	UPROPERTY( Replicated )
	bool mEndOfPath = false;

	/**
	 * Actual time spent on the current target in physical mode
	 */
	float mRealTimeSpentOnTarget = 0.0f;

	/**
	 * For debug purposes, to know how well the physical vehicle is doing compared to simulated mode
	 */
	float mTargetTimeFulfilment = 0.0f;
	
	/**
	 * Used for dynamically searching for vehicle 
	 */
	FVector mDeadlockSegmentCenter;

	/**
	 * The simulated time it takes for this vehicle to get from the previous to the current target.
	 */
	float mTargetTime = 0.0f;

	/**
	 * The simulated time the vehicle has spent trying to reach the current target
	 */
	float mTimeSpentOnTarget = 0.0f;

	/**
	 * The simulated time the vehicle has spent on the path since the path origin (reset every lap)
	 */
	float mTimeSpentOnPath = 0.0f;

	/**
	 * The normalized progress on the path, where each target is worth 1.0
	 */
	float mPathProgress = 0.0f;

	/**
	 * Normalized progress from the previous target to the current one, between 0.0 and 1.0
	 */
	float mTargetProgress = 0.0f;

	/**
	 * Canonical start time for server and ideally client too (see mClientStartTime).
	 */
	UPROPERTY( ReplicatedUsing = OnRep_ServerStartTime )
	float mServerStartTime = 0.0f;

	/**
	 * For client to know at what time the server stopped moving, in case mIsMoving is false.
	 * In that case this is used to continuously recalculate mServerStartTime on client.
	 */
	UPROPERTY( Replicated )
	float mServerPauseTime = 0.0f;

	/**
	 * Continuously adjusted to match mServerStartTime, in case they are not matching.
	 */
	float mClientStartTime = 0.0f;

	/**
	 * Should we trust the simulated location and rotation?
	 */
	bool mHasValidPosition = false;

	/**
	 * Whether path progress is paused because the physical vehicle has not caught up yet (so should never be true for simulated vehicles).
	 */
	bool mIsPaused = false;

	/**
	 * The path-progression time at which this vehicle was paused.
	 */
	float mPauseTime = 0.0f;

	int counter = 0;

	/**
	 * Whether path progress is paused because the vehicle is placed at a docking station waiting for docking to complete.
	 */
	bool mIsDocked = false;

	/**
	 * Whether path progress is paused because the vehicle is blocked by other vehicles.
	 */
	bool mIsBlocked = false;

	/**
	 * Is the vehicle moving? Written on the server as a summary of several properties. Read on client to determine if the vehicle should be standing still.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_IsMoving )
	bool mIsMoving = false;

	/**
	 * How long has this vehicle been blocked?
	 */
	float mTimeBlocked = 0.0f;

	/**
	 * List of the vehicles this vehicle is being blocked by.
	 */
	TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > > mBlockingVehicles;

	/**
	 * List of the vehicles that are in a deadlock with this vehicle.
	 */
	TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > > mDeadlockingVehicles;

	int mDeadlockId = -1;

	/**
	 * The simulated location and rotation of this vehicle.
	 */
	FVector mSimulatedLocation;
	FRotator mSimulatedRotation;
};

FORCEINLINE float AdjustAngle( float angle )
{
	while( angle < -180.0f )
	{
		angle += 360.0f;
	}
	while( angle > 180.0f )
	{
		angle -= 360.0f;
	}
	return angle;
}

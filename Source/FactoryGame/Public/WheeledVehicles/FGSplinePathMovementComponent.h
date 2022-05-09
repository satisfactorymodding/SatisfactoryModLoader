// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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

	void ForceClaimTemporaryEssentialTargets();

	void DestroyPath_Server();

#ifdef DEBUG_SELF_DRIVING
	void DrawDebug( int debugLevel ) const;
#endif

	void TransitionToSplinePath_Server( class AFGTargetPoint* target, const TArray< FVector >& intermediateStops, bool startReversing = false );

	UFUNCTION( Unreliable, NetMulticast )
	void TransitionToSplinePath_Multi( class AFGTargetPoint* target, const TArray< FVector >& intermediateStops, bool startReversing, bool skipTemporaryPath );

	DECLARE_DELEGATE_OneParam( FTargetReached, class AFGTargetPoint* );
	FTargetReached mTargetReachedDelegate;

	void SetPaused( bool isPaused );
	bool IsPaused() const { return mIsPaused; }

	bool IsOnCanonPath() const { return mTemporaryPath == nullptr; }

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

	bool IsOnTemporaryPath() const { return mIsOnTemporaryPath; }

	float GetTimeSpentOnPath() const { return mTimeSpentOnPath; }
	float GetTimeSpentOnRegularPath() const;

	void ResetTarget( bool resetStatus );

	const TSet< TWeakObjectPtr< class AFGTargetPoint > >& GetTemporaryClaimTargets() const { return mTemporaryClaimTargets; }
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

#ifdef DEBUG_SELF_DRIVING
	void DrawDebugVehicle( int visualDebugLevel, int textualDebugLevel );
#endif

	void AdvanceOnSplinePath();

	void TryClaimTarget();

	void SetTarget( class AFGTargetPoint* newTarget, bool resetStatus );

	void ReleaseTemporaryTargets();

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

	UPROPERTY( Replicated )
	FVector mSimulatedLocationOffset = FVector::ZeroVector;

	FVector mVelocityVector = FVector::ZeroVector;

	UPROPERTY( Replicated )
	bool mEndOfPath = false;

	float mRealTimeSpentOnTarget = 0.0f;
	float mTargetTimeFulfilment = 0.0f;
	
	FVector mDeadlockSegmentCenter;

	UPROPERTY( Transient )
	class USplineComponent* mTemporaryPath;

	float mTargetTime = 0.0f;
	float mTimeSpentOnTarget = 0.0f;
	float mTimeSpentOnPath = 0.0f;
	float mLastTimeSpentOnRegularPath = 0.0f;
	float mPathProgress = 0.0f;
	float mTargetProgress = 0.0f;
	float mTempDistance = 0.0f;
	float mTempStraightDistance = 0.0f;
	float mTempSpeed = 0.0f;

	UPROPERTY( ReplicatedUsing = OnRep_ServerStartTime )
	float mServerStartTime = 0.0f;

	UPROPERTY( Replicated )
	float mServerPauseTime = 0.0f;

	float mClientStartTime = 0.0f;

	bool mHasValidPosition = false;

	bool mIsPaused = false;
	float mPauseTime = 0.0f;

	int mIntermediateStopsLeft = 0;
	float mTemporaryProgressStart = 0.0f;

	int counter = 0;

	bool mIsDocked = false;

	bool mIsBlocked = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsMoving )
	bool mIsMoving = false;

	float mTimeBlocked = 0.0f;

	bool mIsOnTemporaryPath = false;

	TSet< TWeakObjectPtr< class AFGTargetPoint > > mTemporaryClaimTargets;
	TSet< TWeakObjectPtr< class AFGTargetPoint > > mTemporaryEssentialClaimTargets;
	int mTemporaryClaimTargetsForceClaimLevel = 0;
	bool mTemporaryClaimTargetsWereReset = false;
	TArray< FVector > mTemporarySearchPoints;
	FVector mTemporarySegmentCenter;
	TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > > mBlockingVehicles;
	TSet< TWeakObjectPtr< class AFGWheeledVehicleInfo > > mDeadlockingVehicles;

	int mDeadlockId = -1;

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

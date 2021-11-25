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

	void DestroyPath_Server();

	void DrawDebug( int debugLevel ) const;

	void TransitionToSplinePath_Server( class AFGTargetPoint* target, const TArray< FVector >* intermediateStops = nullptr, bool startReversing = false );
	void TransitionToSplinePath( class AFGTargetPoint* target, const TArray< FVector >* intermediateStops = nullptr, bool startReversing = false );

	DECLARE_DELEGATE_OneParam( FTargetReached, class AFGTargetPoint* );
	FTargetReached mTargetReachedDelegate;

	void SetPaused( bool isPaused );
	bool IsPaused() const { return mIsPaused; }

	bool IsOnCanonPath() const { return mTemporaryPath == nullptr; }

	bool HasValidPosition() const { return mHasValidPosition; }

	bool IsDocked() const { return mIsDocked; }
	void SetIsDocked( bool isDocked );

	bool IsBlocked() const { return mIsBlocked; }
	void SetIsBlocked( class AFGWheeledVehicle* blockingVehicle );
	void ResetIsBlocked();

	void ResetTransitionTarget() { mTransitionTarget = nullptr; }

	void DrawTargetDebug( bool drawSearchPoints ) const;

	void SetIsDeadlocked( bool isDeadlocked, bool notify = true );
	bool IsDeadlocked() const { return mIsDeadlocked; }

	bool IsOnTemporaryPath() const { return mIsOnTemporaryPath; }

	float GetTimeSpentOnPath() const { return mTimeSpentOnPath; }
	float GetTimeSpentOnRegularPath() const;

	void ResetTarget();

	float GetTargetWaitTime() const { return mTargetWaitTime; }
	bool IsWaitingAtTarget() const { return mTargetWaitTime > 0.0f; }

	const TSet< TWeakObjectPtr< class AFGTargetPoint > >& GetTemporaryClaimTargets() const { return mTemporaryClaimTargets; }
	const TSet< TWeakObjectPtr< class AFGWheeledVehicle > >& GetBlockingVehicles() const { return mBlockingVehicles; }

	bool TryClaim( class AFGTargetPoint* target, bool essentialsOnly );

	bool IsMoving() const { return mIsMoving; }

private:
	static void GetShortestRotation( FRotator& rotation );

	bool HasData() const;

	float GetServerTime() const;
	
	UFUNCTION()
	void OnRep_TransitionTarget();

	UFUNCTION()
	void OnRep_ServerStartTime();

	UFUNCTION()
	void OnRep_IsDocked();

	UFUNCTION()
	void OnRep_IsBlocked();

	bool TickSplinePathMovement( double deltaTime );

#ifdef DEBUG_SELF_DRIVING
	void DrawDebugVehicle( int visualDebugLevel, int textualDebugLevel );
#endif

	void AdvanceOnSplinePath();

	void TryClaimTarget();

	void SetTarget( class AFGTargetPoint* newTarget );

	float GetStartTime( float adjustment );

	void SetStartTime( float startTime );

	bool ShouldAdjustClient() const;

public:
	class AFGWheeledVehicle* mVehicle = nullptr;
	class AFGSimulatedWheeledVehicle* mSimulatedVehicle = nullptr;

	bool mIsServer = false;

	UPROPERTY( Replicated )
	class AFGDrivingTargetList* mTargetList;

	UPROPERTY( Transient )
	class AFGTargetPoint* mTarget;

	UPROPERTY( Transient )
	class AFGTargetPoint* mPreviousTarget;

	FVector mSimulatedLocation;
	FRotator mSimulatedRotation;

	FVector mVelocityVector = { 0.0f, 0.0f, 0.0f };

	UPROPERTY( Replicated )
	bool mEndOfPath = false;

	float mRealTimeSpentOnTarget = 0.0f;
	float mTargetTimeFulfilment = 0.0f;

private:
	UPROPERTY( Transient )
	class USplineComponent* mTemporaryPath;

	UPROPERTY( ReplicatedUsing = OnRep_TransitionTarget)
	class AFGTargetPoint* mTransitionTarget;

	class AFGVehicleSubsystem* mSubsystem = nullptr;

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

	float mClientStartTime = 0.0f;

	bool mHasValidPosition = false;

	bool mIsPaused = false;
	float mPauseTime = 0.0f;

	float mTargetWaitTime = 0.0f;

	int mIntermediateStopsLeft = 0;
	float mTemporaryProgressStart = 0.0f;

	int counter = 0;

	UPROPERTY( ReplicatedUsing = OnRep_IsDocked )
	bool mIsDocked = false;

	UPROPERTY( ReplicatedUsing = OnRep_IsBlocked )
	bool mIsBlocked = false;

	float mTimeBlocked = 0.0f;

	bool mIsOnTemporaryPath = false;

	TSet< TWeakObjectPtr< class AFGTargetPoint > > mTemporaryClaimTargets;
	TSet< TWeakObjectPtr< class AFGTargetPoint > > mTemporaryEssentialClaimTargets;
	int mTemporaryClaimTargetsForceClaimLevel = 0;
	bool mTemporaryClaimTargetsWereReset = false;
	TArray< FVector > mTemporarySearchPoints;
	FVector mTemporarySegmentCenter;
	FVector mDeadlockSegmentCenter;
	TSet< TWeakObjectPtr< class AFGWheeledVehicle > > mBlockingVehicles;
	TSet< TWeakObjectPtr< class AFGWheeledVehicle > > mCoDeadlockedVehicles;

	bool mIsDeadlocked = false;

	bool mIsMoving = false;
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

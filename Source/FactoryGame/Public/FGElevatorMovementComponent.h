// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameFramework/MovementComponent.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "FGElevatorMovementComponent.generated.h"

class AFGBuildableElevatorFloorStop;

USTRUCT(BlueprintType)
struct FElevatorControlPoint
{
	GENERATED_USTRUCT_BODY()
public:
	// The position of the point 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location, meta=(MakeEditWidget=true))
	FVector PositionControlPoint;
	
	// Is the location relative to the root components initial location
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Location)
	bool bPositionIsRelative;

	FElevatorControlPoint()
	{
		PositionControlPoint = FVector::ZeroVector;
		bPositionIsRelative = true;
	}
	FElevatorControlPoint(FVector InPosition, bool bIsRelative)
	{
		PositionControlPoint = InPosition;
		bPositionIsRelative = bIsRelative;
	}
	
	UPROPERTY()
	float StartTime;
	UPROPERTY()
	float DistanceToNext;
	UPROPERTY()
	float Percentage;
};

/**
 * Movement Component responsible for moving and updating an elevator cabin. It is based on the FInterpToMovementComponent (much of the code is clipped from there)
 * This component however is simplified. Its only intended usage is to move between 2 points. Additionally, it behaves differently than other movements comps
 * Its owning actor should not replicate movement. The idea is that the movement is simple and predictable so clients will get the control point information
 * replicated and they will simulate movement themselves locally.
 */
UCLASS( ClassGroup=Movement, BlueprintType )
class UFGElevatorMovementComponent : public UMovementComponent
{
	GENERATED_BODY()

public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnMovementStopped );

	UFGElevatorMovementComponent();
	
	//Begin UActorComponent Interface
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void BeginPlay() override;
	virtual void ApplyWorldOffset(const FVector& InOffset, bool bWorldShift) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	//End UActorComponent Interface

	//Begin UMovementComponent Interface
	virtual void StopMovementImmediately() override;
	//End UMovementComponent Interface

	/**
	 * This will check to see if the InterpTo is still in the world.  It will check things like
	 * the KillZ, outside world bounds, etc. and handle the situation.
	 */
	virtual bool CheckStillInWorld();

	/** Clears the reference to UpdatedComponent, fires stop event, and stops ticking. */
	UFUNCTION(BlueprintCallable, Category="FactorGame|Components|ElevatorMovement")
	void StopSimulating(const FHitResult& HitResult);

	bool HasStoppedSimulation() { return UpdatedComponent == NULL; }

	/**
	 * Compute remaining time step given remaining time and current iterations.
	 * The last iteration (limited by MaxSimulationIterations) always returns the remaining time, which may violate MaxSimulationTimeStep.
	 *
	 * @param RemainingTime		Remaining time in the tick.
	 * @param Iterations		Current iteration of the tick (starting at 1).
	 * @return The remaining time step to use for the next sub-step of iteration.
	 * @see MaxSimulationTimeStep, MaxSimulationIterations
	 * @see ShouldUseSubStepping()
	 */
	float GetSimulationTimeStep(float RemainingTime, int32 Iterations) const;

	/**
	 * Determine whether or not to use substepping in the InterpTo motion update.
	 * If true, GetSimulationTimeStep() will be used to time-slice the update. If false, all remaining time will be used during the tick.
	 * @return Whether or not to use substepping in the InterpTo motion update.
	 * @see GetSimulationTimeStep()
	 */
	virtual bool ShouldUseSubStepping() const;

	/* Add a control point that represents a position. */
	UFUNCTION(BlueprintCallable, Category = "Control")
	virtual void AddControlPointPosition(FVector Pos, bool bPositionIsRelative = true);
	
	/* Reset to start. Sets time to zero and direction to 1.  */
	UFUNCTION(BlueprintCallable, Category = "Control")
	void RestartMovement(float InitialDirection = 1.0f, float clientUpdateTime = 0.f );

	/* Initialise the control points array. Call after adding control points if they are add after begin play .  */
	UFUNCTION(BlueprintCallable, Category = "Control")
	void FinalizeControlPoints();

	/* Clear the control points array and set to stopped. */
	UFUNCTION(BlueprintCallable, Category = "Control")
	void ResetControlPoints();

	UFUNCTION(BlueprintCallable, Category="FactorGame|Components|ElevatorMovement")
	void SetDuration(float newDuration ) { mDuration = newDuration; }

	UFUNCTION(BlueprintCallable, Category="FactorGame|Components|ElevatorMovement")
	float GetTimeToDestination() const { return mDuration - ( mCurrentTime * mDuration ); }

	UFUNCTION()
	void OnRep_ControlPoints( TArray< FElevatorControlPoint > previousControlPoints );

	FVector GetDistanceMovedLastFrame() const { return mDistanceMovedLastFrame; }
	
	UPROPERTY(BlueprintAssignable)
	FOnMovementStopped OnMovementStopped;

	void SetOwningElevatorSpeed( float speed ) { mElevatorSpeed = speed; }

	void SetClientInitialRepControlPoints( const FElevatorControlPoint& point1, const FElevatorControlPoint& point2 )
	{
		mClientControlPointsFromInitialRep.Empty(  );
		mClientControlPointsFromInitialRep.Add( point1 );
		mClientControlPointsFromInitialRep.Add( point2 );
	}

	FORCEINLINE bool GetIsClientUsingCachedControlPoints() const { return mIsUsingClientCachedControlPoints; }

	// Called each time the movement component is moved to force all occupying characters to also move that distance (to avoid clipping through collision)
	// This is similar to movement components "based on" behavior however this treats even non based pawns as "based"
	// It also skips pawns that are currently based upon this comp as that would result in "double" updates
	void ForceMoveOccupyingPawns( FVector moveDelta );
	
protected:
	/* How long to take to move from the first point to the last (or vice versa) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Control,meta=(UIMin=0.1f, ClampMin=0.1f))
	float mDuration;
	
	/** If true, will pause movement on impact. If false it will behave as if the end of the movement range was reached based on the BehaviourType. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Behaviour)
	uint32 mPauseOnImpact:1;

	/** If true, will sweep for blocking collision during movement. If false, it will simply teleport to the next position and ignore collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	bool mSweep = true;

	/** Physics teleport type. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	ETeleportType mTeleportType = ETeleportType::None;

	/* Do we want this comp to perform CheckStillInWorld checks? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Behaviour)
	bool mCheckIfStillInWorld = true;

	/**
	 * If true, forces sub-stepping to break up movement into discrete smaller steps to improve accuracy of the trajectory.
	 * Objects that move in a straight line typically do *not* need to set this, as movement always uses continuous collision detection (sweeps) so collision is not missed.
	 * Sub-stepping is automatically enabled when under the effects of gravity or when homing towards a target.
	 * @see MaxSimulationTimeStep, MaxSimulationIterations
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Simulation)
	uint32 mForceSubStepping:1;


	/**
	 * Max time delta for each discrete simulation step.
	 * Lowering this value can address issues with fast-moving objects or complex collision scenarios, at the cost of performance.
	 *
	 * WARNING: if (MaxSimulationTimeStep * MaxSimulationIterations) is too low for the min framerate, the last simulation step may exceed MaxSimulationTimeStep to complete the simulation.
	 * @see MaxSimulationIterations, bForceSubStepping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="0.0166", ClampMax="0.50", UIMin="0.0166", UIMax="0.50"), Category=Simulation)
	float mMaxSimulationTimeStep;

	/**
	 * Max number of iterations used for each discrete simulation step.
	 * Increasing this value can address issues with fast-moving objects or complex collision scenarios, at the cost of performance.
	 *
	 * WARNING: if (MaxSimulationTimeStep * MaxSimulationIterations) is too low for the min framerate, the last simulation step may exceed MaxSimulationTimeStep to complete the simulation.
	 * @see MaxSimulationTimeStep, bForceSubStepping
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(ClampMin="1", ClampMax="25", UIMin="1", UIMax="25"), Category=Simulation)
	int32 mMaxSimulationIterations;
	
	/* List of control points to visit. */
	UPROPERTY(ReplicatedUsing=OnRep_ControlPoints, BlueprintReadWrite, Category=Control)
	TArray<FElevatorControlPoint> mControlPoints;

	UPROPERTY()
	TArray< FElevatorControlPoint > mClientControlPointsFromInitialRep;


#if WITH_EDITOR
	//~ Begin UObject Interface.
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
	//~ End UObject Interface.
#endif // WITH_EDITOR

protected:

	/** Deal with an impact. Change direction, stop etc depending on the current behaviour setting. */
	virtual void HandleImpact(const FHitResult& Hit, float TimeSlice=0.f, const FVector& MoveDelta = FVector::ZeroVector) override;

	/** Compute the distance for the given time. */
	FVector ComputeMoveDelta(float Time, const TArray< FElevatorControlPoint >& controlPoints ) const;
		
	/* Update the control points. Adjusts the positions of there are any actor control points as well as updating the spline type */
	virtual void UpdateControlPoints(bool InForceUpdate);	

	/* Calculate the new current time */
	float CalculateNewTime( float TimeNow, float Delta, FHitResult& HitResult, bool InBroadcastEvent, bool& OutStopped, float& OutTimeRemainder );

protected:
	float mMaxDesyncTimeFromServer = 0.333f; // 1/3rd second
	
	UPROPERTY( Replicated )
	float mElevatorSpeed;
	
	FVector mDistanceMovedLastFrame;
	
	/* Current position on spline */
	float mCurrentTime;

	/** The amount of time the client has used to update this movement component between control points. */
	float mClientUpdateTime;
	
	/* The amount of time the server has used to update this component between set control points. Used by clients to sync movements if hitches occur */
	UPROPERTY( Replicated )
	float mServerUpdateTime;

	/** Is the client updating off a local copy of the previous control points? This is used to allow clients to complete any transit without stopping short from a server control point clear */
	bool mIsUsingClientCachedControlPoints;
	
	/* User to */
	float mTimeMultiplier;

	/* Current direction along spline timeline */
	float mCurrentDirection;

	/* Have we hit something and are waiting for it to move to carry on moving */
	bool mIsWaiting;

	/* Have we stopped (because we hit something, or reached the end of the cycle */
	bool mStopped;

	/* Are there any actor control points in use*/
	bool mContainsActorControlPoints;

	/** Minimum delta time considered when ticking. Delta times below this are not considered. This is a very small non-zero positive value to avoid potential divide-by-zero in simulation code. */
	static const float MIN_TICK_TIME;

private:
	float mTotalDistance;

	FVector mStartLocation;
	bool mPointsFinalized;
	
};
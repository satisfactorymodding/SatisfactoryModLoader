// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FGVehicleSubsystem.h"
#include "SharedStats.h"
#include "FGWheeledVehicleAIController.generated.h"

DECLARE_CYCLE_STAT( TEXT( "WheeledVehicle" ), STAT_ExecuteInterface_WheeledVehicle, STATGROUP_ExecuteInterface );

UCLASS()
class AFGWheeledVehicleAIController : public AAIController
{
	GENERATED_BODY()
private:
	/**
	 * Set of high-level plans the vehicle can have, and that determine the vehicle's actions
	 */
	enum class Plan
	{
		None,
		Halt,
		FollowInReverse,
		ReverseToAlignment,
		ForwardToAlignment,
		FollowTarget,
		DriveAroundTarget,
		AwaitTarget,
		PauseAtTarget,
		StayAtDock,
		AwaitBlock,
		BreakOut,
		GhostToNext,
		RouteToStation,
		NoFuel,
		NoTarget
	};

	/**
	 * Used to indicate at what part of the vehicle a collision has been detected
	 */
	enum class Quadrant
	{
		None,
		FrontLeft,
		FrontRight,
		BackLeft,
		BackRight
	};

	/**
	 * Contains all the parameters that determine the current state of the vehicle
	 */
	struct Input
	{
		FVector Location = { 0.0f, 0.0f, 0.0f };
		FVector TargetLocation = { 0.0f, 0.0f, 0.0f };
		float YawToTarget = 0.0f;
		float ReverseYawToTarget = 0.0f;
		float YawDifference = 0.0f;
		float Acceleration = 0.0f;
		float Speed = 0.0f;
		float TargetSpeed = 0.0f;
		bool TargetMovingAway = false;
		bool IsReversing = false;
		float Distance3D = 0.0f;
		float Distance2D = 0.0f;
		bool TargetInFront = false;
		bool TargetPaused = false;
		//bool TargetChanged = false;
	};

	/**
	 * Contains the parameters the controller can manipulate as input to the vehicle
	 */
	struct Output
	{
		bool BrakeAsReverse = true;
		float Steering = 0.0f;
		float Throttle = 0.0f;
		float Brake = 0.0f;
		bool Handbrake = false;

		bool Repath = false;
		TArray< FVector > RepathThrough;
	};

public:
	AFGWheeledVehicleAIController();

	//~ Begin AController Interface
	virtual void OnPossess( APawn* InPawn ) override;
	virtual void OnUnPossess() override;
	//~ End AController Interface

	const FString& GetCurrentPlanName() const;
	//FString GetCurrentDockingStepName() const;

private:
	//~ Begin AActor Interface
	virtual void Tick( float DeltaTime ) override;
	//~ End AActor Interface

	void CalculateInput( float deltaTime, Input& input ) const;
	Plan PickPlan( const Input& input ) const;

	/**
	 * Implementation of all of the high-level plans that are listed in the enum Plan
	 */
	void Halt( const Input& input, Output& output );
	void FollowInReverse( const Input& input, Output& output );
	void ReverseToAlignment( const Input& input, Output& output );
	void ForwardToAlignment( const Input& input, Output& output );
	void FollowTarget( const Input& input, Output& output );
	void DriveAroundTarget( const Input& input, Output& output );
	void AwaitTarget( const Input& input, Output& output );
	void PauseAtTarget( const Input& input, Output& output );
	void StayAtDock( const Input& input, Output& output );
	void AwaitBlock( const Input& input, Output& output );
	void BreakOut( const Input& input, Output& output );
	void GhostToNext( const Input& input, Output& output );
	void NoFuel( const Input& input, Output& output );
	void NoTarget( const Input& input, Output& output );

	void Follow( const Input& input, Output& output, bool reversing ) const;

	static void CalculateThrottle( const Input& input, Output& output, bool shouldReverse );

	void ApplyOutput( const Input& input, const Output& output );

	bool FindNewTarget();

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "Vehicle" )
	void VehiclePossessed( class AFGWheeledVehicle* vehicle );

private:
	void CreatePlans();

	void CreateDetectionBox();
	bool CheckCollisions( float deltaTime );

#if DEBUG_SELF_DRIVING
	void DrawDebug( float deltaTime, const Input& input, const Output& output );
#endif

	const FString& GetPlanName( Plan plan ) const;

public:
	static constexpr float FullSteeringAngleThreshold = 45.0f;
	static constexpr float FullSteeringDifferenceThreshold = 45.0f;
	static constexpr float ThrottleReleaseThreshold = 5.0f;
	static constexpr float VehicleStillThreshold = 100.0f;
	static constexpr float VehicleNeedsThrottleThreshold = 500.0f;
	//static constexpr float MaxDistanceToSimulationToSides = 1000.0f;
	//static constexpr float InFrontThreshold = 25.0f;
	static constexpr float AlignedAngleAim = 5.0f;
	static constexpr float TooFastToFollowInReverse = 1000.0f;

private:
	TWeakObjectPtr< class AFGWheeledVehicle > mVehicle;
	TWeakObjectPtr< class UFGWheeledVehicleMovementComponent > mMovement;
	TWeakObjectPtr< class UFGSplinePathMovementComponent > mSimulationMovement;

	class AFGTargetPoint* mCurrentTarget = nullptr;
	class AFGTargetPoint* mPreviousTarget = nullptr;
	
	FVector mDetectionBoxExtent;
	FVector mDetectionBoxLocalOrigin;

	TArray< Quadrant > mCollidingQuadrants;

	bool mBlockedFromLeft = false;
	bool mBlockedFromRight = false;
	bool mBlockedFromFront = false;
	bool mBlockedFromBack = false;
	bool mBlockedByOtherVehicle = false;

	float mIsStuckTimer = 0.0f;
	float mTimeSpentOnTarget = 0.0f;
	int mBreakoutCount = 0;
	//float mTimeToPause = 0.0f;

	class AFGTargetPoint* mDockTarget = nullptr;

	static constexpr float MaxDistanceToPausePoint = 100.0f;
	float mDistanceToPausePointSquared = 0.0f;
	bool mApproachingPausePoint = false;
	bool mPausePointReached = false;

	Plan mPreviousPlan = Plan::None;
	Plan mPlan = Plan::None;

	//DockingStep mPreviousDockingStep = DockingStep::None;
	//DockingStep mDockingStep = DockingStep::None;

	TMap < Plan, TFunction< void( const Input& input, Output& output ) > > mPlanFunctionMap;
	TMap < Plan, FString > mPlanNameMap;

	// Debug
	float mOutputThrottleSampleSum = 0.0f;
	float mMovementThrottleSampleSum = 0.0f;
	float mOutputBrakeSampleSum = 0.0f;
	float mMovementBrakeSampleSum = 0.0f;
	float mOutputHandbrakeSampleSum = 0.0f;
	float mMovementHandbrakeSampleSum = 0.0f;

	float mOutputThrottleAverage = 0.0f;
	float mMovementThrottleAverage = 0.0f;
	float mOutputBrakeAverage = 0.0f;
	float mMovementBrakeAverage = 0.0f;
	float mOutputHandbrakeAverage = 0.0f;
	float mMovementHandbrakeAverage = 0.0f;

	float mSampleCount = 0.0f;
	float mSampleTime = 0.0f;
};

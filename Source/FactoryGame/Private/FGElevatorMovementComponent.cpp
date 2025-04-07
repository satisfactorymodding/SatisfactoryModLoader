#include "FGElevatorMovementComponent.h"
#include "Net/UnrealNetwork.h"

UFGElevatorMovementComponent::UFGElevatorMovementComponent() : Super() {
	this->mDuration = 1.0;
	this->mPauseOnImpact = false;
	this->mSweep = true;
	this->mTeleportType = ETeleportType::None;
	this->mCheckIfStillInWorld = true;
	this->mForceSubStepping = true;
	this->mMaxSimulationTimeStep = 0.0333;
	this->mMaxSimulationIterations = 10;
	this->mElevatorSpeed = 0.0;
	this->mServerUpdateTime = 0.0;
	this->bAutoRegisterPhysicsVolumeUpdates = false;
}
void UFGElevatorMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGElevatorMovementComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGElevatorMovementComponent::ApplyWorldOffset(const FVector& InOffset, bool bWorldShift){ Super::ApplyWorldOffset(InOffset, bWorldShift); }
void UFGElevatorMovementComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGElevatorMovementComponent, mControlPoints);
	DOREPLIFETIME(UFGElevatorMovementComponent, mElevatorSpeed);
	DOREPLIFETIME(UFGElevatorMovementComponent, mServerUpdateTime);
}
void UFGElevatorMovementComponent::StopMovementImmediately(){ Super::StopMovementImmediately(); }
bool UFGElevatorMovementComponent::CheckStillInWorld(){ return false; }
void UFGElevatorMovementComponent::StopSimulating(const FHitResult& HitResult){  }
float UFGElevatorMovementComponent::GetSimulationTimeStep(float RemainingTime, int32 Iterations) const{ return float(); }
bool UFGElevatorMovementComponent::ShouldUseSubStepping() const{ return false; }
void UFGElevatorMovementComponent::AddControlPointPosition(FVector Pos, bool bPositionIsRelative){  }
void UFGElevatorMovementComponent::RestartMovement(float InitialDirection, float clientUpdateTime){  }
void UFGElevatorMovementComponent::FinalizeControlPoints(){  }
void UFGElevatorMovementComponent::ResetControlPoints(){  }
void UFGElevatorMovementComponent::OnRep_ControlPoints(TArray<FElevatorControlPoint> previousControlPoints){  }
void UFGElevatorMovementComponent::ForceMoveOccupyingPawns(FVector moveDelta){  }
#if WITH_EDITOR
void UFGElevatorMovementComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent){ Super::PostEditChangeProperty(PropertyChangedEvent); }
#endif
void UFGElevatorMovementComponent::HandleImpact(const FHitResult& Hit, float TimeSlice, const FVector& MoveDelta){ Super::HandleImpact(Hit, TimeSlice, MoveDelta); }
void UFGElevatorMovementComponent::UpdateControlPoints(bool InForceUpdate){  }
FVector UFGElevatorMovementComponent::ComputeMoveDelta(float Time, const TArray<FElevatorControlPoint>& controlPoints) const{ return FVector(); }
float UFGElevatorMovementComponent::CalculateNewTime(float TimeNow, float Delta, FHitResult& HitResult, bool InBroadcastEvent, bool& OutStopped, float& OutTimeRemainder){ return float(); }

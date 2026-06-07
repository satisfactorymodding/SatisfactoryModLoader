#include "WheeledVehicles/FGVehicleAutopilotComponent.h"
#include "Net/UnrealNetwork.h"

UFGVehicleAutopilotComponent::UFGVehicleAutopilotComponent() : Super() {
	this->mVehicleMass = 6000.0;
	this->mVehicleCrossSectionalArea = 7.5;
	this->mDragCoefficient = 0.7;
	this->mRollingResistanceCoefficient = 0.0045;
	this->mMaxAirBrakingEffort = 20.0;
	this->mDynamicBrakingEffortCurve.EditorCurveData.DefaultValue = 3.40282e+38;
	this->mDynamicBrakingEffortCurve.EditorCurveData.PreInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mDynamicBrakingEffortCurve.EditorCurveData.PostInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mDynamicBrakingEffortCurve.ExternalCurve = nullptr;
	this->mTractiveEffortCurve.EditorCurveData.DefaultValue = 3.40282e+38;
	this->mTractiveEffortCurve.EditorCurveData.PreInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mTractiveEffortCurve.EditorCurveData.PostInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mTractiveEffortCurve.ExternalCurve = nullptr;
	this->mCurvatureSpeedLimitCurve.EditorCurveData.DefaultValue = 3.40282e+38;
	this->mCurvatureSpeedLimitCurve.EditorCurveData.PreInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mCurvatureSpeedLimitCurve.EditorCurveData.PostInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mCurvatureSpeedLimitCurve.ExternalCurve = nullptr;
	this->mAutopilotThrottleChangeRate = 0.2;
	this->mAutopilotAirbrakeReleaseRate = 1.0;
	this->mAutopilotTargetApproachSpeed = 250.0;
	this->mAutopilotTargetStopDistanceTolerance = 10.0;
	this->mAutopilotSpeedLimitChangeRate = 500.0;
	this->mAutopilotVehicleAvoidanceSpacing = 400.0;
	this->mAutopilotSpeedMatchingDistanceFactor = 2.0;
	this->mAutopilotWaitTimeToDeadlock = 120.0;
	this->mWheelSteeringMagnitudeScale = 1.0;
	this->mCurrentServerPathSegment = nullptr;
	this->mNextServerPathSegment = nullptr;
	this->mCurrentServerVehicleSplinePosition = 0.0;
	this->mCurrentServerVehicleForwardSpeed = 0.0;
	this->mServerPathCurvatureSpeedLimit = 0.0;
	this->mServerClosestStopTargetIsSet = false;
	this->mServerClosestStopTarget.DistanceToStopTarget = 0.0;
	this->mCurrentServerTimestamp = 0.0;
	this->mTimeSpentWaitingOnCurrentFreeBlock = 0.0;
	this->mLastVehicleLocation = FVector::ZeroVector;
	this->mLastVehicleRotation = FRotator::ZeroRotator;
	this->mHasAuthoritativeVehicleLocation = false;
	this->mCurrentSimulatedPathSegment = nullptr;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = false;
	this->PrimaryComponentTick.bStartWithTickEnabled = false;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
}
void UFGVehicleAutopilotComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mCurrentServerPathSegment);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mNextServerPathSegment);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mCurrentServerVehicleSplinePosition);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mCurrentServerVehicleForwardSpeed);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mServerPathCurvatureSpeedLimit);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mServerClosestStopTargetIsSet);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mServerClosestStopTarget);
	DOREPLIFETIME(UFGVehicleAutopilotComponent, mCurrentServerTimestamp);
}
bool UFGVehicleAutopilotComponent::ShouldTickAutopilotComponent() const{ return false; }
void UFGVehicleAutopilotComponent::TickAutopilotComponent_Parallel(float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::PostTickAutopilotComponent_GameThread(const FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
bool UFGVehicleAutopilotComponent::ShouldSave_Implementation() const{ return IFGSaveInterface::ShouldSave_Implementation(); }
void UFGVehicleAutopilotComponent::PopulateVehicleVisualState(FFGVehicleVFXData& vehicleVisualState) const{ }
void UFGVehicleAutopilotComponent::ResetAutopilotStateOnServer(){ }
float UFGVehicleAutopilotComponent::GetMaxVehicleMovementSpeed() const{ return float(); }
void UFGVehicleAutopilotComponent::TickVehicleMovementServer_Parallel(float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::PostTickVehicleMovementServer_GameThread(const FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::TickVehicleMovementSimulated_Parallel(float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::PostTickVehicleMovementSimulated_GameThread(const FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::RecalculateVehicleRoute_Parallel(FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::InvalidateVehicleRoute_ThreadSafe(){ }
void UFGVehicleAutopilotComponent::UpdateNextVehiclePathSegment_ThreadSafe(){ }
bool UFGVehicleAutopilotComponent::UpdateVehicleAutopilotStateOnServer(FVehicleAutopilotComponentSimData& simData){ return false; }
void UFGVehicleAutopilotComponent::MoveVehicleAlongSplineOnServer_Parallel(float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::MoveVehicleAlongSplineOnClient_Parallel(float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
float UFGVehicleAutopilotComponent::CalculateMaxVehicleMovementSpeed() const{ return float(); }
void UFGVehicleAutopilotComponent::ReleaseVehiclePathBlockReservations_Parallel(){ }
void UFGVehicleAutopilotComponent::CleanupOldVehiclePathBlockReservations_Parallel(const TSet<FVehiclePathBlockReference>& referencedPathBlockReservations){ }
void UFGVehicleAutopilotComponent::UpdateVehiclePositionFromPathSplineAndDistance_Parallel(const AFGVehiclePathSegment* currentPathSegment, float distanceAlongSpline, float vehicleForwardSpeed, float deltaTime, FVehicleAutopilotComponentSimData& simData){ }
void UFGVehicleAutopilotComponent::PostUpdateVehiclePosition_GameThread(const FVehicleAutopilotComponentSimData& simData){ }
float UFGVehicleAutopilotComponent::CalculateVehicleHalfLength(const AFGWheeledVehicle* wheeledVehicle){ return float(); }
FVehicleCommonInputs UFGVehicleAutopilotComponent::CalculateCommonVehicleInputs(const AFGVehiclePathSegment* currentPathSegment, float currentDistanceAlongSpline, float currentVehicleSpeed) const{ return FVehicleCommonInputs(); }
FVehicleAutopilotEstimate UFGVehicleAutopilotComponent::CalculateAutopilotEstimate(float currentVehicleSpeed, float desiredVehicleSpeed) const{ return FVehicleAutopilotEstimate(); }
void UFGVehicleAutopilotComponent::UpdateVehicleAutopilot_ThreadSafe(const FVehicleAutopilotInputs& autopilotInputs, FVehicleAutopilotState& autopilotState, float deltaTime) const{ }
FVehicleMovementOutputs UFGVehicleAutopilotComponent::CalculateVehicleMovementParameters(const FVehicleCommonInputs& commonInputs, const FVehicleAutopilotState& autopilotState) const{ return FVehicleMovementOutputs(); }
bool UFGVehicleAutopilotComponent::FindPathBlockFromVehiclePosition(float vehicleSplinePosition, FVehicleAutopilotBlockReference& out_autopilotBlockReference, float& out_distanceToEndOfPathBlock) const{ return false; }
bool UFGVehicleAutopilotComponent::CalculatePathBlockSequence(FVehicleAutopilotBlockReference& currentBlockReference, TArray<FVehicleAutopilotBlockReference>& pathBlockSequence) const{ return false; }
float UFGVehicleAutopilotComponent::CalculateTotalDistanceBetweenPathBlocks(const FVehicleAutopilotBlockReference& startBlockReference, const FVehicleAutopilotBlockReference& endBlockReference) const{ return float(); }
FVehicleAutopilotBlockReference UFGVehicleAutopilotComponent::GetPreviousPathBlockReference(const FVehicleAutopilotBlockReference& pathBlockReference) const{ return FVehicleAutopilotBlockReference(); }
FVehicleAutopilotBlockReference UFGVehicleAutopilotComponent::GetNextPathBlockReference(const FVehicleAutopilotBlockReference& pathBlockReference) const{ return FVehicleAutopilotBlockReference(); }
void UFGVehicleAutopilotComponent::ReserveVehiclePathBlocks_Parallel(const TArray<FVehicleAutopilotBlockReference>& pathBlocks, TSet<FVehiclePathBlockReference>& referencedPathBlocks){ }
bool UFGVehicleAutopilotComponent::UpdateVehicleDeadlockStatus_Parallel(const FVehicleCommonInputs& commonInputs, const TArray<FVehicleAutopilotBlockReference>& currentVehicleBlocks, float deltaTime, FVehicleAutopilotComponentSimData& simData){ return false; }
bool UFGVehicleAutopilotComponent::UpdateVehiclePathReservations_Parallel(const FVehicleCommonInputs& commonInputs, float deltaTime, FVehicleAutopilotComponentSimData& simData){ return false; }
void UFGVehicleAutopilotComponent::CalculatePathReservationStopTarget(float maxLookaheadDistance, float vehicleHalfLength, TArray<FVehicleStopTarget>& out_stopTargets) const{ }
void UFGVehicleAutopilotComponent::CalculateDestinationStopTarget(float maxLookaheadDistance, TArray<FVehicleStopTarget>& out_stopTargets) const{ }
void UFGVehicleAutopilotComponent::CalculateVehicleAvoidanceTarget(float maxLookaheadDistance, float vehicleHalfLength, TArray<FVehicleStopTarget>& out_stopTargets) const{ }
TOptional<FVehicleStopTarget> UFGVehicleAutopilotComponent::CalculateClosestStopTarget(const FVehicleCommonInputs& commonInputs, const FVehicleAutopilotState& autopilotState) const{ return TOptional<FVehicleStopTarget>(); }
float UFGVehicleAutopilotComponent::CalculatePathCurvatureSpeedLimit(const FVehicleCommonInputs& commonInputs) const{ return float(); }
void UFGVehicleAutopilotComponent::OnRep_CurrentServerTimestamp(){ }

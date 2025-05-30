// This file has been automatically generated by the Unreal Header Implementation tool

#include "WheeledVehicles/FGWheeledVehicle.h"
#include "Components/BoxComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "FGInventoryComponent.h"
#include "Hologram/FGWheeledVehicleHologram.h"
#include "Net/UnrealNetwork.h"
#include "WheeledVehicles/FGWheeledVehicleMovementComponent.h"

TAutoConsoleVariable<int32> CVarVehicleDebug(TEXT("CVarVehicleDebug"), 0, TEXT(""));
void AFGWheeledVehicle::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGWheeledVehicle, mIsEngineOn);
	DOREPLIFETIME(AFGWheeledVehicle, mAirDampingStrength);
	DOREPLIFETIME(AFGWheeledVehicle, mCurrentFuelAmount);
	DOREPLIFETIME(AFGWheeledVehicle, mIsLoadingVehicle);
	DOREPLIFETIME(AFGWheeledVehicle, mIsUnloadingVehicle);
	DOREPLIFETIME(AFGWheeledVehicle, mVehicleLightsOn);
	DOREPLIFETIME(AFGWheeledVehicle, mVehicleHonkOn);
	DOREPLIFETIME(AFGWheeledVehicle, mTrunkUser);
	DOREPLIFETIME(AFGWheeledVehicle, mIsTrunkOpen);
	DOREPLIFETIME(AFGWheeledVehicle, mInfo);
	DOREPLIFETIME(AFGWheeledVehicle, mTargetList);
	DOREPLIFETIME(AFGWheeledVehicle, mSpeedLimit);
	DOREPLIFETIME(AFGWheeledVehicle, mIsAutopilotEnabled);
	DOREPLIFETIME(AFGWheeledVehicle, mManualDockingState);
	DOREPLIFETIME(AFGWheeledVehicle, mRecordingStatus);
}
AFGWheeledVehicle::AFGWheeledVehicle() : Super() {
	this->mWorkBench = nullptr;
	this->mIsEngineOn = false;
	this->mAirDampingStrength = 2.5;
	this->mRunOverDamageTypeClass = nullptr;
	this->mDamageAtSpeed.EditorCurveData.DefaultValue = 3.40282e+38;
	this->mDamageAtSpeed.EditorCurveData.PreInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mDamageAtSpeed.EditorCurveData.PostInfinityExtrap = ERichCurveExtrapolation::RCCE_Constant;
	this->mDamageAtSpeed.ExternalCurve = nullptr;
	this->mRagdollRunOverMinSpeed = 10.0;
	this->mFuelConsumption = 1.0;
	this->mFuelConsumedWhileRecording = 0.0;
	this->mCurrentFuelAmount = 0.0;
	this->mIsLoadingVehicle = false;
	this->mIsUnloadingVehicle = false;
	this->mVehicleMovement = CreateDefaultSubobject<UFGWheeledVehicleMovementComponent>(TEXT("MovementComp"));
	this->mFoliageCollideBox = CreateDefaultSubobject<UBoxComponent>(TEXT("FoliageBox"));
	this->mFoliageCollideBox->SetMobility(EComponentMobility::Movable);
	this->mVehicleLightsOn = true;
	this->mVehicleHonkOn = false;
	this->mDefaultLockedSprintArmRotation = FRotator::ZeroRotator;
	this->mTrunkUser = nullptr;
	this->mIsTrunkOpen = false;
	this->mFuelInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("FuelInventory"));
	this->mStorageInventory = CreateDefaultSubobject<UFGInventoryComponent>(TEXT("StorageInventory"));
	this->mTargetNodeLinkedList = nullptr;
	this->mNeedsFuelToDrive = true;
	this->mTargetPointClass = nullptr;
	this->mGhostingTimeout = 20.0;
	this->mMaxDistanceToSimulation = 500.0;
	this->mWasFuelAdded = false;
	this->mInfo = nullptr;
	this->mTargetList = nullptr;
	this->mSpeedLimit = -1;
	this->mIsAutopilotEnabled = false;
	this->mRefuelingStation = nullptr;
	this->mManualDockingState = EManualDockingState::MDS_NoDocking;
	this->mCurrentTarget = nullptr;
	this->mRecordingStatus = ERecordingStatus::RS_NoRecording;
	this->mStoredTarget = nullptr;
	this->mHasAutomatedFuelConsumption = false;
	this->mActualAutomatedFuelConsumptionSinceStart = 0.0;
	this->mAutomatedFuelConsumptionStart = 0.0;
	this->mAutomatedFuelConsumptionTimeSkipped = 0.0;
	this->mTargetWaitTime = 0.0;
	this->mHologramClass = AFGWheeledVehicleHologram::StaticClass();
	this->SetReplicatingMovement(false);
	this->mFoliageCollideBox->SetupAttachment(mMesh);
}
void AFGWheeledVehicle::PostInitializeComponents(){ Super::PostInitializeComponents(); }
void AFGWheeledVehicle::BeginPlay(){ Super::BeginPlay(); }
void AFGWheeledVehicle::EndPlay(const EEndPlayReason::Type endPlayReason){ Super::EndPlay(endPlayReason); }
void AFGWheeledVehicle::Destroyed(){ Super::Destroyed(); }
void AFGWheeledVehicle::Tick(float dt){ Super::Tick(dt); }
void AFGWheeledVehicle::DisplayDebug(UCanvas* canvas, const FDebugDisplayInfo& debugDisplay, float& YL, float& YPos){ }
bool AFGWheeledVehicle::DriverEnter(AFGCharacterPlayer* driver){ return bool(); }
bool AFGWheeledVehicle::DriverLeave(bool keepDriving){ return bool(); }
void AFGWheeledVehicle::Server_DriverLeave_Implementation(){ }
void AFGWheeledVehicle::LeavesVehicle(){ }
void AFGWheeledVehicle::SubmergedInWaterUpdated(bool newIsSubmerged){ }
void AFGWheeledVehicle::GainedSignificance_Implementation(){ }
void AFGWheeledVehicle::LostSignificance_Implementation(){ }
bool AFGWheeledVehicle::CanDock_Implementation(EDockStationType atStation) const{ return bool(); }
UFGInventoryComponent* AFGWheeledVehicle::GetDockInventory_Implementation() const{ return nullptr; }
UFGInventoryComponent* AFGWheeledVehicle::GetDockFuelInventory_Implementation() const{ return nullptr; }
void AFGWheeledVehicle::WasDocked_Implementation(AFGBuildableDockingStation* atStation){ }
void AFGWheeledVehicle::WasUndocked_Implementation(){ }
void AFGWheeledVehicle::OnBeginLoadVehicle_Implementation(){ }
void AFGWheeledVehicle::OnBeginUnloadVehicle_Implementation(){ }
void AFGWheeledVehicle::OnTransferComplete_Implementation(){ }
void AFGWheeledVehicle::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGWheeledVehicle::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ }
void AFGWheeledVehicle::UpdateUseState_Implementation( AFGCharacterPlayer* byCharacter, const FVector& atLocation, UPrimitiveComponent* componentHit, FUseState& out_useState){ }
void AFGWheeledVehicle::StartIsLookedAt_Implementation( AFGCharacterPlayer* byCharacter, const FUseState& state){ }
void AFGWheeledVehicle::StopIsLookedAt_Implementation( AFGCharacterPlayer* byCharacter, const FUseState& state){ }
void AFGWheeledVehicle::OnVehicleLanded(){ }
void AFGWheeledVehicle::AddInputBindings(UInputComponent* enhancedInput){ }
void AFGWheeledVehicle::Multicast_OnVehicleEntered_Implementation(AFGCharacterPlayer* driver){ }
void AFGWheeledVehicle::Input_ThrottleSteer(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_GamepadThrottle(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_GamepadBrake(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_GamepadSteer(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_LookAxis(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_Handbrake(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_Honk(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_ToggleCamera(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_ToggleLights(const FInputActionValue& actionValue){ }
void AFGWheeledVehicle::Input_OpenRecorder(const FInputActionValue& actionValue){ }
FVector AFGWheeledVehicle::GetVehicleRealActorLocation() const{ return FVector(); }
UStaticMeshComponent* AFGWheeledVehicle::FindAttachedStaticMesh_Implementation(){ return nullptr; }
UFGWheeledVehicleMovementComponent* AFGWheeledVehicle::GetVehicleMovementComponent() const{ return nullptr; }
bool AFGWheeledVehicle::HasFuel() const{ return bool(); }
float AFGWheeledVehicle::GetForwardSpeed() const{ return float(); }
bool AFGWheeledVehicle::IsValidFuel(TSubclassOf< UFGItemDescriptor > resource) const{ return bool(); }
bool AFGWheeledVehicle::FilterFuelClasses(TSubclassOf< UObject > object, int32 idx) const{ return bool(); }
bool AFGWheeledVehicle::ShouldConsumeFuel() const{ return bool(); }
float AFGWheeledVehicle::GetFuelBurnRatio(){ return float(); }
AFGDrivingTargetList* AFGWheeledVehicle::GetTargetList(bool createIfNeeded){ return nullptr; }
bool AFGWheeledVehicle::GetPathVisibility() const{ return bool(); }
void AFGWheeledVehicle::MeasureVelocities(float deltaTime){ }
FText AFGWheeledVehicle::GetDefaultMapName(TSubclassOf< AFGWheeledVehicle > vehicleType){ return FText(); }
void AFGWheeledVehicle::SyncWithSimulation(){ }
bool AFGWheeledVehicle::HasFullTank() const{ return bool(); }
float AFGWheeledVehicle::GetTotalFuelEnergy() const{ return float(); }
float AFGWheeledVehicle::CalculateFuelNeed() const{ return float(); }
float AFGWheeledVehicle::GetMaxFuelEnergy(TSubclassOf< UFGItemDescriptor > fuelClass){ return float(); }
float AFGWheeledVehicle::GetMaxFuelEnergy() const{ return float(); }
bool AFGWheeledVehicle::HasFuelForRoundtrip() const{ return bool(); }
bool AFGWheeledVehicle::IsSufficientFuelType(TSubclassOf< UFGItemDescriptor > fuelType) const{ return bool(); }
ETransferAnimationState AFGWheeledVehicle::GetTransferAnimationState(float animationLength, float& animationTime) const{ return ETransferAnimationState(); }
void AFGWheeledVehicle::CalculateManualDockingState(){ }
void AFGWheeledVehicle::SetRefuelingStation(AFGBuildableDockingStation* station){ }
void AFGWheeledVehicle::DockToRefuelingStation(){ }
void AFGWheeledVehicle::UpdatePlayerStatus(){ }
void AFGWheeledVehicle::Died(AActor* thisActor){ }
void AFGWheeledVehicle::SetSimulated(bool newIsSimulated){ }
void AFGWheeledVehicle::CreateInventoryItemDrops_Implementation(){ }
void AFGWheeledVehicle::SmoothMovementReplication(float DeltaTime){ }
void AFGWheeledVehicle::ReplicateMovementClientToServer_Implementation(FVector AuthoritativeLoc, FQuat AuthoritativeQuat, FVector AuthoritativeVelocity){ }
void AFGWheeledVehicle::OnCustomizationDataApplied(const FFactoryCustomizationData& customizationData){ }
void AFGWheeledVehicle::TickPendingVehicleCollisions(float dt){ }
float AFGWheeledVehicle::ImpactForceForCollisionSFX(const UPrimitiveComponent* hitComponent, const AActor* otherActor, const UPrimitiveComponent* otherComponent){ return float(); }
void AFGWheeledVehicle::OnRepTrunkUser(){ }
void AFGWheeledVehicle::UpdateVehicleStatus(){ }
void AFGWheeledVehicle::EnsureInfoCreated(){ }
void AFGWheeledVehicle::BurnFuel(const float dt){ }
void AFGWheeledVehicle::SetRecordingStatus(ERecordingStatus recordingStatus){ }
void AFGWheeledVehicle::OnFuelAdded(TSubclassOf< UFGItemDescriptor > itemClass, const int32 numAdded, UFGInventoryComponent* sourceInventory){ }
void AFGWheeledVehicle::OnRep_TransferStatusChanged(){ }
void AFGWheeledVehicle::StopVehicle(){ }
float AFGWheeledVehicle::AdjustThrottle(float throttle) const{ return float(); }
void AFGWheeledVehicle::StartRecording(){ }
void AFGWheeledVehicle::StopRecording(bool isValid){ }
void AFGWheeledVehicle::TickRecording(float deltaTime){ }
void AFGWheeledVehicle::PlaceTargetPoint(){ }
void AFGWheeledVehicle::ClearTargetList(){ }
void AFGWheeledVehicle::CacheSpeedInKMH(){ }
bool AFGWheeledVehicle::ShouldStopVehicle() const{ return bool(); }
void AFGWheeledVehicle::StopAllMovement(){ }
float AFGWheeledVehicle::GetLocalTime() const{ return float(); }
void AFGWheeledVehicle::MoveForward(float throttle, float brake){ }
void AFGWheeledVehicle::MoveRight(float axisValue){ }
void AFGWheeledVehicle::Server_SetVehicleLightsOn_Implementation(bool active){ }
void AFGWheeledVehicle::OnVehicleLightStatusChanged_Implementation(){ }
void AFGWheeledVehicle::Server_SetHonkStatus_Implementation(bool active){ }
void AFGWheeledVehicle::OnHonkStatusChanged_Implementation(){ }
void AFGWheeledVehicle::OnOpenRecorderMenu_Implementation(){ }
void AFGWheeledVehicle::TurnOverVehicle(){ }
bool AFGWheeledVehicle::IsFollowingPath() const{ return bool(); }
void AFGWheeledVehicle::SetIsPossessed(bool isPossessed){ }
bool AFGWheeledVehicle::CanLoadPath() const{ return bool(); }
bool AFGWheeledVehicle::CanSavePath() const{ return bool(); }
void AFGWheeledVehicle::PickNextTarget(){ }
void AFGWheeledVehicle::Server_ToggleAutoPilot_Implementation(){ }
void AFGWheeledVehicle::Server_TogglePathVisibility_Implementation(){ }
void AFGWheeledVehicle::Server_ToggleRecording_Implementation(){ }
void AFGWheeledVehicle::Server_ClearRecordedPath_Implementation(){ }
void AFGWheeledVehicle::Server_SavePath_Implementation(const FString& saveName, const TArray< FLocalUserNetIdBundle >& lastEditedBy){ }
void AFGWheeledVehicle::Server_UnsavePath_Implementation(AFGSavedWheeledVehiclePath* path){ }
void AFGWheeledVehicle::Server_LoadPath_Implementation( AFGDrivingTargetList* targetList){ }
void AFGWheeledVehicle::FindSavedPaths(const FString& textFilter, bool filterOnVehicleType, TArray< AFGSavedWheeledVehiclePath* >& result) const{ }
void AFGWheeledVehicle::OnRep_RecordingStatus(){ }
void AFGWheeledVehicle::OnRep_ManualDockingState(){ }
void AFGWheeledVehicle::OnRep_IsAutopilotEnabled(){ }
void AFGWheeledVehicle::OnRep_Info(){ }
void AFGWheeledVehicle::OnRep_TargetList(AFGDrivingTargetList* oldList){ }
void AFGWheeledVehicle::OnIsSimulatedChanged(){ }
FVector AFGWheeledVehicle::GetVelocityVector() const{ return FVector(); }
void AFGWheeledVehicle::OnSimulationTargetReached(AFGTargetPoint* newTarget){ }
AFGTargetPoint* AFGWheeledVehicle::SpawnNewTargetPoint(const FVector& location, const FRotator& rotation, AFGDrivingTargetList* targetList, int targetSpeed, AFGTargetPoint* afterTarget){ return nullptr; }
void AFGWheeledVehicle::StartGhosting(){ }
void AFGWheeledVehicle::TryLeaveSimulatedMode(){ }
bool AFGWheeledVehicle::IsAboveSolidGround(const FTransform& transform) const{ return bool(); }
AActor* AFGWheeledVehicle::IsOverlappingOther(const FTransform& transform) const{ return nullptr; }
void AFGWheeledVehicle::OnPathVisibilityChanged(bool pathVisibility){ }
void AFGWheeledVehicle::OnRep_EngineAudioChanged(const bool oldEngineState){ }
float AFGWheeledVehicle::CalculateAutomatedFuelToConsume(float deltaTime){ return float(); }
void AFGWheeledVehicle::SetTargetList(AFGDrivingTargetList* targetList){ }
void AFGWheeledVehicle::UpdateVehicleMeshVisibility(bool bNewVisibility){ }
FName AFGWheeledVehicle::VehicleMeshComponentName = FName();
FName AFGWheeledVehicle::VehicleMovementComponentName = FName();

#include "Hologram/FGVehiclePathSegmentHologram.h"
#include "Components/SceneComponent.h"
#include "Components/SplineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FGConstructDisqualifier.h"
#include "Net/UnrealNetwork.h"

AFGVehiclePathSegmentHologram::AFGVehiclePathSegmentHologram() : Super() {
	this->mPathTooShortDisqualifier = nullptr;
	this->mPathTooLongDisqualifier = UFGCDTrackTooLong::StaticClass();
	this->mConnectionAlreadyExistsDisqualifier = nullptr;
	this->mInvalidVehiclePathShapeDisqualifier = nullptr;
	this->mMaxFloorTraceSearchDistance = 2000.0;
	this->mPathFloorTraceElevation = 200.0;
	this->mPathSplineQuantizationLength = 100.0;
	this->mMinPathLength = 100.0;
	this->mMaxPathLength = 10000.0;
	this->mSegmentEndPointSnapDistance = 800.0;
	this->mPathNodeOverlapRadius = 300.0;
	this->mBuildModeStraight = nullptr;
	this->mTempSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("TempSpline"));
	this->mTempSplineComponent->SetMobility(EComponentMobility::Movable);
	this->mPathSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("VehiclePath"));
	this->mPathSplineComponent->SetMobility(EComponentMobility::Movable);
	this->mDirectionalArrowComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DirectionalArrow"));
	this->mDirectionalArrowComponent->SetMobility(EComponentMobility::Movable);
	this->mPlacementVisualizationComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlacementVisualization"));
	this->mPlacementVisualizationComponent->SetMobility(EComponentMobility::Movable);
	this->mBuildStep = EVehiclePathBuildStep::StartPoint;
	this->mSnappedPathNodes[0] = nullptr;
	this->mSnappedPathNodes[1] = nullptr;
	this->mSnappedPathSegments[0] = nullptr;
	this->mSnappedPathSegments[1] = nullptr;
	this->mSnappedPathSegmentSlicePositions[0] = 0.0;
	this->mSnappedPathSegmentSlicePositions[1] = 0.0;
	this->mIsSegmentReversed = false;
	this->mIsPathSegmentShapeInvalid = false;
	this->mCurrentPathValidationVehicleClass = nullptr;
	this->mCurrentPathValidationInfo.Result = EVehiclePathValidationResult::Valid;
	this->mCurrentPathValidationInfo.SplineValidationFailDistance = 0.0;
	this->mCurrentPathValidationInfo.VirtualPathLength = 0.0;
	this->mStartLocation = FVector::ZeroVector;
	this->mStartPointExitDirection = FVector::ZeroVector;
	this->mEndLocation = FVector::ZeroVector;
	this->mEndPointEntryDirection = FVector::ZeroVector;
	this->mUseCustomEndRotation = false;
	this->mStraightMode = false;
	this->mForceSnapFirstPoint = false;
	this->mBlueprintBridgeHologramMode = false;
	this->mNeedsValidFloor = false;
	this->mCanSnapWithAttachmentPoints = false;
	this->mTempSplineComponent->SetupAttachment(RootComponent);
	this->mPathSplineComponent->SetupAttachment(RootComponent);
	this->mDirectionalArrowComponent->SetupAttachment(RootComponent);
	this->mPlacementVisualizationComponent->SetupAttachment(RootComponent);
}
void AFGVehiclePathSegmentHologram::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGVehiclePathSegmentHologram, mSplineData);
	DOREPLIFETIME(AFGVehiclePathSegmentHologram, mBuildStep);
	DOREPLIFETIME(AFGVehiclePathSegmentHologram, mIsPathSegmentShapeInvalid);
	DOREPLIFETIME(AFGVehiclePathSegmentHologram, mCurrentPathValidationVehicleClass);
	DOREPLIFETIME(AFGVehiclePathSegmentHologram, mCurrentPathValidationInfo);
}
void AFGVehiclePathSegmentHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGVehiclePathSegmentHologram::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
bool AFGVehiclePathSegmentHologram::DoMultiStepPlacement(bool isInputFromARelease){ return Super::DoMultiStepPlacement(isInputFromARelease); }
void AFGVehiclePathSegmentHologram::PreConfigureActor(class AFGBuildable* inBuildable){ Super::PreConfigureActor(inBuildable); }
bool AFGVehiclePathSegmentHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGVehiclePathSegmentHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
void AFGVehiclePathSegmentHologram::SetHologramNudgeLocation(){ Super::SetHologramNudgeLocation(); }
int32 AFGVehiclePathSegmentHologram::GetRotationStep() const{ return Super::GetRotationStep(); }
void AFGVehiclePathSegmentHologram::ScrollRotate(int32 delta, int32 step){ Super::ScrollRotate(delta, step); }
bool AFGVehiclePathSegmentHologram::ShouldBuildGunHitVehiclePaths() const{ return Super::ShouldBuildGunHitVehiclePaths(); }
void AFGVehiclePathSegmentHologram::GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const{ Super::GetSupportedBuildModes_Implementation(out_buildmodes); }
void AFGVehiclePathSegmentHologram::ReplaceHologram(AFGHologram* hologram, bool snapTransform){ Super::ReplaceHologram(hologram, snapTransform); }
void AFGVehiclePathSegmentHologram::PostConstructMessageDeserialization(){ Super::PostConstructMessageDeserialization(); }
bool AFGVehiclePathSegmentHologram::CanNudgeHologram() const{ return Super::CanNudgeHologram(); }
ENudgeFailReason AFGVehiclePathSegmentHologram::NudgeTowardsWorldDirection(const FVector& Direction){ return Super::NudgeTowardsWorldDirection(Direction); }
void AFGVehiclePathSegmentHologram::GetClearanceData(TArray<const FFGClearanceData*>& out_ClearanceData) const{ Super::GetClearanceData(out_ClearanceData); }
bool AFGVehiclePathSegmentHologram::IsHologramIdenticalToActor(AActor* actor, const FTransform& hologramTransform) const{ return Super::IsHologramIdenticalToActor(actor, hologramTransform); }
void AFGVehiclePathSegmentHologram::GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const{ Super::GetIgnoredClearanceActors(ignoredActors); }
TSubclassOf<class UFGConstructDisqualifier> AFGVehiclePathSegmentHologram::GetConstructDisqualifierFromClearanceOverlap(const EClearanceOverlapResult& overlapResult, AActor* otherActor) const{ return Super::GetConstructDisqualifierFromClearanceOverlap(overlapResult, otherActor); }
void AFGVehiclePathSegmentHologram::SetupBridgeHologram(bool bIsSegmentReversed){ }
void AFGVehiclePathSegmentHologram::UpdateBridgeHologramLocation(const FVector& startLocation, const FVector& startForwardDirection, AFGVehiclePathNode* endPathNode){ }
void AFGVehiclePathSegmentHologram::SetBridgeHologramStartPathNode(AFGVehiclePathNode* startPathNode){ }
void AFGVehiclePathSegmentHologram::AddIgnoredActorsFromPathNode(AFGVehiclePathNode* pathNode, TSet<AActor*>& ignoredActors){ }
void AFGVehiclePathSegmentHologram::AddIgnoredActorsFromPathSegment(AFGVehiclePathSegment* pathSegment, TSet<AActor*>& ignoredActors){ }
AFGVehiclePathNode* AFGVehiclePathSegmentHologram::OverlapPathNode(const UWorld* world, const FVector& worldLocation, float overlapRadius){ return nullptr; }
AFGVehiclePathNode* AFGVehiclePathSegmentHologram::GetPathNodeFromHitResult(const FHitResult& hitResult) const{ return nullptr; }
bool AFGVehiclePathSegmentHologram::CheckPathCompatibility(const AFGVehiclePathSegment* pathSegment) const{ return false; }
bool AFGVehiclePathSegmentHologram::CheckNodeCompatibility(const AFGVehiclePathNode* pathNode, bool bIsArrivingConnection) const{ return false; }
bool AFGVehiclePathSegmentHologram::TrySnapToPathNode(AFGVehiclePathNode* pathNode){ return false; }
bool AFGVehiclePathSegmentHologram::TrySnapToPathSegment(AFGVehiclePathSegment* pathSegment, const float snapDistance){ return false; }
void AFGVehiclePathSegmentHologram::RouteHologramSpline(){ }
void AFGVehiclePathSegmentHologram::UpdatePathValidationInfoFromSplineComponent(){ }
void AFGVehiclePathSegmentHologram::UpdateHologramVisualState(){ }
void AFGVehiclePathSegmentHologram::GetActiveVehicleTypes(TArray<UFGVehiclePathPreset*>& out_activeVehicleTypes) const{ }
void AFGVehiclePathSegmentHologram::UpdatePathVisualizationHandle(){ }
void AFGVehiclePathSegmentHologram::CheckValidPlacement(){ Super::CheckValidPlacement(); }
void AFGVehiclePathSegmentHologram::CheckBlueprintCommingling(){ Super::CheckBlueprintCommingling(); }
void AFGVehiclePathSegmentHologram::OnHologramLockStateChanged(){ Super::OnHologramLockStateChanged(); }
void AFGVehiclePathSegmentHologram::OnRep_SplineData(){ }
void AFGVehiclePathSegmentHologram::OnRep_HologramState(){ }

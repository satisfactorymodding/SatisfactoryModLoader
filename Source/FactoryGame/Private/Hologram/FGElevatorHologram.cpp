#include "Hologram/FGElevatorHologram.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AFGElevatorHologram::AFGElevatorHologram() : Super() {
	this->mFloorStopHologramRecipe = nullptr;
	this->mHeight1mISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HeightISMC1m"));
	this->mHeight1mISMC->SetMobility(EComponentMobility::Movable);
	this->mHeight4mISMC = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("HeightISMC4m"));
	this->mHeight4mISMC->SetMobility(EComponentMobility::Movable);
	this->mHeightMesh1m = nullptr;
	this->mHeightMesh4m = nullptr;
	this->mBottomMesh = nullptr;
	this->mTopMesh = nullptr;
	this->mChildFloorStops[0] = nullptr;
	this->mChildFloorStops[1] = nullptr;
	this->mPlacedTransform = FTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	this->mTopTransform = FTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	this->mHeight = 0.0;
	this->mIsReversed = false;
	this->mSnappedToElevator = nullptr;
	this->mSnappedTop = false;
	this->mNeedsValidFloor = false;
	this->mHeight1mISMC->SetupAttachment(RootComponent);
	this->mHeight4mISMC->SetupAttachment(RootComponent);
}
void AFGElevatorHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGElevatorHologram::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGElevatorHologram::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGElevatorHologram, mTopTransform);
}
bool AFGElevatorHologram::IsValidHitResult(const FHitResult& hitResult) const{ return Super::IsValidHitResult(hitResult); }
bool AFGElevatorHologram::TrySnapToActor(const FHitResult& hitResult){ return Super::TrySnapToActor(hitResult); }
void AFGElevatorHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
void AFGElevatorHologram::SetHologramNudgeLocation(){ Super::SetHologramNudgeLocation(); }
void AFGElevatorHologram::PostHologramPlacement(const FHitResult& hitResult, bool callForChildren){ Super::PostHologramPlacement(hitResult, callForChildren); }
bool AFGElevatorHologram::DoMultiStepPlacement(bool isInputFromARelease){ return Super::DoMultiStepPlacement(isInputFromARelease); }
int32 AFGElevatorHologram::GetBaseCostMultiplier() const{ return Super::GetBaseCostMultiplier(); }
void AFGElevatorHologram::SpawnChildren(AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator){ Super::SpawnChildren(hologramOwner, spawnLocation, hologramInstigator); }
void AFGElevatorHologram::PreConfigureActor(AFGBuildable* inBuildable){ Super::PreConfigureActor(inBuildable); }
void AFGElevatorHologram::ConfigureActor(AFGBuildable* inBuildable) const{ Super::ConfigureActor(inBuildable); }
int32 AFGElevatorHologram::GetRotationStep() const{ return Super::GetRotationStep(); }
void AFGElevatorHologram::GetClearanceData(TArray<const FFGClearanceData*>& out_ClearanceData) const{ Super::GetClearanceData(out_ClearanceData); }
bool AFGElevatorHologram::IsHologramIdenticalToActor(AActor* actor, const FTransform& hologramTransform) const{ return Super::IsHologramIdenticalToActor(actor, hologramTransform); }
void AFGElevatorHologram::RefreshHologramInstanceInstigators(){ Super::RefreshHologramInstanceInstigators(); }
void AFGElevatorHologram::GetIgnoredClearanceActors(TSet<AActor*>& ignoredActors) const{ Super::GetIgnoredClearanceActors(ignoredActors); }
bool AFGElevatorHologram::CanNudgeHologram() const{ return Super::CanNudgeHologram(); }
FTransform AFGElevatorHologram::GetTransformForChildStop(int32 childIndex){ return FTransform(); }
void AFGElevatorHologram::BuildFloorStopInfos(){ }
void AFGElevatorHologram::OnRep_TopTransform(){ }
void AFGElevatorHologram::UpdateTopTransform(const FHitResult& hitResult, FRotator rotation){ }
void AFGElevatorHologram::UpdateClearance(){ }
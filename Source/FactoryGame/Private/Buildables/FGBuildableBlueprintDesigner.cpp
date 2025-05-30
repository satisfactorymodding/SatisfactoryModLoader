// This file has been automatically generated by the Unreal Header Implementation tool

#include "Buildables/FGBuildableBlueprintDesigner.h"
#include "Components/BoxComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "FGColoredInstanceMeshProxy.h"
#include "Hologram/FGBlueprintDesignerHologram.h"
#include "Net/UnrealNetwork.h"

#if WITH_EDITOR
void AFGBuildableBlueprintDesigner::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent){ Super::PostEditChangeProperty(PropertyChangedEvent); }
#endif 
AFGBuildableBlueprintDesigner::AFGBuildableBlueprintDesigner() : Super() {
	this->mCollisionComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	this->mCollisionComponent->SetMobility(EComponentMobility::Movable);
	this->mTerminalMesh = CreateDefaultSubobject<UFGColoredInstanceMeshProxy>(TEXT("TerminalMesh"));
	this->mTerminalMesh->SetMobility(EComponentMobility::Static);
	this->mFloorMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("FloorMesh"));
	this->mFloorMeshComponent->SetMobility(EComponentMobility::Static);
	this->mRefundLocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RefundLocation"));
	this->mRefundLocationComponent->SetMobility(EComponentMobility::Static);
	this->mFloorMeshTile = nullptr;
	this->mTerminalDistanceFromEdge = 0.0;
	this->mTerminalHalfDepth = 0.0;
	this->mDimensions.X = 8;
	this->mDimensions.Y = 8;
	this->mDimensions.Z = 8;
	this->mDefaultStorageRecipe = nullptr;
	this->mStorage = nullptr;
	this->mStorageLocation = CreateDefaultSubobject<USceneComponent>(TEXT("StorageLocation"));
	this->mStorageLocation->SetMobility(EComponentMobility::Static);
	this->mCurrentBlueprintDescriptor = nullptr;
	this->mIsDismantlingAll = false;
	this->mHologramClass = AFGBlueprintDesignerHologram::StaticClass();
	this->mCollisionComponent->SetupAttachment(RootComponent);
	this->mTerminalMesh->SetupAttachment(RootComponent);
	this->mFloorMeshComponent->SetupAttachment(RootComponent);
	this->mRefundLocationComponent->SetupAttachment(RootComponent);
	this->mStorageLocation->SetupAttachment(RootComponent);
}
void AFGBuildableBlueprintDesigner::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableBlueprintDesigner, mCurrentCost);
	DOREPLIFETIME(AFGBuildableBlueprintDesigner, mStorage);
	DOREPLIFETIME(AFGBuildableBlueprintDesigner, mBuildables);
	DOREPLIFETIME(AFGBuildableBlueprintDesigner, mCurrentRecordData);
}
void AFGBuildableBlueprintDesigner::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableBlueprintDesigner::EndPlay(const EEndPlayReason::Type endPlayReason){ Super::EndPlay(endPlayReason); }
void AFGBuildableBlueprintDesigner::PreSaveGame_Implementation(int32 saveVersion, int32 gameVersion){ }
bool AFGBuildableBlueprintDesigner::CanDismantle_Implementation() const{ return bool(); }
void AFGBuildableBlueprintDesigner::GetChildDismantleActors_Implementation(TArray<AActor*>& out_ChildDismantleActors) const{ }
void AFGBuildableBlueprintDesigner::GetDismantleDependencies_Implementation(TArray<AActor*>& out_dismantleDependencies) const{ }
void AFGBuildableBlueprintDesigner::GetDismantleDisqualifiers_Implementation(TArray<TSubclassOf<UFGConstructDisqualifier>>& out_dismantleDisqualifiers, const TArray<AActor*>& allSelectedActors) const{ }
void AFGBuildableBlueprintDesigner::RegisterInteractingPlayer_Implementation(AFGCharacterPlayer* player){ }
void AFGBuildableBlueprintDesigner::BuildTiledMeshes(UInstancedStaticMeshComponent* tiledMeshComp, const FIntVector& dims){ }
void AFGBuildableBlueprintDesigner::OnBuildableConstructedInsideDesigner(AFGBuildable* buildable){ }
void AFGBuildableBlueprintDesigner::OnBuildableDismantledInsideDesigner(AFGBuildable* buildable){ }
void AFGBuildableBlueprintDesigner::OnBuildableChangedInsideDesigner(AFGBuildable* buildable){ }
void AFGBuildableBlueprintDesigner::CalculateBlueprintCost(TArray<FItemAmount>& cost) const{ }
void AFGBuildableBlueprintDesigner::SaveBlueprint(FBlueprintRecord blueprintRecord, AFGPlayerController* controller, bool bFromDesignerContext){ }
void AFGBuildableBlueprintDesigner::DismantleCurrentBuildables(AFGPlayerController* controller){ }
void AFGBuildableBlueprintDesigner::GetCurrentBuildablesDismantleRefund(TArray< FInventoryStack >& out_refund, bool noBuildCostEnabled){ }
EBlueprintDesignerLoadResult AFGBuildableBlueprintDesigner::LoadBlueprintIntoDesigner(UFGBlueprintDescriptor* blueprintDescriptor, AFGPlayerController* controller){ return EBlueprintDesignerLoadResult(); }
FVector AFGBuildableBlueprintDesigner::GetBlueprintDesignerSize() const{ return FVector(); }
bool AFGBuildableBlueprintDesigner::IsTransformOnPerimeterOfDesigner(const FTransform& trans) const{ return bool(); }
bool AFGBuildableBlueprintDesigner::IsLocationOnPerimeterOfDesigner(const FVector& location) const{ return bool(); }
bool AFGBuildableBlueprintDesigner::IsLocationInsideDesigner(const FVector& location) const{ return bool(); }
void AFGBuildableBlueprintDesigner::GetOffsetTransform(FTransform& out_transform) const{ }
UFGInventoryComponent* AFGBuildableBlueprintDesigner::GetInteractingPlayerInventory(){ return nullptr; }
bool AFGBuildableBlueprintDesigner::CanAffordToLoad(UFGBlueprintDescriptor* blueprintDesc, UFGInventoryComponent* playerInv){ return bool(); }
void AFGBuildableBlueprintDesigner::RemoveCostToLoad(UFGBlueprintDescriptor* blueprintDescriptor, AFGCharacterPlayer* character){ }
void AFGBuildableBlueprintDesigner::OnBuildEffectFinished(){ }
void AFGBuildableBlueprintDesigner::OnRep_Storage(){ }
void AFGBuildableBlueprintDesigner::OnBuildingsChanged(){ }
void AFGBuildableBlueprintDesigner::RecalculateBlueprintCost(){ }
void AFGBuildableBlueprintDesigner::GenerateIntersectionBoxes(){ }
void AFGBuildableBlueprintDesigner::OnRep_Buildables(){ }
void AFGBuildableBlueprintDesigner::OnRep_RecordData(){ }
void AFGBuildableBlueprintDesigner::OnRep_CostChanged(){ }

// This file has been automatically generated by the Unreal Header Implementation tool

#include "Hologram/FGPillarHologram.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Net/UnrealNetwork.h"

AFGPillarHologram::AFGPillarHologram() : Super() {
	this->mMeshComponent = nullptr;
	this->mInstancedMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("Instanced Mesh Component"));
	this->mInstancedMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mForceVerticalSnapThreshold = 0.5;
	this->mBuildStep = EPillarHologramBuildStep::PHBS_Placement;
	this->mBuildModeZoop = nullptr;
	this->mCreateClearanceSnapMeshVisualization = false;
	this->mAllowEdgePlacementInDesignerEvenOnIntersect = true;
	this->mInstancedMeshComponent->SetupAttachment(RootComponent);
}
void AFGPillarHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGPillarHologram::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGPillarHologram, mCurrentZoop);
	DOREPLIFETIME(AFGPillarHologram, mBuildStep);
}
bool AFGPillarHologram::IsValidHitResult(const FHitResult& hitResult) const{ return bool(); }
bool AFGPillarHologram::TrySnapToActor(const FHitResult& hitResult){ return bool(); }
void AFGPillarHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ }
bool AFGPillarHologram::DoMultiStepPlacement(bool isInputFromARelease){ return bool(); }
AActor* AFGPillarHologram::Construct(TArray<AActor*>& out_children, FNetConstructionID constructionID){ return nullptr; }
int32 AFGPillarHologram::GetBaseCostMultiplier() const{ return int32(); }
void AFGPillarHologram::GetSupportedBuildModes_Implementation(TArray<TSubclassOf<UFGBuildGunModeDescriptor>>& out_buildmodes) const{ }
void AFGPillarHologram::OnBuildModeChanged(TSubclassOf<UFGHologramBuildModeDescriptor> buildMode){ }
bool AFGPillarHologram::CanBeZooped() const{ return bool(); }
void AFGPillarHologram::AdjustForGround(FVector& out_adjustedLocation, FRotator& out_adjustedRotation){ }
void AFGPillarHologram::PostHologramPlacement(const FHitResult& hitResult, bool callForChildren){ Super::PostHologramPlacement(hitResult, callForChildren); }
void AFGPillarHologram::GetClearanceData(TArray<const FFGClearanceData*>& out_ClearanceData) const{ Super::GetClearanceData(out_ClearanceData); }
void AFGPillarHologram::FilterAttachmentPoints(TArray< const FFGAttachmentPoint* >& Points, AFGBuildable* pBuildable, const FHitResult& HitResult) const{ }
void AFGPillarHologram::CreateAttachmentPointTransform(FTransform& out_transformResult, const FHitResult& HitResult, AFGBuildable* pBuildable, const FFGAttachmentPoint& BuildablePoint, const FFGAttachmentPoint& LocalPoint){ }
bool AFGPillarHologram::CanIntersectWithDesigner( AFGBuildableBlueprintDesigner* designer) const{ return bool(); }
bool AFGPillarHologram::IsHologramIdenticalToActor(AActor* actor, const FTransform& hologramLocationOffset) const{ return bool(); }
void AFGPillarHologram::OnRep_CurrentZoop(){ }

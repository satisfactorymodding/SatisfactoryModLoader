#include "Hologram/FGPipelinePoleHologram.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"

AFGPipelinePoleHologram::AFGPipelinePoleHologram() : Super() {
	this->mCanAdjustVerticalAngle = true;
	this->mSnapConnection = nullptr;
	this->mVerticalAngle = 0.0;
	this->mSupportTopPartMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pole Top Part"));
	this->mSupportTopPartMeshComponent->SetMobility(EComponentMobility::Movable);
	this->mClearanceExtent = FVector::ZeroVector;
	this->mSupportTopPartMeshComponent->SetupAttachment(RootComponent);
}
void AFGPipelinePoleHologram::BeginPlay(){ Super::BeginPlay(); }
void AFGPipelinePoleHologram::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGPipelinePoleHologram, mVerticalAngle);
}
void AFGPipelinePoleHologram::SetHologramLocationAndRotation(const FHitResult& hitResult){ Super::SetHologramLocationAndRotation(hitResult); }
void AFGPipelinePoleHologram::Scroll(int32 delta){ Super::Scroll(delta); }
void AFGPipelinePoleHologram::ReplaceHologram(AFGHologram* hologram, bool snapTransform){ Super::ReplaceHologram(hologram, snapTransform); }
void AFGPipelinePoleHologram::SnapToConnection(UFGPipeConnectionComponentBase* connection, class AFGPipelineHologram* parentPipeline){ }
bool AFGPipelinePoleHologram::CanAdjustHeight() const{ return Super::CanAdjustHeight(); }
void AFGPipelinePoleHologram::SetVerticalAngle(float newValue){  }
void AFGPipelinePoleHologram::UpdatePoleMesh(){ Super::UpdatePoleMesh(); }
void AFGPipelinePoleHologram::ConfigureActor(class AFGBuildable* inBuildable) const{ Super::ConfigureActor(inBuildable); }
void AFGPipelinePoleHologram::OnRep_VerticalAngle(){ }
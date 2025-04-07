#include "FGBuildablePolePipe.h"
#include "Components/SceneComponent.h"
#include "FGPipeConnectionComponent.h"
#include "FGSwatchGroup.h"
#include "Hologram/FGPipelinePoleHologram.h"
#include "Net/UnrealNetwork.h"

AFGBuildablePolePipe::AFGBuildablePolePipe() : Super() {
	this->mVerticalAngle = 0.0;
	this->mSupportMeshInstanceData.StaticMesh = nullptr;
	this->mSupportMeshInstanceData.RelativeTransform = FTransform(FQuat::Identity, FVector::ZeroVector, FVector::OneVector);
	this->mSupportMeshInstanceData.bUseBatchedCollision = true;
	this->mSupportMeshInstanceData.Mobility = EComponentMobility::Static;
	this->mSupportMeshInstanceData.bApplyRandomOffsetOnInstance = false;
	this->mSupportMeshInstanceData.bApplyRandomScaleOnInstancesBasedOnOrientation = false;
	this->mSupportMeshInstanceData.bScaleByRightVector = false;
	this->mSupportMeshInstanceData.PositionOffset = FVector::ZeroVector;
	this->mSupportMeshInstanceData.ScaleOffset = FVector::ZeroVector;
	this->mSupportMeshInstanceData.CollisionProfileName = TEXT("BlockAll");
	this->mSupportMeshInstanceData.bCastShadows = true;
	this->mSupportMeshInstanceData.bCastDistanceFieldShadows = true;
	this->mSupportMeshInstanceData.MaxDrawDistance = -1.0;
	this->mSupportMeshInstanceData.MaxWPODistance = 50000.0;
	this->mSupportMeshInstanceData.bWorldPositionOffsetWritesVelocity = 0;
	this->mSupportMeshInstanceData.bAllowLazyInstance = false;
	this->mSupportMeshInstanceData.bUseAkGeometry = false;
	this->mSupportMeshInstanceData.MeshType = AkInstancedMeshType::BoundingBox;
	this->mSupportMeshInstanceData.CollisionMeshSurfaceOverride.AcousticTexture = nullptr;
	this->mSupportMeshInstanceData.CollisionMeshSurfaceOverride.bEnableOcclusionOverride = false;
	this->mSupportMeshInstanceData.CollisionMeshSurfaceOverride.OcclusionValue = 0.8;
	this->mSnapOnly0 = CreateDefaultSubobject<UFGPipeConnectionComponentBase>(TEXT("SnapOnly0"));
	this->mSnapOnly0->SetMobility(EComponentMobility::Static);
	this->mHologramClass = AFGPipelinePoleHologram::StaticClass();
	this->mSwatchGroup = UFGSwatchGroup_Pipeline::StaticClass();
	this->mSnapOnly0->SetupAttachment(RootComponent);
}
void AFGBuildablePolePipe::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildablePolePipe, mVerticalAngle);
}
void AFGBuildablePolePipe::SetVerticalAngle(float angle){  }
void AFGBuildablePolePipe::SetupConnectionComponent(){ Super::SetupConnectionComponent(); }
TArray<struct FInstanceData> AFGBuildablePolePipe::GetActorLightweightInstanceData_Implementation() const{ return Super::GetActorLightweightInstanceData_Implementation(); }
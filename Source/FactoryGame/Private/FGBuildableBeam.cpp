// This file has been automatically generated by the Unreal Header Implementation tool

#include "FGBuildableBeam.h"
#include "Net/UnrealNetwork.h"

AFGBuildableBeam::AFGBuildableBeam(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {
	this->mSize = 0.0;
	this->mDefaultLength = 0.0;
	this->mMaxLength = 0.0;
	this->mLength = 0.0;
	this->bTiledMesh = false;
}
void AFGBuildableBeam::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableBeam::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AFGBuildableBeam, mLength);
}
void AFGBuildableBeam::GetAttachmentPoints(TArray< const FFGAttachmentPoint* >& out_points) const{ }
TArray<FInstanceData> AFGBuildableBeam::GetActorLightweightInstanceData_Implementation() const{ return Super::GetActorLightweightInstanceData_Implementation(); }
void AFGBuildableBeam::CreateLightweightBuildableInstanceData(const struct FFGDynamicStruct& typeSpecificData, TArray<FInstanceData>& outLightweightInstanceData) const{ Super::CreateLightweightBuildableInstanceData(typeSpecificData, outLightweightInstanceData); }
FFGDynamicStruct AFGBuildableBeam::GetLightweightTypeSpecificData() const{ return Super::GetLightweightTypeSpecificData(); }
void AFGBuildableBeam::ApplyLightweightTypeSpecificData(const struct FFGDynamicStruct& typeSpecificData){ Super::ApplyLightweightTypeSpecificData(typeSpecificData); }
void AFGBuildableBeam::PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion){ }
int32 AFGBuildableBeam::GetDismantleRefundReturnsMultiplier() const{ return int32(); }
int32 AFGBuildableBeam::GetDismantleRefundReturnsMultiplierForLightweight(const FFGDynamicStruct& typeSpecificData) const{ return Super::GetDismantleRefundReturnsMultiplierForLightweight(typeSpecificData); }
void AFGBuildableBeam::SetLength(float NewLength){ }
int32 AFGBuildableBeam::GetDismantleReturnsMultiplierForBeam(float beamLength) const{ return 0; }
void AFGBuildableBeam::PopulateBeamInstanceData(float beamLength, TArray<FInstanceData>& outInstanceData) const{  }

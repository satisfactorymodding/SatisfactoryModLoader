#include "Buildables/FGBuildableSnowCannon.h"
#include "Components/SceneComponent.h"
#include "FGColoredInstanceMeshProxy.h"

AFGBuildableSnowCannon::AFGBuildableSnowCannon() : Super() {
	this->mBaseMeshComponent = CreateDefaultSubobject<UFGColoredInstanceMeshProxy>(TEXT("Base Mesh Component"));
	this->mBaseMeshComponent->SetMobility(EComponentMobility::Static);
	this->mHeadMeshComponent = CreateDefaultSubobject<UFGColoredInstanceMeshProxy>(TEXT("Head Mesh Component"));
	this->mHeadMeshComponent->SetMobility(EComponentMobility::Static);
	this->mSignificanceRange = 20000.0;
	this->mAngleLimit = FInt32Interval(-90, 90);
	this->mBaseMeshComponent->SetupAttachment(RootComponent);
	this->mHeadMeshComponent->SetupAttachment(RootComponent);
}
void AFGBuildableSnowCannon::BeginPlay(){ Super::BeginPlay(); }
void AFGBuildableSnowCannon::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void AFGBuildableSnowCannon::GainedSignificance_Implementation(){ }
void AFGBuildableSnowCannon::LostSignificance_Implementation(){ }
void AFGBuildableSnowCannon::SetCannonAngle(int32 angle){ }
void AFGBuildableSnowCannon::UpdateCannonMesh(){ }

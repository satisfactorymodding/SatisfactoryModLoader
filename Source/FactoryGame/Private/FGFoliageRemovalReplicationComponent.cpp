#include "FGFoliageRemovalReplicationComponent.h"
#include "Components/SceneComponent.h"

UFGFoliageRemovalReplicationComponent::UFGFoliageRemovalReplicationComponent() : Super() {
	this->mReplicationRadius = 102400.0;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
}
void UFGFoliageRemovalReplicationComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGFoliageRemovalReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGFoliageRemovalReplicationComponent::OnFoliageBucketRemoved(const FIntVector& inCell, const UFoliageType* forFoliageType, int32 bucketId){  }
void UFGFoliageRemovalReplicationComponent::HandleBulkDataReplicationMessage(TArray<uint8>&& Payload){  }
AFGFoliageStateRepProxy::AFGFoliageStateRepProxy() : Super() {
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	this->RootComponent->SetMobility(EComponentMobility::Movable);
}
#include "FGPlayerPipelineDataReplicationComponent.h"
#include "Net/UnrealNetwork.h"

UFGPlayerPipelineDataReplicationComponent::UFGPlayerPipelineDataReplicationComponent() : Super() {
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
	this->SetIsReplicatedByDefault(true);
}
void UFGPlayerPipelineDataReplicationComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UFGPlayerPipelineDataReplicationComponent, mReplicationData);
}
void UFGPlayerPipelineDataReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
UFGPlayerPipelineDataReplicationComponent* UFGPlayerPipelineDataReplicationComponent::Get(const AFGCharacterPlayer* PlayerCharacter){ return nullptr; }
void UFGPlayerPipelineDataReplicationComponent::RegisterInteractedPipeline(AFGBuildablePipeline* Pipeline){  }
void UFGPlayerPipelineDataReplicationComponent::UnregisterInteractedPipeline(const AFGBuildablePipeline* Pipeline){  }
void UFGPlayerPipelineDataReplicationComponent::OnRep_ReplicationData(const TArray<FFGPipelinePlayerReplicationData>& OldReplicationData){  }
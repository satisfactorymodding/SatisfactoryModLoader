#include "FGLightweightBuildableReplicationComponent.h"

UFGLightweightBuildableReplicationComponent::UFGLightweightBuildableReplicationComponent() : Super() {
	this->LightweightBuildableSubsystem = nullptr;
	this->BuildableSubsystem = nullptr;
	this->PrimaryComponentTick.TickGroup = ETickingGroup::TG_DuringPhysics;
	this->PrimaryComponentTick.EndTickGroup = ETickingGroup::TG_PrePhysics;
	this->PrimaryComponentTick.bTickEvenWhenPaused = false;
	this->PrimaryComponentTick.bCanEverTick = true;
	this->PrimaryComponentTick.bStartWithTickEnabled = true;
	this->PrimaryComponentTick.bAllowTickOnDedicatedServer = true;
	this->PrimaryComponentTick.TickInterval = 0.0;
}
void UFGLightweightBuildableReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGLightweightBuildableReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGLightweightBuildableReplicationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction){ Super::TickComponent(DeltaTime, TickType, ThisTickFunction); }
void UFGLightweightBuildableReplicationComponent::HandleBuildableInstanceConstructed(const TSubclassOf<AFGBuildable>& BuildableClass, const FRuntimeBuildableInstanceData& RuntimeData, int32 InstanceID, uint16 ConstructionID, AActor* ConstructionInstigator, int32 BlueprintBuildEffectIndex) const{  }
void UFGLightweightBuildableReplicationComponent::HandleBuildableInstanceRemoved(const TSubclassOf<AFGBuildable>& BuildableClass, int32 InstanceID) const{  }
void UFGLightweightBuildableReplicationComponent::HandleBuildableInstanceUpdated(const TSubclassOf<AFGBuildable>& BuildableClass, const FRuntimeBuildableInstanceData& RuntimeData, int32 InstanceID) const{  }
void UFGLightweightBuildableReplicationComponent::HandleRawLightweightBuildableMessage(TArray<uint8>&& InMessageData){  }
void UFGLightweightBuildableReplicationComponent::SendRawLightweightBuildableMessage(ELightweightBuildableMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGLightweightBuildableReplicationComponent::ReceivedInitialReplicationMessage(const FLightweightBuildableInitialReplicationMessage& InitialReplicationMessage){  }
void UFGLightweightBuildableReplicationComponent::ReceivedConstructionMessage(const FLightweightBuildableConstructionMessage& ConstructionMessage) const{  }
void UFGLightweightBuildableReplicationComponent::ReceivedRemovalMessage(const FLightweightBuildableRemovalMessage& RemovalMessage) const{  }
void UFGLightweightBuildableReplicationComponent::ReceivedUpdateMessage(const FLightweightBuildableUpdateMessage& UpdateMessage) const{  }
void UFGLightweightBuildableReplicationComponent::SendInitialReplicationMessage(){  }
void UFGLightweightBuildableReplicationComponent::SendIncrementalUpdateReplicationMessage(){  }
void UFGLightweightBuildableReplicationComponent::HandleLightweightBuildableConstructionData(const FLightweightBuildableConstructionData& ConstructionData) const{  }
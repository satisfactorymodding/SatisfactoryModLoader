#include "FGMapManagerReplicationComponent.h"

#include "GameplayTagContainer.h"

void UFGMapManagerReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGMapManagerReplicationComponent::SendFullFogOfWarDataToPlayer(){  }
void UFGMapManagerReplicationComponent::InitializeAsClient(){  }
void UFGMapManagerReplicationComponent::HandleRawMessage(FGameplayTag InTag, TArray<uint8>&& InMessageData) const{ }
void UFGMapManagerReplicationComponent::SendRawMessage(EMapManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGMapManagerReplicationComponent::ReceiveFullFogOfWarUpdate(const FMapManagerFullFogOfWarDataMessage& Message) const{  }
#include "FGConveyorChainSubsystemReplicationComponent.h"

void UFGConveyorChainSubsystemReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGConveyorChainSubsystemReplicationComponent::InitializeAsClient(){  }
void UFGConveyorChainSubsystemReplicationComponent::SendInitialReplicationData(){  }
void UFGConveyorChainSubsystemReplicationComponent::HandleRawMessage(TArray<uint8>&& InMessageData) const{  }
void UFGConveyorChainSubsystemReplicationComponent::SendRawMessage(EConveyorChainSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGConveyorChainSubsystemReplicationComponent::ReceiveInitialReplicationData(const FConveyorChainSubsystemInitialReplicationMessage& Message) const{  }
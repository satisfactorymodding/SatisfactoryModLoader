#include "FGBlueprintSubsystemReplicationComponent.h"

void UFGBlueprintSubsystemReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
bool UFGBlueprintSubsystemReplicationComponent::SendBlueprintFileToPlayer(const FString& BlueprintName){ return false; }
void UFGBlueprintSubsystemReplicationComponent::InitializeAsClient(){  }
void UFGBlueprintSubsystemReplicationComponent::HandleRawMessage(TArray<uint8>&& InMessageData) const{  }
void UFGBlueprintSubsystemReplicationComponent::SendRawMessage(EBlueprintSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGBlueprintSubsystemReplicationComponent::ReceiveBlueprintFileDownload(const FBlueprintSubsystemFileDownloadMessage& Message) const{  }
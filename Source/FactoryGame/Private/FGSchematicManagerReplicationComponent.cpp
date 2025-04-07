#include "FGSchematicManagerReplicationComponent.h"

UFGSchematicManagerReplicationComponent::UFGSchematicManagerReplicationComponent() : Super() {
	this->mSchematicManager = nullptr;
}
void UFGSchematicManagerReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGSchematicManagerReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGSchematicManagerReplicationComponent::NotifySchematicsPurchased(TArrayView<const TSubclassOf<UFGSchematic>> Schematics, AFGCharacterPlayer* AccessInstigator, ESchematicUnlockFlags UnlockFlags){  }
void UFGSchematicManagerReplicationComponent::NotifySchematicsReset(TArrayView<const TSubclassOf<UFGSchematic>> Schematics){  }
void UFGSchematicManagerReplicationComponent::InitializeAsClient(){  }
void UFGSchematicManagerReplicationComponent::SendInitialReplicationMessageToPlayer(){  }
void UFGSchematicManagerReplicationComponent::HandleRawSchematicManagerMessage(TArray<uint8>&& InMessageData){  }
void UFGSchematicManagerReplicationComponent::SendRawSchematicManagerMessage(ESchematicManagerMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{  }
void UFGSchematicManagerReplicationComponent::ReceivedInitialReplicationMessage(const FSchematicManagerInitialReplicationMessage& InitialReplicationMessage){  }
void UFGSchematicManagerReplicationComponent::ReceivedSchematicsPurchasedMessage(const FSchematicsPurchasedMessage& SchematicsPurchasedMessage) const{  }
void UFGSchematicManagerReplicationComponent::ReceivedSchematicsResetMessage(const FResetSchematicsMessage& ResetSchematicsMessage) const{  }
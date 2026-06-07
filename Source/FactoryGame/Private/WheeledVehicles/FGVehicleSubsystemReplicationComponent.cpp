#include "WheeledVehicles/FGVehicleSubsystemReplicationComponent.h"

void UFGVehicleSubsystemReplicationComponent::BeginPlay(){ Super::BeginPlay(); }
void UFGVehicleSubsystemReplicationComponent::EndPlay(const EEndPlayReason::Type EndPlayReason){ Super::EndPlay(EndPlayReason); }
void UFGVehicleSubsystemReplicationComponent::NotifyPathNetworkRemoved(int32 PathNetworkID){ }
void UFGVehicleSubsystemReplicationComponent::NotifyPathNetworkCreated(const FVehiclePathNetworkReplicationData& ReplicationData){ }
void UFGVehicleSubsystemReplicationComponent::NotifyPathNetworkTraversabilityChanged(const FVehiclePathNetworkTraversabilityReplicationData& ReplicationData){ }
void UFGVehicleSubsystemReplicationComponent::InitializeAsClient(){ }
void UFGVehicleSubsystemReplicationComponent::SendInitialReplicationMessage(){ }
void UFGVehicleSubsystemReplicationComponent::HandleRawMessage(FGameplayTag InTag, TArray<uint8>&& InMessageData) const{ }
void UFGVehicleSubsystemReplicationComponent::SendRawMessage(EVehicleSubsystemMessageId MessageId, const TFunctionRef<void(FArchive&)>& MessageSerializer) const{ }
void UFGVehicleSubsystemReplicationComponent::ReceiveInitialPathNetworkReplication(const FVehicleSubsystemInitialPathNetworkReplicationMessage& Message) const{ }
void UFGVehicleSubsystemReplicationComponent::ReceivePathNetworkRemoval(const FVehicleSubsystemRemovePathNetworkMessage& Message) const{ }
void UFGVehicleSubsystemReplicationComponent::ReceivePathNetworkCreation(const FVehicleSubsystemCreatePathNetworkMessage& Message) const{ }
void UFGVehicleSubsystemReplicationComponent::ReceivePathNetworkTraversabilityUpdate(const FVehicleSubsystemUpdatePathNetworkTraversabilityMessage& Message) const{ }

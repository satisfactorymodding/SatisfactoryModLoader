#include "Buildable/BuildableFactoryReplicated.h"
#include "Buildable/ReplicationDetailActorGenerated.h"

void ABuildableFactoryReplicated::GetReplicatedInventoryComponents(
    TMap<FName, FReplicatedInventoryProperty>& OutReplicatedProps)
{
}

UClass* ABuildableFactoryReplicated::GetReplicationDetailActorClass() const {
    return AReplicationDetailActorGenerated::StaticClass();
}

void ABuildableFactoryReplicated::OnReplicationDetailActorCreated() {
    Super::OnReplicationDetailActorCreated();
}

void ABuildableFactoryReplicated::OnRep_ReplicationDetailActor() {
    TMap<FName, FReplicatedInventoryProperty> ReplicatedInventoryProperties;
    GetReplicatedInventoryComponents(ReplicatedInventoryProperties);
    if (mReplicationDetailActor) {
        AReplicationDetailActorGenerated* DetailActor = Cast<AReplicationDetailActorGenerated>(mReplicationDetailActor);
        if (DetailActor->HasCompletedInitialReplication()) {
            Super::OnRep_ReplicationDetailActor();
            //Iterate inventory properties, set inventory component for each of our handlers
            for(const FReplicatedInventoryInfo& InventoryInfo : DetailActor->InventoryInfos) {
                FReplicatedInventoryProperty& Property = ReplicatedInventoryProperties.FindChecked(InventoryInfo.InventoryName);
                UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property.InventoryComponentHandlerProperty);
                UFGReplicationDetailInventoryComponent* Component = Cast<UFGReplicationDetailInventoryComponent>(ObjectProperty->GetObjectPropertyValue_InContainer(this));
                checkf(Component, TEXT("InventoryComponentHandler is nullptr"));
                Component->SetReplicationInventoryComponent(InventoryInfo.InventoryComponent);                
            }
        } else {
            //Re-schedule method execution later to check if we completed initial replication
            FTimerHandle OutTimerHandle;
            FTimerManager& TimerManager = GetWorldTimerManager();
            TimerManager.SetTimer(OutTimerHandle, this, &ABuildableFactoryReplicated::OnRep_ReplicationDetailActor, 0.5, false);
        }
    }
}

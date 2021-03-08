#include "Buildable/ReplicationDetailActorGenerated.h"
#include "Buildable/BuildableFactoryReplicated.h"
#include "Net/UnrealNetwork.h"

void AReplicationDetailActorGenerated::InitReplicationDetailActor(AFGBuildable* owningActor) {
    Super::InitReplicationDetailActor(owningActor);
    ABuildableFactoryReplicated* Buildable = Cast<ABuildableFactoryReplicated>(owningActor);
    TMap<FName, FReplicatedInventoryProperty> ReplicatedInventoryProperties;
    Buildable->GetReplicatedInventoryComponents(ReplicatedInventoryProperties);

    if (Buildable) {
        for (const auto& InventoryPair : ReplicatedInventoryProperties) {
            const FReplicatedInventoryProperty& Property = InventoryPair.Value;
            UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property.InventoryComponentHandlerProperty);
            UFGReplicationDetailInventoryComponent* ComponentHandler = Cast<UFGReplicationDetailInventoryComponent>(ObjectProperty->GetObjectPropertyValue_InContainer(this));
            checkf(ComponentHandler, TEXT("InventoryComponentHandler is nullptr"));
            
            UFGInventoryComponent* ActiveComponent = ComponentHandler->GetActiveInventoryComponent();
            //Create new inventory component, copy values from parent component
            UClass* InventoryClass = ActiveComponent->GetClass();
            UFGInventoryComponent* NewInventoryComponent = UFGInventoryLibrary::CreateInventoryComponentOfClass(this, InventoryClass, InventoryPair.Key);
            NewInventoryComponent->SetIsReplicated(true);
            NewInventoryComponent->CopyFromOtherComponent(ActiveComponent);
            
            ComponentHandler->SetReplicationInventoryComponent(NewInventoryComponent);
            InventoryInfos.Add(FReplicatedInventoryInfo{NewInventoryComponent, InventoryPair.Key});
        }
    }
}

void AReplicationDetailActorGenerated::FlushReplicationActorStateToOwner() {
    Super::FlushReplicationActorStateToOwner();
    ABuildableFactoryReplicated* Buildable = Cast<ABuildableFactoryReplicated>(mOwningBuildable);
    TMap<FName, FReplicatedInventoryProperty> ReplicatedInventoryProperties;
    Buildable->GetReplicatedInventoryComponents(ReplicatedInventoryProperties);
    if (Buildable) {
        for(const FReplicatedInventoryInfo& InventoryInfo : InventoryInfos) {
            FReplicatedInventoryProperty& Property = ReplicatedInventoryProperties.FindChecked(InventoryInfo.InventoryName);
            UObjectProperty* ObjectProperty = Cast<UObjectProperty>(Property.InventoryComponentProperty);
            UFGInventoryComponent* Component = Cast<UFGInventoryComponent>(ObjectProperty->GetObjectPropertyValue_InContainer(this));
            checkf(Component, TEXT("InventoryComponent is nullptr"));
            //Flush replicated inventory values to parent component
            Component->CopyFromOtherComponent(InventoryInfo.InventoryComponent);           
        }
    }
}

void AReplicationDetailActorGenerated::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AReplicationDetailActorGenerated, InventoryInfos);
}

bool AReplicationDetailActorGenerated::HasCompletedInitialReplication() const {
    return Super::HasCompletedInitialReplication() && InventoryInfos.Num() > 0;
}

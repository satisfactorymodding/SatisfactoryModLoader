#include "GeneratedReplicationDetailActor.h"


#include "FGInventoryLibrary.h"
#include "UnrealNetwork.h"

ABuildableFactory_Replicated::ABuildableFactory_Replicated() {
}

void ABuildableFactory_Replicated::BeginPlay() {
    Super::BeginPlay();
}

void ABuildableFactory_Replicated::GetReplicatedInventoryComponents(
    TMap<FName, FReplicatedInventoryProperty>& OutReplicatedProps)
{
}

UClass* ABuildableFactory_Replicated::GetReplicationDetailActorClass() const {
    return AReplicationDetailActor_Generated::StaticClass();
}

void ABuildableFactory_Replicated::OnReplicationDetailActorCreated() {
    Super::OnReplicationDetailActorCreated();
}

void ABuildableFactory_Replicated::OnRep_ReplicationDetailActor() {
    TMap<FName, FReplicatedInventoryProperty> ReplicatedInventoryProperties;
    GetReplicatedInventoryComponents(ReplicatedInventoryProperties);
    if (mReplicationDetailActor) {
        AReplicationDetailActor_Generated* DetailActor = Cast<AReplicationDetailActor_Generated>(mReplicationDetailActor);
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
            TimerManager.SetTimer(OutTimerHandle, this, &ABuildableFactory_Replicated::OnRep_ReplicationDetailActor, 0.5, false);
        }
    }
}

void AReplicationDetailActor_Generated::InitReplicationDetailActor(AFGBuildable* owningActor) {
    Super::InitReplicationDetailActor(owningActor);
    ABuildableFactory_Replicated* Buildable = Cast<ABuildableFactory_Replicated>(owningActor);
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
        ExpectedNumberOfEntries = InventoryInfos.Num();
    }
}

void AReplicationDetailActor_Generated::FlushReplicationActorStateToOwner() {
    Super::FlushReplicationActorStateToOwner();
    ABuildableFactory_Replicated* Buildable = Cast<ABuildableFactory_Replicated>(mOwningBuildable);
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

void AReplicationDetailActor_Generated::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AReplicationDetailActor_Generated, InventoryInfos);
}

bool AReplicationDetailActor_Generated::HasCompletedInitialReplication() const {
    return Super::HasCompletedInitialReplication() && ExpectedNumberOfEntries > 0 && InventoryInfos.Num() == ExpectedNumberOfEntries;
}



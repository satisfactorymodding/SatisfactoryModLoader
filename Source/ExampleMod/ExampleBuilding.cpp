#include "ExampleBuilding.h"
#include "FGInventoryLibrary.h"
#include "ReplicationDetailActor_ExampleBuilding.h"
#include "util/Logging.h"

AExampleBuilding::AExampleBuilding() {
    LeftInventoryHandler = CreateDefaultSubobject<UFGReplicationDetailInventoryComponent>(TEXT("ReplicationDetailComponent_LeftInventory"));
    RightInventoryHandler = CreateDefaultSubobject<UFGReplicationDetailInventoryComponent>(TEXT("ReplicationDetailComponent_RightInventory"));
}

UClass* AExampleBuilding::GetReplicationDetailActorClass() const {
    return AReplicationDetailActor_ExampleBuilding::StaticClass();
}

void AExampleBuilding::OnRep_ReplicationDetailActor() {
    Super::OnRep_ReplicationDetailActor();
    if (!HasAuthority() && mReplicationDetailActor) {
        //Cast replication detail actor, set active replication inventory component
        //On client these will be used for UI and other logic run on client side
        AReplicationDetailActor_ExampleBuilding* DetailActor = Cast<AReplicationDetailActor_ExampleBuilding>(mReplicationDetailActor);
        if (DetailActor->HasCompletedInitialReplication()) {
            LeftInventoryHandler->SetReplicationInventoryComponent(DetailActor->InventoryComponentLeft);
            RightInventoryHandler->SetReplicationInventoryComponent(DetailActor->InventoryComponentRight);
        } else {
            FTimerManager& TimerManager = this->GetWorldTimerManager();
            FTimerHandle TimerHandle;
            TimerManager.SetTimer(TimerHandle, this, &AExampleBuilding::OnRep_ReplicationDetailActor, 0.5f, false);
        }
    }
}

void AExampleBuilding::BeginPlay() {
    Super::BeginPlay();
    if (HasAuthority()) {
        //Initialize inventories, set default inventory sizes
        InventoryComponentLeft = UFGInventoryLibrary::CreateInventoryComponent(this, TEXT("LeftInventory"));
        InventoryComponentLeft->SetDefaultSize(10);
        InventoryComponentRight = UFGInventoryLibrary::CreateInventoryComponent(this, TEXT("RightInventory"));
        InventoryComponentRight->SetDefaultSize(10);
        
        //Set main inventory reference for replication inventory handler
        //When ReplicationDetailActor is NOT SPAWNED, these represent REAL inventory states
        //But when one appears, it will copy state from then and from that moment we ARE NOT the owner of the inventories
        LeftInventoryHandler->SetMainInventoryComponent(InventoryComponentLeft);
        RightInventoryHandler->SetMainInventoryComponent(InventoryComponentRight);
    }
}

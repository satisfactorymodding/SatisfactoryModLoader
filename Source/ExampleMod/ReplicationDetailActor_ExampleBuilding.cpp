#include "ReplicationDetailActor_ExampleBuilding.h"
#include "UnrealNetwork.h"
#include "ExampleBuilding.h"
#include "FGInventoryLibrary.h"

//Add our fields to replicated list
void AReplicationDetailActor_ExampleBuilding::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
    DOREPLIFETIME(AReplicationDetailActor_ExampleBuilding, InventoryComponentLeft);
    DOREPLIFETIME(AReplicationDetailActor_ExampleBuilding, InventoryComponentRight);
}

//Create our inventory components, copy state from original, set replicated inventory components
void AReplicationDetailActor_ExampleBuilding::InitReplicationDetailActor(AFGBuildable* owningActor) {
    Super::InitReplicationDetailActor(owningActor);
    //Remember: UPROPERTY(Replicated) will only replicate property value, not the actual component
    InventoryComponentLeft = UFGInventoryLibrary::CreateInventoryComponent(this, TEXT("InventoryLeft"));
    InventoryComponentLeft->SetIsReplicated(true);
    InventoryComponentRight = UFGInventoryLibrary::CreateInventoryComponent(this, TEXT("InventoryRight"));
    InventoryComponentRight->SetIsReplicated(true);

    //Copy component states from the owner building
    AExampleBuilding* ExampleBuilding = Cast<AExampleBuilding>(owningActor);
    InventoryComponentLeft->CopyFromOtherComponent(ExampleBuilding->InventoryComponentLeft);
    InventoryComponentRight->CopyFromOtherComponent(ExampleBuilding->InventoryComponentRight);

    //Set replicated component values for host. For client they are set in OnRep_ReplicationDetailActor
    //After that, WE are considered the MASTER state of the inventories
    //So inventory WE own is actually what represents REAL STATE
    ExampleBuilding->LeftInventoryHandler->SetReplicationInventoryComponent(InventoryComponentLeft);
    ExampleBuilding->RightInventoryHandler->SetReplicationInventoryComponent(InventoryComponentRight);
}

//Copy replicated component values back to main inventory components
void AReplicationDetailActor_ExampleBuilding::FlushReplicationActorStateToOwner() {
    Super::FlushReplicationActorStateToOwner();
    if (mOwningBuildable) {
        //Copy replicated component values back to buildable inventory components
        //After that, WE NO LONGER represent a MASTER state of the inventories
        //REAL STATE is owned by the BUILDABLE inventories themselves now
        AExampleBuilding* ExampleBuilding = Cast<AExampleBuilding>(mOwningBuildable);
        ExampleBuilding->InventoryComponentLeft->CopyFromOtherComponent(InventoryComponentLeft);
        ExampleBuilding->InventoryComponentRight->CopyFromOtherComponent(InventoryComponentRight);
    }
}

bool AReplicationDetailActor_ExampleBuilding::HasCompletedInitialReplication() const {
    return Super::HasCompletedInitialReplication() && InventoryComponentLeft && InventoryComponentRight;
}

#include "ExampleBuildable.h"

AExampleBuildable::AExampleBuildable() {
    INITIALIZE_INVENTORY_COMPONENT(InputInventory, UFGInventoryComponent);
}

void AExampleBuildable::GetReplicatedInventoryComponents(TMap<FName, FReplicatedInventoryProperty>& OutReplicatedProps) {
    REPLICATE_INVENTORY(AExampleBuildable, InputInventory);
}
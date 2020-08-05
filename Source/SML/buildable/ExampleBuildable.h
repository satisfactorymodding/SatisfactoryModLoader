#pragma once
#include "GeneratedReplicationDetailActor.h"
#include "ExampleBuildable.generated.h"

/**
 * This buildable shows the basic example of ABuidableFactory_Replicated usage
 * for automatically generating replicated and saved indentory components
 */
UCLASS()
class AExampleBuildable : public ABuildableFactory_Replicated {
    GENERATED_BODY()
public:
    AExampleBuildable();
    virtual void GetReplicatedInventoryComponents(TMap<FName, struct FReplicatedInventoryProperty>& OutReplicatedProps) override;
public:
    DEFINE_REPLICATED_INVENTORY_PROPERTY(InputInventory, UFGInventoryComponent);    
};


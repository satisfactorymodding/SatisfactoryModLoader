#pragma once
#include "FGReplicationDetailActor_BuildableFactory.h"
#include "ReplicationDetailActor_ExampleBuilding.generated.h"

UCLASS()
class AReplicationDetailActor_ExampleBuilding : public AFGReplicationDetailActor_BuildableFactory {
    GENERATED_BODY()
public:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    void InitReplicationDetailActor(AFGBuildable* owningActor) override;
    void FlushReplicationActorStateToOwner() override;
    bool HasCompletedInitialReplication() const override;
private:
    friend class AExampleBuilding;
    UPROPERTY(Replicated)
    UFGInventoryComponent* InventoryComponentLeft;
    UPROPERTY(Replicated)
    UFGInventoryComponent* InventoryComponentRight;
};

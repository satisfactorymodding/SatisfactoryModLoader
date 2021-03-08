#pragma once
#include "CoreMinimal.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "ReplicationDetailActorGenerated.generated.h"

USTRUCT()
struct SML_API FReplicatedInventoryInfo {
    GENERATED_BODY()
public:
    UPROPERTY()
    UFGInventoryComponent* InventoryComponent;
    UPROPERTY()
    FName InventoryName;
};

UCLASS()
class SML_API AReplicationDetailActorGenerated : public AFGReplicationDetailActor_BuildableFactory {
    GENERATED_BODY()
public:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    void InitReplicationDetailActor(AFGBuildable* owningActor) override;
    void FlushReplicationActorStateToOwner() override;
    bool HasCompletedInitialReplication() const override;
public:
    UPROPERTY(Replicated)
    TArray<FReplicatedInventoryInfo> InventoryInfos;
};

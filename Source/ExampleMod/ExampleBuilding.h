#pragma once
#include "FGBuildableFactory.h"
#include "ExampleBuilding.generated.h"

UCLASS(Blueprintable)
class EXAMPLEMOD_API AExampleBuilding : public AFGBuildableFactory {
    GENERATED_BODY()
public:
    AExampleBuilding();
    
    void BeginPlay() override;
    UClass* GetReplicationDetailActorClass() const override;

    UFUNCTION( BlueprintPure, Category = "Inventory" )
    FORCEINLINE class UFGInventoryComponent* GetLeftInventory() const { return LeftInventoryHandler->GetActiveInventoryComponent(); }
    UFUNCTION( BlueprintPure, Category = "Inventory" )
    FORCEINLINE class UFGInventoryComponent* GetRightInventory() const { return RightInventoryHandler->GetActiveInventoryComponent(); }
protected:
    friend class AReplicationDetailActor_ExampleBuilding;
    void OnRep_ReplicationDetailActor() override;
    
    /** Inventory pointers used for actually storing content */
    UPROPERTY(SaveGame)
    UFGInventoryComponent* InventoryComponentLeft;
    UPROPERTY(SaveGame)
    UFGInventoryComponent* InventoryComponentRight;

    UFGReplicationDetailInventoryComponent* LeftInventoryHandler;
    UFGReplicationDetailInventoryComponent* RightInventoryHandler;
};

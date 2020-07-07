#pragma once

#include "FGBuildableFactory.h"
#include "GameFramework/Actor.h"
#include "Replication/FGReplicationDetailActor_BuildableFactory.h"
#include "FGInventoryLibrary.h"
#include "GeneratedReplicationDetailActor.generated.h"

#define REPLICATE_INVENTORY_INNER(Class, InventoryTitle, InventoryName, HandlerName) \
    OutReplicatedProps.Add(TEXT(#InventoryTitle), FReplicatedInventoryProperty{\
        Class::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(Class, InventoryName)), \
        Class::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(Class, HandlerName))});

#define REPLICATE_INVENTORY(Class, InventoryName) \
    REPLICATE_INVENTORY_INNER(Class, InventoryName, PREPROCESSOR_JOIN(InventoryName, Inventory), PREPROCESSOR_JOIN(InventoryName, InventoryHandler));

#define DEFINE_REPLICATED_INVENTORY_PROPERTY(InventoryName, InventoryClass) \
    private: \
        UPROPERTY(SaveGame) \
        UFGInventoryComponent* PREPROCESSOR_JOIN(InventoryName, Inventory); \
        UPROPERTY() \
        UFGReplicationDetailInventoryComponent* PREPROCESSOR_JOIN(InventoryName, InventoryHandler); \
    public: \
        FORCEINLINE InventoryClass* Get##InventoryName() { return Cast<InventoryClass>(PREPROCESSOR_JOIN(InventoryName, InventoryHandler)->GetActiveInventoryComponent()); };

#define INITIALIZE_INVENTORY_COMPONENT_INNER(InventoryClass, InventoryName, InventoryHandlerName) \
    InventoryName = UFGInventoryLibrary::CreateInventoryComponentOfClass(this, InventoryClass::StaticClass(), TEXT(PREPROCESSOR_TO_STRING(InventoryName))); \
    InventoryHandlerName = NewObject<UFGReplicationDetailInventoryComponent>(this, TEXT(PREPROCESSOR_TO_STRING(InventoryHandlerName))); \
    InventoryHandlerName->RegisterComponent(); \
    InventoryHandlerName->SetMainInventoryComponent(InventoryName);

#define INITIALIZE_INVENTORY_COMPONENT(InventoryName, InventoryClass) \
    INITIALIZE_INVENTORY_COMPONENT_INNER(InventoryClass, PREPROCESSOR_JOIN(InventoryName, Inventory), PREPROCESSOR_JOIN(InventoryName, InventoryHandler));

struct FReplicatedInventoryProperty {
    /*
     * Reference to properties for inventory component and inventory component handler
     * Used for replication and obtaining information for usage by AReplicationDetailActor_Generated
     */
    UProperty* InventoryComponentProperty;
    UProperty* InventoryComponentHandlerProperty;
};

USTRUCT()
struct SML_API FReplicatedInventoryInfo {
    GENERATED_BODY()
public:
    UPROPERTY()
    UFGInventoryComponent* InventoryComponent;
    UPROPERTY()
    FName InventoryName;
};

UCLASS(Abstract)
class SML_API ABuildableFactory_Replicated : public AFGBuildableFactory {
    GENERATED_BODY()
public:
    ABuildableFactory_Replicated();
    virtual void BeginPlay() override;
    virtual void GetReplicatedInventoryComponents(TMap<FName, struct FReplicatedInventoryProperty>& OutReplicatedProps);

    virtual UClass* GetReplicationDetailActorClass() const override;
    virtual void OnReplicationDetailActorCreated() override;
    virtual void OnRep_ReplicationDetailActor() override;
};

UCLASS()
class SML_API AReplicationDetailActor_Generated : public AFGReplicationDetailActor_BuildableFactory {
    GENERATED_BODY()
public:
    void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
    void InitReplicationDetailActor(AFGBuildable* owningActor) override;
    void FlushReplicationActorStateToOwner() override;
    bool HasCompletedInitialReplication() const override;
public:
    UPROPERTY(Replicated)
    int32 ExpectedNumberOfEntries;
    UPROPERTY(Replicated)
    TArray<FReplicatedInventoryInfo> InventoryInfos;
};

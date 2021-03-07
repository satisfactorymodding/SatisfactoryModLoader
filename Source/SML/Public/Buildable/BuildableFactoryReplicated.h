#pragma once
#include "Buildables/FGBuildableFactory.h"
#include "FGInventoryLibrary.h"
#include "BuildableFactoryReplicated.generated.h"

/**
 * Use this macro inside GetReplicatedInventoryComponents of your building and
 * specify inventory name equal to what you specified in DEFINE_REPLICATED_INVENTORY. Example:
 *
 * REPLICATE_INVENTORY(UFGInventoryComponent, ExampleInventory);
 */
#define REPLICATE_INVENTORY(Class, InventoryName) \
    REPLICATE_INVENTORY_INNER(Class, InventoryName, PREPROCESSOR_JOIN(InventoryName, Inventory), PREPROCESSOR_JOIN(InventoryName, InventoryHandler));

/**
 * Use this macro inside class body to define properties required for replicated inventory
 * It will automatically create InventoryHandler and InventoryComponent fields that you will
 * need to initialize in BeginPlay. Example:
 *    GENERATED_BODY()
 *     ...
 *     DEFINE_REPLICATED_INVENTORY(ExampleInventory, UFGInventoryComponent);
 */
#define DEFINE_REPLICATED_INVENTORY(InventoryName, InventoryClass) \
    private: \
        UPROPERTY(SaveGame) \
        UFGInventoryComponent* PREPROCESSOR_JOIN(InventoryName, Inventory); \
        UPROPERTY() \
        UFGReplicationDetailInventoryComponent* PREPROCESSOR_JOIN(InventoryName, InventoryHandler); \
    public: \
        FORCEINLINE InventoryClass* Get##InventoryName() { return Cast<InventoryClass>(PREPROCESSOR_JOIN(InventoryName, InventoryHandler)->GetActiveInventoryComponent()); };

/**
 * Use this macro in BeginPlay to initialize inventory component with given name
 * which was defined earlier using DEFINE_REPLICATED_INVENTORY. Example:
 *
 * INITIALIZE_INVENTORY_COMPONENT(ExampleInventory, UFGInventoryComponent);
 */
#define INITIALIZE_INVENTORY_COMPONENT(InventoryName, InventoryClass) \
    INITIALIZE_INVENTORY_COMPONENT_INNER(InventoryClass, PREPROCESSOR_JOIN(InventoryName, Inventory), PREPROCESSOR_JOIN(InventoryName, InventoryHandler));

UCLASS(Abstract)
class SML_API ABuildableFactoryReplicated : public AFGBuildableFactory {
    GENERATED_BODY()
public:
    /**
     * Override this one to list inventories and their handlers components for replication
     * You should use macro REPLICATE_INVENTORY to generate necessary boilerplate code for replicating inventory
     * component by it's name that you specified in DEFINE_REPLICATED_INVENTORY. Example:
     * 
     * REPLICATE_INVENTORY(UFGInventoryComponent, ExampleInventory);
     */
    virtual void GetReplicatedInventoryComponents(TMap<FName, struct FReplicatedInventoryProperty>& OutReplicatedProps);

    virtual UClass* GetReplicationDetailActorClass() const override;
    virtual void OnReplicationDetailActorCreated() override;
    virtual void OnRep_ReplicationDetailActor() override;
};

/*
* Reference to properties for inventory component and inventory component handler
* Used for replication and obtaining information for usage by AReplicationDetailActor_Generated
*/
struct SML_API FReplicatedInventoryProperty {
    UProperty* InventoryComponentProperty;
    UProperty* InventoryComponentHandlerProperty;
};

#define INITIALIZE_INVENTORY_COMPONENT_INNER(InventoryClass, InventoryName, InventoryHandlerName) \
    InventoryHandlerName = CreateDefaultSubobject<UFGReplicationDetailInventoryComponent>(TEXT(PREPROCESSOR_TO_STRING(InventoryHandlerName))); \
    Component->SetNetAddressable(); \
    Component->RegisterComponent(); \
    if (HasAuthority()) { \
        InventoryName = UFGInventoryLibrary::CreateInventoryComponentOfClass(this, InventoryClass::StaticClass(), TEXT(PREPROCESSOR_TO_STRING(InventoryName))); \
        InventoryHandlerName->SetMainInventoryComponent(InventoryName); \
    }

#define REPLICATE_INVENTORY_INNER(Class, InventoryTitle, InventoryName, HandlerName) \
    OutReplicatedProps.Add(TEXT(#InventoryTitle), FReplicatedInventoryProperty{\
    Class::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(Class, InventoryName)), \
    Class::StaticClass()->FindPropertyByName(GET_MEMBER_NAME_CHECKED(Class, HandlerName))});

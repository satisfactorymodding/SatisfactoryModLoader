#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Module/WorldModule.h"
#include "WorldModuleManager.generated.h"

/** Manages registered world modules and their lifecycle events */
UCLASS(NotBlueprintable)
class SML_API AWorldModuleManager : public AInfo {
    GENERATED_BODY()
private:
    /** Root map of modules for every registered mod reference */
    UPROPERTY()
    TMap<FName, UWorldModule*> RootModuleMap;

    /** Root module list for fast iteration according to order of registration */
    UPROPERTY()
    TArray<UWorldModule*> RootModuleList;
public:
    /** Retrieves world module manager for provided world */
    UFUNCTION(BlueprintPure)
    static AWorldModuleManager* Get(UObject* WorldContext); 
    
    /** Retrieves world module by provided mod reference */
    UFUNCTION(BlueprintPure)
    UWorldModule* FindModule(const FName& ModReference) const;
private:
    friend class UModLoadingLibrary;
    
    /** Registers world module manager */
    static void RegisterModuleManager();
    
    /** Called when world actors have been initialized */
    void Initialize();

    /** Called when world post initialization has been completed */
    void PostInitialize();
    
    /** Allocates root module object for instance and registers it */
    void CreateRootModule(const FName& ModReference, TSubclassOf<UWorldModule> ObjectClass);

    /** Dispatches lifecycle event to all registered modules */
    void DispatchLifecycleEvent(ELifecyclePhase Phase);
};

UCLASS()
class SML_API UWorldModuleManagerComponent : public UActorComponent {
    GENERATED_BODY()
private:
    UPROPERTY()
    AWorldModuleManager* ModuleManager;
public:
    void SpawnModuleManager();
    FORCEINLINE AWorldModuleManager* GetModuleManager() const { return ModuleManager; }
};
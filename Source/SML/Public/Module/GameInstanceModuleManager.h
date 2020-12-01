#pragma once
#include "GameInstanceSubsystem.h"
#include "Module/GameInstanceModule.h"
#include "GameInstanceModuleManager.generated.h"

/** Manages registered game instance modules and their lifecycle event processing */
UCLASS()
class SML_API UGameInstanceModuleManager : public UGameInstanceSubsystem {
    GENERATED_BODY()
private:
    /** Root map of modules for every registered mod reference */
    UPROPERTY()
    TMap<FName, UGameInstanceModule*> RootModuleMap;

    /** Root module list for fast iteration according to order of registration */
    UPROPERTY()
    TArray<UGameInstanceModule*> RootModuleList;
public:
    /** Retrieves root game instance module by provided mod reference */
    UFUNCTION(BlueprintPure)
    UGameInstanceModule* FindModule(const FName& ModReference) const;
private:
    friend class FModHandler;
    
    /** Allocates root module object for instance and registers it */
    void CreateRootModule(const FName& ModReference, TSubclassOf<UGameInstanceModule> ObjectClass);

    /** Dispatches lifecycle event to all registered modules */
    void DispatchLifecycleEvent(ELifecyclePhase Phase);
};

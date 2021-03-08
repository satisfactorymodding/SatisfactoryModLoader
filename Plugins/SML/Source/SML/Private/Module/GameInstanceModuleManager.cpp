#include "Module/GameInstanceModuleManager.h"

UGameInstanceModule* UGameInstanceModuleManager::FindModule(const FName& ModReference) const {
    UGameInstanceModule* const* GameInstanceModule = RootModuleMap.Find(ModReference);
    if (GameInstanceModule != NULL) {
        return *GameInstanceModule;
    }
    return NULL;
}

void UGameInstanceModuleManager::CreateRootModule(const FName& ModReference, TSubclassOf<UGameInstanceModule> ObjectClass) {
    //Allocate module object and set mod reference
    UGameInstanceModule* RootGameInstanceModule = NewObject<UGameInstanceModule>(this, ObjectClass, ModReference);
    check(RootGameInstanceModule);
    RootGameInstanceModule->SetOwnerModReference(ModReference);
    
    //Add it to internal lists
    RootModuleMap.Add(ModReference, RootGameInstanceModule);
    RootModuleList.Add(RootGameInstanceModule);
}

void UGameInstanceModuleManager::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Iterate modules in their order of registration and dispatch lifecycle event to them
    for (UGameInstanceModule* RootModule : RootModuleList) {
        RootModule->DispatchLifecycleEvent(Phase);
    }
}

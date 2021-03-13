#include "Module/GameInstanceModuleManager.h"
#include "SatisfactoryModLoader.h"
#include "ModLoading/PluginModuleLoader.h"

UGameInstanceModule* UGameInstanceModuleManager::FindModule(const FName& ModReference) const {
    UGameInstanceModule* const* GameInstanceModule = RootModuleMap.Find(ModReference);
    if (GameInstanceModule != NULL) {
        return *GameInstanceModule;
    }
    return NULL;
}

void UGameInstanceModuleManager::Initialize(FSubsystemCollectionBase& Collection) {
    const TArray<FDiscoveredModule> DiscoveredModules = FPluginModuleLoader::FindRootModulesOfType(UGameInstanceModule::StaticClass());

    TMap<FString, FString> AlreadyLoadedMods;
    for (const FDiscoveredModule& Module : DiscoveredModules) {
        
        //Make sure we are not trying to register a single plugin twice
        if (AlreadyLoadedMods.Contains(Module.OwnerPluginName)) {
            const FString OtherModulePath = AlreadyLoadedMods.FindChecked(Module.OwnerPluginName);
            UE_LOG(LogSatisfactoryModLoader, Fatal, TEXT("Failed to initialize Game Instane Module for Plugin %s: "
                "Multiple root modules have been discovered, %s and %s. Only one root module is allowed"),
                *Module.OwnerPluginName, *OtherModulePath, *Module.ModuleClass->GetPathName());
            continue;
        }

        //Register module in the game instance module manager now
        const TSubclassOf<UGameInstanceModule> GameInstanceModule = Module.ModuleClass.Get();
        AlreadyLoadedMods.Add(Module.OwnerPluginName, Module.ModuleClass->GetPathName());
        CreateRootModule(*Module.OwnerPluginName, GameInstanceModule);
    }
    
    UE_LOG(LogSatisfactoryModLoader, Log, TEXT("Discovered %s game instance modules"), AlreadyLoadedMods.Num());
    
    //Dispatch lifecycle events in a sequence
    DispatchLifecycleEvent(ELifecyclePhase::CONSTRUCTION);
    DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
    DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
}

bool UGameInstanceModuleManager::ShouldCreateSubsystem(UObject* Outer) const {
    //We only want to initialize modules for PIE and game worlds, never for editor and other worlds
    UGameInstance* GameInstance = CastChecked<UGameInstance>(Outer);
    return FPluginModuleLoader::ShouldLoadModulesForWorld(GameInstance->GetWorld());
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
    //Notify log of our current loading phase, in case of things going wrong
    const FString PhaseName = StaticEnum<ELifecyclePhase>()->GetNameStringByValue((int64) Phase);
    UE_LOG(LogSatisfactoryModLoader, Log, TEXT("Dispatching lifecycle event %s to game instance modules"), *PhaseName);
    
    //Iterate modules in their order of registration and dispatch lifecycle event to them
    for (UGameInstanceModule* RootModule : RootModuleList) {
        RootModule->DispatchLifecycleEvent(Phase);
    }
}

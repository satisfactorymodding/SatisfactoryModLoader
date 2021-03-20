#include "Module/WorldModuleManager.h"

#include "FGGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SatisfactoryModLoader.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Module/GameWorldModule.h"
#include "Module/MenuWorldModule.h"

AWorldModuleManager* AWorldModuleManager::Get(UObject* WorldContext) {
    UWorld* World = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::Assert);
    AGameStateBase* GameState = World->GetGameState();
    check(GameState);
    UWorldModuleManagerComponent* ModuleManagerComponent = GameState->FindComponentByClass<UWorldModuleManagerComponent>();
    
    if (ModuleManagerComponent == NULL) {
        //World Module Manager has not been initialized yet, perform lazy initialization
        ModuleManagerComponent = NewObject<UWorldModuleManagerComponent>(GameState, TEXT("WorldModuleManagerComponent"));
        check(ModuleManagerComponent);
        ModuleManagerComponent->SpawnModuleManager();
        ModuleManagerComponent->RegisterComponent();
    }
    
    return ModuleManagerComponent->GetModuleManager();
}

UWorldModule* AWorldModuleManager::FindModule(const FName& ModReference) const {
    UWorldModule* const* WorldModule = RootModuleMap.Find(ModReference);
    if (WorldModule != NULL) {
        return *WorldModule;
    }
    return NULL;
}

void AWorldModuleManager::RegisterModuleManager() {
    //Spawn mod modules as soon as world actors are initialized (e.g static map objects are spawned)
    FWorldDelegates::OnWorldInitializedActors.AddLambda([](const UWorld::FActorsInitializedParams Params) {
        if (FPluginModuleLoader::ShouldLoadModulesForWorld(Params.World)) {
            AWorldModuleManager* ModuleManager = AWorldModuleManager::Get(Params.World);
            ModuleManager->Initialize();
        }
    });
    
    //Post initialize mod modules when world is fully loaded and is ready to be used
    FCoreUObjectDelegates::PostLoadMapWithWorld.AddLambda([](UWorld* World){
        if (FPluginModuleLoader::ShouldLoadModulesForWorld(World)) {
            AWorldModuleManager* ModuleManager = AWorldModuleManager::Get(World);
            ModuleManager->PostInitialize();
        }
    });
}

void AWorldModuleManager::Initialize() {
    //Use game world module by default
    TSubclassOf<UWorldModule> ModuleTypeClass = UGameWorldModule::StaticClass();

    //Use MenuWorldModule if we have a game mode and it is set to main menu
    AFGGameMode* GameMode = Cast<AFGGameMode>(GetWorld()->GetAuthGameMode());
    if (GameMode != NULL && GameMode->IsMainMenuGameMode()) {
        ModuleTypeClass = UMenuWorldModule::StaticClass();
    }

    //Discover modules of the relevant types
    const TArray<FDiscoveredModule> DiscoveredModules = FPluginModuleLoader::FindRootModulesOfType(ModuleTypeClass);

    TMap<FString, FString> AlreadyLoadedMods;
    for (const FDiscoveredModule& Module : DiscoveredModules) {
        
        //Make sure we are not trying to register a single plugin twice
        if (AlreadyLoadedMods.Contains(Module.OwnerPluginName)) {
            const FString OtherModulePath = AlreadyLoadedMods.FindChecked(Module.OwnerPluginName);
            UE_LOG(LogSatisfactoryModLoader, Fatal, TEXT("Failed to initialize World Module for Plugin %s: "
                "Multiple root modules have been discovered, %s and %s. Only one root module is allowed"),
                *Module.OwnerPluginName, *OtherModulePath, *Module.ModuleClass->GetPathName());
            continue;
        }

        //Register module in the game instance module manager now
        const TSubclassOf<UWorldModule> WorldModule = Module.ModuleClass.Get();
        AlreadyLoadedMods.Add(Module.OwnerPluginName, Module.ModuleClass->GetPathName());
        CreateRootModule(*Module.OwnerPluginName, WorldModule);
    }
    
    UE_LOG(LogSatisfactoryModLoader, Log, TEXT("Discovered %d world modules of class %s"), AlreadyLoadedMods.Num(), *ModuleTypeClass->GetName());
    
    //Dispatch lifecycle events in a sequence
    DispatchLifecycleEvent(ELifecyclePhase::CONSTRUCTION);
    DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
}

void AWorldModuleManager::PostInitialize() {
    //Finish loading and dispatch post init now
    DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
}

void AWorldModuleManager::CreateRootModule(const FName& ModReference, TSubclassOf<UWorldModule> ObjectClass) {
    //Allocate module object and set mod reference
    UWorldModule* RootWorldModule = NewObject<UWorldModule>(this, ObjectClass, ModReference);
    check(RootWorldModule);
    RootWorldModule->SetOwnerModReference(ModReference);
    
    //Add it to internal lists
    RootModuleMap.Add(ModReference, RootWorldModule);
    RootModuleList.Add(RootWorldModule);
}

void AWorldModuleManager::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Notify log of our current loading phase, in case of things going wrong
    UE_LOG(LogSatisfactoryModLoader, Log, TEXT("Dispatching lifecycle event %s to world %s modules"), 
        *UModModule::LifecyclePhaseToString(Phase), *GetWorld()->GetMapName());
    
    //Iterate modules in their order of registration and dispatch lifecycle event to them
    for (UWorldModule* RootModule : RootModuleList) {
        RootModule->DispatchLifecycleEvent(Phase);
    }
}

void UWorldModuleManagerComponent::SpawnModuleManager() {
    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = GetOwner();
    SpawnParams.Name = TEXT("WorldModuleManager");
    this->ModuleManager = GetWorld()->SpawnActor<AWorldModuleManager>(SpawnParams);
    check(ModuleManager);
}

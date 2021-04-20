#include "Module/WorldModuleManager.h"

#include "FGGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SatisfactoryModLoader.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Module/GameWorldModule.h"
#include "Module/MenuWorldModule.h"

UWorldModuleManager::UWorldModuleManager() {
	this->bPostponeInitializeModules = false;
	this->bPostponePostInitializeModules = false;
}

UWorldModule* UWorldModuleManager::FindModule(const FName& ModReference) const {
    UWorldModule* const* WorldModule = RootModuleMap.Find(ModReference);
    if (WorldModule != NULL) {
        return *WorldModule;
    }
    return NULL;
}

bool UWorldModuleManager::ShouldCreateSubsystem(UObject* Outer) const {
	UWorld* WorldOuter = CastChecked<UWorld>(Outer);
	return FPluginModuleLoader::ShouldLoadModulesForWorld(WorldOuter);
}

void UWorldModuleManager::Initialize(FSubsystemCollectionBase& Collection) {
	UWorld* OuterWorld = GetWorld();
	OuterWorld->GameStateSetEvent.AddUObject(this, &UWorldModuleManager::OnGameStateSet);
	OuterWorld->OnActorsInitialized.AddUObject(this, &UWorldModuleManager::InitializeModules);
	OuterWorld->OnWorldBeginPlay.AddUObject(this, &UWorldModuleManager::PostInitializeModules);
	ConstructModules();
}

void UWorldModuleManager::OnGameStateSet(AGameStateBase*) {
	if (bPostponeInitializeModules) {
		DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
		this->bPostponeInitializeModules = false;
	}

	if (bPostponePostInitializeModules) {
		DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
		this->bPostponePostInitializeModules = false;
	}
}

void UWorldModuleManager::InitializeModules(const UWorld::FActorsInitializedParams&) {
	if (GetWorld()->GetGameState()) {
		DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
	} else {
		this->bPostponeInitializeModules = true;
	}
}

void UWorldModuleManager::PostInitializeModules() {
	if (GetWorld()->GetGameState()) {
		DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
	} else {
		this->bPostponePostInitializeModules = true;
	}
}


void UWorldModuleManager::ConstructModules() {
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
    
    //Dispatch construction lifecycle event
    DispatchLifecycleEvent(ELifecyclePhase::CONSTRUCTION);
}

void UWorldModuleManager::CreateRootModule(const FName& ModReference, TSubclassOf<UWorldModule> ObjectClass) {
    //Allocate module object and set mod reference
    UWorldModule* RootWorldModule = NewObject<UWorldModule>(this, ObjectClass, ModReference);
    check(RootWorldModule);
    RootWorldModule->SetOwnerModReference(ModReference);
    
    //Add it to internal lists
    RootModuleMap.Add(ModReference, RootWorldModule);
    RootModuleList.Add(RootWorldModule);
}

void UWorldModuleManager::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Notify log of our current loading phase, in case of things going wrong
    UE_LOG(LogSatisfactoryModLoader, Log, TEXT("Dispatching lifecycle event %s to world %s modules"), 
        *UModModule::LifecyclePhaseToString(Phase), *GetWorld()->GetMapName());
    
    //Iterate modules in their order of registration and dispatch lifecycle event to them
    for (UWorldModule* RootModule : RootModuleList) {
        RootModule->DispatchLifecycleEvent(Phase);
    }
}
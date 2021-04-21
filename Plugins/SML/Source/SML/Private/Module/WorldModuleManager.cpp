#include "Module/WorldModuleManager.h"

#include "FGGameMode.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Engine.h"
#include "Engine/World.h"
#include "SatisfactoryModLoader.h"
#include "ModLoading/PluginModuleLoader.h"
#include "Module/GameWorldModule.h"
#include "Module/MenuWorldModule.h"
#include "Registry/ModContentRegistry.h"

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
}

void UWorldModuleManager::OnGameStateSet(AGameStateBase*) {
	//We want to postpone initialization by one more tick, because OnGameStateSet is basically
	//called from AGameStateBase, which is too early for any kind of initialization inside of the AFGGameState
	//It will be done right after broadcasting event though, so just delaying registration solves the problem
	if (bPostponeInitializeModules || bPostponePostInitializeModules) {
		GetWorld()->GetTimerManager().SetTimerForNextTick(this, &UWorldModuleManager::OnGameStateFullyInitialized);
	}
}

void UWorldModuleManager::OnGameStateFullyInitialized() {
	if (bPostponeInitializeModules) {
		DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
		NotifyContentRegistry();
		this->bPostponeInitializeModules = false;
	}
    
	if (bPostponePostInitializeModules) {
		DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
		this->bPostponePostInitializeModules = false;
	}
}

void UWorldModuleManager::InitializeModules(const UWorld::FActorsInitializedParams&) {
	//We always construct modules when world actors are initialized,
	//because actors are not supposed to try and access registry and subsystems in the construction phase
	//It's still useful to do it here though, because that way modules on remote
	//get the chance to handle OnWorldActorsInitialized event (which they won't get in init because
	//it will get postponed since game state is not replicated yet)
	ConstructModules();

	//Initialized can be delayed when we haven't replicated game state yet,
	//modules can still use construct to react specifically to OnWorldActorsInitialized event
	if (GetWorld()->GetGameState()) {
		DispatchLifecycleEvent(ELifecyclePhase::INITIALIZATION);
		NotifyContentRegistry();
	} else {
		this->bPostponeInitializeModules = true;
	}
}

void UWorldModuleManager::PostInitializeModules() {
	//Post initialization can be postponed if we haven't replicated game state yet
	//Overall, OnWorldBeginPlay is a very simple event which just means that all of the actors in the world
	//had BeginPlay dispatched, technically making it earliest place where world is fully initialized
	//It's okay to run initialization a bit later on remote, since world is already fully initialized at this point
	if (GetWorld()->GetGameState()) {
		DispatchLifecycleEvent(ELifecyclePhase::POST_INITIALIZATION);
	} else {
		this->bPostponePostInitializeModules = true;
	}
}

void UWorldModuleManager::NotifyContentRegistry() {
	AModContentRegistry* ContentRegistry = AModContentRegistry::Get(this);
	check(ContentRegistry);
	ContentRegistry->NotifyModuleRegistrationFinished();
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
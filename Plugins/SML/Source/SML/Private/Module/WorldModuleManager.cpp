#include "Module/WorldModuleManager.h"
#include "GameFramework/GameStateBase.h"
#include "Engine/Engine.h"
#include "Engine/World.h"

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

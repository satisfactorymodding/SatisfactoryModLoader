#include "Registry/SubsystemHolderRegistry.h"
#include "FGGameState.h"
#include "Patching/NativeHookManager.h"
#include "Subsystem/SMLSubsystemHolder.h"

DEFINE_LOG_CATEGORY(LogSubsystemHolderRegistry);

USubsystemHolderRegistry::USubsystemHolderRegistry() {
    bRegistryFrozen = false;
}

void USubsystemHolderRegistry::InitializeSubsystems(AFGGameState* GameState) {
    UGameInstance* GameInstance = GameState->GetWorld()->GetGameInstance();
    const USubsystemHolderRegistry* Registry = GameInstance->GetSubsystem<USubsystemHolderRegistry>();
    
    const bool bIsAuthority = GameState->HasAuthority();
    UE_LOG(LogSubsystemHolderRegistry, Display, TEXT("Initializing modded subsystem holders"));
	
    for (const FSubsystemHolderRegistrarEntry& RegistrarEntry : Registry->RegisteredSubsystemHolders) {
        UClass* SubsystemHolderClass = RegistrarEntry.SubsystemHolderClass;
        check(SubsystemHolderClass->IsChildOf<UModSubsystemHolder>());
        UE_LOG(LogSubsystemHolderRegistry, Display, TEXT("Initializing subsystem holder %s, owned by %s"), *SubsystemHolderClass->GetPathName(), *RegistrarEntry.OwnerModReference);
        const FString SubsystemComponentName = FString::Printf(TEXT("%s_%s"), *RegistrarEntry.OwnerModReference, *SubsystemHolderClass->GetName());
        
        UModSubsystemHolder* Component = NewObject<UModSubsystemHolder>(GameState, SubsystemHolderClass, *SubsystemComponentName);
        Component->SetNetAddressable();
        Component->SetIsReplicated(true);
        Component->RegisterComponent();
		
        Component->InitLocalSubsystems();
        Component->K2_InitLocalSubsystems();
		
        if (bIsAuthority) {
            Component->InitSubsystems();
            Component->K2_InitSubsystems();
        }
    } 
}

void USubsystemHolderRegistry::RegisterSubsystemHolder(const FString& ModReference, TSubclassOf<UModSubsystemHolder> SubsystemHolderClass) {
    if (bRegistryFrozen) {
        UE_LOG(LogSubsystemHolderRegistry, Fatal, TEXT("Attempt to register object in frozen subsystem holder registry"));
    }
    RegisteredSubsystemHolders.Add(FSubsystemHolderRegistrarEntry{ModReference, SubsystemHolderClass});
}

void USubsystemHolderRegistry::Initialize(FSubsystemCollectionBase& Collection) {
    RegisterSubsystemHolder(TEXT("SML"), USMLSubsystemHolder::StaticClass());
}

void USubsystemHolderRegistry::InitializePatches() {
    void* ObjectInstance = GetMutableDefault<AFGGameState>();
    SUBSCRIBE_METHOD_VIRTUAL_AFTER(AFGGameState::Init, ObjectInstance, [](AFGGameState* GameState) {
        InitializeSubsystems(GameState);
    });
}

void USubsystemHolderRegistry::FreezeRegistry() {
    checkf(!bRegistryFrozen, TEXT("Attempt to re-freeze already frozen registry"));

    UE_LOG(LogSubsystemHolderRegistry, Display, TEXT("Freezing subsystem holder registry"));
    bRegistryFrozen = true;
}

#include "Registry/SubsystemHolderRegistry.h"
#include "FGGameState.h"
#include "Logging.h"
#include "NativeHookManager.h"

DEFINE_LOG_CATEGORY(LogSubsystemHolderRegistry);

USubsystemHolderRegistry::USubsystemHolderRegistry() {
    bIsRegistryFrozen = false;
}

void USubsystemHolderRegistry::InitializeRegistry() {
    SUBSCRIBE_METHOD_AFTER(AFGGameState::Init, [](AFGGameState* GameState) {
        InitializeSubsystems(GameState);
    });
}

void USubsystemHolderRegistry::InitializeSubsystems(AFGGameState* GameState) {
    const USubsystemHolderRegistry* Registry = GetDefault<USubsystemHolderRegistry>();
    const bool bIsAuthority = GameState->Role == ENetRole::ROLE_Authority;
    SML_LOG(LogSubsystemHolderRegistry, Log, TEXT("Initializing modded subsystem holders"));
	
    for (const FSubsystemHolderRegistrarEntry& RegistrarEntry : Registry->RegisteredSubsystemHolders) {
        UClass* SubsystemHolderClass = RegistrarEntry.SubsystemHolderClass;
        check(SubsystemHolderClass->IsChildOf<UModSubsystemHolder>());
        SML_LOG(LogSubsystemHolderRegistry, Log, TEXT("Initializing subsystem holder %s, owned by %s"), *SubsystemHolderClass->GetPathName(), *RegistrarEntry.OwnerModReference);
        const FString SubsystemComponentName = FString::Printf(TEXT("%s_%s"), *RegistrarEntry.OwnerModReference, *SubsystemHolderClass->GetName());
        
        UModSubsystemHolder* Component = NewObject<UModSubsystemHolder>(SubsystemHolderClass, *SubsystemComponentName);
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
    if (bIsRegistryFrozen) {
        SML_LOG(LogSubsystemHolderRegistry, Fatal, TEXT("Attempt to register object in frozen subsystem holder registry"));
    }
    USubsystemHolderRegistry* Registry = GetMutableDefault<USubsystemHolderRegistry>();
    Registry->RegisteredSubsystemHolders.Add(FSubsystemHolderRegistrarEntry{ModReference, SubsystemHolderClass});
}


bool USubsystemHolderRegistry::bIsRegistryFrozen = false;

void USubsystemHolderRegistry::FreezeRegistry() {
    checkf(!bIsRegistryFrozen, TEXT("Attempt to re-freeze already frozen registry"));

    SML_LOG(LogSubsystemHolderRegistry, Display, TEXT("Freezing subsystem holder registry"));
    bIsRegistryFrozen = true;
}

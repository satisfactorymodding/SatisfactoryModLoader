#include "Subsystem/SMLSubsystemHolder.h"
#include "Command/ChatCommandLibrary.h"
#include "Registry/ModContentRegistry.h"
#include "Registry/SubsystemHolderRegistry.h"

void USMLSubsystemHolder::InitSubsystems() {
    SpawnSubsystem(ChatCommandSubsystem, AChatCommandSubsystem::StaticClass(), TEXT("ChatCommandSubsystem"));
    ChatCommandSubsystem->Init();
}

void USMLSubsystemHolder::InitLocalSubsystems() {
    SpawnSubsystem(ModContentRegistry, AModContentRegistry::StaticClass(), TEXT("ModContentRegistry"));
    ModContentRegistry->Init();
}

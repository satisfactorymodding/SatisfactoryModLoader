#include "Subsystem/SMLSubsystemHolder.h"
#include "ChatCommandLibrary.h"
#include "ModContentRegistry.h"
#include "SubsystemHolderRegistry.h"

void USMLSubsystemHolder::InitSubsystems() {
    SpawnSubsystem(ChatCommandSubsystem, AChatCommandSubsystem::StaticClass(), TEXT("ChatCommandSubsystem"));
    ChatCommandSubsystem->Init();
}

void USMLSubsystemHolder::InitLocalSubsystems() {
    SpawnSubsystem(ModContentRegistry, AModContentRegistry::StaticClass(), TEXT("ModContentRegistry"));
    ModContentRegistry->Init();
}

void USMLSubsystemHolder::RegisterSubsystemHolder() {
    USubsystemHolderRegistry::RegisterSubsystemHolder(TEXT("SML"), USMLSubsystemHolder::StaticClass());
}

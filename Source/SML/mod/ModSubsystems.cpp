#include "ModSubsystems.h"
#include "FGGameState.h"
#include "mod/hooking.h"
#include "util/FuncNames.h"

static TArray<UClass*> SubsystemHolders;

void FSubsystemInfoHolder::RegisterSubsystemHolder(TSubclassOf<UModSubsystemHolder> Class) {
	SubsystemHolders.Add(Class.Get());
}

void FSubsystemInfoHolder::SetupHooks() {
	SUBSCRIBE_METHOD_AFTER(FG_GAME_STATE_INIT_FUNC_DESC, AFGGameState::Init, [](AFGGameState* GameState) {
		InitializeSubsystems(GameState);
	});
}

void FSubsystemInfoHolder::InitializeSubsystems(AFGGameState* GameState) {
	if (GameState->Role == ENetRole::ROLE_Authority) {
		for (UClass* ComponentClass : SubsystemHolders) {
			check(ComponentClass->IsChildOf<UModSubsystemHolder>());
			UModSubsystemHolder* Component = NewObject<UModSubsystemHolder>(GameState, ComponentClass);
			Component->RegisterComponent();
			Component->SetIsReplicated(true);
			Component->InitSubsystems();
		}
	}
}

void UModSubsystemHolder::InitSubsystems() {
	K2_InitSubsystems();
}

void USMLSubsystemHolder::InitSubsystems() {
	SpawnSubsystem(ChatCommandSubsystem, AChatCommandSubsystem::StaticClass(), TEXT("ChatCommandSubsystem"));
	ChatCommandSubsystem->Init();
}





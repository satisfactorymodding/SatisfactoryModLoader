#include "ModSubsystems.h"
#include "FGGameState.h"
#include "mod/hooking.h"
#include "util/FuncNames.h"
#include "util/Logging.h"

static TArray<UClass*> SubsystemHolders;

void FSubsystemInfoHolder::RegisterSubsystemHolder(TSubclassOf<UModSubsystemHolder> Class) {
	SubsystemHolders.Add(Class.Get());
}

void FSubsystemInfoHolder::SetupHooks() {
	SUBSCRIBE_METHOD_AFTER(FG_GAME_STATE_INIT_FUNC_DESC, AFGGameState::Init, [](AFGGameState* GameState) {
		RegisterSubsystemHolder(USMLSubsystemHolder::StaticClass());
		InitializeSubsystems(GameState);
	});
}

void FSubsystemInfoHolder::InitializeSubsystems(AFGGameState* GameState) {
	if (GameState->Role == ENetRole::ROLE_Authority) {
		SML::Logging::info(TEXT("Initializing modded subsystems..."));
		for (UClass* ComponentClass : SubsystemHolders) {
			check(ComponentClass->IsChildOf<UModSubsystemHolder>());
			UModSubsystemHolder* Component = NewObject<UModSubsystemHolder>(GameState, ComponentClass);
			Component->RegisterComponent();
			Component->SetIsReplicated(true);
			Component->InitSubsystems();
		}
	}
}

AFGSubsystem* UModSubsystemHolder::K2_SpawnSubsystem(TSubclassOf<AFGSubsystem> SpawnClass, FName SpawnName) const {
	if (!IsValid(SpawnClass)) {
		UE_LOG(LogTemp, Error, TEXT("ModSubsystems::SpawnSubsystem failed for '%s', no class given."), *SpawnName.ToString());
		return nullptr;
	}
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Name = SpawnName;

	return GetWorld()->SpawnActor<AFGSubsystem>(SpawnClass, SpawnParams);
}

void UModSubsystemHolder::InitSubsystems() {
	K2_InitSubsystems();
}

void USMLSubsystemHolder::InitSubsystems() {
	SpawnSubsystem(ChatCommandSubsystem, AChatCommandSubsystem::StaticClass(), TEXT("ChatCommandSubsystem"));
	ChatCommandSubsystem->Init();
}
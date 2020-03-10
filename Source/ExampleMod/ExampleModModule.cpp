#include "ExampleModModule.h"
#include "ExampleActor.h"
#include "../SML/mod/hooking.h"
#include "FGGameMode.h"
#include <fstream>

void FExampleModModule::StartupModule() {
	SUBSCRIBE_METHOD("?InitGameState@AFGGameMode@@UEAAXXZ", AFGGameMode::InitGameState, [](CallScope<void, AFGGameMode>& scope, AFGGameMode* gameMode) {
		AExampleActor* actor = gameMode->GetWorld()->SpawnActor<AExampleActor>(FVector::ZeroVector, FRotator::ZeroRotator);
		actor->DoStuff();
		scope(gameMode);
	});
}

IMPLEMENT_GAME_MODULE(FExampleModModule, ExampleMod);

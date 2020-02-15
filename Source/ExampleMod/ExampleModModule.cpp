#include "ExampleModModule.h"
#include "ExampleActor.h"
#include "../SML/mod/hooking.h"
#include "FGGameMode.h"
#include <fstream>

void FExampleModModule::StartupModule() {
	SUBSCRIBE_METHOD(AFGGameMode::InitGameState, [](CallResult<void>&, AFGGameMode* gameMode) {
		AExampleActor* actor = gameMode->GetWorld()->SpawnActor<AExampleActor>(FVector::ZeroVector, FRotator::ZeroRotator);
		actor->DoStuff();
	});
}

IMPLEMENT_GAME_MODULE(FExampleModModule, ExampleMod);

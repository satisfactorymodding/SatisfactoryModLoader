#include "PlayerControllerHelper.h"
#include "FGPlayerController.h"
	
SML_API AFGCharacterPlayer* FPlayerControllerHelper::GetPlayerCharacter(const UPlayer* Player) {
    return static_cast<AFGCharacterPlayer*>(Player->GetPlayerController(nullptr)->GetCharacter());
}

TArray<AFGPlayerController*> FPlayerControllerHelper::GetConnectedPlayers(const UWorld* World) {
	TArray<AFGPlayerController*> Result;
	//iterate connected players
	for (FConstPlayerControllerIterator iterator = World->GetPlayerControllerIterator(); iterator; ++iterator) {
		APlayerController* controller = (*iterator).Get();
		if (controller == nullptr) continue;
		Result.Add(static_cast<AFGPlayerController*>(controller));
	}
	return Result;
   }

AFGPlayerController* FPlayerControllerHelper::GetPlayerByName(const UWorld* World, const FString& PlayerName) {
	TArray<AFGPlayerController*> ConnectedPlayers = GetConnectedPlayers(World);
    for (AFGPlayerController* Controller : ConnectedPlayers) {
    	if (Controller->PlayerState->GetPlayerName() == PlayerName) {
			return Controller;
    	}
    }
	return nullptr;
}
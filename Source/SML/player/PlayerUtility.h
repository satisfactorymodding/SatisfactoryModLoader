#pragma once

#include "FGCharacterPlayer.h"

namespace SML {
	void InitializePlayerComponent();
	
    SML_API AFGCharacterPlayer* GetPlayerCharacter(const UPlayer* Player);

	SML_API TArray<AFGPlayerController*> GetConnectedPlayers(const UWorld* World);

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* World, const FString& PlayerName);
}

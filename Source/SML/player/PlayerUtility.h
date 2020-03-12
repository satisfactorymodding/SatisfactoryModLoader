#pragma once

#include "FGCharacterPlayer.h"

namespace SML {
	void initializePlayerComponent();
	
    SML_API AFGCharacterPlayer* getPlayerCharacter(const UPlayer* player);

	SML_API TArray<AFGPlayerController*> getConnectedPlayers(const UWorld* world);

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* world, const FString& playerName);
}

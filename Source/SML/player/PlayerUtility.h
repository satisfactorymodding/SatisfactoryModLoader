#pragma once

#include "FGCharacterPlayer.h"
#include "SatisfactoryModLoader.h"


namespace SML {
    SML_API AFGCharacterPlayer* getPlayerCharacter(const UPlayer* player);

	SML_API std::vector<AFGPlayerController*> getConnectedPlayers(const UWorld* world);

	SML_API AFGPlayerController* GetPlayerByName(const UWorld* world, const FString& playerName);
}

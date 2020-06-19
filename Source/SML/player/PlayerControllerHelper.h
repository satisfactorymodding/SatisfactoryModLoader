#pragma once
#include "FGCharacterPlayer.h"

class FPlayerControllerHelper {
public:
    /**
     * Retrieves AFGCharacterPlayer from given UPlayer object
     */
    static SML_API AFGCharacterPlayer* GetPlayerCharacter(const UPlayer* Player);

    /**
     * Retrieves controllers of all connected players in the given world
     */
    static SML_API TArray<AFGPlayerController*> GetConnectedPlayers(const UWorld* World);

    /**
     * Searches player controller with given name in the world, returns null if not found
     */
    static SML_API AFGPlayerController* GetPlayerByName(const UWorld* World, const FString& PlayerName);
};

#pragma once
#include "CoreMinimal.h"

/** Handles enabling cheats for players joining when enableCheatConsoleCommands SML config option is enabled */
class FPlayerCheatManagerHandler {
public:
    /** Registers cheat manager handler in game mode callbacks */
    static void RegisterHandler();
};

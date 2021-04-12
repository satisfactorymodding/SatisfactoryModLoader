#include "Player/PlayerCheatManagerHandler.h"
#include "FGPlayerController.h"
#include "SatisfactoryModLoader.h"
#include "SMLConfiguration.h"
#include "GameFramework/GameModeBase.h"

void FPlayerCheatManagerHandler::HandlePlayerJoined(class AGameModeBase* /*GameMode*/, APlayerController* PlayerController) {
    const FSMLConfiguration Configuration = FSatisfactoryModLoader::GetSMLConfiguration();
    if (Configuration.bEnableCheatConsoleCommands) {
        PlayerController->AddCheats(true);
    }
}

void FPlayerCheatManagerHandler::RegisterHandler() {
    FGameModeEvents::GameModePostLoginEvent.AddStatic(HandlePlayerJoined);
}

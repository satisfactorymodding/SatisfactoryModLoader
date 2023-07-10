#include "Player/PlayerCheatManagerHandler.h"
#include "GameFramework/PlayerController.h"
#include "Patching/NativeHookManager.h"
#include "SatisfactoryModLoader.h"

static TAutoConsoleVariable CVarForceAllowCheats(
    TEXT("SML.ForceAllowCheats"),
    false,
    TEXT("Allows EnableCheats to be used to activate Cheat Manager regardless of the Game Mode settings. This is on by default in non-Shipping builds."),
    ECVF_Default);

void FPlayerCheatManagerHandler::RegisterHandler() {
    SUBSCRIBE_UOBJECT_METHOD(APlayerController, EnableCheats, [](auto& Scope, APlayerController* PlayerController) {
        if (CVarForceAllowCheats.GetValueOnGameThread()) {
            PlayerController->AddCheats(true);
            UE_LOG(LogSatisfactoryModLoader, Warning, TEXT("Cheats enabled via EnableCheats console command"));
        }
        else {
            UE_LOG(LogSatisfactoryModLoader, Error, TEXT("Failed to enable cheats. Are you sure the Session Setting is enabled and that you are multiplayer host?"));
        }
        Scope.Cancel();
    });
}

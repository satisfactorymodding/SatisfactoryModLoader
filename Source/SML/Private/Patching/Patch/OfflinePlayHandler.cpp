#include "Patching/Patch/OfflinePlayerHandler.h"
#include "FGLocalPlayer.h"
#include "NativeHookManager.h"
#include "OnlineEngineInterface.h"

void FOfflinePlayerHandler::RegisterHandler() {
    SUBSCRIBE_METHOD(ULocalPlayer::GetNickname, [](auto& Call, const ULocalPlayer* Player) {
        const FString ReturnedParentValue = Call(Player);
        if (ReturnedParentValue.IsEmpty()) {
             const FString UsernameOverride = FOfflinePlayerHandler::GetOfflineUsernameOverride();
             Call.Override(UsernameOverride);
        }
    });
    SUBSCRIBE_METHOD(ULocalPlayer::GetUniqueNetIdFromCachedControllerId, [](auto& Call, const ULocalPlayer* Player) {
        const FUniqueNetIdRepl ReturnedParentValue = Call(Player);
        if (!ReturnedParentValue.IsValid()) {
            const FString Username = Player->GetNickname();
            Call.Override(FOfflinePlayerHandler::GenerateUniqueNetIdFromUsername(Username));
        }
    });
}

FString FOfflinePlayerHandler::GetOfflineUsernameOverride() {
    FString UsernameOverride = TEXT("");
    FParse::Value(FCommandLine::Get(), TEXT("-Username="), UsernameOverride);
    return UsernameOverride;
}

FUniqueNetIdRepl FOfflinePlayerHandler::GenerateUniqueNetIdFromUsername(const FString& Username) {
    return FUniqueNetIdRepl(UOnlineEngineInterface::Get()->CreateUniquePlayerId(Username));
}




 
#include "FGLocalPlayer.h"
#include "OnlineEngineInterface.h"
#include "mod/hooking.h"
#include "util/Logging.h"


extern void GRegisterOfflinePlayHandler() {
    FString UsernameOverride = TEXT("");
    FParse::Value(FCommandLine::Get(), TEXT("-Username="), UsernameOverride);

    if (!UsernameOverride.IsEmpty()) {
        SML::Logging::info(TEXT("Offline Username Override: "), *UsernameOverride);
        SUBSCRIBE_METHOD(ULocalPlayer::GetNickname, [=](auto& Call, ULocalPlayer* Player) {
            FString ReturnedParentValue = Call(Player);
            if (ReturnedParentValue.IsEmpty()) {
                SML::Logging::info(TEXT("Online Subsystem Nickname not provided, falling back to -Username"));
                Call.Override(UsernameOverride);
            }
            SML::Logging::info(TEXT("Parent GetNickname: "), *ReturnedParentValue);
        });

        SUBSCRIBE_METHOD(ULocalPlayer::GetUniqueNetIdFromCachedControllerId, [=](auto& Call, ULocalPlayer* Player) {
            FUniqueNetIdRepl ReturnedParentValue = Call(Player);
            if (!ReturnedParentValue.IsValid()) {
                SML::Logging::info(TEXT("Online Subsystem UniqueNotId not provided, falling back to -Username-generated UniqueId"));
                const TSharedPtr<const FUniqueNetId> UniqueNetIdPtr = UOnlineEngineInterface::Get()->CreateUniquePlayerId(UsernameOverride);
                Call.Override(FUniqueNetIdRepl(UniqueNetIdPtr));
            }
        });
    }
}
 
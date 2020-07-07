#include "FGLocalPlayer.h"
#include "OnlineEngineInterface.h"
#include "mod/hooking.h"
#include "util/Logging.h"

class IFuckingHateConstMethods {
public:
    FString* ShittyMethod(FString* OutReturnValue) { return nullptr; }
    FUniqueNetIdRepl* ShittyMethod2(FUniqueNetIdRepl* OutUniqueNetIdRepl) { return nullptr; }
};

extern void GRegisterOfflinePlayHandler() {
    FString UsernameOverride = TEXT("");
    FParse::Value(FCommandLine::Get(), TEXT("-Username="), UsernameOverride);
    if (!UsernameOverride.IsEmpty()) {
        SML::Logging::info(TEXT("Offline Username Override: "), *UsernameOverride);
        SUBSCRIBE_METHOD_MANUAL("ULocalPlayer::GetNickname", IFuckingHateConstMethods::ShittyMethod, [=](auto& Call, auto* Player, FString* OutReturnValue) {
            FString* ReturnedParentValue = Call(Player, OutReturnValue);
            if (ReturnedParentValue->IsEmpty()) {
                SML::Logging::info(TEXT("Online Subsystem Nickname not provided, falling back to -Username"));
                *OutReturnValue = UsernameOverride;
                Call.Override(OutReturnValue);
            }
            SML::Logging::info(TEXT("Parent GetNickname: "), **ReturnedParentValue);
        });
        SUBSCRIBE_METHOD_MANUAL("ULocalPlayer::GetUniqueNetIdFromCachedControllerId", IFuckingHateConstMethods::ShittyMethod2, [=](auto& Call, auto* Player, FUniqueNetIdRepl* OutReturnValue) {
            FUniqueNetIdRepl* ReturnedParentValue = Call(Player, OutReturnValue);
            if (!ReturnedParentValue->IsValid()) {
                SML::Logging::info(TEXT("Online Subsystem UniqueNotId not provided, falling back to -Username-generated UniqueId"));
                const TSharedPtr<const FUniqueNetId> UniqueNetIdPtr = UOnlineEngineInterface::Get()->CreateUniquePlayerId(UsernameOverride);
                *OutReturnValue = FUniqueNetIdRepl(UniqueNetIdPtr);
                Call.Override(OutReturnValue);
            }
        });
    }
}
 
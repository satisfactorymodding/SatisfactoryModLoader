#include "Player/PlayerCommandSender.h"
#include "FGPlayerController.h"
#include "Player/SMLRemoteCallObject.h"

FString UPlayerCommandSender::GetSenderName() const {
    AFGPlayerController* PlayerController = GetPlayer();
    if (PlayerController != NULL) {
        APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>();
        if (PlayerState != NULL) {
            return PlayerState->GetPlayerName();
        }
    }
    return TEXT("[unknown]");
}

void UPlayerCommandSender::SendChatMessage(const FString& Message, const FLinearColor PrefixColor) {
    AFGPlayerController* PlayerController = GetPlayer();
    if (PlayerController != NULL) {
        USMLRemoteCallObject* RemoteCallObject = Cast<USMLRemoteCallObject>(PlayerController->GetRemoteCallObjectOfClass(USMLRemoteCallObject::StaticClass()));
        if (RemoteCallObject != NULL) {
            RemoteCallObject->SendChatMessage(Message, PrefixColor);
        }
    }
}

bool UPlayerCommandSender::IsPlayerSender() const {
    return true;
}

AFGPlayerController* UPlayerCommandSender::GetPlayer() const {
    return GetTypedOuter<AFGPlayerController>();
}

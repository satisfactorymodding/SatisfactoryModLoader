#include "Command/CommandSender.h"

AFGPlayerController* UCommandSender::GetPlayer() const {
    checkf(false, TEXT("GetPlayer not implemented by CommandSource %s"));
    return nullptr;
}

FString UCommandSender::GetSenderName() const {
    return TEXT("Unspecified");
}

bool UCommandSender::IsPlayerSender() const {
    return false;
}

void UCommandSender::SendChatMessage(const FString& Message, const FLinearColor PrefixColor) {
}

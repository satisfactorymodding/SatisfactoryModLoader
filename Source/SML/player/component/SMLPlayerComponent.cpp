#include "SMLPlayerComponent.h"
#include "command/ChatCommandAPI.h"

void USMLPlayerComponent::HandleChatCommand_Implementation(const FString& commandLine) {
	SML::ChatCommand::runChatCommand(commandLine, static_cast<AFGPlayerController*>(GetOwner()));
}

void USMLPlayerComponent::SendChatMessage_Implementation(const FString& message, const FLinearColor& color) {
	AFGChatManager* chatManager = AFGChatManager::Get(GetWorld());
	FChatMessageStruct messageStruct;
	messageStruct.MessageString = message;
	messageStruct.MessageType = EFGChatMessageType::CMT_SystemMessage;
	messageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
	messageStruct.CachedColor = color;
	chatManager->AddChatMessageToReceived(messageStruct);
}

bool USMLPlayerComponent::HandleChatCommand_Validate(const FString& commandLine) {
	return true;
}

USMLPlayerComponent* USMLPlayerComponent::Get(APlayerController* player) {
	return player->FindComponentByClass<USMLPlayerComponent>();
}


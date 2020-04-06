#include "SMLPlayerComponent.h"
#include "command/ChatCommandLibrary.h"

bool UPlayerCommandSender::IsPlayerSender() const {
	return true;
}

void UPlayerCommandSender::SendChatMessage(const FString& Message, const FLinearColor PrefixColor) {
	USMLPlayerComponent* PlayerComponent = GetTypedOuter<USMLPlayerComponent>();
	check(PlayerComponent);
	PlayerComponent->SendChatMessage(Message, PrefixColor);
}

FString UPlayerCommandSender::GetSenderName() const {
	return GetPlayer()->PlayerState->GetPlayerName();
}

AFGPlayerController* UPlayerCommandSender::GetPlayer() const {
	AFGPlayerController* Controller = GetTypedOuter<AFGPlayerController>();
	check(Controller);
	return Controller;
}

USMLPlayerComponent::USMLPlayerComponent() {
	CommandSender = CreateDefaultSubobject<UPlayerCommandSender>(TEXT("CommandSender"));
}

void USMLPlayerComponent::HandleChatCommand_Implementation(const FString& CommandLine) {
	AChatCommandSubsystem* ChatSystem = AChatCommandSubsystem::Get(this);
	check(ChatSystem);
	ChatSystem->RunChatCommand(CommandLine, CommandSender);
}

void USMLPlayerComponent::SendChatMessage_Implementation(const FString& Message, const FLinearColor& Color) {
	AFGChatManager* ChatManager = AFGChatManager::Get(GetWorld());
	FChatMessageStruct MessageStruct;
	MessageStruct.MessageString = Message;
	MessageStruct.MessageType = EFGChatMessageType::CMT_SystemMessage;
	MessageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
	MessageStruct.CachedColor = Color;
	ChatManager->AddChatMessageToReceived(MessageStruct);
}

bool USMLPlayerComponent::HandleChatCommand_Validate(const FString& CommandLine) {
	return true;
}

USMLPlayerComponent* USMLPlayerComponent::Get(APlayerController* Player) {
	return Player->FindComponentByClass<USMLPlayerComponent>();
}


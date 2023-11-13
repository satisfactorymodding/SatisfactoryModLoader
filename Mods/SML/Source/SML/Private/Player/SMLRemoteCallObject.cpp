#include "Player/SMLRemoteCallObject.h"
#include "Command/ChatCommandLibrary.h"
#include "FGChatManager.h"
#include "FGPlayerController.h"
#include "SatisfactoryModLoader.h"
#include "Net/UnrealNetwork.h"

USMLRemoteCallObject::USMLRemoteCallObject() {
	CommandSender = CreateDefaultSubobject<UPlayerCommandSender>(TEXT("PlayerCommandSender"));
}

bool USMLRemoteCallObject::IsClientModInstalled(const FString& ModId) const {
	return ClientInstalledMods.Contains(ModId);
}

FVersion USMLRemoteCallObject::GetClientModVersion(const FString& ModId) const {
	const FVersion* Result = ClientInstalledMods.Find(ModId);
	return Result ? *Result : FVersion{};
}

void USMLRemoteCallObject::HandleChatCommand_Implementation(const FString& CommandLine) {
	AChatCommandSubsystem* ChatSystem = AChatCommandSubsystem::Get(this);
	check(ChatSystem);
	ChatSystem->RunChatCommand(CommandLine, CommandSender);
}

void USMLRemoteCallObject::SendChatMessage_Implementation(const FString& Message, const FLinearColor& Color) {
	AFGChatManager* ChatManager = AFGChatManager::Get(GetWorld());
	FChatMessageStruct MessageStruct;
	MessageStruct.MessageString = Message;
	MessageStruct.MessageType = EFGChatMessageType::CMT_SystemMessage;
	MessageStruct.ServerTimeStamp = GetWorld()->TimeSeconds;
	MessageStruct.CachedColor = Color;
	ChatManager->AddChatMessageToReceived(MessageStruct);
}

bool USMLRemoteCallObject::HandleChatCommand_Validate(const FString& CommandLine) {
	return true;
}

void USMLRemoteCallObject::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const {
	DOREPLIFETIME(USMLRemoteCallObject, DummyReplicatedField);
}

void USMLRemoteCallObject::RegisterChatCommandPatch() {
	
	AFGPlayerController::PlayerControllerBegunPlay.AddLambda( []( AFGPlayerController* PlayerController )
	{
		PlayerController->ChatMessageEntered.AddLambda( [=]( const FChatMessageStruct& ChatMessage, bool& bCancelChatMessage )
		{
			if (ChatMessage.MessageString.StartsWith(TEXT("/")))
			{
				const FString CommandLine = ChatMessage.MessageString.TrimStartAndEnd().RightChop(1);
				if ( USMLRemoteCallObject* RemoteCallObject = PlayerController->GetRemoteCallObjectOfClass<USMLRemoteCallObject>() )
				{
				   RemoteCallObject->HandleChatCommand(CommandLine);
				   bCancelChatMessage = true;
				}
			}
		} );
	} );
}

#include "HelpCommandInstance.h"
#include "ChatCommandLibrary.h"
#include "CommandSender.h"

AHelpCommandInstance::AHelpCommandInstance() {
	CommandName = TEXT("help");
	Usage = TEXT("/help - Command help");
	Aliases.Add(TEXT("?"));
}

EExecutionStatus AHelpCommandInstance::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) {
	AChatCommandSubsystem* CommandSubsystem = AChatCommandSubsystem::Get(this);
	check(CommandSubsystem);
	if (Arguments.Num() >= 2) {
		const FString& CommandName = Arguments[1];
		AChatCommandInstance* CommandEntry = CommandSubsystem->FindCommandByName(CommandName);
		if (!CommandEntry) {
			Sender->SendChatMessage(FString(TEXT("Command not found: ")) += CommandName, FLinearColor::Red);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		Sender->SendChatMessage(CommandEntry->Usage);
		return EExecutionStatus::COMPLETED;
	}
	Sender->SendChatMessage(TEXT("Command List:"));
	for (const AChatCommandInstance* CommandEntry : CommandSubsystem->GetRegisteredCommands()) {
		Sender->SendChatMessage(CommandEntry->Usage);
	}
	return EExecutionStatus::COMPLETED;
}
#include "SMLChatCommands.h"
#include "ChatCommandLibrary.h"
#include "SatisfactoryModLoader.h"
#include "player/PlayerControllerHelper.h"
#include "AkComponent.h"

AHelpCommandInstance::AHelpCommandInstance() {
	ModId = TEXT("SML");
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

AInfoCommandInstance::AInfoCommandInstance() {
	ModId = TEXT("SML");
	CommandName = TEXT("info");
	Usage = TEXT("/info - Information about environment");
	Aliases.Add(TEXT("version"));
}

EExecutionStatus AInfoCommandInstance::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) {
	Sender->SendChatMessage(FString::Printf(TEXT("Running SML v.%s"), *SML::GetModLoaderVersion().String()));
	Sender->SendChatMessage(FString::Printf(TEXT("Powered by Bootstrapper v.%s"), *SML::GetBootstrapperVersion().String()));
	FModHandler& ModHandler = SML::GetModHandler();
	auto LoadedModsVector = ModHandler.GetLoadedMods();
	TArray<FString> LoadedMods;
	for (const FString& LoadedModId : LoadedModsVector) {
		const FModContainer& ModContainer = ModHandler.GetLoadedMod(LoadedModId);
		LoadedMods.Add(ModContainer.ModInfo.Name);
	}
	Sender->SendChatMessage(FString::Printf(TEXT("Loaded Mods: %s"), *FString::Join(LoadedMods, TEXT(", "))));
	return EExecutionStatus::COMPLETED;
}

APlayerListCommandInstance::APlayerListCommandInstance() {
	ModId = TEXT("SML");
	CommandName = TEXT("list");
	Usage = TEXT("/list - List players online");
	Aliases.Add(TEXT("players"));
}

EExecutionStatus APlayerListCommandInstance::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) {
	TArray<FString> PlayersList;
	for (AFGPlayerController* Controller : FPlayerControllerHelper::GetConnectedPlayers(GetWorld())) {
		PlayersList.Add(Controller->PlayerState->GetPlayerName());
	}
	Sender->SendChatMessage(FString(TEXT("Players Online: ")) += FString::Join(PlayersList, TEXT(", ")));
	return EExecutionStatus::COMPLETED;
}
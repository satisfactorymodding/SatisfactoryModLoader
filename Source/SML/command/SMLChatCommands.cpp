#include "SMLChatCommands.h"
#include "ChatCommandAPI.h"
#include "player/component/SMLPlayerComponent.h"
#include "SatisfactoryModLoader.h"
#include "player/PlayerUtility.h"
#include "util/Logging.h"
using namespace SML::ChatCommand;

#define REGISTER_COMMAND(name, usage, aliases, handler, ...) registerCommand(FCommandRegistrarEntry{TEXT("SML"), TEXT(name), TArray<FString>(aliases), TEXT(usage), new CommandHandler(handler) });

void SML::ChatCommand::registerSMLChatCommands() {
	REGISTER_COMMAND("help", "/help - Command help", {TEXT("?")}, [](const FCommandData& data) {
		USMLPlayerComponent* component = USMLPlayerComponent::Get(data.player);
		if (data.argv.Num() >= 2) {
			const FString& commandName = data.argv[1];
			const TOptional<FCommandRegistrarEntry>& commandEntry = getCommandByName(commandName);
			if (!commandEntry.IsSet()) {
				component->SendChatMessage(FString(TEXT("Command not found: ")) += commandName, FLinearColor::Red);
				return EExecutionStatus::BAD_ARGUMENTS;
			}
			component->SendChatMessage(commandEntry.GetValue().usage);
			return EExecutionStatus::COMPLETED;
		}
		component->SendChatMessage(TEXT("Command List:"));
		for (const FCommandRegistrarEntry& commandEntry : getRegisteredCommands()) {
			component->SendChatMessage(commandEntry.usage);
		}
		return EExecutionStatus::COMPLETED;
	});
	
	REGISTER_COMMAND("info", "/info - Information about environment", {TEXT("version")}, [](const FCommandData& data) {
		USMLPlayerComponent* component = USMLPlayerComponent::Get(data.player);
		component->SendChatMessage(FString::Printf(TEXT("Running SML v.%s"), *SML::getModLoaderVersion().string()));
		component->SendChatMessage(FString::Printf(TEXT("Powered by Bootstrapper v.%s"), *SML::getBootstrapperVersion().string()));
		Mod::FModHandler& modHandler = SML::getModHandler();
		auto loadedModsVector = modHandler.getLoadedMods();
		TArray<FString> loadedMods;
		for (const FString& loadedModId : loadedModsVector) {
			const Mod::FModContainer& modContainer = modHandler.getLoadedMod(loadedModId);
			loadedMods.Add(modContainer.modInfo.name);
		}
		component->SendChatMessage(FString::Printf(TEXT("Loaded Mods: %s"), *FString::Join(loadedMods, TEXT(", "))));
		return EExecutionStatus::COMPLETED;
	});
	
	REGISTER_COMMAND("list", "/list - List players online", {TEXT("players")}, [](const FCommandData& data) {
		USMLPlayerComponent* component = USMLPlayerComponent::Get(data.player);
		TArray<FString> playersList;
		UWorld* world = data.player->GetWorld();
		for (AFGPlayerController* controller : getConnectedPlayers(world)) {
			playersList.Add(controller->PlayerState->GetPlayerName());
		}
		component->SendChatMessage(FString(TEXT("Players Online: ")) += FString::Join(playersList, TEXT(", ")));
		return EExecutionStatus::COMPLETED;
	});
}

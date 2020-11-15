 #include "InfoCommandInstance.h"
#include "CommandSender.h"
#include "ModHandler.h"
#include "SatisfactoryModLoader.h"

AInfoCommandInstance::AInfoCommandInstance() {
	CommandName = TEXT("info");
	Usage = TEXT("/info - Information about environment");
	Aliases.Add(TEXT("version"));
}

EExecutionStatus AInfoCommandInstance::ExecuteCommand_Implementation(UCommandSender* Sender, const TArray<FString>& Arguments, const FString& Label) {
	const FVersion Version = FSatisfactoryModLoader::GetModLoaderVersion();
	Sender->SendChatMessage(FString::Printf(TEXT("Running SML v.%s"), *Version.ToString()));
	FModHandler* ModHandler = FSatisfactoryModLoader::GetModHandler();
	if (ModHandler != NULL) {
		TArray<FString> LoadedMods;
		for (const FModContainer* ModContainer : ModHandler->GetLoadedMods()) {
			LoadedMods.Add(ModContainer->ModInfo.Name);
		}
		Sender->SendChatMessage(FString::Printf(TEXT("Loaded Mods: %s"), *FString::Join(LoadedMods, TEXT(", "))));
	}
	return EExecutionStatus::COMPLETED;
}
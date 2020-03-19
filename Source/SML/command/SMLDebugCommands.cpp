#include "SMLDebugCommands.h"
#include "ChatCommandAPI.h"
#include "player/component/SMLPlayerComponent.h"
#include "SatisfactoryModLoader.h"
#include "util/Logging.h"
#include "FGResearchManager.h"
#include "FGResearchTree.h"
#include "AvailabilityDependencies/FGAvailabilityDependency.h"
using namespace SML::ChatCommand;

#define REGISTER_COMMAND(name, usage, aliases, handler) registerCommand(FCommandRegistrarEntry{TEXT("SML"), TEXT(name), TArray<FString>(aliases), TEXT(usage), new CommandHandler(handler) });

void SML::ChatCommand::registerSMLDebugCommands() {
	REGISTER_COMMAND("research_load", "/research_load <PathName> - load research tree", {}, [](const FCommandData& Data) {
		USMLPlayerComponent* Component = USMLPlayerComponent::Get(Data.player);
		if (!(Data.argv.Num() >= 2)) {
			SML::ChatCommand::PrintCommandUsage(Data);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		const FString& ResearchTreePath = Data.argv[1];
		UClass* ResearchTreeClass = LoadClass<UFGResearchTree>(nullptr, *ResearchTreePath);
		if (ResearchTreeClass == nullptr) {
			Component->SendChatMessage(FString::Printf(TEXT("Couldn't find reseach tree at %s"), *ResearchTreePath), FLinearColor::Red);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		AFGResearchManager* ResearchManager = AFGResearchManager::Get(Data.player->GetWorld());
		if (ResearchManager->mAllResearchTrees.Contains(ResearchTreeClass)) {
			Component->SendChatMessage(TEXT("Research Tree with that name is already loaded"), FLinearColor::Red);
			return EExecutionStatus::UNCOMPLETED;
		}
		ResearchManager->mAllResearchTrees.Add(ResearchTreeClass);
		Component->SendChatMessage(TEXT("Added Research Tree Successfully!"));
		return EExecutionStatus::COMPLETED;
	});

	REGISTER_COMMAND("research_test", "/research_test <PathName> - test research tree unlock dependencies", {}, [](const FCommandData& Data) {
		USMLPlayerComponent* Component = USMLPlayerComponent::Get(Data.player);
		if (!(Data.argv.Num() >= 2)) {
			SML::ChatCommand::PrintCommandUsage(Data);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		const FString& ResearchTreePath = Data.argv[1];
		UClass* ResearchTreeClass = LoadClass<UFGResearchTree>(nullptr, *ResearchTreePath);
		if (ResearchTreeClass == nullptr) {
			Component->SendChatMessage(FString::Printf(TEXT("Couldn't find reseach tree at %s"), *ResearchTreePath), FLinearColor::Red);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		TArray<UFGAvailabilityDependency*> UnlockDeps = UFGResearchTree::GetUnlockDependencies(ResearchTreeClass);
		Component->SendChatMessage(TEXT("Unlock Deps: "));
		for (UFGAvailabilityDependency* Dep : UnlockDeps) {
			const bool DependencyMet = Dep->AreDependenciesMet(Data.player);
			Component->SendChatMessage(FString::Printf(TEXT("%s - %d"), *Dep->GetPathName(), DependencyMet));
		}
		AFGResearchManager* ResearchManager = AFGResearchManager::Get(Data.player->GetWorld());
		const bool TreeUnlocked = ResearchManager->IsResesearchTreeUnlocked(ResearchTreeClass);
		Component->SendChatMessage(FString::Printf(TEXT("Research Tree Unlocked? %d"), TreeUnlocked));
		Component->SendChatMessage(TEXT("UpdateUnlockedResearchTrees()"));
		ResearchManager->UpdateUnlockedResearchTrees();
		const bool TreeUnlockedNow = ResearchManager->IsResesearchTreeUnlocked(ResearchTreeClass);
		Component->SendChatMessage(FString::Printf(TEXT("Research Tree Unlocked Now? %d"), TreeUnlockedNow));
		return EExecutionStatus::COMPLETED;
	});

	REGISTER_COMMAND("research_unlock", "/research_unlock <PathName> - unlock research tree", {}, [](const FCommandData& Data) {
		USMLPlayerComponent* Component = USMLPlayerComponent::Get(Data.player);
		if (!(Data.argv.Num() >= 2)) {
			SML::ChatCommand::PrintCommandUsage(Data);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		const FString& ResearchTreePath = Data.argv[1];
		UClass* ResearchTreeClass = LoadClass<UFGResearchTree>(nullptr, *ResearchTreePath);
		if (ResearchTreeClass == nullptr) {
			Component->SendChatMessage(FString::Printf(TEXT("Couldn't find reseach tree at %s"), *ResearchTreePath), FLinearColor::Red);
			return EExecutionStatus::BAD_ARGUMENTS;
		}
		AFGResearchManager* ResearchManager = AFGResearchManager::Get(Data.player->GetWorld());
		ResearchManager->UnlockResearchTree(ResearchTreeClass);
		return EExecutionStatus::COMPLETED;
	});
}
#include "SMLInitMod.h"
#include "ChatCommandLibrary.h"
#include "FGSchematicManager.h"
#include "FGResourceSinkSettings.h"
#include "SubsystemHolderRegistry.h"
#include "GameFramework/GameModeBase.h"
#include "registry/ModContentRegistry.h"
#include "tooltip/ItemTooltipSubsystem.h"

void ASMLInitMod::InitDefaultContent() {
	UFunction* OverridenFunction = FindFunctionChecked(TEXT("PlayerJoined"));
	UFunction* SourceFunction = ASMLInitMod::StaticClass()->FindFunctionByName(TEXT("PlayerJoined"));
	//Only subscribe to delegate if we are overriding PlayerJoined in blueprint (e.g UFunction objects from base class and current class are different)
	if (OverridenFunction != SourceFunction) {
		FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &ASMLInitMod::PostPlayerLogin);	
	}

	AModContentRegistry* ModContentRegistry = AModContentRegistry::Get(this);

	for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
		ModContentRegistry->RegisterSchematic(*ModReference, Schematic);
	}

	for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
		ModContentRegistry->RegisterResearchTree(*ModReference, ResearchTree);
	}

	UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable.LoadSynchronous();
	if (ModResourceSinkPointsTable != NULL) {
		ModContentRegistry->RegisterResourceSinkItemPointTable(*ModReference, ModResourceSinkPointsTable);
	}

	AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(this);
	if (ChatCommandSubsystem != NULL) {
		for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands) {
			ChatCommandSubsystem->RegisterCommand(*ModReference, ChatCommand);
		}
	}
}

void ASMLInitMod::PostPlayerLogin(AGameModeBase*, APlayerController* PlayerController) {
	AFGPlayerController* Controller = Cast<AFGPlayerController>(PlayerController);
	if (Controller != NULL) {
		PlayerJoined(Controller);
	}
}

void ASMLInitMod::RegisterEarlyLoadContent(const FString& ModReference, UGameInstance* GameInstance) const {
	USubsystemHolderRegistry* SubsystemHolderRegistry = GameInstance->GetSubsystem<USubsystemHolderRegistry>();
	UItemTooltipSubsystem* TooltipSubsystem = GameInstance->GetSubsystem<UItemTooltipSubsystem>();
	
	for (UClass* ModSubsystemHolderClass : mModSubsystems) {
		SubsystemHolderRegistry->RegisterSubsystemHolder(ModReference, ModSubsystemHolderClass);
	}
	for (UClass* GlobalTooltipProviderClass : GlobalItemTooltipProviders) {
		TooltipSubsystem->RegisterGlobalTooltipProvider(ModReference, GlobalTooltipProviderClass->GetDefaultObject());
	}
}

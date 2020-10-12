#include "SMLInitMod.h"
#include "FGSchematicManager.h"
#include "SML/util/Logging.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "registry/ModContentRegistry.h"
#include "tooltip/ItemTooltipHandler.h"

void ASMLInitMod::InitDefaultContent() {
	FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &ASMLInitMod::PostPlayerLogin);
	
	AModContentRegistry* ModContentRegistry = AModContentRegistry::Get(this);

	for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics_DEPRECATED) {
		ModContentRegistry->RegisterSchematic(GetOwnerModReference(), Schematic);
	}

	for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees_DEPRECATED) {
		ModContentRegistry->RegisterResearchTree(GetOwnerModReference(), ResearchTree);
	}

	UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable_DEPRECATED.LoadSynchronous();
	if (ModResourceSinkPointsTable != NULL) {
		ModContentRegistry->RegisterResourceSinkItemPointTable(GetOwnerModReference(), ModResourceSinkPointsTable);
	}

	AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(this);
	if (ChatCommandSubsystem != NULL) {
		for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands_DEPRECATED) {
			ChatCommandSubsystem->RegisterCommand(GetOwnerModReference(), ChatCommand);
		}
	}
}

void ASMLInitMod::PostPlayerLogin(AGameModeBase*, APlayerController* PlayerController) {
	AFGPlayerController* Controller = Cast<AFGPlayerController>(PlayerController);
	if (Controller != NULL) {
		PlayerJoined(Controller);
	}
}

void ASMLInitMod::RegisterEarlyLoadContent(const FString& ModReference) const {
	for (UClass* ModSubsystemHolderClass : mModSubsystems_DEPRECATED) {
		FSubsystemInfoHolder::RegisterSubsystemHolder(ModReference, ModSubsystemHolderClass);
	}
	for (UClass* GlobalTooltipProviderClass : GlobalItemTooltipProviders_DEPRECATED) {
		UItemTooltipHandler::RegisterGlobalTooltipProvider(ModReference, GlobalTooltipProviderClass->GetDefaultObject());
	}
}

void ASMLInitMod::DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) {
	switch (LifecyclePhase) {
		case ELifecyclePhase::INITIALIZATION: {
			PreInit();
			Init();
			break;
		}
		case ELifecyclePhase::POST_INITIALIZATION: {
			InitDefaultContent();
			PostInit();
			break;
		}
		default: break;
	}
}

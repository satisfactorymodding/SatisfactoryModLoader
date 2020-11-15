#include "SMLInitMod.h"

#include "ChatCommandLibrary.h"
#include "FGSchematicManager.h"
#include "FGResourceSinkSettings.h"
#include "SubsystemHolderRegistry.h"
#include "GameFramework/GameModeBase.h"
#include "registry/ModContentRegistry.h"
#include "tooltip/ItemTooltipHandler.h"

void ASMLInitMod::InitDefaultContent() {
	UFunction* OverridenFunction = FindFunctionChecked(TEXT("PlayerJoined"));
	UFunction* SourceFunction = ASMLInitMod::StaticClass()->FindFunctionByName(TEXT("PlayerJoined"));
	//Only subscribe to delegate if we are overriding PlayerJoined in blueprint (e.g UFunction objects from base class and current class are different)
	if (OverridenFunction != SourceFunction) {
		FGameModeEvents::GameModePostLoginEvent.AddUObject(this, &ASMLInitMod::PostPlayerLogin);	
	}

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
		USubsystemHolderRegistry::RegisterSubsystemHolder(ModReference, ModSubsystemHolderClass);
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

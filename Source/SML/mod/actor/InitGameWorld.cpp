#include "InitGameWorld.h"
#include "FGSchematicManager.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "mod/ModHandler.h"
#include "registry/ModContentRegistry.h"

void AInitGameWorld::InitDefaultContent() {
	AModContentRegistry* ModContentRegistry = AModContentRegistry::Get(this);

	for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
		ModContentRegistry->RegisterSchematic(GetOwnerModReference(), Schematic);
	}

	for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
		ModContentRegistry->RegisterResearchTree(GetOwnerModReference(), ResearchTree);
	}

	UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable.LoadSynchronous();
	if (ModResourceSinkPointsTable != NULL) {
		ModContentRegistry->RegisterResourceSinkItemPointTable(GetOwnerModReference(), ModResourceSinkPointsTable);
	}

	AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(this);
	if (ChatCommandSubsystem != NULL) {
		for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands) {
			ChatCommandSubsystem->RegisterCommand(GetOwnerModReference(), ChatCommand);
		}
	}
}

void AInitGameWorld::InitNative() {
}

void AInitGameWorld::PostInitNative() {
}

void AInitGameWorld::DispatchLifecyclePhase(ELifecyclePhase LifecyclePhase) {
	switch (LifecyclePhase) {
		case ELifecyclePhase::INITIALIZATION: {
			InitDefaultContent();
			InitNative();
			Init();
			break;		
		}
		case ELifecyclePhase::POST_INITIALIZATION: {
			PostInitNative();
			PostInit();
			break;		
		}
		default: break;
	}
}

#include "Module/GameWorldModule.h"
#include "Command/ChatCommandLibrary.h"
#include "Registry/ModContentRegistry.h"
#include "Registry/ContentTagRegistry.h"
#include "Subsystem/SubsystemActorManager.h"

#if WITH_EDITOR
EDataValidationResult UGameWorldModule::IsDataValid(TArray<FText>& ValidationErrors) {
	EDataValidationResult ValidationResult = Super::IsDataValid(ValidationErrors);

	//Check that we do not have any null schematics, or research trees
	for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
		if (Schematic == nullptr) {
			ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "Validation_NullSchematic", "Null Schematic found. Was the content it previously referenced deleted or moved?"));
			ValidationResult = EDataValidationResult::Invalid;
		}
	}
	for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
		if (ResearchTree == nullptr) {
			ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "Validation_NullSResearchTree", "Null ResearchTree found. Was the content it previously referenced deleted or moved?"));
			ValidationResult = EDataValidationResult::Invalid;
		}
	}
	for (const TSubclassOf<AModSubsystem>& Subsystem : ModSubsystems) {
		if (Subsystem == nullptr) {
			ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "Validation_NullModSubsystem", "Null ModSubsystem found. Was the content it previously referenced deleted or moved?"));
			ValidationResult = EDataValidationResult::Invalid;
		}
	}

	return ValidationResult;
}
#endif

void UGameWorldModule::DispatchLifecycleEvent(ELifecyclePhase Phase) {
    //Register default content before calling blueprint event logic
	if (Phase == ELifecyclePhase::CONSTRUCTION) {
		RegisterConstructionPhaseContent();
	}
	
    if (Phase == ELifecyclePhase::INITIALIZATION) {
        RegisterDefaultContent();
    }
    Super::DispatchLifecycleEvent(Phase);
}

void UGameWorldModule::RegisterConstructionPhaseContent() {
	//Register mod subsystem actors very early so other mods can access them during Initialization phase
	UWorld* WorldObject = GetWorld();
	USubsystemActorManager* SubsystemActorManager = WorldObject->GetSubsystem<USubsystemActorManager>();
	check(SubsystemActorManager);
	
	for (const TSubclassOf<AModSubsystem>& SubsystemClass : ModSubsystems) {
		SubsystemActorManager->RegisterSubsystemActor(SubsystemClass);
	}
}

void UGameWorldModule::RegisterDefaultContent() {
    //Register default content
    UWorld* WorldObject = GetWorld();
    UModContentRegistry* ModContentRegistry = UModContentRegistry::Get(WorldObject);
    AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(WorldObject);
    UContentTagRegistry* ContentTagRegistry = UContentTagRegistry::Get(WorldObject);
	check(ModContentRegistry);
    check(ContentTagRegistry);

    auto ModReference = GetOwnerModReference();

    //Register schematics
    for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
        ModContentRegistry->RegisterSchematic(ModReference, Schematic);
    }

    //Register research trees
    for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
        ModContentRegistry->RegisterResearchTree(ModReference, ResearchTree);
    }

    //Register resource sink table points
    UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable.LoadSynchronous();
    if (ModResourceSinkPointsTable != NULL) {
        ModContentRegistry->RegisterResourceSinkItemPointTable(ModReference, ModResourceSinkPointsTable, EResourceSinkTrack::RST_Default);
    }
    UDataTable* ModExplorationResourceSinkPointsTable = mExplorationResourceSinkItemPointsTable.LoadSynchronous();
    if (ModExplorationResourceSinkPointsTable != NULL) {
        ModContentRegistry->RegisterResourceSinkItemPointTable(ModReference, ModExplorationResourceSinkPointsTable, EResourceSinkTrack::RST_Exploration);
    }

    //Register tag additions
    UDataTable* ContentTagAdditionsTable = mContentTagAdditionsTable.LoadSynchronous();
    if (ContentTagAdditionsTable != NULL) {
        ContentTagRegistry->RegisterTagAdditionTable(ModReference, ContentTagAdditionsTable);
    }

    //Register chat commands (on server side only)
    if (ChatCommandSubsystem != NULL) {
        for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands) {
            ChatCommandSubsystem->RegisterCommand(ModReference.ToString(), ChatCommand);
        }
    }
}

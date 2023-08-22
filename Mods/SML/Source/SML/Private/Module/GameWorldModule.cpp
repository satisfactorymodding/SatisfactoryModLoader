#include "Module/GameWorldModule.h"
#include "Command/ChatCommandLibrary.h"
#include "Registry/ModContentRegistry.h"
#include "Subsystem/SubsystemActorManager.h"
#include "Unlocks/FGUnlockRecipe.h"

#if WITH_EDITOR
EDataValidationResult ValidateRecipe(TSubclassOf<UFGRecipe> Recipe, TArray<FText>& ValidationErrors) {
	if (Recipe == nullptr) {
		ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "NullRecipe", "Null recipe entry. Was the content it previously referenced deleted or moved?"));
		return EDataValidationResult::Invalid;
	}
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	TArray<FItemAmount> AllReferencedItems;
	AllReferencedItems.Append(UFGRecipe::GetIngredients(Recipe));
	AllReferencedItems.Append(UFGRecipe::GetProducts(Recipe));

	for (const FItemAmount& ItemAmount : AllReferencedItems) {
		if (ItemAmount.ItemClass == nullptr) {
			ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "NullRecipeItem", "Null item referenced by recipe. Was the content it previously referenced deleted or moved?"));
			ValidationResult = EDataValidationResult::Invalid;
		}
	}

	return ValidationResult;
}

EDataValidationResult ValidateSchematic(TSubclassOf<UFGSchematic> Schematic, TArray<FText>& ValidationErrors) {
	if (Schematic == nullptr) {
		ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "NullSchematic", "Null schematic entry. Was the content it previously referenced deleted or moved?"));
		return EDataValidationResult::Invalid;
	}
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	TArray<TSubclassOf<UFGRecipe>> Recipes;
	AModContentRegistry::ExtractRecipesFromSchematic(Schematic, Recipes);
	for (TSubclassOf<UFGRecipe> Recipe : Recipes) {
		TArray<FText> RecipeValidationErrors;
		ValidationResult = FMath::Min(ValidationResult, ValidateRecipe(Recipe, RecipeValidationErrors));
		for (const FText& Error : RecipeValidationErrors) {
			ValidationErrors.Add(
				FText::Format(
					NSLOCTEXT("GameWorldModule", "SchematicRecipeValidationErrorDetail", "Error in Recipe {0}: {1}"),
					FText::FromString(Recipe ? Recipe->GetPackage()->GetPathName() : TEXT("")),
					Error));
		}
	}
	return ValidationResult;
}

EDataValidationResult ValidateResearchTree(TSubclassOf<UFGResearchTree> ResearchTree, TArray<FText>& ValidationErrors) {
	if (ResearchTree == nullptr) {
		ValidationErrors.Add(NSLOCTEXT("GameWorldModule", "NullResearchTree", "Null research tree entry. Was the content it previously referenced deleted or moved?"));
		return EDataValidationResult::Invalid;
	}
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;
	TArray<TSubclassOf<UFGSchematic>> Schematics;
	AModContentRegistry::ExtractSchematicsFromResearchTree(ResearchTree, Schematics);
	for (TSubclassOf<UFGSchematic> Schematic : Schematics) {
		TArray<FText> SchematicValidationErrors;
		ValidationResult = FMath::Min(ValidationResult, ValidateSchematic(Schematic, SchematicValidationErrors));
		for (const FText& Error : SchematicValidationErrors) {
			ValidationErrors.Add(
				FText::Format(
					NSLOCTEXT("GameWorldModule", "ResearchTreeSchematicValidationErrorDetail", "Error in Schematic {0}: {1}"),
					FText::FromString(Schematic ? Schematic->GetPackage()->GetPathName() : TEXT("")),
					Error));
		}
	}
	return ValidationResult;
}

EDataValidationResult UGameWorldModule::IsDataValid(TArray<FText>& ValidationErrors) {
	EDataValidationResult ValidationResult = EDataValidationResult::Valid;

	//Check that we do not have any null schematics, research trees, recipes or items
	for (const TSubclassOf<UFGSchematic>& Schematic : mSchematics) {
		TArray<FText> SchematicValidationErrors;
		ValidationResult = FMath::Min(ValidationResult, ValidateSchematic(Schematic, SchematicValidationErrors));
		for (const FText& Error : SchematicValidationErrors) {
			ValidationErrors.Add(
				FText::Format(
					NSLOCTEXT("GameWorldModule", "SchematicValidationErrorDetail", "Error in Schematic {0}: {1}"),
					FText::FromString(Schematic ? Schematic->GetPackage()->GetPathName() : TEXT("")),
					Error));
		}
	}
	for (const TSubclassOf<UFGResearchTree>& ResearchTree : mResearchTrees) {
		TArray<FText> ResearchTreeValidationErrors;
		ValidationResult = FMath::Min(ValidationResult, ValidateResearchTree(ResearchTree, ResearchTreeValidationErrors));
		for (const FText& Error : ResearchTreeValidationErrors) {
			ValidationErrors.Add(
				FText::Format(
					NSLOCTEXT("GameWorldModule", "ResearchTreeValidationErrorDetail", "Error in Research tree {0}: {1}"),
					FText::FromString(ResearchTree ? ResearchTree->GetPackage()->GetPathName() : TEXT("")),
					Error));
		}
	}

	ValidationResult = FMath::Min(ValidationResult, Super::IsDataValid(ValidationErrors));
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
    AModContentRegistry* ModContentRegistry = AModContentRegistry::Get(WorldObject);
    AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(WorldObject);
	check(ModContentRegistry);

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

    //Register chat commands (on server side only)
    if (ChatCommandSubsystem != NULL) {
        for (const TSubclassOf<AChatCommandInstance>& ChatCommand : mChatCommands) {
            ChatCommandSubsystem->RegisterCommand(ModReference.ToString(), ChatCommand);
        }
    }
}

#include "InitGameWorld.h"
#include "FGSchematicManager.h"
#include "SML/util/Logging.h"
#include "FGResearchManager.h"
#include "FGResourceSinkSettings.h"
#include "FGResourceSinkSubsystem.h"
#include "tooltip/ItemTooltipHandler.h"

void AInitGameWorld::Init_Implementation() {
}

void AInitGameWorld::PostInit_Implementation() {
}

void AInitGameWorld::PreInit_Implementation() {
}

void AInitGameWorld::PreLoadModContent() {
	//Register subsystem holders
}

static TArray<FString> ProviderClassNamesRegistered;

void AInitGameWorld::LoadModContent() {
	AFGSchematicManager* schematicManager = AFGSchematicManager::Get(this);
	//No need to register AvailableSchematics on client side, they are replicated
	if (schematicManager->HasAuthority()) {
		for (TSubclassOf<UFGSchematic> schematic : mSchematics) {
			TArray<TSubclassOf<UFGSchematic>> availableSchematics;
			schematicManager->GetAvailableSchematics(availableSchematics);
			SML::Logging::debug("Loading schematic ", *UFGSchematic::GetSchematicDisplayName(schematic).ToString(), " of mod ", *this->GetClass()->GetPathName());
			if (!schematicManager->IsSchematicPurchased(schematic) && !availableSchematics.Contains(schematic)) {
				SML::Logging::debug("Adding schematic ", *UFGSchematic::GetSchematicDisplayName(schematic).ToString());
				schematicManager->AddAvailableSchematic(schematic);
			}
		}
	}
	//Add research trees
	AFGResearchManager* ResearchManager = AFGResearchManager::Get(this);
	for (TSubclassOf<UFGResearchTree> ResearchTree : mResearchTrees) {
		SML::Logging::debug("Loading research tree ", *UFGResearchTree::GetDisplayName(ResearchTree).ToString(), " of mod ", *this->GetClass()->GetPathName());
		if (!ResearchManager->mAllResearchTrees.Contains(ResearchTree)) {
			SML::Logging::debug("Adding research tree ", *UFGResearchTree::GetDisplayName(ResearchTree).ToString());
			ResearchManager->mAllResearchTrees.Add(ResearchTree);
		}
	}
	//Update unlocked trees because new research trees might have been added
	ResearchManager->UpdateUnlockedResearchTrees();
	AChatCommandSubsystem* ChatCommandSubsystem = AChatCommandSubsystem::Get(this);
	if (ChatCommandSubsystem != nullptr && ChatCommandSubsystem->HasAuthority()) {
		//Register chat commands on server side only
		for (const TSubclassOf<AChatCommandInstance>& RegistrarEntry : mChatCommands) {
			SML::Logging::info(TEXT("Registering chat command "), *RegistrarEntry->GetPathName());
			ChatCommandSubsystem->RegisterCommand(RegistrarEntry);
		}
	}
	UDataTable* ModResourceSinkPointsTable = mResourceSinkItemPointsTable.LoadSynchronous();
	AFGResourceSinkSubsystem* ResourceSinkSubsystem = AFGResourceSinkSubsystem::Get(this);
	if (ResourceSinkSubsystem != NULL && ModResourceSinkPointsTable != NULL) {
		checkf(ModResourceSinkPointsTable->RowStruct != nullptr &&
			ModResourceSinkPointsTable->RowStruct->IsChildOf(FResourceSinkPointsData::StaticStruct()),
			TEXT("Invalid AWESOME Sink item points table in mod %s: Row Type should be Resource Sink Points Data"), *this->GetClass()->GetPathName());
		TArray<FResourceSinkPointsData*> OutModPointsData;
		ModResourceSinkPointsTable->GetAllRows(TEXT("ResourceSinkPointsData"), OutModPointsData);
		for (FResourceSinkPointsData* ModItemRow : OutModPointsData) {
			ResourceSinkSubsystem->mResourceSinkPoints.Add(ModItemRow->ItemClass, FMath::Max(ModItemRow->Points, ModItemRow->OverriddenResourceSinkPoints));
		}
		SML::Logging::info(TEXT("Registered %d AWESOME sink entries for mod %s"), *this->GetClass()->GetPathName());
	}
}

void AInitGameWorld::PlayerJoined_Implementation(AFGPlayerController* Player) {
}

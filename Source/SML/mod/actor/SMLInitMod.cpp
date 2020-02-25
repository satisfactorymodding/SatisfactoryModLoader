#include "SMLInitMod.h"
#include "FGSchematicManager.h"
#include "SML/util/Logging.h"

void ASMLInitMod::LoadSchematics() {
	AFGSchematicManager* schematicManager = AFGSchematicManager::Get(this);
	for (TSubclassOf<UFGSchematic> schematic : mSchematics) {
		TArray<TSubclassOf<UFGSchematic>> availableSchematics;
		schematicManager->GetAvailableSchematics(availableSchematics);
		SML::Logging::debug("Loading schematic ", *UFGSchematic::GetSchematicDisplayName(schematic).ToString(), " of mod ", *this->GetClass()->GetPathName());
		if (!schematicManager->IsSchematicPurchased(schematic) && !availableSchematics.Contains(schematic)) {
			SML::Logging::debug("Adding schematic ", *UFGSchematic::GetSchematicDisplayName(schematic).ToString(), " of mod ", *this->GetClass()->GetPathName());
			schematicManager->AddAvailableSchematic(schematic);
		}
	}
}
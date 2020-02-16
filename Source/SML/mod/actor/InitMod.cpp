#include "InitMod.h"
#include "FGSchematicManager.h"

void AInitMod::LoadSchematics() {
	AFGSchematicManager* schematicManager = AFGSchematicManager::Get(this);
	for (TSubclassOf<UFGSchematic> schematic : mSchematics) {
		TArray<TSubclassOf<UFGSchematic>> availableSchematics;
		schematicManager->GetAvailableSchematics(availableSchematics);
		if (!schematicManager->IsSchematicPurchased(schematic) && !availableSchematics.Contains(schematic)) {
			schematicManager->AddAvailableSchematic(schematic);
		}
	}
}
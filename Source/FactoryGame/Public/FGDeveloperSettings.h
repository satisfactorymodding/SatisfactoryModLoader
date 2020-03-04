#pragma once
#include "SubclassOf.h"
#include "Curves/CurveFloat.h"
#include "UObject/Class.h"

#include "FGSchematic.h"
#include "FGActorRepresentation.h"
#include "Engine/DeveloperSettings.h"
#include "FGDeveloperSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory Developer Settings" ) )
class FACTORYGAME_API UFGDeveloperSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY( VisibleAnywhere, config, Category = Focus, meta = ( 
		ToolTip = "Should widgets grab focus back on focus lost in PIE. Default is off to avoid intrusive behaviour when trying to work. You can override this value in Game.ini. Ask K2 how" ) )
	bool mGreedyFocusInPIE;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockRecipe > mUnlockRecipeClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockScannableResource > mUnlockScannerResourceClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockMap > mUnlockMapClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockBuildEfficiency > mUnlockBuildEfficiencyClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockBuildOverclock > mUnlockBuildOverclockClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockInventorySlot > mUnlockInvetorySlotClass;

	UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
	TSubclassOf< class UFGUnlockArmEquipmentSlot > mUnlockArmEquipmentClass;

	UPROPERTY( EditAnywhere, config, Category = "Schematic category classes for migrating from old enum to new object based type" )
	TMap< ESchematicCategory, TSubclassOf< class UFGSchematicCategory > > mSchematicCategoryMigrationData;

public:
	FORCEINLINE ~UFGDeveloperSettings() = default;
};
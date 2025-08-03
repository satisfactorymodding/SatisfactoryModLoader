// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGSchematic.h"
#include "FGMigrationSettings.generated.h"


/**
* Settings class where you can put in migration variables to specify native and BP classes for access in native code
*/

/**
* Example to get a BP class that derives from UFGUnlockRecipe used in migration of unlock recipes
*
* UPROPERTY( EditAnywhere, config, Category = "Unlock Classes For Migrating To New Unlock System" )
* TSubclassOf< class UFGUnlockRecipe > mUnlockRecipeClass;
*
* Depending on your use case it might be suitable to wrap the code that access these settings with
* #if WITH_EDITORONLY_DATA or WITH_EDITOR
* ...
* #endif
*/

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Satisfactory Migration Settings" ) )
class FACTORYGAME_API UFGMigrationSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGMigrationSettings* Get() { return GetDefault<UFGMigrationSettings>(); };

public:
	UPROPERTY( EditAnywhere, config, Category = "Dependency class for schematic purchased" )
	TSoftClassPtr< class UFGSchematicPurchasedDependency > mSchematicPurchasedDependencyClass;

	UPROPERTY( EditAnywhere, config, Category = "Dependency class for item pickup" )
	TSoftClassPtr< class UFGItemPickedUpDependency > mItemPickedUpDependencyClass;

	/** Tobias 2025-03-26: Referencing legacy poles here so that they get packaged with the game, as the buildable isn't referenced anywhere else. They got unreferenced with a pole refactor between 1.0 and 1.1, but still need to exist for 1.0 and earlier saves. */
	UPROPERTY( EditAnywhere, config, Category = "Legacy class for sign poles" )
	TSoftClassPtr< class AFGBuildableSignSupport > mLegacySignPoleClass;
};
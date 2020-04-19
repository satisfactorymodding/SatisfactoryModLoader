#pragma once
#include "Engine/DeveloperSettings.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

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
	UPROPERTY( EditAnywhere, config, Category = "Dependency class for migrating to new dependency system" )
	TSubclassOf< class UFGSchematicPurchasedDependency > mSchematicPurchasedDependencyClass;


public:
	FORCEINLINE ~UFGMigrationSettings() = default;
};
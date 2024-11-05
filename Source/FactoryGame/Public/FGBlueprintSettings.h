// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "Templates/SubclassOf.h"
#include "FGBlueprintSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Blueprints" ) )
class FACTORYGAME_API UFGBlueprintSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UFGBlueprintSettings* Get() { return GetDefault<UFGBlueprintSettings>(); };
	
	UPROPERTY( EditAnywhere, config, Category = "The blueprint recipe class shared for all instanced blueprint descriptors" )
	TSoftClassPtr< class UFGRecipe > mBlueprintRecipeClass; // <FL> [WuttkeP] Replaced a few TSubclassOf with TSoftClassPtr to fix editor initialization.

	UPROPERTY( EditAnywhere, config, Category = "The blueprint designer recipe class" )
	TSoftClassPtr< class UFGRecipe > mBlueprintDesignerRecipeClass; // <FL> [WuttkeP] Replaced a few TSubclassOf with TSoftClassPtr to fix editor initialization.

	UPROPERTY(  EditAnywhere, config, Category = "Factory Blueprint Settings", meta = ( ToolTip = "The Icon ID to used for undefined categories" ))
	int32 mUndefinedCategoryIconID;
	
};

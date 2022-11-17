// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Templates/SubclassOf.h"
#include "Engine/DeveloperSettings.h"
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
	TSubclassOf< class UFGRecipe > mBlueprintRecipeClass;

	UPROPERTY(  EditAnywhere, config, Category = "Factory Blueprint Settings", meta = ( ToolTip = "The Icon ID to used for undefined categories" ))
	int32 mUndefinedCategoryIconID;
	
};

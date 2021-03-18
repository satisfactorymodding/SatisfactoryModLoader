// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "UObject/NoExportTypes.h"
#include "FGLootSettings.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGLootSettings : public UObject
{
	GENERATED_BODY()
	
public:
	/** Gets default object for loot settings */
	UFUNCTION( BlueprintPure, Category = "LootSettings|Utilities", meta = ( DeterminesOutputType = "inClass") )
	static UObject* GetLootSettingsDefaultObject( TSubclassOf< UFGLootSettings >  inClass );
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGUnlockSettings.generated.h"

/**
 * 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Unlocks" ) )
class FACTORYGAME_API UFGUnlockSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	static const UFGUnlockSettings* Get() { return GetDefault<UFGUnlockSettings>(); };
	
	UFUNCTION( BlueprintPure, Category = "Settings" )
	static TSubclassOf<class UFGSchematic> GetCheckmarkSchematicClass();
	
	/** Schematic class for the FICSIT Checkmark™ schematic */
	UPROPERTY( Config, EditDefaultsOnly, Category = "Settings")
	TSoftClassPtr< class UFGSchematic > mCheckmarkSchematic;
};

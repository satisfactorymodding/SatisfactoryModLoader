// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Engine/DeveloperSettings.h"
#include "FGNewGameSettings.generated.h"

/** Settings for when starting a new game, either locally or on a dedicated server */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "New Game Settings" ) )
class FACTORYGAME_API UFGNewGameSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UFGNewGameSettings();

	/** Returns the global settings singleton */
	static const UFGNewGameSettings* Get();

	/** Default map to use when creating a new game */
	UPROPERTY( EditAnywhere, Config, Category = "New Game Settings" )
	TSoftObjectPtr<UWorld> mDefaultMap;

	/** Test map reference when using TestMap as a starting location and not specifying a map override */
	UPROPERTY( EditAnywhere, Config, Category = "New Game Settings" )
	TSoftObjectPtr<UWorld> mTestMap;
};

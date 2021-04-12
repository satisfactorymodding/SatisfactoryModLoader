// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "FGBuildableLightSettings.generated.h"

/**
 * Settings to define the usage of buildable lights such as color slots etc. 
 */
UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Buildable Lights" ) )
class FACTORYGAME_API UFGBuildableLightSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGBuildableLightSettings* Get() { return GetDefault<UFGBuildableLightSettings>(); };
	
	UPROPERTY( EditAnywhere, config, Category = "Buildable Light Colors", meta = ( ToolTip = "The different colors that a light can be set to by default. Players can adjust these later in game" ) )
	TArray< FLinearColor > mDefaultColorSlots;

};

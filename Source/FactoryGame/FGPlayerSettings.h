#pragma once
#include "Engine/DeveloperSettings.h"
#include "Array.h"
#include "UObject/Class.h"

#include "FGPlayerState.h"
#include "FGPlayerSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Player" ) )
class FACTORYGAME_API UFGPlayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	UPROPERTY( EditAnywhere, config, Category = "Player Colors", meta = ( ToolTip = "The different colors to represent players over the network" ) )
	TArray< FSlotData > mPlayerColors;
};
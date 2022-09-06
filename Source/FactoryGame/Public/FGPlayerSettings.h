// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGPlayerState.h"
#include "FGPlayerSettings.generated.h"

UCLASS( config = Game, defaultconfig, meta = ( DisplayName = "Player" ) )
class FACTORYGAME_API UFGPlayerSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGPlayerSettings* Get() { return GetDefault<UFGPlayerSettings>(); };
	
	UPROPERTY( EditAnywhere, config, Category = "Player Colors", meta = ( ToolTip = "The different colors to represent players over the network" ) )
	TArray< FPlayerColorData > mPlayerColors;

	UPROPERTY( EditAnywhere, config, Category = "Player Colors", meta = ( ToolTip = "The color we set to players that are offline" ) )
	FLinearColor mOfflinePlayerColor;

	UPROPERTY( EditAnywhere, config, Category = "Player Name", meta = ( ToolTip = "The name we give players with no cached name. Should only happen for old saves until the players joined again so we can cache their user name" ) )
	FText mNoCachedPlayerName;

	UPROPERTY( EditAnywhere, config, Category = "Inventory Slots", meta = ( ToolTip = "The number of starting slots for players inventory" ) )
	int32 mDefaultPlayerInventorySlots;

	UPROPERTY( EditAnywhere, config, Category = "Inventory Slots", meta = ( ToolTip = "The number of starting slots for players arm equipments" ) )
	int32 mDefaultArmEquipmentSlots;
};
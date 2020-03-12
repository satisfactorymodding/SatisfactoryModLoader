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

	UPROPERTY( EditAnywhere, config, Category = "Inventory Slots", meta = ( ToolTip = "The number of starting slots for players inventory" ) )
	int32 mDefaultPlayerInventorySlots;

	UPROPERTY( EditAnywhere, config, Category = "Inventory Slots", meta = ( ToolTip = "The number of starting slots for players arm equipments" ) )
	int32 mDefaultArmEquipmentSlots;

public:
	FORCEINLINE ~UFGPlayerSettings() = default;
};
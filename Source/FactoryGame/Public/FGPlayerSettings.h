// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGPlayerState.h"
#include "FGRecipe.h"
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

	/** Affected in game by AFGUnlockSubssytem::mUnlockedCentralStorageUploadSlots */
	UPROPERTY( EditAnywhere, config, Category = "Inventory Slots", meta = ( ToolTip = "The number of starting slots for players upload inventory (central storage)" ) )
	int32 mDefaultUploadSlots;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources", meta = ( ToolTip = "The default items each player will start with. This will be given once per player when they join a new game" ) )
	TMap< TSoftClassPtr< class UFGItemDescriptor >, int32 >mStartingItems;
	
	UPROPERTY( EditAnywhere, config, Category = "Starting Resources", meta = ( ToolTip = "The recipes you should be able to build when you start a new game. The integer key represents starting tier. 0 is tutorial and so on. The combined items from the specified recipes in the given tier is given once to the FIRST player joining a game" ) )
	TMap< int32, FRecipeAmounts > mRecipesToGivePlayersPerTier;

	/** Reference to the default walk head bob shake */
	UPROPERTY( EditDefaultsOnly, Config, Category = "Movement" )
	TSoftObjectPtr<UCameraAnimationSequence> mDefaultWalkHeadBobCameraAnim;

	/** Reference to the default sprint head bob shake */
	UPROPERTY( EditDefaultsOnly, Config, Category = "Movement" )
	TSoftObjectPtr<UCameraAnimationSequence> mDefaultSprintHeadBobCameraAnim;
};
// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "ItemAmount.h"
#include "FGLocalSettings.generated.h"

/**
 * 
 */
UCLASS( config = EditorPerProjectUserSettings, meta = ( DisplayName = "Satisfactory Local Settings" ) )
class FACTORYGAME_API UFGLocalSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGLocalSettings* Get() { return GetDefault<UFGLocalSettings>(); };
public:
	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
		ToolTip = "Skips the tutorial step if we play in PIE" ) )
	bool mSkipTutoialInPIE = true;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
	ToolTip = "If enabled we will autosave when playing in PIE" ) )
	bool mEnableAutoSaveInPIE;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
	ToolTip = "Disables HUD, playerFOV" ) )
	bool mTrailerMode;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources", meta = (
		ToolTip = "Extra items we always give you on startup in PIE and standalone" ) )
	TArray< FItemAmount > mExtraItemsToStartWith;

	UPROPERTY( EditAnywhere, config, Category = Focus, meta = (
		ToolTip = "Should widgets grab focus back on focus lost in PIE. Default is off to avoid intrusive behaviour when trying to work. This is a local change only" ) )
	bool mLocalGreedyFocusInPIE;
};

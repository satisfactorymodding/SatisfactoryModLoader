// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGNavigationConfig.h"
#include "Engine/DeveloperSettings.h"
#include "ItemAmount.h"
#include "FGCreatureSubsystem.h"
#include "FGLocalSettings.generated.h"

/**
 * 
 */
UCLASS( config = EditorPerProjectUserSettings, meta = ( DisplayName = "Satisfactory Starting Resources/Cheats" ) )
class FACTORYGAME_API UFGLocalSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGLocalSettings* Get() { return GetDefault<UFGLocalSettings>(); };
	
	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Extra items we always give you on startup in PIE and standalone" ) )
	TMap< TSoftClassPtr< class UFGItemDescriptor >, int32 > mExtraItemsToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Recipes you want to start with in PIE and standalone" ) )
	TArray< TSoftClassPtr<class UFGRecipe> > mRecipesToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Schematics you want to start with in PIE and standalone" ) )
	TArray< TSoftClassPtr<class UFGSchematic> > mSchematicsToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
	ToolTip = "Schematics you don't want to get when you give all schematics in PIE and standalone. Works for both the cheat menu and the bool below" ) )
	TArray< TSoftClassPtr<class UFGSchematic> > mSchematicsToFilterWithGiveAllSchematics;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mGodMode;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Set fly enabled on all players if true" ) )
	bool mEnableFly = true;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
	ToolTip = "Set auto landing off on all players if false. Does nothing if flying is off." ) )
	bool mEnableAutoLanding = true;
	
	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Set fly ghost enabled on all players if true" ) )
	bool mEnableFlyGhost;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mNoCost;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mNoPower;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mNoFuel;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mGiveAllSchematics;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mGiveCheatSchematics;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mNoNarrativeMessages;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	EPlayerHostilityMode mSetCreatureHostility;
	
};

UCLASS( config = EditorPerProjectUserSettings, meta = ( DisplayName = "Satisfactory Local Dev Settings" ) )
class FACTORYGAME_API UFGLocalDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGLocalDevSettings* Get() { return GetDefault<UFGLocalDevSettings>(); };
	
	UPROPERTY( EditAnywhere, config, Category = Tutorial, meta = (
		ToolTip = "Skips the tutorial/onboarding steps if we play in PIE" ) )
	bool mSkipTutoialInPIE = true;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = ( 
		ToolTip = "If enabled we will autosave when playing in PIE" ) )
	bool mEnableAutoSaveInPIE;
	
	UPROPERTY( EditAnywhere, config, Category = Game, meta = ( ToolTip = "Enable this if you want the welcome pioneer logo to show when starting a game in editor" ) )
	bool mShowFicsitSplashWidget;
	
	UPROPERTY( EditAnywhere, config, Category = Game, meta = ( ToolTip = "When true it doesn't show the Unstable Save Version and Offline Session popups in editor and standalone" ) )
	bool mDisableSaveVersionAndOfflineWarnings;

	// Couldn't use InlineEditConditionToggle for this because it wouldn't save the new value to the config so it was always reset on startup
	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
		ToolTip = "When true we speed up research, dropship delivery etc in editor. See mReducedWaitTime to set the time" ) )
	bool mEnableReducedWaitTime = true;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = ( EditCondition="mEnableReducedWaitTime", ClampMin = 0.2,
		ToolTip = "When mEnableReducedWaitTime is true we replace the UFGSchematic::GetTimeToComplete time with this float value. This affects research and dropship delivery etc in PIE and standalone" ) )
	float mReducedWaitTime = 1;

	UPROPERTY( EditAnywhere, config, Category = Trailer, meta = (
    	ToolTip = "Disables HUD, playerFOV" ) )
    bool mTrailerMode;

	UPROPERTY( EditAnywhere, config, Category = Input, meta = ( 
		ToolTip = "Enable input for all devices (keyboard, mouse & gamepad) and activate adaptive UI when switching between them." ) )
	bool mEnableAdaptiveInputUI = false;
};

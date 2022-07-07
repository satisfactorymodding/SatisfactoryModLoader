// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
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
	TArray< FItemAmount > mExtraItemsToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Recipes you want to start with in PIE and standalone" ) )
	TArray< TSubclassOf<class UFGRecipe> > mRecipesToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Schematics you want to start with in PIE and standalone" ) )
	TArray< TSubclassOf<class UFGSchematic> > mSchematicsToStartWith;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
	ToolTip = "Schematics you don't want to get when you give all schematics in PIE and standalone. Works for both the cheat menu and the bool below" ) )
	TArray< TSubclassOf<class UFGSchematic> > mSchematicsToFilterWithGiveAllSchematics;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats" )
	bool mGodMode;

	UPROPERTY( EditAnywhere, config, Category = "Starting Resources/Cheats", meta = (
		ToolTip = "Set fly enabled on all players if true" ) )
	bool mEnableFly;

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
	TEnumAsByte<ECreatureHostility> mSetCreatureHostility;
	
};

UCLASS( config = EditorPerProjectUserSettings, meta = ( DisplayName = "Satisfactory Local Dev Settings" ) )
class FACTORYGAME_API UFGLocalDevSettings : public UDeveloperSettings
{
	GENERATED_BODY()
public:
	static const UFGLocalDevSettings* Get() { return GetDefault<UFGLocalDevSettings>(); };

#if WITH_EDITOR
	virtual void PostEditChangeProperty( FPropertyChangedEvent& PropertyChangedEvent ) override
	{
		Super::PostEditChangeProperty( PropertyChangedEvent );

		const FName propertyName = PropertyChangedEvent.Property ? PropertyChangedEvent.Property->GetFName() : NAME_None;
		if( propertyName == GET_MEMBER_NAME_CHECKED( UFGLocalDevSettings, mEnableTabAndKeyNavigation ) )
		{
			FFGNavigationConfig::EnableTabAndNavKeys( mEnableTabAndKeyNavigation );
		}
	}
#endif
	
	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
		ToolTip = "Skips the tutorial step if we play in PIE" ) )
	bool mSkipTutoialInPIE = true;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
		ToolTip = "If enabled we will autosave when playing in PIE" ) )
	bool mEnableAutoSaveInPIE;

	UPROPERTY( EditAnywhere, config, Category = Game, meta = (
		ToolTip = "Disables HUD, playerFOV" ) )
	bool mTrailerMode;
	
	UPROPERTY( EditAnywhere, config, Category = Focus, meta = (
		ToolTip = "Should widgets grab focus back on focus lost in PIE. Default is off to avoid intrusive behaviour when trying to work. This is a local change only" ) )
	bool mLocalGreedyFocusInPIE;

	UPROPERTY( EditAnywhere, config, Category = Navigation, meta = (
		ToolTip = "Enable Tab and Key navigation locally so we can test it without impact for rest of dev team or players. When this is true FFGNavigationConfig::EnableTabAndNavKeys will always set navigation to true" ) )
	bool mEnableTabAndKeyNavigation;
};

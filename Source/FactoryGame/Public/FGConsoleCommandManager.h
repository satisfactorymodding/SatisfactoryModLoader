// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "FGConsoleCommandManager.generated.h"

/**
 * Console commands that are non-cheats that can be exposed to the players.
 */
UCLASS( Within = FGPlayerController )
class FACTORYGAME_API UFGConsoleCommandManager : public UObject
{
	GENERATED_BODY()
public:
	/** Use the Outer Player Controller to get a World.  */
	virtual UWorld* GetWorld() const override;

	/** Perform a MFA analysis on the given recipes (comma separated). Output is shown in the log. */
	UFUNCTION( Exec )
	void MaterialFlowAnalysis( FString recipeNames );
	/** Perform a Material Lookup. Output is shown in the log. */
	UFUNCTION( Exec )
	void MaterialLookup( FString itemName );

	/** Rename the name of this save session, added for older saves that got their name nulled out. */
	UFUNCTION( exec )
	void SetSessionName( FString newSessionName );
	/** Save to a new save with a new session name. */
	UFUNCTION( exec )
	void SaveWithNewSessionName( const FString& saveName, const FString& sessionName );

	/** Dumps all known ak stats to the log. */
	UFUNCTION( exec )
	void TrackAllAkStats();
	/** Dumps the top playing components to log, grouped either by class or actor playing. */
	UFUNCTION( exec )
	void TrackAkComponents( bool byClass = true );
	/** Dumps the stats for wwise memory pools to the log. */
	UFUNCTION( exec )
	void TrackAkMemoryPools();
	/** Dumps all ak components with no position (0,0,0) or owner to the log. */
	UFUNCTION( exec )
	void TrackAkComponentsWithNoPositionOrOwner();
	/** Dumps all FGFactoryMaterialInstanceManager stats for debugging */
	UFUNCTION( exec )
	void DumpFactoryMaterialInstanceManagerStats();

	/** Useful for testing the crash reporter. */
	UFUNCTION( exec )
	void CrashTheGame();
	/** Some of the properties the crash reporter sends with a crash. */
	UFUNCTION( exec )
	void DumpCrashContext();

	/**
	 * Tries to find a recipe that built a building and (re)applies it to the building,
	 * This fixes so a correct refund is returned when dismantling it.
	 * By default this only looks at buildings where the recipe is missing, optionally it can look for a better match and reapply that.
	 * A summary of the buildings fixed up is outputted to the log.
	 */
	UFUNCTION( exec )
	void FixupBuiltByRecipeInOldSave( bool reapplyRecipeIfBetterMatchFound = false );

	/** Dump some stats about the factory to the log such as number of buildings and kilometers of railway built. */
	UFUNCTION( exec, category = "Log" )
	void DumpFactoryStatsToLog();

	/** Copy the player coordinates to cliboard */
	UFUNCTION( exec )
	void CopyPlayerCoordinates();

	/** Dumps the player coordinates to log, potentially with a label and copy to clipboard */
	UFUNCTION( exec )
	void DumpPlayerCoordinates( const FString& label = TEXT(""), bool copyToClipboard = false );

public:
	FORCEINLINE ~UFGConsoleCommandManager() = default;
};

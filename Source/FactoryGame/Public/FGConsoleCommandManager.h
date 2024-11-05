// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCheatManager.h"
#include "FGConsoleCommandManager.generated.h"

// This should later be moved into a plugin dedicated to localization
class FPatchTable
{
	// We need an array keyed on namespace+key
	// and an interface to retrieve a row given namespace and key
	// Row should support metadata retrieval given metadata column name
public:
	struct FPatchTableRow
	{
		FString Path = TEXT( "" );
		FString Namespace = TEXT( "" );
		FString Key = TEXT( "" );
		FString StringTable = TEXT( "" );
		FString NewKey = TEXT( "" );
		FString SourceString = TEXT( "" );
		TMap<FName, FString> MetdataByColumnName; // This oughtta be initialized from locaSettings
	};
	TArray<FPatchTableRow> Rows;

	bool Init( const FString& patchTableFilePathName );
	const FPatchTable::FPatchTableRow* FindRow( const FString& inNamespace, const FString& inKey ) const;
};

/**
 * Console commands that are non-cheats that can be exposed to the players.
 */
UCLASS( Within = FGPlayerController )
class FACTORYGAME_API UFGConsoleCommandManager : public UObject, public IFGCheatBoardFunctionCategoryProvider
{
	GENERATED_BODY()
public:
	/** Use the Outer Player Controller to get a World.  */
	virtual UWorld* GetWorld() const override;

	// Begin IFGCheatBoardFunctionCategoryProvider interface
	virtual TMap<FString, FString> GetFunctionCategories() const override;
	// End IFGCheatBoardFunctionCategoryProvider interface

	/** Perform a MFA analysis on the given recipes (comma separated). Output is shown in the log. */
	UFUNCTION( Exec, CheatBoard )
	void MaterialFlowAnalysis( FString recipeNames );
	/** Perform a Material Lookup. Output is shown in the log. */
	UFUNCTION( Exec, CheatBoard )
	void MaterialLookup( FString itemName );

	/** Rename the name of this save session, added for older saves that got their name nulled out. */
	UFUNCTION( Exec, CheatBoard )
	void SetSessionName( FString newSessionName );
	/** Save to a new save with a new session name. */
	UFUNCTION( Exec, CheatBoard )
	void SaveWithNewSessionName( const FString& saveName, const FString& sessionName );

	/** Dumps all known ak stats to the log. */
	UFUNCTION( Exec, CheatBoard )
	void TrackAllAkStats();
	/** Dumps the top playing components to log, grouped either by class or actor playing. */
	UFUNCTION( Exec, CheatBoard )
	void TrackAkComponents( bool byClass = true );
	/** Dumps all ak components with no position (0,0,0) or owner to the log. */
	UFUNCTION( Exec, CheatBoard )
	void TrackAkComponentsWithNoPositionOrOwner();

	/** Useful for testing the crash reporter. */
	UFUNCTION( Exec, CheatBoard )
	void CrashTheGame();
	/** Some of the properties the crash reporter sends with a crash. */
	UFUNCTION( Exec, CheatBoard )
	void DumpCrashContext();

	/** Tells online services to reset stats / achievements. */
	UFUNCTION( Exec, CheatBoard )
	void ResetOnlineStats();

	/**
	 * Tries to find a recipe that built a building and (re)applies it to the building,
	 * This fixes so a correct refund is returned when dismantling it.
	 * By default this only looks at buildings where the recipe is missing, optionally it can look for a better match and reapply that.
	 * A summary of the buildings fixed up is outputted to the log.
	 */
	UFUNCTION( Exec, CheatBoard )
	void FixupBuiltByRecipeInOldSave( bool reapplyRecipeIfBetterMatchFound = false );

	/** Dump some stats about the factory to the log such as number of buildings and kilometers of railway built. */
	UFUNCTION( Exec, CheatBoard )
	void DumpFactoryStatsToLog();

	/** Copy the player coordinates to clipboard */
	UFUNCTION( Exec, CheatBoard )
	void CopyPlayerCoordinates();

	/** Dumps the player coordinates to log, potentially with a label and copy to clipboard */
	UFUNCTION( Exec, CheatBoard )
	void DumpPlayerCoordinates( const FString& label = TEXT(""), bool copyToClipboard = false );

	UFUNCTION( Exec, CheatBoard )
	void DumpDynamicOptionsSettings();

	/** Toggle visualization of railroad blocks on/off. */
	UFUNCTION( Exec, CheatBoard )
	void ToggleRailroadBlockVisualization( bool enabled );

	/** Enable the train scheduler's black box, dumps state when a deadlock is detected or continuously if num records to keep is set to 0. */
	UFUNCTION( exec )
	void EnableTrainSchedulerBlackBox( int32 numRecordsToKeep );

	/** Disable the train scheduler's black box and optionally dumps state. */
	UFUNCTION( exec )
	void DisableTrainSchedulerBlackBox( bool dump );

	/** Tries to dismantle vehicles that are under the player (50m down or lower in a 100m radius) and places the recovered resources in front of the player. */
	UFUNCTION( Exec, CheatBoard )
	void DismantleVehiclesUnderWorld();

#if WITH_EDITOR
	static bool ParsePatchTableArgs( const TArray<FString>& args, TSet<FString>& out_paths, TSet<FString>& out_stringTables, int32& out_limit, bool& out_ignoreSourceStringMismatch );
	static void PatchUpFTextInAssets( const TArray<FString>& args );
	
	static void PatchUpTextFiles( const TSet<TPair<FString, FString>>& textKeysToPatch, const FPatchTable& patchTable );

#endif
};
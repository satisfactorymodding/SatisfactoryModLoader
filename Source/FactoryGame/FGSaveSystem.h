#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Object.h"
#include "FGOnlineSessionSettings.h"
#include "FGSaveSystem.generated.h"

namespace SaveSystemConstants
{
	// Several locations require the . in the extension
	static FString SaveExtension( TEXT( ".sav" ) );

	// Custom name for the custom version when setting versions of archives
	static const TCHAR* CustomVersionFriendlyName = TEXT( "SaveVersion" );

	// Custom name for the save header
	static const TCHAR* HeaderCustomVersionFriendlyName = TEXT( "SaveHeaderVersion" );
}

UENUM( BlueprintType )
enum class ESaveExists : uint8
{
	SE_DoesntExist			UMETA( DisplayName="DoesntExist" ),
	SE_ExistsInSameSession	UMETA( DisplayName="ExistsInSameSession" ),
	SE_ExistsInOtherSession UMETA( DisplayName="ExistsInOtherSession" )
};

typedef FString SessionNameType;

/** The header with information about a save game */
USTRUCT( BlueprintType )
struct FSaveHeader
{
	GENERATED_BODY()

	// if you modify this struct, increment this number
	enum Type
	{
		// First version
		InitialVersion = 0,

		// @2017-01-20: Added BuildVersion, MapName and MapOptions
		PrepareForLoadingMaps,

		// @2017-02-07: Added SessionId for autosaves
		AddedSessionId,

		// @2018-02-23 Added PlayDuration to header
		AddedPlayDuration,

		// @2018-04-10 SessionID from int32 to FString, also added when the save was saved
		SessionIDStringAndSaveTimeAdded,

		// @2019-01-15 Added session visibility to the header so we can set it up with the same visibility
		AddedSessionVisibility,

		// @2019-06-19 This was put in the wrong save version thingy and is now on experimental so cant remnove it.
		LookAtTheComment,

		// -----<new versions can be added above this line>-----
		VersionPlusOne,
		LatestVersion = VersionPlusOne - 1 // Last version to use
	};

	FSaveHeader();

	FSaveHeader( int32 saveVersion, int32 buildVersion, FString mapName, FString mapOptions, FString sessionName, int32 playDurationSeconds, FDateTime saveDateTime, ESessionVisibility sessionVisibility ) :
		SaveVersion( saveVersion ),
		BuildVersion( buildVersion ),
		MapName( mapName ),
		MapOptions( mapOptions ),
		SessionName( sessionName ),
		PlayDurationSeconds( playDurationSeconds ),
		SaveDateTime( saveDateTime ),
		SessionVisibility( sessionVisibility )
	{
	}

	/** Version of the save game */
	int32 SaveVersion;

	/** CL the game was on when this was stored */
	int32 BuildVersion;

	/** Name of the save game, not store to disc */
	FString SaveName;

	/** The map this save is valid on  */
	FString MapName;

	/** Options we want to pass to the game mode */
	FString MapOptions;

	/** A unique id for each session, used for generating autosaves that's unique */
	SessionNameType SessionName;

	/** How long play time has this save been going on for */
	int32 PlayDurationSeconds;

	/** The time we saved this save */
	FDateTime SaveDateTime;

	/** What was the last visibility of the game when we played it */
	TEnumAsByte<ESessionVisibility> SessionVisibility;

	// @todosave: Add LastPlayDate as uint64 (Timestamp)
	// @todosave: Add if it's a autosave

	/** Store / load data */
	friend FArchive& operator<< ( FArchive& ar, FSaveHeader& header );

	// The GUID for this custom version number
	const static FGuid GUID;
};

/**
 * For when a artist/LD has changed the name of a map
 */
USTRUCT()
struct FMapRedirector
{
	GENERATED_BODY()

	/** Old map name */
	UPROPERTY()
	FString OldMapName;

	/** New map name */
	UPROPERTY()
	FString NewMapName;
};

USTRUCT( BlueprintType )
struct FSessionSaveStruct
{
	GENERATED_BODY()

	FSessionSaveStruct() :
		SessionName( TEXT( "NO_SESSION_ID" ) )
	{
	}
		
	FSessionSaveStruct( SessionNameType sessionName ) :
		SessionName( sessionName )
	{
	}

	/** The name of the session */
	SessionNameType SessionName;

	/** The saves that are in this session */
	UPROPERTY( BlueprintReadOnly )
	TArray< FSaveHeader > SaveHeaders;		
};

UCLASS(Config=Engine)
class UFGSaveSystem : public UObject
{
	GENERATED_BODY()
public:
	/** Initialize our save system, checks for available session ids */
	virtual void Init();

	/** Get the path to the save folder */
	static FString GetSaveDirectoryPath();

	/** All directories to find save data from */
	static void GetSourceSaveDirectoriesPaths( TArray<FString>& out_sourceSaves );

	/** Get the save system from a world */
	static class UFGSaveSystem* Get( class UWorld* world );

	/** Get the save system from a world */
	UFUNCTION( BlueprintPure, Category = "Save", meta = (DisplayName = "GetSaveSystem") )
	static class UFGSaveSystem* Get( class UObject* worldContext );

	/**
	 * Find all available save games from disc
	 *
	 * @param out_saveGames a list with the available save games
	 */
	UFUNCTION( BlueprintCallable, Category = "Save" )
	void FindSaveGames( TArray<FSaveHeader>& out_saveGames, bool newestFirst );

	/**
	* Loops through all save games and group them by session
	* and sorts the saves by dates and then session by last save date
	*/
	UFUNCTION( BlueprintCallable, Category = "Save" )
	void GetAllSavesPerSession( TArray< FSessionSaveStruct >& out_sessions );

	UFUNCTION( BlueprintPure, Category = "Save" )
	bool IsSessionNameUsed( FString sessionName ) const;

	// @todo: Move Widget_PlayMenuAlpha::CheckSessionNameForError to native, so we can verify the error natively too
	
	void AddSessionNameToUsed( FString sessionName );

	/** Helper, used to verify if the save game name is valid */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static bool IsValidSaveName( FString saveName );

	/** Return true if a save gave with the given name exists */
	bool SaveGameExists( FString saveName );
	
	/** Check if a save game exists, if you don't care about session name, pass in empty currentSessionName and check != ESaveExists::SE_DoesntExist */
	UFUNCTION( BlueprintPure, Category = "Save" )
	ESaveExists GetSaveExists( const FString& saveName, const FString& currentSessionName );

	/**
	 * Delete a save game
	 *
	 * @param saveName - the save file's name without extension
	 * @return true if we managed to delete the save
	 */
	UFUNCTION( BlueprintCallable, Category = "Save" )
	bool DeleteSave( FString saveName );

	/**
	 * Converts a save name to a absolute path for a existing save game
	 *
	 * @param saveName - a save game
	 * @param out_absoluteSaveGame - if the function returns true, then the save give outputted here
	 * @return true if we manage to find a valid save game
	 */
	static bool GetAbsolutePathForSaveGame( const FString& saveName, FString& out_absoluteSaveGame );

	/**
	 * Creates a absolute path for a new save game (or when to overwrite a save gave)
	 *
	 * @param saveName - save name without file extension
	 * @return the absolute path of the save
	 */
	static FString CreateAbsolutePath( const FString& saveName );

	/** Sanitize the name of the map, used when saving */
	static FString SanitizeMapName( const FString& mapName );

	/** Generate a new session id and then marks it as used */
	SessionNameType GenerateNewSessionName();

	/**
	 * Look for a new mapname
	 *
	 * @param oldMapName - the old map name
	 * @param out_newMapName - the new map name if one was found
	 *
	 * @return true if the mapname was redirected
	 */
	static bool FindNewMapName( const FString& oldMapName, FString& out_newMapName );

	/**
	* Look for a new classname
	*
	* @param oldClassName - the old class name
	* @param out_newClassName - the new class name if one was found
	*
	* @return true if the classname was redirected
	*/
	static bool FindNewClassName( const FString& oldClassName, FString& out_newClassName );

	/**
	 * Look for a new objectname
	 * 
	 * @param oldName - the old object name
	 * @param out_newName - the new object name if one was found
	 *
	 * @return true if the objectname was redirected
	 */
	static bool FindNewObjectName( const FString& oldObjectName, FString& out_newObjectName );

	/** Set so that we use our internal saves */
	static FORCEINLINE void SetUseBundledSaves( bool useInternal ){ mIsUsingBundledSaves = useInternal; }

	/** Return if we should use internal saves */
	static FORCEINLINE bool IsUsingBundledSaves(){ return mIsUsingBundledSaves; }

	/** If true, then we are in the progress of verifying the save system */
	static FORCEINLINE bool IsVerifyingSaveSystem(){ return mIsVerifyingSaveSystem; }

	/** Set if we are currently verifying the save system, @todo: This should check so that we don't switch at bad times */
	static FORCEINLINE void SetIsVerifyingSaveSystem( bool inVerifying ){ mIsVerifyingSaveSystem = inVerifying; }
protected:
	/** Migrate saves to new save location */
	void MigrateSavesToNewLocation();

	/** Does the actual searching, searches on SaveLocation for save games */
	void FindSaveGames_Internal( const FString& saveDirectory, TArray<FSaveHeader>& out_saveGames );

	/** Convert a filename with a save directory to a filename */
	static FString SaveNameToFileName( const FString& directory, const FString& saveName );

	/** Make sure we can get a world easily */
	class UWorld* GetWorld() const override;
	
	/** Gather up used id's from saves */
	void GatherUsedSaveIds();
protected:
	/** The session id's that used */
	TArray<SessionNameType> mUsedSessionNames;

	/** Redirects for the maps when someone renames a map */
	UPROPERTY( GlobalConfig )
	TArray<FMapRedirector> mMapRedirectors;

	/** We are currently running verification tests on the save system */
	static bool mIsVerifyingSaveSystem;

	/** We are currently using internal saves */
	static bool mIsUsingBundledSaves;
};
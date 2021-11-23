// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "UObject/Object.h"
#include "FGOnlineSessionSettings.h"
#include "FGSaveManagerInterface.h"
#include "FGSaveSystem.generated.h"


DECLARE_DELEGATE_ThreeParams( FOnEnumerateSaveGamesComplete, bool, const TArray<FSaveHeader>&, void* );
DECLARE_DELEGATE_FourParams( FOnEnumerateSessionsComplete, bool Success, const TArray<struct FSessionSaveStruct>& Sessions, int32 CurrentSession, void* UserData );
DECLARE_DELEGATE_TwoParams( FOnDeleteSaveGameComplete, bool, void* );
DECLARE_MULTICAST_DELEGATE( FOnSaveCollectionChanged );

/**
 * Handles the "higher level" save functionality, like listing saves, save directories, sorting saves and validating filenames.
 * A lot of the functionality is static as it doesn't operate on the actual save session, but can be used from anywhere.
 *
 * This interface should only be used when you know you really want to use things that's on the local machine. This is mostly
 * used from FGAdminInterface so that clients call the functionally of the interface and load/save remotely. So consider
 * if the UI should use this interface directly, or if it should go through the admin interface when you are making a
 * BlueprintCallable function in this class.
 */
UCLASS( Config = Engine )
class FACTORYGAME_API UFGSaveSystem : public UObject, public IFGSaveManagerInterface
{
	GENERATED_BODY()
public:
	/** Initialize our save system, checks for available session ids */
	virtual void Init();
	virtual void BeginDestroy() override;
	
	/** Get the path to the save folder */
	static FString GetSaveDirectoryPath();

	/** Get the path to the save folder for EPIC user ID, will return path to common directory if it fails to get EPIC user ID */
	static bool GetUserSaveDirectoryPath( const UWorld* world, FString& out_dirPath );

	/** Get the path to the save folder for saves not connected to an EPIC user ID (offline play, PIE, etc) */
	static FString GetCommonSaveDirectoryPath();

	/** Get the path to save backup folder. This is for storing files outside the Cloud Sync location */
	static FString GetBackupSaveDirectoryPath();

	/** All directories to find save data from */
	static void GetSourceSaveDirectoriesPaths( const UWorld* world, TArray<FString>& out_sourceSaves );

	/** Get the save system from a world */
	static class UFGSaveSystem* Get( class UWorld* world );

	/** Get the save system from a world */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save", meta = (DisplayName = "GetSaveSystem") )
	static class UFGSaveSystem* Get( class UObject* worldContext );

	/**
	 * Find all available save games from disc
	 *
	 * @param out_saveGames a list with the available save games
	 */
	void NativeEnumerateSaveGames( FOnEnumerateSaveGamesComplete onCompleteDelegate, void* userData );

	/**
	 * Find all available save games from disc and groups them into sessions. Also determines which session is the one that is currently loaded in game
	 */
	void NativeEnumerateSessions( FOnEnumerateSessionsComplete onCompleteDelegate, void* userData );

	/**
	 * Synchronous value-returning version of the above
	 **/ 
	TArray<FSaveHeader> NativeEnumerateSaveGames();

	/**
	 * Groups a save list by their corresponding session
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Save" )
	static void GroupSavesPerSession( const TArray< FSaveHeader >& saves, TArray< FSessionSaveStruct >& out_groupedBySession );

	/**
	 * Sort sessions
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Save" )
	static void SortSessions( UPARAM(ref) TArray< FSessionSaveStruct >& sessions, ESaveSortMode sortMode, ESaveSortDirection sortDirection );

	/**
	 * Sort saves
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Save" )
	static void SortSaves( UPARAM(ref) TArray< FSaveHeader >& saves, ESaveSortMode sortMode, ESaveSortDirection sortDirection );

	/**
	 * Get the state we consider the save so we can warn if a save is potentially dangerous to load
	 */
	UFUNCTION( BlueprintPure, Category="FactoryGame|Save" )
	static ESaveState GetSaveState( const FSaveHeader& saveGame );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	bool IsSessionNameUsed( FString sessionName ) const;

	// @todosave: Move Widget_PlayMenuAlpha::CheckSessionNameForError to native, so we can verify the error natively too
	
	void AddSessionNameToUsed( FString sessionName );

	/** Helper, used to verify if the save game name is valid */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static bool IsValidSaveName( FString saveName );

	/** Checks on file system if the save file exists */
	bool SaveGameExistsSync( FString saveName );

	/** Check if a save game exists in the list of saves. if you don't care about session name, pass in empty currentSessionName and check != ESaveExists::SE_DoesntExist */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static ESaveExists GetCachedSaveExists( const TArray<FSaveHeader>& cachedSaves, const FString& saveName, const FString& currentSessionName );

	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static ESaveExists GetCachedSaveExistsInSessions( const TArray<FSessionSaveStruct>& sessions, const FString& saveName, int32 CurrentSession );
	
	/** Get the last result of EnumerateSaves */
	//UFUNCTION( BlueprintPure, Category="FactoryGame|Save")
	FORCEINLINE const TArray<FSaveHeader>& GetCachedSaves() const { return mCachedSaves; }

	/**
	 * Deletes a list of saves, just calls DeleteSaveFile
	 *
	 * @param saveNames - list of the save files without extension
	 * @param completeDelegate - triggers when the file deletion is complete with the result
	 * @param userData - data you want passed to the complete delegate
	 */
	void DeleteSaveFiles( const TArray<FString>& saveNames, FOnDeleteSaveGameComplete completeDelegate, void* userData );

	/**
	 * Converts a save name to a absolute path for a existing save game
	 *
	 * @param saveName - a save game
	 * @param out_absoluteSaveGame - if the function returns true, then the save give outputted here
	 * @return true if we manage to find a valid save game
	 */
	static bool GetAbsolutePathForSaveGame( const UWorld* world, const FString& saveName, FString& out_absoluteSaveGame );

	/**
	 * Creates a absolute path for a new save game (or when to overwrite a save gave)
	 *
	 * @param saveName - save name without file extension
	 * @return the absolute path of the save
	 */
	static FString CreateAbsolutePath( const UWorld* world, const FString& saveName, bool saveInCommonDir );

	/** Sanitize the name of the map, used when saving */
	static FString SanitizeMapName( const FString& mapName );

	/** Generate a new session id and then marks it as used */
	FString GenerateNewSessionName();

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

	/** Moves a save file present in /common/ to the currently logged in player's epic ID folder */
	static bool MoveSaveFileFromCommonToEpicLocation( const UWorld* world, const FString& saveName );

	static bool SaveFileExistsInCommonSaveDirectory( const FString& saveName );


	/** Set so that we use our internal saves */
	static FORCEINLINE void SetUseBundledSaves( bool useInternal ){ mIsUsingBundledSaves = useInternal; }

	/** Return if we should use internal saves */
	static FORCEINLINE bool IsUsingBundledSaves(){ return mIsUsingBundledSaves; }

	/** If true, then we are in the progress of verifying the save system */
	static FORCEINLINE bool IsVerifyingSaveSystem(){ return mIsVerifyingSaveSystem; }

	/** Set if we are currently verifying the save system, @todo: This should check so that we don't switch at bad times */
	static FORCEINLINE void SetIsVerifyingSaveSystem( bool inVerifying ){ mIsVerifyingSaveSystem = inVerifying; }

	/** Get the max number of saves allowed for backup */
	FORCEINLINE int32 GetMaxNumBackupSaves() { return mMaxNumBackupSaves; }

	// IFGSaveManagerInterface overrides
	virtual void EnumerateSessions(const FOnSaveManagerEnumerateSessionsComplete& CompleteDelegate) override;
	virtual bool IsEnumeratingLocalSaves() override;
	virtual bool IsSaveManagerAvailable() override;
	virtual void DeleteSaveFile(const FSaveHeader& SaveGame, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual void DeleteSaveSession(const FSessionSaveStruct& Session, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual void LoadSaveFile(const FSaveHeader& SaveGame, class APlayerController* Player) override;
	virtual void SaveGame(const FString& SaveName, FOnSaveMgrInterfaceSaveGameComplete CompleteDelegate ) override;
	// end IFGSaveManagerInterface overrides
	
	static FOnSaveCollectionChanged OnSaveCollectionChanged;
protected:
	/** 
	* Checks the local backup directory for saves and if their are too many it deletes the oldest ones
	*/
	void BackupSaveCleanup();

	/** Migrate saves to new save location */
	void MigrateSavesToNewLocation( const FString& oldSaveLocation );

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
	TArray<FString> mUsedSessionNames;
	
	/** Last result of EnumerateSaves */
	TArray<FSaveHeader> mCachedSaves;

	/** Redirects for the maps when someone renames a map */
	UPROPERTY( GlobalConfig )
	TArray<FMapRedirector> mMapRedirectors;

	/** Maximum Number of Backup saves (will cull to this number on application startup, not during sessions while saving) */
	UPROPERTY( Config )
	int32 mMaxNumBackupSaves;

	/** We are currently running verification tests on the save system */
	static bool mIsVerifyingSaveSystem;

	/** We are currently using internal saves */
	static bool mIsUsingBundledSaves;

	/** A delegate handle from UFGSaveSystem::FOnSaveCollectionChanged that we need for cleanup purposes */
	FDelegateHandle mOnSaveCollectionUpdatedDelegateHandle;
};

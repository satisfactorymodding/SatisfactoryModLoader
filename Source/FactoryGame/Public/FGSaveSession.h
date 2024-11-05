// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGSaveManagerInterface.h"
#include "FGObjectReference.h"
#include "UObject/Object.h"
#include "Engine/EngineBaseTypes.h"
#include "Engine/TimerHandle.h"
#include "FGSaveSession.generated.h"

// @todosave: Change the FText to a Enum, so server and client can have different localizations
DECLARE_DELEGATE_ThreeParams( FOnSaveGameComplete, bool, const FText&, void* );
DECLARE_DELEGATE_OneParam( FOnLevelPlacedActorDestroyed, AActor* );

FArchive& DeserializeObjectData( FArchive& Ar, TArray<UObject*> &A );

struct FPerBasicLevelSaveData
{
	FPerBasicLevelSaveData() = default;
	
	// @return true if the blob is populated for the level
	FORCEINLINE bool HasBlobData() const { return !TOCBlob.IsEmpty() || !TOCBlob64.IsEmpty(); }

	// @return true if there is any destroyed actors for the level
	FORCEINLINE bool HasDestroyedActors() const{ return DestroyedActors.Num() > 0; }

#if STATS
	// Track how much memory this level contains
	uint32 GetMemoryConsumption() const;
#endif

	/** Blob data to hold the Table of Contents */
	TArray<uint8, TSizedDefaultAllocator<64> > TOCBlob64;
	
	/** Save blob for the level */
	TArray<uint8, TSizedDefaultAllocator<64> > DataBlob64;

	/** Legacy TOC when coming from 32bit */
	TArray<uint8 > TOCBlob;

	/** Legacy Data when coming from 32bit */
	TArray<uint8> DataBlob;

	/** Destroyed actors in the level */
	TArray<struct FObjectReferenceDisc> DestroyedActors;
};

/**
 * Members are pointer as this struct might be moved around in memory as it's in a TMap
 */
struct FPerStreamingLevelSaveData: public FPerBasicLevelSaveData
{
	FPerStreamingLevelSaveData( int32 saveVersion )
		: FPerBasicLevelSaveData()
		, SaveVersion( saveVersion )
		, IsUpToDate( false )
		, IsPersistentLevelData( false )
		, IsRuntimeData( false )
	{
	}

	/** Initalize the save data */
	void PreAllocate( int32 initialBlobSize, int32 estimatedDestroyedActors );

	// @return true if we need to recalculate this when we save the game
	FORCEINLINE bool IsDirty() const{ return !IsUpToDate || IsRuntimeData; }

	/** The save version that this persistent level's TOC blob was serialized with. */
	int32 SaveVersion;
	
	/** If true, then this data is up to date and doesn't need to update before a save to disc */
	uint8 IsUpToDate:1;

	/** If true, then this data represents a persistent level */
	uint8 IsPersistentLevelData:1;

	/** If true, then the data is for a runtime level, and then we don't need the destroyed actors */
	uint8 IsRuntimeData:1;
	
};

/**
* During save games, where object dependencies need to be sorted, we need all world objects that depend on runtime spawned actors
* to be lumped together in the same grouping and put in one blob array. This special data struct is used to combine all persistent
* and runtime data into one struct for serializing. This has to be done this way so that Runtime Spawned Actors can reference Persistent
* world Actors in always loaded levels.
*/
struct FPersistentAndRuntimeSaveData: public FPerBasicLevelSaveData
{
	FPersistentAndRuntimeSaveData() {}

	void ResetBlobData();

	/** Each Persistent (read: AlwaysLoaded) level will get its own entry using its name as the map key.
	 *	Only meaningful in the context of non partitioned worlds. For partitioned worlds, FPerBasicLevelSaveData::DestroyedActors is used instead
	 */
	TMap< FString, TArray< struct FObjectReferenceDisc> > LevelToDestroyedActorsMap;
};

/**
* Struct to holds legacy (pre-sublevel) save data for objects. This struct will be created and modified only when opening old save data.
* As objects are resolved (read, sublevels are streamed in and the objects are resolved) this structs array will shrink
* @todoSave - This will currently continue to collect missing Actors if they get deleted by level designers. I'm actually holding off until 
* the World team and the sublevel changes come together so I can know if we want to do another save version to stop collecting this data.
*/
struct FUnresolvedWorldSaveData
{
	FUnresolvedWorldSaveData() {}

	FORCEINLINE bool HasUnresolvedDestroyedActors() const { return DestroyedActors.Num() > 0; }

	/** Destroyed actors in the level */
	TArray<struct FObjectReferenceDisc> DestroyedActors;

};

/**
* << Overrides to handle the serialization of the custom perlevel and Unresolved Data structs
*/
FArchive& operator<<( FArchive& ar, FPerStreamingLevelSaveData& saveData );
FArchive& operator<<( FArchive& ar, FPersistentAndRuntimeSaveData& saveData );
FArchive& operator<<( FArchive& ar, FUnresolvedWorldSaveData& saveData );

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FSaveWorldImplementationSignature, bool, wasSuccessful, FText, errorMessage );

/**
 * Handles serialization for save and load functionality in a single session. It does the meat of the bones functionality
 * of gathering the objects that's required to save the state of the world in a session.
 *
 * @todosave: Separate this into a base class UFGSaveBase. As we most likely want to be able to be able to store some persistent
 * player progression also (like, amount of foliage gathered over all sessions, if you have unlocked some special skin etc). This
 * save would be nice if it could be done the exact same way. What would differ then is that progression files: "SaveWorldImplementation".
 *
 * Most important function is LoadGame and SaveWorldImplementation. Neither of these
 * should be called directly, but from their respective chains.
 *
 * LoadGame comes from: AFGGameMode::InitGameState, and is required to come from there as that before BeginPlay has been called,
 * but after all objects has been loaded into memory in a map.
 *
 * If you want to call SaveWorldImplementation, call SaveGame instead. It will ensure that SaveWorldImplementation is called at end of frame, so that all actors
 * has been ticked the same amount of times and that we don't half a frame of ticked actors saved.
 */
UCLASS(Config=Engine)
class FACTORYGAME_API UFGSaveSession : public UObject
{
	GENERATED_BODY()
public:
	UFGSaveSession();
	~UFGSaveSession();

	// Begin UObject interface
	virtual void BeginDestroy() override;
	// End UObject interface

	/** Get the save version of a header */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE int32 GetVersion( UPARAM(ref) FSaveHeader& header ){ return header.SaveVersion; }

	/** Get the build version this save was saved with */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE int32 GetBuildVersion( UPARAM( ref ) FSaveHeader& header ) { return header.BuildVersion; }

	/** Get the map that this save was saved with */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FString GetMapName( UPARAM( ref ) FSaveHeader& header ) { return header.MapName; }

	/** Get the options that this save was saved with */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FString GetMapOptions( UPARAM( ref ) FSaveHeader& header ) { return header.MapOptions; }

	/** The name of the save game */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FString GetName( const FSaveHeader& header ) { return header.SaveName; } // <FL> [WuttkeP] Removed UPARAM(ref) so the function can be called with const instances.

	/** The session ID of the save game */
	UE_DEPRECATED( 4.20, "Use GetSessionName instead" )
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSessionName instead") )
	static FORCEINLINE FString GetSessionID( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The session name of the save game */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FString GetSessionName( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The play duration */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE int32 GetPlayDurationSeconds( UPARAM( ref ) FSaveHeader& header ) { return header.PlayDurationSeconds; }

	/** The time this was saved */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FDateTime GetSaveDateTime( UPARAM( ref ) FSaveHeader& header ) { return header.SaveDateTime; }

	/** Returns Metadata from save header */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session" )
	static FORCEINLINE FString GetLoadedHeaderMetadata( UPARAM( ref ) FSaveHeader& header ) { return header.ModMetadata; }

	/** Returns whether or not this save has ever been saved with mods */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session" )
	static FORCEINLINE bool GetIsModded( UPARAM( ref ) FSaveHeader& header ) { return header.IsModdedSave; }

	/** Returns if creative mode is enabled for this save */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session" )
	static FORCEINLINE bool GetIsCreativeModeEnabled( UPARAM( ref ) FSaveHeader& header ) { return header.IsCreativeModeEnabled; }


	/** Returns the name of this session */
	UE_DEPRECATED( 4.20, "Use GetSaveSessionName instead" )
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSaveSessionName instead")  )
	static FORCEINLINE FString GetSaveSessionID( UPARAM( ref ) FSessionSaveStruct& session ) { return session.SessionName; }

	/** Returns the name of this session */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session" )
	static FORCEINLINE FString GetSaveSessionName( UPARAM( ref ) FSessionSaveStruct& session ) { return session.SessionName; }

	/**
	 * Initialize the save system,
	 *
	 * @param willLoad - we will later on get a LoadGame call
	 */
	void Init( bool willLoad, class AFGGameMode* gameMode );

	/** Called when auto save interval option is updated */
	UFUNCTION()
	void OnAutosaveIntervalUpdated( FString cvar );

	/** Cleans up the save session properly */
	void Cleanup();

	/** Get the save system from a world */
	static class UFGSaveSession* Get( class UWorld* world );

	/** Get the save system from a world */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save", meta = (DisplayName = "GetSaveSession") )
	static class UFGSaveSession* Get( class UObject* worldContext );

	/** Run post load on all loaded objects */
	void RoutePostLoadGame();

	/**
	 * Starts off the chain that triggers a save, save won't happen immidiately, but at end of frame
	 * to ensure that we don't save a incorrect state (i.e, half the worlds actors is ticked)                                                                  
	 *
	 * @param fileName - a valid filename that we want to save the game to
	 * @param return true if the file name is a valid file name
	 */
	void SaveGame( const FString& fileName, FOnSaveGameComplete completeDelegate, void* userData );
	
	/**
	 * Reads the raw save game data that can the be used for example in a load.
	 *
	 * @param saveName - name of the save to read the save game data for
	 * @param out_rawSaveData - the data that was read.
	 * @return true if the data was read successfully
	 */
	bool ReadRawSaveGameData( const FString& saveGameName, TArray< uint8 >& out_rawSaveData ) const;

	/**
	 * Starts loading a game
	 *
	 * @param saveName - the save file's name without extension
	 * @return true if a save game with that name exists and load happend successfully
	 */
	bool LoadGame( const FString& saveName );

	/** Get the number of rotating autosaves */
	FORCEINLINE uint8 GetNumRotatingAutosaves() const{ return mNumRotatingAutosaves; }

	/**
	 * Serializes the header data while validating the format
	 *
	 * @param Ar the archive serializing to/from
	 * @param FSaveHeader the information we store in the save file
	 *
	 * @return false if we try to load a old header or if we can't load from a ar, true otherwise
	 */
	static bool SerializeHeader( FArchive& Ar, FSaveHeader& saveHeader );

	/** Retrieves just the header for any valid save file. Returns true/false if it manages to read the header. */
	static bool PeekAtFileHeader( const FString& fullFilePath, FSaveHeader& out_fileHeader ); // <FL> [WuttkeP] Made this function static.


	/** Converts a saveName to a file name */
	static FString SaveNameToFileName( const FString& saveName );
	
	static FObjectReferenceDisc FixupObjectReferenceForPartitionedWorld( const FObjectReferenceDisc& Reference, const class AFGWorldSettings& WorldSettings );

	/** Called every time by timer to trigger a autosave. Can be called manually if we want to trigger a autosave for key events */
	UFUNCTION()
	void Autosave();

	/** Gets the autosave interval */
	FORCEINLINE int32 GetAutosaveInterval(){ return mAutosaveInterval; }

	/** Updates the autosave interval */
	void SetAutosaveInterval( int32 newInterval );

	UFUNCTION( BlueprintCallable, Category = "Factory Game|Save")
	void SetAutoSaveEnabled( bool enabled );

	/** Returns true if we have a save game operation pending (e.g. we are about to perform a save on game thread, or we are waiting for the background compression/file system write to be done) */
	FORCEINLINE bool HasSaveGameOperationPending() const { return mSaveOperationIsPending; }

	/** Set the ModMetadata. This does not append. If you wish to append, use the getter and manually append whatever data you desire to the existing */
	UFUNCTION( BlueprintCallable, Category="Factory Game|SaveSession" )
	void SetModMetadata( FString newMetadata ) { mModMetadata = newMetadata; }

	/** Set the ModMetadata. This does not append. If you wish to append, use the getter and manually append whatever data you desire to the existing */
	UFUNCTION( BlueprintPure, Category = "Factory Game|SaveSession" )
	FORCEINLINE FString GetModMetadata() { return mModMetadata; }

	/** Returns the unique identifier for this save. */
	FORCEINLINE FString GetSaveIdentifier() { return mSaveHeader.SaveIdentifier; }

	/** Logs all Unresolved object references stored in the Destroyed Actors array */
	void DumpUnresolvedDestroyedActors();

	/** Purges the list of unresolved destroyed actors */
	void PurgeUnresolvedDestroyedActors();

	/** Exposed for scannable subssytem */
	const FUnresolvedWorldSaveData& GetUnresolvedWorldSaveData() const { return mUnresolvedWorldSaveData; }
	const TMap< FString, TUniquePtr<FPerStreamingLevelSaveData> >& GetPerLevelDataMap() const { return mPerLevelDataMap; }

protected:
	friend class AFGBlueprintSubsystem;
	
	// Load a save game that was created before the LevelStreaming save era
	bool LoadPreLevelStreamingSave( FString saveName );

	/** Called whenever a level is added to the world, used to expand the list with actors to save */
	UFUNCTION()
	void OnLevelAddedToWorld( ULevel* inLevel, UWorld* inWorld );

	/** Called whenever a level is removed from the world, used to make the list smalled with the actors to save */
	UFUNCTION()
	void OnLevelRemovedFromWorld( ULevel* inLevel, UWorld* inWorld );

	/** Called when a level placed save actor placed in the level is destroyed */
	UFUNCTION()
	void OnLevelPlacedActorDestroyed( AActor* destroyedActor );

	/** Called when a runtime spawned save actor is destroyed */
	UFUNCTION()
	void OnRuntimeSpawnedActorDestroyed( AActor* destroyedActor );

	/** Called when a new actor is spawned */
	UFUNCTION()
	void OnActorSpawned( AActor* spawnedActor );

	/**
	 * If passed a valid level, saves the levels state. Otherwise it saves the persistent/runtime world state
	 * @param forLevel - The level we want to save the state of. If nullptr, then all AlwaysLoaded and Runtime Data is saved.
	 * @param markAsUpToDate - If true then the perLevelData will be marked as up to date. This is not desired when triggering a world save (as those levels may still be loaded)
	*/
	void SaveLevelState( ULevel* forLevel, bool markAsUpToDate = true );
	
	/**
	* Clears all memory allocations and resets the Persistent/Runtime data state
	*/
	void CleanupPerLevelData();

	/**
	* A Helper function that returns a Map of only StreamingLevels and their PerLevelSaveData. Is used during SaveWorldImplementation() to filter out Always Loaded / Persistent level data
	*/
	FORCEINLINE void GetStearmingLevelDataMap( TMap< FString, FPerStreamingLevelSaveData* >& out_data );

	/**
	* A helper function that will call GetLevelSaveData( const FString& levelName, bool isPersistent )
	* @param level - The level to retrive the FPerLevelSaveData for.
	*/
	FPerStreamingLevelSaveData& GetLevelSaveData( ULevel* level );

	/** 
	* Will return the FPerLevelSaveData that matches the given the passed level name. If one is not found it will be created
	* @param levelName - The full level name of the level to use as the key to look up in the mPerLevelSaveData map
	* @param isPersistent - If this is a persistent level or and always loaded level. This is important for determining how the level data is serialized during a save
	*/
	FPerStreamingLevelSaveData& GetLevelSaveData( const FString& levelName, bool isPersistent );

	/** 
	 * Deletes a existing save of the session id that has that autosave number
	 * @param sessionName - the session we want to delete
	 * @param autosaveNum - the autosave number of that save session to delete
	 */
	void DeleteSave( FString sessionName, int32 autosaveNum );

	/** Generate the next autosave name, calling this twice will give you different results */
	FString GenerateAutosaveName( int32& out_autosaveNum, const FString& sessionName );

	/** Get the full map name */
	FString GetFullMapName() const;

	/** Setup the autosave timer */
	void SetupAutosave();
	
	/** Check if we should broadcast an auto save notification and potentially start a new notification timer */
	void CheckAutoSaveNotificationTimer();

	/**
	 * Sort the object list so that objects always have their dependencies first
	 *
	 * @param io_objectsToSerialize - the object list to sort
	 */
	void SortObjectsByDependency( TArray< UObject* >& io_objectsToSerialize );

	/**
	 * Traces from a rootobjects and finds all children from that root that implements the FGSaveInterface
	 *
	 * @param level - the level objects in which we are collecting. References to objects outside of that level will be ignored. If null, persistent level is assumed
	 * @param rootSet - the base objects
	 * @param out_objectsToSerialize - A reference to the array that holds all the objects we want to serialize
	 */
	void CollectObjects( UWorld* world, ULevel* level, TArray<UObject*>& rootSet, TArray< UObject* >& out_objectsToSerialize );

	/**
	 * Generate root set of objects to be saved for a level
	 */
	void GenerateRootSet( class ULevel* level, TArray<UObject*>& out_rootSet );

	/** Destroy actors that's marked for destroy in the levels FPerLevelSaveData::DestroyedActors */
	void LoadDestroyActors( ULevel* level );

	/** Load legacy Destroyed actors (this will also create the neccessary migration data to resolve destroyed actors when loading in sublevels) */
	void LoadLegacyDestroyedActors();

	/**
	* Called when deserializing level states to attempt to remove legacy (potentially migrated) destroyed actors with new levels as their outer 
	* 
	* @return - The number of successfully resolved Destroyed Actors
	*/
	int32 TryResolveLegacyDestroyedActors( class ULevel* level );

	/**
	 * Prepare Level Designer-placed actors for the load system in the specified level
	 * @param level - the level we want to load from
	 * @param prepareForLoad - prepare the actors for a load so that they generate overlaps etc
	 **/
	void PrepareLevelActors( ULevel* level, bool prepareForLoad );

	/**
	 * Read the state for all the actors in the level
	 *
	 * @param level - level we want to get the state from
	 */
	void DeserializeStreamingLevelState( ULevel* level );

	/**
	* Read the sate for all actors in persistent levels and the runtime level state
	*/
	void DeserializePersistentAndRuntimeState();

	// Debug function, makes sure that we are gathering all actors when saving
	void MakeSureAllActorsAreSaved();
public:
	/** Used to optimize checking for redirects on GameMode and GameState to avoid casting checks after they have already been resolved */
	inline static int32 mRedirectedSingletonCount = 0;

	/** This static map is used to store temporary serialized versions of objects so that PostLoadGame can execute knowing the version the object was deserialized with */
	inline static TMap< UObject*, int32 > mObjectToSerailizedVersion = TMap< UObject*, int32 >();
	
	/** Delegate that listens for when level placed actor is destroyed */
	FOnLevelPlacedActorDestroyed mOnLevelPlacedActorDestroyed;

	static TArray< AActor* > GatherSaveActors( ULevel* level );
protected:
	// Map with unique data for each level
	TMap< FString, TUniquePtr<FPerStreamingLevelSaveData> > mPerLevelDataMap;

	/** Data for the data spawned runtime - This represents the actors that are spawned at runtime and has no correlation to a streaming level 
	 * @note - All other FPerLevelSaveData will have IsRuntimeData == false.
	 * @todoNOW - After refactoring the way world / always loaded levels are handled I believe this is unused. Delete / Clean up if so.
	 */
	FPerStreamingLevelSaveData mRuntimeLevelState{ -1 };

	/** Data used when saving the level state of the persistent worlds and runtime data. They get merged into one block of data */
	FPersistentAndRuntimeSaveData mPersistentAndRuntimeData;

	/** Struct to hold the information about actors that are present in a save but fail to resolve (likely because they have been moved to a streaming level) */
	FUnresolvedWorldSaveData mUnresolvedWorldSaveData;

	/** Objects that has been runtime spawned */
	UPROPERTY()
	TArray< class AActor* > mSpawnedActors;

	/** Objects that have been loaded per level */
	TMap< ULevel*, TArray< class UObject* > > mPerStreamingLevelLoadedObjects;

	/** Objects that have been loaded either from runtime state or a persistent level */
	TArray< class UObject* > mPersistentAndRuntimeLoadedObjects;

	/** For Legacy Saves to deserialize the Destroyed actor list into */
	TArray< FObjectReferenceDisc > mLegacyDestroyedActors;

	/** For Legacy Saves to deserialize the Destroyed actor list into */
	TArray< class UObject* > mLegacyLoadedObjects;

	/** Cached save header from last save game */
	FSaveHeader mSaveHeader;

	/** Timer holding the autosave timer */
	FTimerHandle mAutosaveHandle;

	/** Timer holding the autosave notification timer */
	FTimerHandle mAutosaveNotificationHandle;

	/** How much time there should be left on the auto save timer when the next auto save notification should be broadcasted  */
	float mNextAutoSaveNotificationTiming;

	/** Delegate that listens for when the save is done */
	FOnSaveGameComplete mOnSaveCompleteDelegate;

	/** User data to pass to on save complete delegate */
	void* mSaveCompleteUserData = nullptr;

	/** Handle with the on actor spawn stuff */
	FDelegateHandle mOnActorSpawnHandle;

	/** How often in seconds to autosave, a value of < 0 means disabled */
	UPROPERTY( Transient )
	float mAutosaveInterval;

	/** Whether or not auto save is enabled. */
	UPROPERTY( Transient )
	bool mAutosaveEnabled;

	/** The number of autosaves to rotate */
	UPROPERTY( Config )
	int32 mNumRotatingAutosaves;

	/** Name of the save that will be saved at end of frame */
	FString mPendingSaveName;

	/** True if there is currently a save operation pending, either in background or in game thread at the end of the world tick */
	bool mSaveOperationIsPending{false};
	/** Is pending save an auto save? */
	bool mPendingSaveIsAuto{false};
	/** Callback to end of frame to be removed after save */
	FDelegateHandle mPendingSaveWorldHandle;

	/** Cached ModMetadata - This is cached when loading a save from the loaded SaveHeader. Use the getter/setter to modify this property. 
	*	This is the value that will be written to metadata next save.
	*/
	FString mModMetadata;

private:
	// We want the game state to be able to trigger save games properly without exposing the nitty gritty details to the interface
	friend class AFGGameMode;
	// The map editor utility needs private access to avoid over exposing these functions
	friend class UFGMapUtility;
	friend class FWPSaveDataMigrationContext;
	friend class FFGSaveSystemBackgroundSaveGameAsyncTask;

	/** Called after actor ticking so we can save when all actors have been saved */
	void SaveWorldEndOfFrame( class UWorld* world, ELevelTick, float );
	void SaveWorldImplementation( const FString& gameName );

	/** Called to initiate the background save compression and file system write operation. */
	void StartBackgroundSave( const FString& fullFilePath, class FBufferArchive64&& memArchive, const FSaveHeader& saveHeader );

	/** SaveToDiskWithCompression
	 * Saves the current session at the given absolute file location. The file's contents will be compressed
	 * with the ZLIB compression (27-08-2019). Important to note is that the header for save file will not
	 * be compressed as it is read from the game on demand. 
	 *
	 * Binary File structure is as follows:
	 * [[FSaveHeader(uncompressed)], [SaveWorld(compressed)]]
	 *
	 * @param saveSession - save session that owns this background save operation
	 * @param fullFilePath - The absolute file path to the file location to save.
	 * @param memArchive - The SaveWorld archive containing data to be compressed.
	 * @param saveHeader - The FSaveHeader containing header data for the save file, will not be compressed.
	 */
	static void SaveToDiskWithCompressionInBackground( const TWeakObjectPtr<UFGSaveSession>& saveSession, const FString& fullFilePath, class FBufferArchive64& memArchive, FSaveHeader& saveHeader, bool bIsAutoSave, bool bAllowSaveBackups );

	/** Called when background save operation is completed to finish the work on the main thread. This function will be called on background thread and should schedule it's own execution on main thread itself */
	static void CompleteBackgroundSave( const TWeakObjectPtr<UFGSaveSession>& saveSession, bool bResult, const FText& ErrorMessage );
	/** Called on game thread to complete the background saving operation */
	void CompleteBackgroundSaveOnGameThread( bool bResult, const FText& ErrorMessage );
	
	/** Loads a save file that has been compressed. This includes serializing the SaveHeader. */
	bool LoadCompressedFileFromDisk( const FString& saveGameName );

	/** Loads a save file prior to compressed save versions. This includes serializing the SaveHeader. */
	bool LoadDeprecatedFileFromDisk( const FString& saveGameName );

	/**
	* Serializes the Save Session from a loaded and decompressed archive.
	* @param memArchive - A loaded archive (excluding the header) that is used to serialize the session.
	* @param includesSaveHeader - Whether or not the archive parameter contains the SaveHeader (which will also be serialized in this case)
	*/
	bool SerializeLoadedObjects( FArchive& memArchive, bool includesSaveHeader );

	/**
	* Serializes a save file that was saved before sublevel saving was introduced
	*/
	bool SerializeLoadedObjectsLegacy( FArchive& memArchive );

	void BundledSaveWorldImplementation( FString gameName );

	/** Collection of all Uobjects gathered while saving. Will only be filled if strict save checking is enabled*/
	TArray<AActor*> mAllCollectedSaveActors;

};

FORCEINLINE void UFGSaveSession::GetStearmingLevelDataMap( TMap< FString, FPerStreamingLevelSaveData* >& out_data )
{
	for( TPair< FString, TUniquePtr<FPerStreamingLevelSaveData> >& data : mPerLevelDataMap )
	{
		if( ( data.Value )->IsPersistentLevelData == false )
		{
			out_data.Add( TPair< FString, FPerStreamingLevelSaveData* >( data.Key, data.Value.Get() ) );
		}
	} 
}

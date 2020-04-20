// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Serialization/BufferArchive.h"
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "Object.h"
#include "UObject/Interface.h"
#include "FGSaveSystem.h"
#include "FGObjectReference.h"
#include "Engine/EngineTypes.h"
#include "FGSaveSession.generated.h"

// @todosave: Change the FText to a Enum, so server and client can have different localizations
DECLARE_DELEGATE_ThreeParams( FOnSaveGameComplete, bool, const FText&, void* );

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
	static FORCEINLINE FString GetName( UPARAM( ref ) FSaveHeader& header ) { return header.SaveName; }

	/** The session ID of the save game */
	UE_DEPRECATED( 4.20, "Use GetSessionName instead" )
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSessionName instead") )
	static FORCEINLINE FString GetSessionID( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The session name of the save game */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FString GetSessionName( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The name of the save game */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE int32 GetPlayDurationSeconds( UPARAM( ref ) FSaveHeader& header ) { return header.PlayDurationSeconds; }

	/** The time this was saved */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save" )
	static FORCEINLINE FDateTime GetSaveDateTime( UPARAM( ref ) FSaveHeader& header ) { return header.SaveDateTime; }

	/** Returns saved visibility of the session */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Save Session" )
	static FORCEINLINE TEnumAsByte<ESessionVisibility> GetSaveSessionVisibility( UPARAM( ref ) FSaveHeader& header ) { return header.SessionVisibility; }

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
	void Init( bool willLoad );

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


	/** Converts a saveName to a file name */
	static FString SaveNameToFileName( const FString& saveName );

	/**
	 * Called by shared inventory code to report that a shared inventory pointer has been loaded.
	 * Used to verify that no actor has several references.
	 */
	static void SharedInventoryPtrLoaded( struct FSharedInventoryStatePtr& ptr );

	/** Called every time by timer to trigger a autosave. Can be called manually if we want to trigger a autosave for key events */
	UFUNCTION()
	void Autosave();

	/** Gets the autosave interval */
	FORCEINLINE int32 GetAutosaveInterval(){ return mAutosaveInterval; }

	/** Updates the autosave interval */
	void SetAutosaveInterval( int32 newInterval );

	/** Returns true if we have called SaveGame this frame */
	FORCEINLINE bool HasTriggedSaveThisFrame() const { return mPendingSaveWorldHandle.IsValid(); }
protected:
	/** Make sure we can get a world easily */
	class UWorld* GetWorld() const override;

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
	 * @param rootSet - the base objects
	 * @param out_objectsToSerialize - A reference to the array that holds all the objects we want to serialize
	 */
	void CollectObjects( TArray<UObject*> rootSet, TArray< UObject* >& out_objectsToSerialize );

	/**
	 * Traces from a rootobject and finds all children from that root that implements the FGSaveInterface
	 *
	 * @param rootObject - the base object
	 * @param out_objectsToSerialize - A reference to the array that holds all the objects we want to serialize
	 */
	void CollectObjects( UObject* rootObject, TArray< UObject* >& out_objectsToSerialize );

	/**
	 * Generate the root set of objects
	 */
	void GenerateRootSet( TArray<UObject*>& out_rootSet );

	/** Destroy actors in mDestroyedActors list */
	void LoadDestroyActors();

	/**
	 * Prepare Level Designer-placed actors for a game
	 * @param prepareForLoad - prepare the actors for a load game
	 **/
	void PrepareLevelActors( bool prepareForLoad );

	/** Called when a save actor placed in the level is destroyed */
	UFUNCTION()
	void OnActorDestroyed( AActor* destroyedActor );
protected:
	/** Actors in the world that's destroyed */
	TArray< FObjectReferenceDisc > mDestroyedActors;

	/** Objects that has been loaded */
	TArray< class UObject* > mLoadedObjects;

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

	/** How often in seconds to autosave, a value of < 0 means disabled */
	UPROPERTY( Transient )
	float mAutosaveInterval;

	/** The number of autosaves to rotate */
	UPROPERTY( Config )
	int32 mNumRotatingAutosaves;

	/** Name of the save that will be saved at end of frame */
	FString mPendingSaveName;
	
	/** Callback to end of frame to be removed after save */
	FDelegateHandle mPendingSaveWorldHandle;
private:
	// We want the game state to be able to trigger save games properly without exposing the nitty gritty details to the interface
	friend class AFGGameMode;

	/** Called after actor ticking so we can save when all actors have been saved */
	void SaveWorldEndOfFrame( class UWorld* world, ELevelTick, float );
	void SaveWorldImplementation( const FString& gameName );

	/** SaveToDiskWithCompression
	 * Saves the current session at the given absolute file location. The file's contents will be compressed
	 * with the ZLIB compression (27-08-2019). Important to note is that the header for save file will not
	 * be compressed as it is read from the game on demand. 
	 *
	 * Binary File structure is as follows:
	 * [[FSaveHeader(uncompressed)], [SaveWorld(compressed)]]
	 *
	 * @param fullFilePath - The absolute file path to the file location to save.
	 * @param memArchive - The SaveWorld archive containing data to be compressed.
	 * @param saveHeader - The FSaveHeader containing header data for the save file, will not be compressed.
	 * 
	 * @return bool - Returns true if file was successfully compressed and saved.
	 */
	bool SaveToDiskWithCompression(const FString& fullFilePath, FBufferArchive& memArchive, FSaveHeader& saveHeader );
	
	/** Loads a save file that has been compressed. This includes serializing the SaveHeader. */
	bool LoadCompressedFileFromDisk( const FString& saveGameName );

	/** Loads a save file prior to compressed save versions. This includes serializing the SaveHeader. */
	bool LoadDeprecatedFileFromDisk( const FString& saveGameName );

	/** Retrieves just the header for any valid save file. Returns true/false if it manages to read the header. */
	bool PeekAtFileHeader( const FString& fullFilePath, FSaveHeader& out_fileHeader ) const;

	/**
	* Serializes the Save Session from a loaded and decompressed archive.
	* @param memArchive - A loaded archive (excluding the header) that is used to serialize the session.
	* @param includesSaveHeader - Whether or not the archive parameter contains the SaveHeader (which will also be serialized in this case)
	*/
	bool SerializeLoadedObjects( FArchive& memArchive, bool includesSaveHeader );
	void BundledSaveWorldImplementation( FString gameName );
};

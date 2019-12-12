// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FSaveWorldImplementationSignature, bool, wasSuccessful, FText, errorMessage );

/**
 * Handles serialization for save and load functionality
 */
UCLASS(Config=Engine)
class FACTORYGAME_API UFGSaveSession : public UObject
{
	GENERATED_BODY()
public:
	UFGSaveSession();
	~UFGSaveSession();

	/** Get the save version of a header */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE int32 GetVersion( UPARAM(ref) FSaveHeader& header ){ return header.SaveVersion; }

	/** Get the build version this save was saved with */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE int32 GetBuildVersion( UPARAM( ref ) FSaveHeader& header ) { return header.BuildVersion; }

	/** Get the map that this save was saved with */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FString GetMapName( UPARAM( ref ) FSaveHeader& header ) { return header.MapName; }

	/** Get the options that this save was saved with */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FString GetMapOptions( UPARAM( ref ) FSaveHeader& header ) { return header.MapOptions; }

	/** The name of the save game */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FString GetName( UPARAM( ref ) FSaveHeader& header ) { return header.SaveName; }

	/** The session ID of the save game */
	DEPRECATED( 4.20, "Use GetSessionName instead" )
	UFUNCTION( BlueprintPure, Category = "Save", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSessionName instead") )
	static FORCEINLINE FString GetSessionID( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The session name of the save game */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FString GetSessionName( UPARAM( ref ) FSaveHeader& header ) { return header.SessionName; }

	/** The name of the save game */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE int32 GetPlayDurationSeconds( UPARAM( ref ) FSaveHeader& header ) { return header.PlayDurationSeconds; }

	/** The time this was saved */
	UFUNCTION( BlueprintPure, Category = "Save" )
	static FORCEINLINE FDateTime GetSaveDateTime( UPARAM( ref ) FSaveHeader& header ) { return header.SaveDateTime; }

	/** Returns saved visibility of the session */
	UFUNCTION( BlueprintPure, Category = "Save Session" )
	static FORCEINLINE TEnumAsByte<ESessionVisibility> GetSaveSessionVisibility( UPARAM( ref ) FSaveHeader& header ) { return header.SessionVisibility; }

	/** Returns the name of this session */
	DEPRECATED( 4.20, "Use GetSaveSessionName instead" )
	UFUNCTION( BlueprintPure, Category = "Save Session", meta = (DeprecatedFunction, DeprecationMessage = "Use GetSaveSessionName instead")  )
	static FORCEINLINE FString GetSaveSessionID( UPARAM( ref ) FSessionSaveStruct& session ) { return session.SessionName; }

	/** Returns the name of this session */
	UFUNCTION( BlueprintPure, Category = "Save Session" )
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
	UFUNCTION( BlueprintPure, Category = "Save", meta = (DisplayName = "GetSaveSession") )
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
	UFUNCTION( BlueprintCallable, Category = "Save" )
	bool SaveGame( FString fileName );

	
	/**
	 * Reads the raw save game data that can the be used for example in a load.
	 *
	 * @param saveName - name of the save to read the save game data for
	 * @param out_rawSaveData - the data that was read.
	 * @return true if the data was read successfully
	 */
	bool ReadRawSaveGameData( FString saveGameName, TArray< uint8 >& out_rawSaveData );

	/**
	 * Starts loading a game
	 *
	 * @param saveName - the save file's name without extension
	 * @return true if a save game with that name exists and load happend successfully
	 */
	UFUNCTION( BlueprintCallable, Category = "Save" )
	bool LoadGame( FString saveName );

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

	/** Delegate to listen for the result of the SaveWorldImpelementation */
	UPROPERTY( BlueprintAssignable, Category = "Save" )
	FSaveWorldImplementationSignature mOnSaveWorld;

	/** Called every time by timer to trigger a autosave. Can be called manually if we want to trigger a autosave for key events */
	UFUNCTION()
	void Autosave();

	/** Gets the autosave interval */
	FORCEINLINE int32 GetAutosaveInterval(){ return mAutosaveInterval; }

	/** Updates the autosave interval */
	void SetAutosaveInterval( int32 newInterval );

protected:
	/** 
	 * Deletes a existing save of the session id that has that autosave number
	 * @param sessionName - the session we want to delete
	 * @param autosaveNum - the autosave number of that save session to delete
	 */
	void DeleteSave( FString sessionName, int32 autosaveNum );

	/** Make sure we can get a world easily */
	class UWorld* GetWorld() const override;

	/** Generate the next autosave name, calling this twice will give you different results */
	FString GenerateAutosaveName( int32& out_autosaveNum, FString sessionName );

	/** Get the full map name */
	FString GetFullMapName() const;

	/** Setup the autosave timer */
	void SetupAutosave();

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

	/** How often in seconds to autosave, a value of < 0 means disabled */
	UPROPERTY( Transient )
	float mAutosaveInterval;

	/** The number of autosaves to rotate */
	UPROPERTY( Config )
	int32 mNumRotatingAutosaves;
private:
	// We want the game state to be able to trigger save games properly without exposing the nitty gritty details to the interface
	friend class AFGGameMode;
	void SaveWorldImplementation( FString gameName );
	void BundledSaveWorldImplementation( FString gameName );
};

// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"
#include "Engine/World.h"
#include "FGSaveSystem.h"
#include "GameFramework/GameMode.h"
#include "FGSaveInterface.h"
#include "FGGameMode.generated.h"

class UFGRemoteCallObject;

UCLASS(minimalapi, config = Game )
class AFGGameMode : public AGameMode, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGGameMode();

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	// Begin AFGGameModeBase interface
	virtual void FinishRestartPlayer( AController* NewPlayer, const FRotator& StartRotation );
	virtual void InitGame( const FString& mapName, const FString& options, FString& out_errorMessage ) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation( AController* newPlayer, const FTransform& spawnTransform ) override;
	virtual void InitGameState() override;
	virtual bool AllowCheats( APlayerController* p );
	virtual AActor* ChoosePlayerStart_Implementation( AController* player ) override;
	virtual void RestartPlayer( AController* newPlayer ) override;
	virtual void PostLogin( APlayerController* newPlayer ) override;
	virtual void Logout( AController* exiting ) override;
	// End AGameModeBase interface

	/** All actors initialized, notify the save system */
	void PostActorsInitialized( const UWorld::FActorsInitializedParams& inParams );

	/** Get the current options we started the map with */
	const FString& GetCurrentOptions() const{ return mOptions; }

	/** Generate the next autosave id */
	uint8 GenerateNextAutosaveId();

	/** Get the session id of our current session */
	FORCEINLINE SessionNameType GetSaveSessionName() const{ return mSaveSessionName; }

	/** Kick a player from the game */
	UFUNCTION(BlueprintCallable, Category="Online")
	void KickPlayer( APlayerState* ps );

	/** Set the session id of our current session */
	void SetSaveSessionName( SessionNameType name );

	/** Get the save system */
	FORCEINLINE class UFGSaveSession* GetSaveSession() const{ return mSaveSession; }

	/** Get the length of the day parsed from the game options */
	FORCEINLINE float GetDayLength() const{ return mDayLength; }

	/** Get the length of the night parsed from the game options */
	FORCEINLINE float GetNightLength() const{ return mNightLength; }

	/** Does this Game Mode function specifically as the main menu? */
	FORCEINLINE bool IsMainMenuGameMode() const { return mIsMainMenu; }

	/** Returns true if we should setup save for this gamemode */
	virtual bool ShouldSetupSave() const;

	/**
	 * Get the capsule size of the the default player pawn
	 *
	 * @param world - the world we want to get this default from
	 * @param out_capsuleRadius - radius of capsule
	 * @param out_capsuleRadius - half height capsule
	 * @return false if there is no default player class
	 */
	static bool GetDefaultPlayerCapsuleSize( UWorld* world, float& out_capsuleRadius, float& out_capsuleHalfHeight );

	/** Debugging stuffs */
	void Debug_SetStartingPoint( FName startingPoint ) { mDebugStartingPointTagName = startingPoint; }


	UFUNCTION( BlueprintPure, Category = "Remote Call Object" )
	bool RegisterRemoteCallObjectClass( TSubclassOf< UFGRemoteCallObject > inClass );

	void RegisterCallObjectOnAllCurrentPlayers( TSubclassOf<UFGRemoteCallObject> inClass );

public:
	/** Name of the start location option that is parsed */
	static const TCHAR* StartLocationOption;
protected:
	/** Trigger a save to save the world */
	UFUNCTION( exec )
	void TriggerWorldSave( FString saveGameName );

	/** Trigger a save to save the world */
	UFUNCTION( exec )
	void TriggerBundledWorldSave( FString saveGameName );

	/**
	 * If return true, then this is a pawn that we can take control of during spawning, else it's not valid
	 * for some reason (dead maybe)
	 */
	bool IsValidPawnToReclaim( APawn* pawn ) const;
private:
	/**
	 * Caches the player starts by PlayerStartTag as the key.
	 * @return Play from here player start, if found; otherwise nullptr.
	 */
	class APlayerStart* CachePlayerStarts( TMap< FName, TArray< class APlayerStart* > >& out_playerStarts );

	void PartitionPlayerStartsByOccupancy(
		const TArray< class APlayerStart* >& playerStarts,
		TSubclassOf< class APawn > pawnClassToFit,
		TArray< class APlayerStart* >& out_unOccupied,
		TArray< class APlayerStart* >& out_occupied );
protected:
	UPROPERTY()
	class UFGSaveSession* mSaveSession;
private:
	struct FLoadData
	{
		bool IsValidLoad;
		FString LoadName;
	} mLoadData;

	/** If true, then this game should be started from a load game */
	bool mFromLoadGame;

	/** Options this game was started with */
	FString mOptions;

	/** Last autosave was this id */
	UPROPERTY(SaveGame)
	uint8 mLastAutosaveId;

	/** The save session (should actually be SaveSessionId */
	UPROPERTY(SaveGame)
	int32 mSessionId_DEPRECATED;

	/** The name of the session we are playing, migrated over to mSaveSessionName */
	UPROPERTY( SaveGame )
	FString mSessionIDString_DEPRECATED;

	/** The name of the session we are playing */
	UPROPERTY( SaveGame )
	FString mSaveSessionName;

	/** In minutes, how long is the daytime */
	float mDayLength;

	/** In minutes, how long is the nighttime */
	float mNightLength;

	/** Selected starting point */
	UPROPERTY( SaveGame )
	FName mStartingPointTagName;

	/** Overriding selected starting point when respawning. */
	UPROPERTY()
	FName mDebugStartingPointTagName;

	UPROPERTY( EditDefaultsOnly, Category = "Default" )
	bool mIsMainMenu;

	/** These are the default Remote Call Objects for this PlayerController, should be put in config? */
	UPROPERTY( Config )
	TArray< FSoftClassPath > mDefaultRemoteCallObjectsClassNames;

	TArray< TSubclassOf< UFGRemoteCallObject > > mRemoteCallObjectsClassNames;
};

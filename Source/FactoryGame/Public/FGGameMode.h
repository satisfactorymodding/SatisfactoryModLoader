// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "Engine/World.h"
#include "FGSaveInterface.h"
#include "GameFramework/GameMode.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FGGameMode.generated.h"

class AFGGameSession;
class UFGRemoteCallObject;
class AFGAdminInterface;
class AFGGameMode;
class FVariant;

/** Struct holding a data about the save game data is pending to be loaded */
struct FACTORYGAME_API FGameModeLoadData
{
	/** True if we will load a save game */
	bool IsValidLoad{false};
	/** Name of the save game to load */
	FString LoadName;
};

class FACTORYGAME_API FDedicatedServerGameModeComponentPreLoginDataInterface
{
public:
	virtual ~FDedicatedServerGameModeComponentPreLoginDataInterface() = default;
};

/** Interface the implementation of which the dedicated server subsystem can provide to implement dedicated server specific logic in the game mode */
UCLASS( Abstract, Within = "FGGameMode" )
class FACTORYGAME_API UFGDedicatedServerGameModeComponentInterface : public UObject
{
	GENERATED_BODY()
public:
	// Begin UObject interface
	virtual UWorld* GetWorld() const override;
	// End UObject interface

	AFGGameMode* GetOwnerGameMode() const;
	
	/** Notifies the dedicated server game mode component that the owner's FGGameMode has received BeginPlay */
	virtual void NotifyBeginPlay() {}

	/** Notifies the dedicated server game mode component that the owner's FGGameMode has received EndPlay */
	virtual void NotifyEndPlay( EEndPlayReason::Type ) {}

	/** Gives the server component a chance to tick with the game mode */
	virtual void Tick( float DeltaTime ) {}

	/** Allows the DS game mode component to be notified when the game mode's game is initialized, and potentially abort it */
	virtual void NotifyInitGame( const FString& MapName, const FString& Options, FString& ErrorMessage ) {}

	/** Called as a validation step during the AGameMode::Login to make sure the dedicated servers allows the player to log in */
	virtual bool PreLogin( UPlayer* NewPlayer, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage, TSharedPtr<FDedicatedServerGameModeComponentPreLoginDataInterface>& OutPreLoginData ) { return true; }

	/** Called after the PreLogin has been processed and the player created */
	virtual void PostLogin( APlayerController* PlayerController, const TSharedPtr<FDedicatedServerGameModeComponentPreLoginDataInterface>& PreLoginData ) {}

	/** Notifies the DS game mode component that the player is leaving the game */
	virtual void NotifyPlayerLogout( AController* ExitingController ) {}

	/** Allows the dedicated server to determine whenever the game mode in question should skip onboarding. */
	virtual bool ShouldSkipOnboarding( bool bGameModeSkipOnboarding ) const { return bGameModeSkipOnboarding; };

	/** Allows the dedicated server to determine whenever the game mode in question should currently be paused. */
	virtual bool IsPaused( bool bGameModePaused ) const { return bGameModePaused; }

	/** Allows the dedicated server to determine whenever the player in question is allowed to cheat. */
	virtual bool AllowCheats( APlayerController* PlayerController ) const { return false; }

	/** Allows the dedicated server to override the default game mode class */
	virtual TSubclassOf<AFGGameSession> OverrideGameSessionClass( TSubclassOf<AFGGameSession> InGameSessionClass ) const { return InGameSessionClass; }
};

/** Base class for the FactoryGame GameModes, both in main menu and in game */
UCLASS( Config = "Game" )
class FACTORYGAME_API AFGGameMode : public AGameMode, public IFGSaveInterface
{
	GENERATED_BODY()
	friend class UFGGameModeStatics;
public:
	AFGGameMode();

	// Begin UObject interface
	virtual void Serialize( FArchive& ar ) override;
	// End UObject Interface

	// Begin AActor
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	// End AActor

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
	virtual void FinishRestartPlayer( AController* NewPlayer, const FRotator& StartRotation ) override;
	virtual void InitGame( const FString& mapName, const FString& options, FString& out_errorMessage ) override;
	virtual APawn* SpawnDefaultPawnAtTransform_Implementation( AController* newPlayer, const FTransform& spawnTransform ) override;
	virtual void InitGameState() override;
	virtual bool AllowCheats( APlayerController* p ) override;
	virtual AActor* ChoosePlayerStart_Implementation( AController* player ) override;
	virtual void RestartPlayer( AController* newPlayer ) override;
	virtual void PostLogin( APlayerController* newPlayer ) override;
	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage) override;
	virtual void Logout( AController* exiting ) override;
	virtual bool FindInactivePlayer( APlayerController* PC ) override;
	virtual void GenericPlayerInitialization(AController* C) override;
	virtual bool IsPaused() const override;
	virtual void InitStartSpot_Implementation(AActor* StartSpot, AController* NewPlayer) override;
	// End AGameModeBase interface

	/** All actors initialized, notify the save system */
	void PostActorsInitialized( const UWorld::FActorsInitializedParams& inParams );

	/** Get the current options we started the map with */
	const FString& GetCurrentOptions() const { return mOptions; }

	/** Generate the next AutoSave id */
	uint8 GenerateNextAutoSaveId();

	/** Get the session id of our current session */
	FORCEINLINE FString GetSaveSessionName() const { return mSaveSessionName; }

	/** Set the session id of our current session */
	UFUNCTION( BlueprintCallable )
	void SetSaveSessionName( const FString& name );

	/** Get the save system */
	FORCEINLINE class UFGSaveSession* GetSaveSession() const { return mSaveSession; }

	/** Get the length of the day parsed from the game options */
	FORCEINLINE float GetDayLength() const { return mDayLength; }

	/** Get the length of the night parsed from the game options */
	FORCEINLINE float GetNightLength() const { return mNightLength; }

	/** Does this Game Mode function specifically as the main menu? */
	UFUNCTION( BlueprintPure, Category = "Game Mode" )
	FORCEINLINE bool IsMainMenuGameMode() const { return mIsMainMenu; }

	/** Returns true if we should setup save for this GameMode */
	bool ShouldSetupSave() const;

	/**
	 * Get the capsule size of the the default player pawn
	 *
	 * @param world - the world we want to get this default from
	 * @param out_capsuleRadius - radius of capsule
	 * @param out_capsuleHalfHeight - half height capsule
	 * @return false if there is no default player class
	 */
	static bool GetDefaultPlayerCapsuleSize( const UWorld* world, float& out_capsuleRadius, float& out_capsuleHalfHeight );

	/** Debugging stuffs */
	void Debug_SetStartingPoint( const FName startingPoint ) { mDebugStartingPointTagName = startingPoint; }

	UFUNCTION( BlueprintPure, Category = "Remote Call Object" )
	bool RegisterRemoteCallObjectClass( const TSubclassOf< UFGRemoteCallObject > inClass );

	void RegisterCallObjectOnAllCurrentPlayers( const TSubclassOf<UFGRemoteCallObject> inClass );

	/** Saves the game, and then restarts from the load */
	UFUNCTION()
	void RebootSession();

	/** Check if we should skip onboarding/tutorial. Safe to call after AGameModeBase::InitGame */
	virtual bool ShouldSkipOnboarding() const;

	/** Returns the data about the pending save game load. Only useful in a very limited amount of cases. */
	FORCEINLINE FGameModeLoadData GetLoadData() const { return mLoadData; }

	FORCEINLINE UFGDedicatedServerGameModeComponentInterface* GetDedicatedServerInterface() const { return mDedicatedServerInterface; }
public:
	/** Name of the start location option that is parsed */
	static const TCHAR* StartLocationOption;

	/** Name of the load game option that is parsed */
	static const TCHAR* LoadGameOption;

	/** Name of the session name option that is parsed */
	static const TCHAR* SessionNameOption;

	/** Name for the skip onboarding/tutorial/intro option */
	static const TCHAR* SkipOnboarding;

	/** Name for the advanced game settings (Game Modes) option when starting a new session */
	static const TCHAR* AdvancedGameSettingsOption;

	/** Name for the enabling advanced game settings (Game Modes) option when loading a save */
	static const TCHAR* EnableAdvancedGameSettingsOption;

	/** Name for the option enabling possessing any player pawn on the map */
	static const TCHAR* AllowPossessAnyOption;

	/** List of map options that should never be saved into the save files. This includes options that are saved in the different places, for example, or one-time options like ?listen */
	static TSet<FString> MapOptionsToNeverSave;
protected:
	/** Trigger a save to save the world */
	UFUNCTION( exec )
	void TriggerWorldSave( const FString& saveGameName );

	/** Trigger a save to save the world */
	UFUNCTION( exec )
	void TriggerBundledWorldSave( const FString& saveGameName );

	/** Just a test function, do not use in real code */
	UFUNCTION( exec )
	void BuildFoundationsBro( int32 howMany );

	UFUNCTION( exec )
	void ShowInviteUI();

	UFUNCTION( exec )
	void PrintSessionId();

	/**
	 * If return true, then this is a pawn that we can take control of during spawning, else it's not valid
	 * for some reason (dead maybe)
	 */
	bool IsValidPawnToReclaim( APawn* pawn ) const;
	
private:
	/** Called by the option manager when the session restart interval has changed */
	void OnSessionRestartTimeSlotUpdated( FString OptionName, FVariant OptionValue );
public:
	/**
	 * Get the name of the save that we want to create when rebooting the session due to long server uptimes
	 */
	void GetRestartSessionSaveName( FString& out_sessionName ) const;
private:
	/** Build the URL for restarting the session */
	void BuildRestartSessionURL( const FString& saveName, FString& out_sessionUrl ) const;

	/**
	 * Caches the player starts by PlayerStartTag as the key.
	 * @return Play from here player start, if found; otherwise nullptr.
	 */
	class APlayerStart* CachePlayerStarts( TMap< FName, TArray< APlayerStart* > >& out_playerStarts );

	void PartitionPlayerStartsByOccupancy(
		const TArray< APlayerStart* >& playerStarts,
		TSubclassOf< APawn > pawnClassToFit,
		TArray< APlayerStart* >& out_unOccupied,
		TArray< APlayerStart* >& out_occupied ) const;

	void DiscoverDefaultRemoteCallObjects();
	void RecalculateSessionRestartTime();
	void TickSessionRebootTimer();
protected:
	UPROPERTY()
	UFGSaveSession* mSaveSession;

	/** Data about the save game we will load */
	FGameModeLoadData mLoadData;

	/** The name of the session we are playing */
	UPROPERTY( SaveGame )
	FString mSaveSessionName;
private:

	/** If true, then this game should be started from a load game */
	bool mFromLoadGame;

	/** Options this game was started with */
	FString mOptions;

	/** Last AutoSave was this id */
	UPROPERTY( SaveGame )
	uint8 mLastAutoSaveId;

	/** In minutes, how long is the daytime */
	float mDayLength;

	/** In minutes, how long is the nighttime */
	float mNightLength;

	/** Selected starting point */
	UPROPERTY( SaveGame )
	FName mStartingPointTagName;

	/** Command line param -PossesAny will allow players using authorization to posses other players on startup regardless of if their UniqueIds match */
	UPROPERTY()
	bool mAllowPossessAny;

	/** Overriding selected starting point when respawning. */
	UPROPERTY()
	FName mDebugStartingPointTagName;

	/** These are the default Remote Call Objects for this PlayerController */
	UPROPERTY( Transient )
	TArray< TSubclassOf< UFGRemoteCallObject > > mRemoteCallObjectsClassNames;

	bool bWantsSessionReboot{false};
	FDateTime SessionStartTime;
	FDateTime SessionRestartTime;
	int32 LastSessionRestartTimerNotificationIndex{100};
	bool bSessionRestartScheduled{false};

	UPROPERTY( EditDefaultsOnly, Category = "Default" )
	bool mIsMainMenu;

	/** Dedicated server component interface */
	UPROPERTY( Transient )
	UFGDedicatedServerGameModeComponentInterface* mDedicatedServerInterface;
};

UCLASS(BlueprintType)
class FACTORYGAME_API UFGGameModeStatics: public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintPure)
	static FName GetStartingAreaNameFromOptions(const TMap<FString, FString> &Options);

	UFUNCTION(BlueprintPure)
	static bool HasSkipOnboardingOption(const TMap<FString, FString> &Options);

	UFUNCTION(BlueprintPure)
	static bool HasAdvancedGameSettings(const TMap<FString, FString> &Options);
};

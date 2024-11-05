// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGDSAuthenticationTypes.h"
#include "Templates/SubclassOf.h"
#include "FGDSGameplayTypes.generated.h"

class UFGSchematic;
class UFGGamePhase;
class UFGDedicatedServerGameModeComponentInterface;
class AFGGameMode;
struct FCommonSessionCreationSettings;
class USessionMigrationSequence;
struct FEncryptionKeyResponse;
enum class EEncryptionFailureAction : uint8;

/** Possible states the server can be in */
UENUM()
enum class EServerState : uint8
{
	Offline,
	Idle,
	Loading,
	Playing,
};

/**
 * State of the game currently running on the dedicated server
 */
USTRUCT( BlueprintType )
struct FACTORYGAME_API FServerGameState
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	FString ActiveSessionName;

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	int32 NumConnectedPlayers{0};

	/** Maximum amount of players that can be connected to the server */
	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	int32 PlayerLimit{0};

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	int32 TechTier{0};

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	TSubclassOf<UFGSchematic> ActiveSchematic;

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	TObjectPtr<UFGGamePhase> GamePhase;
	
	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	bool IsGameRunning{false};

	/** Total playtime of the currently running session */
	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	int32 TotalGameDuration{0};

	/** True if the game is paused. If the game is paused, the total game duration will not be updated */
	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	bool IsGamePaused{false};

	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	float AverageTickRate{0.0f};

	/** Name of the session the most recent save of which will be automatically loaded by the server upon restart. */
	UPROPERTY( BlueprintReadWrite, Category = "Server Game State" )
	FString AutoLoadSessionName;
};

/**
 * A data that is needed on the server to start a new game
 */
USTRUCT( BlueprintType, meta = ( BlueprintInternalUseOnly = "true" ) )
struct FACTORYGAME_API FFGServerNewGameData
{
	GENERATED_BODY()

	// Name of the session to create. This will be the session name for the save game file.
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	FString SessionName;

	// Name of the map to use to start a new game. If empty, the default map will be used.
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	FString MapName;

	// Name of the starting location to spawn the players at
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	FString StartingLocation;

	// True if we should skip the onboarding
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	bool bSkipOnboarding{false};

	// Map of the overriden advanced game settings values to set on the save game.
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	TMap<FString, FString> AdvancedGameSettings;

	// Custom options to be passed as map options for creating a new game.
	// ONLY FOR MODDING/THIRD PARTY SUPPORT. IF YOU ARE A COFFEE STAIN EMPLOYEE, MAKE A NEW PROPERTY ABOVE INSTEAD
	UPROPERTY( BlueprintReadWrite, Category = "New Game Data" )
	TMap<FString, FString> CustomOptionsOnlyForModding;
};

/** Contains information needed to join a dedicated server */
USTRUCT()
struct FACTORYGAME_API FFGServerJoinDataResponse
{
	GENERATED_BODY()

	/** When not empty, the following encryption token should be provided to a connection */
	UPROPERTY()
	FString EncryptionToken;

	/** Hex-encoded encryption key that the client should use locally for encrypting the connection to the server */
	UPROPERTY()
	FString EncryptionKey;

	/** Server entry token the client should pass in the Join URL to be able to join with their privilege level */
	UPROPERTY()
	FServerEntryToken ServerEntryToken;
};

/** Interface that the dedicated server subsystem implements to route a few game instance level functions to the dedicated server implementation */
UINTERFACE()
class FACTORYGAME_API UFGDedicatedServerInterface : public UInterface
{
	GENERATED_BODY()
};

class FACTORYGAME_API IFGDedicatedServerInterface
{
	GENERATED_BODY()
public:
	/** Attempts to auto load the most recent session from the auto load save game specified from the server settings. Returns true if succeeded, false if not. If true is returned, game instance will not travel to the default map. */
	virtual bool AttemptAutoLoadMostRecentSession() = 0;

	/** Creates a game mode component implementation for the given game mode */
	virtual UFGDedicatedServerGameModeComponentInterface* MakeGameModeComponent( AFGGameMode* GameMode ) const = 0;

	/** Creates the session using the provided settings and travels to the map */
	virtual USessionMigrationSequence* CreateSession( const FCommonSessionCreationSettings& SessionCreationSettings ) = 0;

	/** Called by the game instance to generate an encryption key to encrypt the network connection to the client using the server secret. */
	virtual FEncryptionKeyResponse GenerateEncryptionKey( const FString& EncryptionToken ) = 0;

	/** Called to determine whenever the encryption is required by the Dedicated Server */
	virtual EEncryptionFailureAction IsEncryptionRequired() const = 0;
};


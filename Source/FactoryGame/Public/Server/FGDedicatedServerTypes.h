// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGGamePhaseManager.h"
#include "FGDedicatedServerTypes.generated.h"

UENUM()
enum class EServerState : uint8
{
	Offline,
	Idle,
	Loading,
	Playing,
};

USTRUCT()
struct FServerStateShort
{
	GENERATED_BODY()
	
	UPROPERTY()
	FString GameVersion;

	UPROPERTY()
	EServerState ServerState = EServerState::Offline;
};

UENUM( BlueprintType )
enum class EPrivilegeLevel : uint8
{
	/// This player is not authenticated and may not perform any operations on the server
	NotAuthenticated,
	/// This player is authenticated as a client and may only join games on the server
	Client,
	/// This player is an administrator and may perform any administration tasks, such as starting new games, saving games, loading games, kicking players aso
	Administrator,
	/// This player is an initial administrator. The sole purpose of this privilege level is to allow a player to set an admin password and a server name. No other operations are allowed.
	InitialAdmin
};

/**
 * A Persistent authentication token that a client may hold. It's authenticity can be verified cryptographically by the UFGServerSubsystem class
 */
USTRUCT( BlueprintType )
struct FServerAuthenticationToken
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	EPrivilegeLevel PrivilegeLevel;

	UPROPERTY()
	FString Fingerprint;
};

/**
 * A short lived game entry token that a client needs to provide when actually joining a server game. It's authenticity can be verified cryptographically by the UFGServerSubsystem class
 */
USTRUCT()
struct FServerEntryToken
{
	GENERATED_BODY()

	UPROPERTY()
	EPrivilegeLevel Privilege;

	UPROPERTY()
	FDateTime IssueDate;

	UPROPERTY()
	FString Fingerprint;
};

FArchive& operator<<( FArchive& AR, FServerEntryToken& GameToken );
FArchive& operator<<( FArchive& AR, FServerAuthenticationToken& Token );

UENUM( BlueprintType )
enum class EServerMessage : uint8
{
	InvalidHost,
	IncorrectPassword,
	Timeout,
	NoGameRunning,
	LoadingGame_Disconnect,
	NotAuthorized
};

DECLARE_DYNAMIC_DELEGATE_OneParam( FServerSetAdminPasswordCallback, const FString&, AdminPassword );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FServerTryPasswordCallback, const FString&, Password, EPrivilegeLevel, MinimumTargetPrivilege );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerSetJoinPasswordCallback, const FString&, JoinPassword );
DECLARE_DYNAMIC_DELEGATE_OneParam( FServerClaimCallback, const FString&, ServerName );
DECLARE_DYNAMIC_DELEGATE_TwoParams( FServerCreateGameCallback, const FString&, GameName, const FString&, StartLoc );

DECLARE_DYNAMIC_DELEGATE( FServerCancelOperationCallback );


UINTERFACE( MinimalAPI, Blueprintable )
class UFGDedicatedServerUIProxy : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface that a dedicated server connection needs to use for User Interaction. Whenever a dedicated server requires user input, it will
 * be requested through this interface. 
 */ 
class IFGDedicatedServerUIProxy
{
	GENERATED_BODY()

public:

	/**
	 * A connection to the server could not be established. An appropriate message should be presented to the user
	 **/ 
	UFUNCTION( BlueprintNativeEvent )
	void HandleServerMessage( EServerMessage Message );

	/**
	 * The server is asking for a password.
	 * Must be followed up by calling either @TryPasswordCallback or @CancelCallback
	 **/ 
	UFUNCTION( BlueprintNativeEvent )
	void HandlePasswordRequest( EPrivilegeLevel MinimumTargetPrivilege, const FServerTryPasswordCallback &TryPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	* The client is required to set an administration password.
	* Must be followed up by calling either @SetAdminPasswordCallback or @CancelCallback
	**/ 
	UFUNCTION( BlueprintNativeEvent )
	void HandleSetAdminPasswordRequest( const FServerSetAdminPasswordCallback &SetAdminPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	* The server has not been claimed and is asking the local player to claim it.
	* Must be followed up by calling either @ServerClaimCallback or @CancelCallback
	**/
	UFUNCTION( BlueprintNativeEvent )
	void HandleUnclaimedServerGreeting( const FServerClaimCallback &ServerClaimCallback, const FServerCancelOperationCallback &CancelCallback );

	/**
	 * The client is required to set an optional join password.
	 * Must be followed up by calling either @SetJoinPasswordCallback or @CancelCallback
	 **/ 
	UFUNCTION( BlueprintNativeEvent )
	void HandleSetJoinPasswordRequest( const FServerSetJoinPasswordCallback &SetJoinPasswordCallback, const FServerCancelOperationCallback &CancelCallback );

	/** 
	 * The client is required to create a game on the Server.
	 * Must be followed up by calling either @CreateGameCallback or @CancelCallback
	 **/ 
	UFUNCTION( BlueprintNativeEvent )
	void HandleCreateGameRequest( const FServerCreateGameCallback &CreateGameCallback, const FServerCancelOperationCallback &CancelCallback );
};

USTRUCT( BlueprintType )
struct FServerGameState
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	FString ActiveSessionName = {};

	UPROPERTY( BlueprintReadOnly )
	int32 NumConnectedPlayers = 0;

	UPROPERTY( BlueprintReadOnly )
	int32 TechTier = 0;

	UPROPERTY( BlueprintReadOnly )
	TSubclassOf< class UFGSchematic > ActiveSchematic;

	UPROPERTY( BlueprintReadOnly )
	TEnumAsByte<EGamePhase> GamePhase = EGamePhase::EGP_Victory;
	
	UPROPERTY( BlueprintReadOnly )
	bool IsGameRunning = false;

	UPROPERTY( BlueprintReadOnly )
	int32 TotalGameDuration = 0.f;

	UPROPERTY( BlueprintReadOnly )
	float AverageTickRate = 0.f;
};

/**
 * A temporary struct with basic server settings. Will be replaced with something else once the server settings handling has been defined
 */ 
USTRUCT( BlueprintType )
struct FServerBasicSettings
{
	GENERATED_BODY()

	UPROPERTY( BlueprintReadOnly )
	bool AutoPause;

	UPROPERTY( BlueprintReadOnly )
	bool AutoSaveOnDisconnect;

	UPROPERTY( BlueprintReadOnly )
	FString AutoLoadSessionName;
};

/**
 * Aggregates the three states that can be determine what operations are possible into on state to simplify logic in blueprints
 **/ 
UENUM( BlueprintType )
enum class EServerComplexState : uint8
{
	/**
	 * Server is offline. Nothing can be done to it in this state
	 */ 
	ServerOffline,
	/**
	 * The server is online and it is currently idle (not running a game). We have no control connection established to it and that
	 * is the only thing we can do in this state
	 */ 
	NoGameRunning_NotConnected_CompatibleVersion,
	NoGameRunning_NotConnected_IncompatibleVersion,
	/**
	 * Server online and connection pending
	 */ 
	NoGameRunning_ConnectionPending,
	NoGameRunning_ConnectionFailed,
	/**
	 * Server Online, game not running and we are connected as clients. In this state we can't do much other than wait for an administrator to start a game.
	 */ 
	NoGameRunning_Connected_Client,
	/**
	 * Server Online, game not running and we are connected as admins. In this state we can create a game on the server or perform any admin operations, such as changing server settings. 
	 */
	NoGameRunning_Connected_Admin,
	/**
	 * Server Online, game not running and we are not authenticated
	 */ 
	NoGameRunning_Connected_NonAuthenticated,
	/**
	 * The server is loading a game. At this point, all we can do is wait for it to finish as it is unable to receive connections in this state
	 */
	GameLoading,
	/**
	 * A game is running and we are not connected. We need to establish a connection before we can do anything. 
	 */
	GameRunning_NotConnected_CompatibleVersion,
	GameRunning_NotConnected_IncompatibleVersion,
	/**
	 * Game is running and connection is pending
	 */
	GameRunning_ConnectionPending,
	GameRunning_ConnectionFailed,
	/**
	 * A game is running and we are connected as clients. At this point we can join the game
	 */ 
	GameRunning_Connected_Client,
	/**
	 * Game running, us admins, we can perform any admin operation. 
	 */ 
	GameRunning_Connected_Admin,
	/**
	 * Game running, we are not authenticated. 
	 */ 
	GameRunning_Connected_NonAuthenticated
};

enum class EServerManagerVersion : uint8
{
	SVM_InitialVersion,
	// Address is now the address as it was entered by the users. It needs to be DNS resolved before it's usable.
	SVM_NoDNSCaching,
	
	SVM_CurrentVersion = SVM_NoDNSCaching,
	SVM_EndVersions
};

struct FServerNetStats
{
	static constexpr int32 NumPollsForAverage = 25;
	
	/// Used to compute the average round trip times over the last @NumPollsForAverage polls
	TCircularQueue< int16 > RoundTripTimesQueue = TCircularQueue<int16>( NumPollsForAverage + 1 );

	/// The cached sum of all entries in @RoundTripTimesQueue
	int64 RoundTripTimesSum = 0;

	/// Average roundtrip over the last @NumPollsForAverage polls
	int16 AverageRoundTripTime;

	/// When did this server last show any signs of life 
	FDateTime TimeWhenLastResponded;

	/// When did we last try to ping this server
	FDateTime TimeWhenLastPolled;

	/// Time when last interesting is used to determine whether a server should be pinged or not in relation to it's ping rate
	/// Cannot use TimeWhenLastResponded for this alone as there other other triggers for beginning to poll a server, such as a new listener
	/// subscribing to it's state.
	FDateTime TimeWhenLastInteresting;

	/// The rate at which we are currently polling this server
	float PollingRate = .25f;
};

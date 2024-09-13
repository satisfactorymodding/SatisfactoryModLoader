// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "UObject/Interface.h"
#include "Networking/FGClientAPIContext.h"
#include "Server/FGDSAuthenticationTypes.h"
#include "Server/FGDSGameplayTypes.h"
#include "Server/FGDSQueryTypes.h"
#include "Server/FGDSSharedTypes.h"
#include "FGSaveManagerInterface.h"
#include "FGServerStateListener.h"
#include "Security/FGClientCertificateManager.h"
#include "FGServerObject.generated.h"

enum class EServerMessage : uint8;
class FFGRequestPayload;
class IFGOptionInterface;
class IFGAdvancedGameSettingsInterface;
class UFGServerObjectOptionAdapter;
enum class EServerManagerVersion : int32;
class IFGDedicatedServerUIProxy;
class UFGClientStateRequester;
class UFGClientAPIManager;
class IFGServerStateListener;
class UFGServerManager;
class UFGClientRequesterArray;
class IFGAdvancedGameSettingsInterface;

/**
 * Possible states of the Server API for a particular Server Object.
 * Most of the operations on the Server Object require the Server API to be initialized and available.
 * You can check the state of the Server API by using IsServerAPIValid, CanCallServerAPI and GetServerAPIState
 */
UENUM( BlueprintType )
enum class EFGServerAPIState : uint8
{
	/** The Server API is unavailable and the requests to it will fail */
	Unavailable UMETA( DisplayName = "Unavailable" ),

	/** The server API is unavailable and the last attempt to establish a connection with it ended up with an error */
	UnavailableWithError UMETA( DisplayName = "Unavailble (with Error)" ),
	
	/**
	 * The Server API address has been resolved, but there might be an additional problem with using it such as certificate mismatch.
	 * This state can transition either back to Unavailable or to Configured.
	 **/
	Pending UMETA( DisplayName = "Pending" ),

	/** The Server API is available and can serve the operations on this Server Object */
	Configured UMETA( DisplayName = "Configured" )
};

/**
* Holds information about dedicated servers that we know about
* Typically, a server gets to be known about by connecting to it
**/ 
UCLASS( BlueprintType, Within = "FGServerManager" )
class FACTORYDEDICATEDCLIENT_API UFGServerObject : public UObject, public IFGSaveManagerInterface, public IFGClientAPIContext
{
	GENERATED_BODY()

	friend class UFGServerManager;
	friend class AFGServerBeaconClient;
public:
	UFGServerObject();

	// Begin IFGClientAPIContext interface
	virtual UFGClientAPIManager* GetClientAPIManager() const override { return mClientAPIManager; }
	// End IFGClientAPIContext interface

	// Begin IFGSaveManagerInterface
	virtual void EnumerateSessions(const FOnSaveManagerEnumerateSessionsComplete& CompleteDelegate) override;
	virtual bool IsEnumeratingLocalSaves() const override;
	virtual bool IsSaveManagerAvailable() const override;
	virtual void DeleteSaveFile(const FSaveHeader& SaveGame, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual void DeleteSaveSession(const FSessionSaveStruct& Session, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual USessionMigrationSequence* LoadSaveFile(const FSaveHeader& SaveGame, const FLoadSaveFileParameters& LoadSaveFileParameters, APlayerController* Player) override;
	virtual USessionMigrationSequence* CreateNewGame(const FString& SessionName, const FSoftObjectPath& MapAssetName, const FCreateNewGameParameters& CreateNewGameParameters, APlayerController* Player) override;
	virtual void SaveGame(const FString& SaveName, FOnSaveMgrInterfaceSaveGameComplete CompleteDelegate) override;
	virtual void UploadSave(const FSaveHeader& Save, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate) override;
	virtual void DownloadSave(const FSaveHeader& SaveGame, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate) override;
	virtual bool IsTransferInProgress() const override;
	virtual bool SupportsOnlineSettings() const override;
	// End IFGSaveManagerInterface

	/** Returns the current state of the Server API, the primary communication channel with the server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE EFGServerAPIState GetServerAPIState() const { return mServerAPIState; }

	/** Returns the current state of the game on the server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FServerGameState GetGameState() const { return mGameState; }

	/** Returns the authentication token we are currently using. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FServerAuthenticationToken GetAuthenticationToken() const { return mAuthenticationToken; }

	/** Returns the average time it takes to send the data to the server and receive the response. The average is over all of the queries received from the server. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE int32 GetAverageRoundtripTimeMs() const { return mAverageRoundtripTimeMs; }

	/** Returns a history of the user commands inputted into the server console and their responses. Does not actually contain any server logs. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FString GetServerConsole() const { return mServerConsole; }

	/** Returns true if we are waiting for a result of a command execution */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE bool IsWaitingForConsoleResult() const { return mWaitingForConsoleResult; }

	FORCEINLINE EServerFlags GetServerFlags() const { return mServerFlags; }
	FORCEINLINE bool HasAnyServerFlags( const EServerFlags InFlags ) const { return EnumHasAnyFlags( mServerFlags, InFlags ); }
	
	FORCEINLINE uint16 GetServerAPIPort() const { return mQueryPort; }
	FORCEINLINE int32 GetGamePort() const { return mQueryPort; }
	
	/** Returns the name of the remote server, as reported by the server state */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FString GetServerName() const { return mServerName; }

	/** Returns the hostname of the remote server, as it has been inputted by the user when adding this server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FString GetServerHostname() const { return mServerHostname; }

	/** Returns the current state of this server. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE EServerState GetServerState() const { return mServerState; }

	/** Returns the NetCL of this server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE int32 GetServerNetCL() const { return mServerNetCL; }; 

	/** Returns the query port specified by the user. Can be INDEX_NONE if the port is default or the hostname was resolved via the SRV record! */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE int32 GetQueryPort() const { return mQueryPort; }

	/** Returns true if this server is modded. We do not attempt to connect to the modded servers on vanilla clients */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE bool IsServerModded() const { return HasAnyServerFlags( EServerFlags::Modded ); }

	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE FFGServerCertificate GetServerCertificate() const { return mServerCertificate; }
	
	FORCEINLINE const TArray<TSharedPtr<FInternetAddr>>& GetQueryAddresses() const { return mSolvedAddresses; }

	/** Returns true if Creative Mode/Advanced Game Settings are enabled for the session currently running on the Server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FORCEINLINE bool IsCreativeModeEnabled() const { return mAdvancedGameSettingsEnabled; }

	/** Returns the Option Interface for the Server Options (e.g. server-global options not constrained by the currently loaded session) */
	UFUNCTION( BlueprintPure, Category = "Server" )
	TScriptInterface<IFGOptionInterface> GetServerOptionsInterface() const;

	/** Returns the Option Interface for the Advanced Game Settings in the session currently running on the server. Any change will automatically enable AGS on the save game. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	TScriptInterface<IFGOptionInterface> GetAdvancedGameSettingsInterface() const;

	/** Returns the Advanced Game Settings interface to be used as a local manager to store settings into for the "New Game" menu in the Server Manager */
	UFUNCTION( BlueprintPure, Category = "Server" )
	TScriptInterface<IFGAdvancedGameSettingsInterface> GetNewGameAdvancedGameSettings() const;

	/** Returns true if server API information is valid and we can query server API state. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	bool IsServerAPIAvailableAndCompatible() const;

	/** Returns true if Server API calls are possible right now, using the minimum privilege level provided */
	UFUNCTION( BlueprintPure, Category = "Server" )
	bool CanCallServerAPI( EPrivilegeLevel MinPrivilegeLevel ) const;

	/** Returns true if the currently stored authentication token has a valid fingerprint (as per client view) and given privilege level */
	UFUNCTION( BlueprintPure, Category = "Server" )
	bool IsAuthenticationTokenValid( EPrivilegeLevel MinPrivilegeLevel ) const;

	/** Attempts to retry the Server API connection, if it is Unavailable. Will trigger HealthCheck and react on the results of it. */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	bool AttemptServerAPIConnection();

	/** Attempts to refresh the authentication token with the server, or get a new one to make sure the target privilege level is achieved */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void Authenticate( EPrivilegeLevel MinimumTargetedPrivilege, bool bAutomaticLogin = false );

	/** Attempts to run a console command on the server. Should only be run with a valid Server API */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void ConsoleCommand( const FString& Command );

	/** Attempts to join this server */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	bool Join();

	/** Prompts the user to change the server name by opening a prompt. */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void PromptChangeServerName();

	/** Updates the server name that this server currently has. */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void ChangeServerName( const FString& NewServerName );

	/** Updates the name of the session that the server should automatically load on the start */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void SetAutoLoadSessionName( const FString& SessionName );
	
	/** Prompts the user to change the Client Password for the Server. The user must already have Administrator privileges. */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void ChangeClientPassword();

	/** Prompts the user to change the Admin Password for the Server. The user must already have Administrator privileges. */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void ChangeAdminPassword();

	/** Forces an immediate game state update from the server */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void FetchGameState();

	/** Forces an immediate server options update from the server */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void FetchServerOptions();

	/** Forces an immediate advanced game settings update from the server */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void FetchAdvancedGameSettings();

	/**
	 * Called from the Server Manager to notify that this server is now active and can emit pop-up requests
	 * without the user interaction. That means we can fully initiate the authentication flow, or show the user server claim dialog
	 * because normally we do not want to initiate pop-ups that have not been triggered by the user interaction from the ServerObject code.
	 */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void OnServerActivated();

	/** Opposite of OnServerActivated: Called from the server manager when the server is un-selected in the Server Manager list */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void OnServerDeactivated();

	/** Returns true if the server is claimed (we are not an InitialAdmin, and the ServerName is non-empty). Non-valid Server API configuration is considered claimed. */
	UFUNCTION( BlueprintPure, Category = "Server" )
	bool IsServerClaimed() const;

	/**
	 * Called when PasswordlessLogin resulted in InitialAdmin privileges, which means the user needs to claim the server and set the admin password
	 * Also can be called manually in case the client has logged in as InitialAdmin as a part of the Automatic Authentication Flow
	 */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void GreetAsUnclaimedServer();

	/** Pulls the command from the command history. Used for implementing ArrowUp and ArrowDown in the server Console */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	FString PullCommandFromHistory( bool GoBackInTime );

	/** Returns the complex state of the server for the UI */
	UFUNCTION( BlueprintPure, Category = "Server" )
	EServerComplexState GetComplexState() const;

	/** Returns true if we are currently playing as a client on this server */
	UFUNCTION( BlueprintPure, Category = "Server" )
	bool IsClientConnectedToTheServer() const;

	/** Returns the response from the last Health Check performed on the Server API. Will be OK if no health check has been performed yet! */
	UFUNCTION( BlueprintPure, Category = "Server" )
	FFGServerErrorResponse GetLastHealthCheckResponse() const { return mLastHealthCheckResponse; }

	/** Registers server state listener for this server object */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void RegisterStateListener( TScriptInterface<IFGServerStateListener> Listener );

	/** Un-registers server state listener for this server object */
	UFUNCTION( BlueprintCallable, Category = "Server" )
	void UnRegisterStateListener( TScriptInterface<IFGServerStateListener> Listener );

	/** Returns the Server Manager hoisting this server object */
	UFUNCTION( BlueprintPure, Category = "Server" )
	UFGServerManager* GetOuterServerManager() const;

	/** Called by the Server API manager to prompt the user to manually inspect the server certificate and accept it if they deem it secure */
	void PromptUserToAllowCertificate( const FFGServerCertificate& NewServerCertificate );

	/** Called by the Server API to discard the certificate that we have previously accepted. Returns true if there was a certificate discarded, false otherwise */
	bool DiscardServerCertificate();

	/** Called by the Server API in case an error has been received */
	void OnServerAPIError( const FFGServerErrorResponse& ErrorResponse );

	/** Displays a server message to the user if the UI is open, prints it to the log file instead if not */
	void ShowServerMessage( EServerMessage ServerMessage ) const;

	/** Called when the server has been added or loaded from the save game */
	void OnServerAddedOrLoaded();

	/** Called when the server object is about to be removed from the list, due to game subsystem shutdown or because the user removed it. */
	void OnServerRemoved();

	/** Called repeatedly by the server manager to update the state of this server if necessary */
	void Tick( float DeltaTime );

	/** Called to initialize the server right after it has been added */
	void SetupServer( const FString& Hostname, int32 QueryPort, const TArray<TSharedPtr<FInternetAddr>>& ResolvedQueryAddress );

	/** Processes the poll response from the server */
	void ProcessServerStatePollResponse( const FServerStatePollResponse& PollResponse );

	/** Attempts to apply the settings from the option adapter, regardless of it's underlying type */
	void AttemptApplySettings( const UFGServerObjectOptionAdapter* OptionAdapter, const TMap<FString, FString>& ChangedSettings ) const;

	/** Internal function exposing direct access to the Requester array. DO NOT CALL ANY FUNCTIONS THERE MANUALLY! */
	FORCEINLINE UFGClientRequesterArray* Internal_GetClientRequesterArray() const { return mClientRequesterArray; }
protected:
	friend class UFGClientAuthenticationRequester;
	friend class UFGClientManagementRequester;
	friend class UFGClientSaveGameRequester;
	friend class UFGClientStateRequester;

	EServerComplexState GetComplexState_Playing() const;
	EServerComplexState GetComplexState_Idle() const;

	/** Dispatches requests to process set dirty state bits. */
	void ProcessDirtySubStateBits();

	/** Called when the game state response has been received */
	void OnGameStateReceived( const FFGServerErrorResponse& ErrorResponse, const FServerGameState& NewState );

	/** Updates the game state of the server to the newly supplied one */
	void SetGameState( const FServerGameState& NewState );

	/** Called when the query addresses have been resolved and we can start pinging the server with the lightweight query */
	void OnServerQueryAddressResolved( const TArray<TSharedPtr<FInternetAddr>>& ResolvedQueryAddress );

	/** Called as a result of the health check */
	void OnHealthCheckResult( const FFGServerErrorResponse& HealthCheckResult, const FString& ServerCustomData );

	/** Called from the request handler to notify the ServerObject that the command request has completed */
	void OnConsoleCommandOutputReceived( const FString& ConsoleCommandOutput );

	/** Called from the request handler to notify that the login request has concluded */
	void OnPasswordlessLoginCompleted( FFGServerErrorResponse& ErrorResponse, EPrivilegeLevel MinPrivilegeLevel, FServerAuthenticationToken InAuthenticationToken, bool bAutomaticLogin );

	/** Called from the request handler to notify that the login request has concluded */
	void OnPasswordLoginCompleted( FFGServerErrorResponse& ErrorResponse, EPrivilegeLevel MinPrivilegeLevel, FServerAuthenticationToken InAuthenticationToken );

	/** Called when we receive the response for the create game request */
	void OnCreateGameResponse( const FFGServerErrorResponse& ErrorResponse );

	/** Called when we receive the response for the join game request */
	void OnLoadGameResponse( const FFGServerErrorResponse& ErrorResponse );

	/** Called when the join request response is received. */
	void OnJoinRequestResponse( const FFGServerErrorResponse& ErrorResponse, const FFGServerJoinDataResponse& ServerJoinData );

	/** Called when an update of the server options is received from the server */
	void OnServerOptionsUpdated( const FFGServerErrorResponse& ErrorResponse, const TMap<FString, FString>& NewServerOptions, const TMap<FString, FString>& PendingServerOptions );

	/** Called when an update of the AGS is received from the server */
	void OnAdvancedGameSettingsUpdated( const FFGServerErrorResponse& ErrorResponse, const TMap<FString, FString>& NewAdvancedGameSettings, bool bCreativeModeEnabled );

	/** Called when the token verification has concluded to determine the future flow of the authentication */
	void OnLoginTokenVerificationFinished( FFGServerErrorResponse& ErrorResponse, EPrivilegeLevel MinPrivilegeLevel, bool bAutomaticLogin );

	/** Called when the server is claimed */
	void OnServerClaimResponse( FFGServerErrorResponse& ErrorResponse, const FString& NewAuthenticationToken );

	/** Called when the server admin password has been updated */
	void OnAdminPasswordSetResponse( const FString& NewAuthenticationToken );

	/** Called when Client password has been set */
	UFUNCTION()
	void OnClientJoinPasswordSet( const FString& NewClientJoinPassword );

	/** Called when Admin password has been set */
	UFUNCTION()
	void OnAdminPasswordSet( const FString& NewAdminPassword );

	/** Called when the server has been claimed and admin password set */
	UFUNCTION()
	void OnAdminPasswordSetAndServerClaimed( const FString& NewAdminPassword );

	/** Called when the server is claimed. Changes the server name and offers the possibility of setting the admin password */
	UFUNCTION()
	void OnServerClaimed( const FString& NewServerName );

	/** Called when we have finished enumerating the save sessions */
	void OnEnumerateSaveSessionsCompleted( const FFGServerErrorResponse& ErrorResponse, const TArray<FSessionSaveStruct>& Sessions, int32 CurrentSessionIndex );

	/** Called when the save game upload completes. Used to just decrement the number of pending transfers back. */
	void OnUploadSaveGameComplete( FFGServerErrorResponse& ServerResponse, FOnSaveManagerTransferCompleted CompleteDelegate );

	/** Called when save game download is complete */
	void OnDownloadSaveGameComplete( FFGServerErrorResponse& ServerResponse, const TSharedPtr<FFGRequestPayload>& SaveGamePayload, FOnSaveManagerTransferCompleted CompleteDelegate );
private:
	/** Updates the locally cached server name. Does not make the remote server change it's name. */
	void SetServerName( const FString& NewServerName );

	/** Called to notify the local Save Management UI that the remote saves have changed and need to be re-fetched */
	void ServerSavesUpdated() const;

	/** Called regularly to poll the server state by sending the lightweight query */
	void PollState();

	/** Called to notify the UI that the complex state of the server has changed */
	void NotifyComplexStateChange();

	/** Updates the state of the servers, triggers subscribes and starts state transition */
	void SetServerState( EServerState NewState );	

	/** Updates the Server API state to the specified one and notifies all of the Server Listeners about the change */
	void SetServerAPIState( EFGServerAPIState NewServerAPIState );

	/** Called to update the currently used authentication token for the server */
	void SetAuthenticationToken( const FServerAuthenticationToken& Token );

	/** Called when any of the authentication flow routines fail with an unknown error code. Wipes the current token and resets the authentication flow. */
	void AbortAuthenticationFlow( const FFGServerErrorResponse& Reason );
protected:
	UFUNCTION()
	void OnUserPasswordRequestCompleted( const FString& Password, EPrivilegeLevel MinimumTargetPrivilege );
	
	UFUNCTION()
	void OnUserPasswordRequestCancelled();

	UFUNCTION()
	void OnUserAcceptedRemoteCertificate( FFGServerCertificate ServerCertificate );

	UFUNCTION()
	void OnUserDeclinedRemoteCertificate();

	/** Called when we update the authentication token to a new value. This is a good place to re-request certain parts of the server state that might need some privileges to be read */
	void OnAuthenticationTokenChanged();

	/** Requests the password from the user */
	void RequestPassword( EPrivilegeLevel MinPrivilegeLevel );

	/** Checks the version compatibility between the Server API and the game */
	bool CheckVersionCompatibility() const;

	/** Writes the current state of the server manager to the save file */
	void SaveState() const;

	/** True if we have any listeners that are interested in the updates on this server's state and thus should try to poll it */
	bool IsPollingServerState();

	/** Purges dead listeners from the server listeners array */
	void PurgeDeadListeners();
public:
	/** Custom data that is stored into the server manager save game */
	UPROPERTY( SaveGame )
	FFGDynamicStruct SavedCustomData;

	/** Custom data that is not saved and will be voided once the server is unloaded or removed*/
	UPROPERTY( Transient )
	FFGDynamicStruct TransientCustomData;

	/** True if we should automatically accept remote certificate. Used in development time for example to automatically add PIE server */
	bool mForceAutoAcceptRemoteCertificate{false};
private:
	/** Current state of the Server API. */
	EFGServerAPIState mServerAPIState{ EFGServerAPIState::Unavailable };

	/** Name of the Server, as reported by the remote dedicated server. */
	UPROPERTY( SaveGame )
	FString mServerName;

	/** Raw "hostname" of this server, as it has been added by the user. This is before DNS lookup, and can represent either a hostname or a Raw IP string */
	UPROPERTY( SaveGame )
	FString mServerHostname;

	/**
	 * A list of resolved addresses to be used for querying the server using the lightweight query.
	 * We do not use the results of solving for Server API or Joining Games, both do Address Resolution by themselves already.
	 */
	TArray<TSharedPtr<FInternetAddr>> mSolvedAddresses;

	/** Authentication token that the client has obtained since the last communication with the server. */
	UPROPERTY( SaveGame )
	FServerAuthenticationToken mAuthenticationToken;

	/** Current state of the game on the server*/
	UPROPERTY( Transient )
	FServerGameState mGameState;

	/** Query port, as it has been set by the user. Keep in mind that if the user did not set the port or the server was resolved via the SRV record, this will be INDEX_NONE */
	UPROPERTY( SaveGame )
	int32 mQueryPort;

	/** The certificate that the server has presented and the player has agreed to trust */
	UPROPERTY( SaveGame )
	FFGServerCertificate mServerCertificate;

	/** Current state of the server */
	EServerState mServerState = EServerState::Offline;

	/** Returns the changelist that the server is running in remote. */
	int32 mServerNetCL{0};

	/** Server flags set on the remote server. They determine compatibility and other preconditions and can be queried. */
	EServerFlags mServerFlags{};

	/** Average ping time to the server and back */
	int32 mAverageRoundtripTimeMs{0};

	/** A log of the server console. Only gets populated with the feedback to the user commands, does not actually do any logging from the server. */
	FString mServerConsole;

	/** UI proxy handling the UI requests from this server for user input. Usually does so by showing the action pop-ups */
	UPROPERTY( Transient )
	TScriptInterface<IFGDedicatedServerUIProxy> mServerUIProxy;

	/** List of all of the listeners that want to be notified when the state of this server changes. Array of IFGServerStateListener, but unfortunately UHT is stupid. */
	UPROPERTY( Transient )
	TArray<TScriptInterface<IFGServerStateListener>> mStateListeners;
	
	TArray<FString> mCommandHistory;
	int32 mHistoryIndex = 0;

	/** True if we are waiting for a result of the console command execution */
	uint8 mWaitingForConsoleResult : 1;
	/** True if we are waiting on the server state to be join-able so we can join immediately */
	uint8 mWaitingToJoinGame : 1;
	/** True if we are actively authenticating right now */
	uint8 mAuthenticationPending : 1;
	/** True if we are currently in the Join Game flow and should not attempt to client travel again */
	uint8 mJoinGamePending : 1;
	/** True if we have attempted to access the Server API but got a certificate that we do not trust by default, and need the user to confirm it. */
	uint8 mWaitingForServerCertificateConfirmation : 1;
	/** True if we are currently waiting on a result of a health check */
	uint8 mHealthCheckInProgress : 1;
	/** True if we have accepted the certificate while the health check was still in progress. That means we will need to immediately re-schedule it later */
	uint8 mCertificateAcceptedDuringHealthCheck : 1;
	/** True if we are waiting for the LoadGame response */
	uint8 mWaitingForLoadGameResponse: 1;
	/** True if we are waiting for the CreateNewGame response */
	uint8 mWaitingForCreateNewGameResponse: 1;

	/** True if we are currently fetching the game state */
	uint8 mFetchingGameState: 1;
	/** True if we are currently fetching the server options */
	uint8 mFetchingServerOptions : 1;
	/** True if we are currently fetching the advanced game settings */
	uint8 mFetchingAdvancedGameSettings: 1;
	/** A list of delegates that are waiting for the result of save session enumeration. Stored as a class member so that multiple listeners can use the same request. */
	TArray<FOnSaveManagerEnumerateSessionsComplete> mListenersWaitingForEnumerateSaveSessions;

	/** Response from the last health check, regardless of whenever it has completed successfully or failed */
	FFGServerErrorResponse mLastHealthCheckResponse;

	/** Cached sub state version IDs */
	TMap<EServerSubStateId, uint16> mCachedSubStateVersions;
	/** Bits set for each dirty sub state ID we have */
	TSet<EServerSubStateId> mDirtySubStateIdsBitset;

	/** True if the server is currently active in the server manager */
	bool mServerCurrentlyActiveInServerManager{false};
	/** Total number of the save game transfers that are currently pending. Usually either 1 or 0 */
	int32 mNumPendingSaveGameTransfers;
	/** Delta time accumulated between the frames. Used to increment play duration in integral steps */
	float mAccumulatedDeltaTime;

	FServerNetStats mNetStats;

	/** True if the server has advanced game settings enabled right now */
	bool mAdvancedGameSettingsEnabled;
	/** Cached claimed server name when we are claiming the server */
	FString mCachedClaimedServerName;

	UPROPERTY( Transient )
	UFGClientAPIManager* mClientAPIManager;

	UPROPERTY( Transient )
	UFGClientRequesterArray* mClientRequesterArray;

	UPROPERTY( Transient )
	UFGServerObjectOptionAdapter* mServerOptionsAdapter;

	UPROPERTY( Transient )
	UFGServerObjectOptionAdapter* mAdvancedGameSettingsAdapter;

	UPROPERTY( Transient )
	UFGServerObjectOptionAdapter* mNewGameAdvancedGameSettings;
};

// This interface had to be moved to this file unfortunately because UHT is dumb and claims that there is a circular dependency between it and FGServerObject, when there is not.
UINTERFACE( Blueprintable )
class FACTORYDEDICATEDCLIENT_API UFGServerStateListener : public UInterface
{
	GENERATED_BODY()
};

/*
 * A Server state listener is a utility interface available both to native code and blueprints that makes it possible to listen for any server
 * state changes. For a listener to receive notifications, it needs to register itself with a @UFGServerObject::RegisterStateListener
 * Similarly, once a listener does not want to receive notification any more it can unregister itself by calling @UFGServerObject::UnRegisterStateListener
 **/ 
class FACTORYDEDICATEDCLIENT_API IFGServerStateListener
{
	GENERATED_BODY()
public:
	virtual void NativeOnServerStateChanged( UFGServerObject* Server, EServerState State );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server State Changed" ) )
	void BP_OnServerStateChanged( UFGServerObject* Server, EServerState State );

	virtual void NativeOnServerGameStateChanged( UFGServerObject* Server, const FServerGameState& GameState );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Game State Changed" ) )
	void BP_OnServerGameStateChanged( UFGServerObject* Server, const FServerGameState& GameState );

	virtual void NativeOnServerAPIStateChanged( UFGServerObject* Server, EFGServerAPIState ServerAPIState );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server API State Changed" ) )
	void BP_OnServerAPIStateChanged( UFGServerObject* Server, EFGServerAPIState ServerAPIState );
	
	virtual void NativeOnServerAuthenticationChanged( UFGServerObject* Server, const FServerAuthenticationToken& AuthToken );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Authentication State Changed" ) )
	void BP_OnServerAuthenticationChanged( UFGServerObject* Server, const FServerAuthenticationToken& AuthToken );

	virtual void NativeOnServerRenamed( UFGServerObject* Server, const FString& Name );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Renamed" ) )
	void BP_OnServerRenamed( UFGServerObject* Server, const FString& Name );

	virtual void NativeOnServerComplexStateChanged( UFGServerObject* Server, EServerComplexState State );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On Server Complex State Changed" ) )
	void BP_OnServerComplexStateChanged( UFGServerObject* Server, EServerComplexState State );

	virtual void NativeOnNewServerConsoleOutput( UFGServerObject* Server, const FString& NewOutput );
	UFUNCTION( BlueprintImplementableEvent, Category = "Server Info Listener", meta = ( DisplayName = "On New Server Console Output" ) )
	void BP_OnNewServerConsoleOutput( UFGServerObject* Server, const FString& ConsoleOutput );
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGSaveManagerInterface.h"
#include "UObject/Object.h"
#include "Server/FGDedicatedServerTypes.h"
#include "OnlineBeaconClient.h"
#include "FGServerObject.generated.h"


struct FServerQueryAddressInfo
{
	TSharedPtr< class FInternetAddr > Address;
	class FClientQuerySocket* QuerySocket = nullptr;
};

/**
* Holds information about dedicated servers that we know about
* Typically, a server gets to be known about by connecting to it
**/ 
UCLASS( BlueprintType, Within=FGServerManager )
class FACTORYGAME_API UFGServerObject : public UObject, public IFGSaveManagerInterface
{
	GENERATED_BODY()
	friend class UFGServerManager;
	friend class AFGServerBeaconClient;
public:
	UFGServerObject();
	
	UFUNCTION( BlueprintCallable, Category = Server )
	bool Join();

	UFUNCTION( BlueprintCallable, Category = Server )
	bool IsConnected() const;

	UFUNCTION( BlueprintCallable, Category = Server )
	void CreateGame( const FString& SessionName, const FString& StartingLocation, bool JoinOnceLoaded );

	UFUNCTION( BlueprintCallable, Category = Server )
	void ConsoleCommand( const FString& Command );

	// IFGSaveManagerInterface overrides
	virtual void EnumerateSessions(const FOnSaveManagerEnumerateSessionsComplete& CompleteDelegate) override;
	virtual bool IsEnumeratingLocalSaves() override;
	virtual bool IsSaveManagerAvailable() override;
	virtual void DeleteSaveFile(const FSaveHeader& SaveGame, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual void DeleteSaveSession(const FSessionSaveStruct& Session, FOnSaveMgrInterfaceDeleteSaveGameComplete CompleteDelegate) override;
	virtual void LoadSaveFile(const FSaveHeader& SaveGame,  class APlayerController* Player) override;
	virtual void SaveGame(const FString& SaveName, FOnSaveMgrInterfaceSaveGameComplete CompleteDelegate) override;
	virtual void UploadSave(const FSaveHeader& Save, FOnSaveManagerTransferCompleted CompleteDelegate, FOnSaveManagerTransferProgress ProgressDelegate) override;
	virtual bool IsTransferInProgress() override;
	//
	
	const FString& GetServerName() const
	{
		return ServerName;
	}

	const FString& GetAddress() const
	{
		return Address;
	}

	int32 GetQueryPort() const
	{
		return QueryPort;
	}

	uint16 GetBeaconPort() const
	{
		return ServerBeaconPort;
	}

	int32 GetGamePort() const
	{
		return ServerGamePort;
	}

	const FServerGameState& GetGameState() const
	{
		return GameState;
	}

	const FServerAuthenticationToken& GetAuthenticationToken() const
	{
		return AuthenticationToken;
	}

	UFUNCTION( BlueprintCallable, BlueprintPure )
	EBeaconConnectionState GetConnectionState();

	void SetServerState( EServerState NewState );
	EServerState GetServerState() const
	{
		return ServerState;
	}

	const TArray<FServerQueryAddressInfo>& GetQueryAddresses() const
	{
		return SolvedAddresses;
	} 

	UFUNCTION( BlueprintCallable )
	void RegisterStateListener( TScriptInterface< class IFGServerStateListener> Listener );

	UFUNCTION( BlueprintCallable )
	void UnRegisterStateListener( TScriptInterface< class IFGServerStateListener> Listener );

	UFUNCTION( BlueprintCallable )
	EServerComplexState GetComplexState();

	UFUNCTION( BlueprintCallable )
	void Authenticate( EPrivilegeLevel MinimumTargetedPrivilege );

	UFUNCTION( BlueprintCallable )
	FString PullCommandFromHistory( bool GoBackInTime );

	UFUNCTION( BlueprintCallable )
	void SetAutoPause( bool AutoPause );

	UFUNCTION( BlueprintCallable )
	void SetAutoSaveOnDisconnect( bool AutoSave );

	UFUNCTION( BlueprintCallable )
	void SetAutoLoadSessionName( const FString& SessionName );

	UFUNCTION( BlueprintCallable )
	void ChangeAdminPassword();

	UFUNCTION( BlueprintCallable )
	void FetchGameState();
	
	UFUNCTION( BlueprintCallable )
	void ChangeClientPassword();

	UFUNCTION( BlueprintCallable )
	void ChangeServerName( const FString& NewServerName );

	void CustomSerialize(FStructuredArchive::FRecord Record, EServerManagerVersion Version);
private:
	void SetAuthenticationToken( const FServerAuthenticationToken& Token );
	// @todo: Naming is confusing
	void SetServerName( const FString& ServerName );
	void NotifyComplexStateChange();
	void ProcessServerStatePollResponse( const struct FServerStatePollResponse& Beat );
	void PollState();
	class UFGServerManager& GetOuterServerManager() const;
	void ServerSavesUpdated() const;
	
protected:
	virtual void BeginDestroy() override;
	void SaveState() const;

	void DropConnection();
	
	UFUNCTION( BlueprintCallable )
	void EnsureConnected();
	
	void AutoConnect();
	bool IsPollingServerState();
	void PurgeDeadListeners();
	
	UPROPERTY( BlueprintReadOnly, SaveGame )
	FString ServerName;

	/// The actual address of this server, after DNS lookup.
	UPROPERTY( BlueprintReadOnly, SaveGame )
	FString Address;
	
	TArray< FServerQueryAddressInfo > SolvedAddresses;
	
	UPROPERTY( BlueprintReadOnly, SaveGame )
	FServerAuthenticationToken AuthenticationToken;

	UPROPERTY( BlueprintReadOnly, Transient )
	FServerGameState GameState;

	UPROPERTY( BlueprintReadOnly, Transient )
	FServerBasicSettings BasicSettings;

	/// An array with all addresses that the user has ever tried to connect to this server with. These can be IP address or they can be domain names.
	/// Many strings may lead to the same address hence the need for an array (eg: localhost,127.0.0.1 -> 127.0.0.1 )
	UPROPERTY( BlueprintReadOnly, SaveGame )
	TArray<FString> BeforeDNSLookupAddresses;

	/// An alias the player has assigned to this server, if any
	UPROPERTY( BlueprintReadOnly, SaveGame )
	FString Alias;

	UPROPERTY( BlueprintReadOnly, SaveGame )
	int32 QueryPort;

	UPROPERTY( BlueprintReadOnly, Transient )
	EServerState ServerState = EServerState::Offline;

	UPROPERTY( BlueprintReadOnly, Transient )
	int32 mAverageRoundtripTimeMs;

	UPROPERTY( BlueprintReadOnly, Transient )
	FString mServerConsole;

	UPROPERTY( BlueprintReadOnly, Transient )
	int32 ServerNetCL = 0;

	/// The beacon port of this server
	int32 ServerBeaconPort = 0;

	uint32 ServerGamePort = 0; 
	UPROPERTY( Transient )
	class AFGServerBeaconClient* ServerConnection = nullptr;

	UPROPERTY( Transient )
	TArray< TScriptInterface<class IFGServerStateListener> > mStateListeners;
	
	TArray< FString > mCommandHistory;
	int32 mHistoryIndex = 0;
	
	UPROPERTY( BlueprintReadOnly, Transient )
	uint8 mWaitingForConsoleResult : 1;

	uint8 mConnectionAttemptFailed : 1;
	uint8 mWaitingToJoinGame : 1;
	FServerNetStats mNetStats;
	
	void SetGameState( const FServerGameState& NewState );
	void SetBasicSettings( const FServerBasicSettings& Settings );
	bool HasValidConnection() const;

	void ServerConnected( AFGServerBeaconClient& Connection );
	void ServerConnectionFailure( AFGServerBeaconClient& Connection );
	void ServerDisconnected();
	void ConnectionStateChanged( EBeaconConnectionState State );

	TArray<FSessionSaveStruct> CachedSessions;
	int32 CachedCurrentSession = -1;
};

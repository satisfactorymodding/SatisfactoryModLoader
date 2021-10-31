// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Server/FGDedicatedServerTypes.h"
#include "OnlineBeaconClient.h"
#include "FGServerObject.generated.h"


/**
* Holds information about dedicated servers that we know about
* Typically, a server gets to be known about by connecting to it
**/ 
UCLASS( BlueprintType, Within=FGServerManager )
class FACTORYGAME_API UFGServerObject : public UObject
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
	void UploadSave( const struct FSaveHeader& SaveHeader, bool LoadImmediately );

	UFUNCTION( BlueprintCallable, Category = Server )
	void ConsoleCommand( const FString& Command );

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
		return mNetStats.ServerBeaconPort;
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
	void ChangeClientPassword();

	UFUNCTION( BlueprintCallable )
	void ChangeServerName( const FString& NewServerName );

private:
	void SetAuthenticationToken( const FServerAuthenticationToken& Token );
	// @todo: Naming is confusing
	void SetServerName( const FString& ServerName );
	void NotifyComplexStateChange();
	void ProcessServerStatePollResponse( const struct FServerStatePollResponse& Beat );
	void CheckServerHealth();
	
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
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "OnlineBeaconClient.h"
#include "Server/FGDedicatedServerTypes.h"
#include "FGSaveSystem.h"

#include "FGServerBeaconClient.generated.h"

DECLARE_LOG_CATEGORY_EXTERN( LogServerConnection, Log, Log );

DECLARE_DELEGATE_TwoParams( FOnJoinRequestAccepted, int32 Port, FServerEntryToken Ticket );

DECLARE_DELEGATE_TwoParams( FOnServerConnectionEstablished, class AFGServerBeaconClient& ServerConnection, const FString& ServerName );
DECLARE_DELEGATE_OneParam( FOnServerConnectionFailure, class AFGServerBeaconClient& ServerConnection );
DECLARE_DELEGATE_TwoParams( FOnServerCommandExecuted, const FString& Command, const FString& Result );
DECLARE_DELEGATE_TwoParams( FOnServerOperationCompleted, bool Success, const FText& ErrorMessage );
DECLARE_DELEGATE_ThreeParams( FOnTransferCompletedInternal, class FLargeDataTransfer& Transfer, bool Success, const FText& ErrorMessage );
DECLARE_DELEGATE_TwoParams( FOnTransferCompleted, bool Success, const FText& ErrorMessage );
DECLARE_DELEGATE_TwoParams( FOnTransferProgress, int32 Progress, int32 Total );

UCLASS( Abstract, Blueprintable, BlueprintType )
class FACTORYGAME_API UFGBaseServerInteractionHandler : public UObject, public IFGDedicatedServerUIProxy
{
	GENERATED_BODY()
public:
	virtual UWorld* GetWorld() const override;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	UWorld* World = nullptr;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	APlayerController* OwningPlayer = nullptr;

	UFUNCTION( BlueprintCallable, BlueprintPure )
	static FText GetServerMessageDescription( EServerMessage Message );
};

class FLargeDataTransfer
{
public:
	FLargeDataTransfer( const TArray<uint8>& Data, FOnTransferCompletedInternal OnTransferCompletedInternal, FOnTransferCompleted OnTransferCompleted, FOnTransferProgress OnTransferProgress);
	FLargeDataTransfer( const FGuid& ID, int32 Size );
	
	FLargeDataTransfer( const FLargeDataTransfer&) = delete;
	FLargeDataTransfer( FLargeDataTransfer&& ) = default;
	FLargeDataTransfer& operator=(const FLargeDataTransfer&) = delete;
	FLargeDataTransfer& operator=(FLargeDataTransfer&&) = delete;

	bool operator==(const FLargeDataTransfer& Other ) const;

	TArray<uint8> GetChunk( int32 Chunk ) const;
	bool SetChunk( int32 Chunk, const TArray<uint8>& ChunkData );
	int32 NumChunks() const;
	int32 NumTransferredChunks() const;
	void ChunkTransferred();
	const FGuid& GetID() const;
	const FOnTransferCompleted& OnTransferCompleted() const;
	const FOnTransferProgress& OnTransferProgress() const;
	const FOnTransferCompletedInternal& OnTransferCompletedInternal() const;
	
	const TArray<uint8>& GetData() const
	{
		return mData;
	} 
private:
	const int32 mNumChunks;
	int32 mTransferredChunks = 0;
	TArray<uint8> mData;
	FGuid mTransferID;
	FOnTransferCompleted mOnTransferCompleted;
	FOnTransferProgress mOnTransferProgress;
	FOnTransferCompletedInternal mOnTransferCompletedInternal;
};

/**
 * A beacon connection can make light connections to a server without having to load in the whole map. Ideal for dedicated servers
 * since it can be used to work with a server while sitting in the main menu. Very secure, can safely transport secrets such as passwords
 * since it uses DTLS as an underlying protocol. All sensitive data should go through this channel.
 */
UCLASS( BlueprintType )
class FACTORYGAME_API AFGServerBeaconClient : public AOnlineBeaconClient
{
	GENERATED_BODY()
public:
	/// Initiates a connection to the dedicated server specified by @ServerAdress. Uses @UIProxy if the server asks for user input.
	/// UIProxy !!must!! be a living object
	/// This needs to be called before any other methods on this class may be called.
	/// Should be used in conjunction with @OnConnectionEstablished and @OnConnectionFailure
	void Connect( class UFGServerObject* ServerInfoObject, TScriptInterface<IFGDedicatedServerUIProxy> UIProxy );

	/// Asks the server for a game entry token which can later be used to join the game. Must be called once connected to the server
	void JoinGame( FOnJoinRequestAccepted OnJoinRequestAccepted );

	/// Change server admin password
	UFUNCTION( Server, Reliable )
	void ChangeAdminPassword();

	/// Change server client password
	UFUNCTION( Server, Reliable )
	void ChangeClientPassword();

	/// Cancels any operations that are currently in progress
	UFUNCTION( Server, Reliable )
	void CancelOperation();

	/// Uploads a save file to the server
	void UploadSaveGame( const FSaveHeader& SaveGame, FOnTransferCompleted CompleteDelegate, FOnTransferProgress ProgressDelegate );

	bool HasOngoingTransfers() const; 
	
	/// Shuts down the server
	UFUNCTION( Server, Reliable )
	void Shutdown_Server();

	/// Runs a console command on the server
	void ConsoleCommand( const FString& Command, FOnServerCommandExecuted OnCompletion );

	void QueryServerState();

	UFUNCTION( Server, Reliable )
	void CreateGame_Server( const FString& Name, const FString& StartLoc );

	UFUNCTION( Server, Reliable )
	void AuthenticationRequest( const FServerAuthenticationToken &CurrentAuth, EPrivilegeLevel MinimumPrivilege );
	
	const FServerAuthenticationToken& GetAuthenticationToken() const
	{
		return mAuthenticationToken;
	}

	UFUNCTION( Client, Reliable )
	void GameStateUpdate( const FServerGameState& Response );
	
	UFUNCTION( Client, Reliable )
	void BasicSettingsUpdate( const FServerBasicSettings& BasicSettings );

	/// Temporary setters until a better way to handle server settings is identified
	UFUNCTION( Server, Reliable, WithValidation )
	void SetAutoPause( bool AutoPause );

	UFUNCTION( Server, Reliable, WithValidation )
	void SetAutoSaveOnDisconnect( bool AutoSaveOnDisconnect );

	UFUNCTION( Server, Reliable, WithValidation )
	void SetAutoLoadSessionName( const FString &SessionName );

	/// Changes the server name
	UFUNCTION( Server, Reliable )
	void RenameServer( const FString& ServerName );

	void EnumerateSaveSessions( FOnEnumerateSessionsComplete OnCompletion, void* UserData );
	void SaveGame( const FString& SaveName, FOnServerOperationCompleted OnCompletion );
	void DeleteSaveFile(const FSaveHeader& SaveGame, FOnDeleteSaveGameComplete CompleteDelegate, void* UserData );
	void DeleteSaveSession(const FSessionSaveStruct& Session, FOnDeleteSaveGameComplete CompleteDelegate, void* UserData );
	
	UFUNCTION( Server, Reliable )
	void LoadSaveFile(const FSaveHeader& SaveGame); 	

protected:
	virtual void OnConnected() override;
	virtual void OnFailure() override;
	virtual void OnNetCleanup(UNetConnection* Connection) override;
	virtual void SetConnectionState(EBeaconConnectionState NewConnectionState) override;
private:

	enum class EPendingOperation : int8
	{
		RenameServer,
		JoinGameRequest,
		SetAdminPassword,
		SetClientPassword,
		RequestCreateGame,
		ChangeAdminPassword,
		ChangeClientPassword,
		CreateGame,
		LargeDataTransferBegin,
		Shutdown,
		Command,
		ServerStateQuery
	};

	struct FPendingOperationState
	{
		FPendingOperationState( EPendingOperation Op, EPrivilegeLevel RP )
			: PendingOperation( Op )
			, RequiredPrivilege( RP )
		{}
		
		EPendingOperation PendingOperation;
		EPrivilegeLevel RequiredPrivilege;
	};
	
	template<typename... Ts>
	struct TPendingOperationStateParams : public FPendingOperationState, public TTuple<Ts...>
	{
		template <typename ...TParams>
		TPendingOperationStateParams( EPendingOperation Op, EPrivilegeLevel RP, TParams&&... Params )
			: FPendingOperationState( Op, RP )
			, TTuple<Ts...>( std::forward<TParams>(Params)...) {}
	};

	TArray<TUniquePtr<FPendingOperationState>> mPendingOperationsStack;
	
	/// Hashes the password and forwards it to the server to be verified. It may be either an admin or client password
	UFUNCTION()
	void TryPassword( const FString& Password, EPrivilegeLevel MinimumTargetPrivilege );

	/// Sets the admin password
	UFUNCTION()
	void SetAdminPassword( const FString& Password );

	/// Creates a new game on the server
	UFUNCTION()
	void CreateGame( const FString& Name, const FString& StartLoc );

	/// Sets the join password
	UFUNCTION()
	void SetClientPassword( const FString& Password );

	/// Initiates a large data transfer to the server.This creates state on the server which is then augmented using follow-up methods defined below 
	UFUNCTION( Server, Reliable )
	void LargeDataTransfer_Begin_C2S( const FGuid& TransferID, int32 TransferSize );

	/// Server acknowledges the beginning of a large data transfer and is ready to receive the chunks
	UFUNCTION( Client, Reliable )
	void LargeDataTransfer_AcknowledgeBegin_C2S( const FGuid& TransferID );

	/// Transfers a chunk of a large data transfer. 
	UFUNCTION( Server, Reliable, WithValidation )
	void LargeDataTransfer_Chunk_C2S( const FGuid& TransferID, int32 ChunkIx, const TArray<uint8>& ChunkData );

	/// Server acknowledges the transfer of a large data transfer chunk and is ready to receive another
	UFUNCTION( Client, Reliable )
	void LargeDataTransfer_AcknowledgeChunk_C2S( const FGuid& TransferID, int32 ChunkIx );

	/// Asks the server to cleanup a large data transfer - essentially to free up all state pertaining to a respective transfer
	UFUNCTION( Server, Reliable, WithValidation )
	void LargeDataTransfer_Cleanup_C2S( const FGuid& TransferID );

	/// Writes the contents of a completed large data transfer to a save file and optionally loads it immediately. 
	UFUNCTION( Server, Reliable )
	void Request_WriteRawBufferToSaveFile_Server( const FGuid& BufferID, const FString& SaveName, bool CleanTransfer = true );

	UFUNCTION( Client, Reliable )
	void Response_WriteRawBufferToSaveFile_Server( const FGuid& BufferID, bool Success, const FText& Error );

	/// Cleans up all state associated to a data transfer
	FLargeDataTransfer* GetTransfer(FGuid ID);
	void DropTransfer(FGuid ID);

	/// Parses a url into hostname and port. 
	static bool ParseURL( const FString &URL, FString& Host, int16& Port);

	UFUNCTION( Server, Reliable )
	void JoinGameRequest_Server();

	UFUNCTION( Client, Reliable )
	void JoinGameResponse(int32 ListenPort, FServerEntryToken Ticket );
	
	UFUNCTION( Server, Reliable )
	void SetClientPassword_Server( const FString& NewJoinPassword );

	UFUNCTION( Server, Reliable )
	void SetAdminPassword_Server( const FString& NewHashedPassword );

	/// First message sent by the client to the server when the beacon is connected
	UFUNCTION( Server, Reliable )
	void ClientHello( const FServerAuthenticationToken& Cookie );

	/// Server introduces itself to the client once authentication has been completed
	UFUNCTION( Client, Reliable )
	void ServerHello( const FString& ServerName, const FServerAuthenticationToken& Cookie );

	UFUNCTION( Client, Reliable )
	void UpdateAuthToken( const FServerAuthenticationToken& Cookie );

	UFUNCTION( Client, Reliable )
	void UpdateServerName( const FString& NewName );
	
	UFUNCTION( Server, Reliable )
	void TryPassword_Server( const FString& HashedPassword, EPrivilegeLevel MinimumTargetPrivilege );

	/// The server is asking the client for a password
	UFUNCTION( Client, Reliable )
	void RequestPassword( EPrivilegeLevel MinimumPrivilege );

	UFUNCTION( Client, Reliable )
	void ServerMessage( EServerMessage Message );

	/// Runs a console command on the server
	UFUNCTION( Server, Reliable, BlueprintCallable )
	void Command_Server( const FGuid& ID, const FString& Command );

	UFUNCTION( Client, Reliable )
	void CommandCompleted( const FGuid& ID, const FString& Result );

	UFUNCTION( Client, Reliable )
	void GreetAsUnclaimedServer();

	UFUNCTION( Client, Reliable )
	void RequestSetAdminPassword();

	UFUNCTION( Client, Reliable )
	void RequestSetClientPassword();

	UFUNCTION( Client, Reliable )
	void RequestCreateGame();

	UFUNCTION( Client, Reliable )
	void PasswordRejected();

	UFUNCTION( Server, Reliable )
	void QueryServerState_Server();

	UFUNCTION( Server, Reliable )
	void Request_EnumerateSessions( const FGuid& RequestID );

	UFUNCTION( Client, Reliable )
	void Response_EnumerateSessions( const FGuid& RequestID, bool Success, const TArray<FSessionSaveStruct> &Sessions, int32 CurrentSessionIx );

	UFUNCTION( Server, Reliable )
	void SaveGameRequest( const FGuid& RequestID, const FString& SaveName );

	UFUNCTION( Client, Reliable )
	void SaveGameResponse( const FGuid& RequestID, bool Success, const FText& ErrorMessage );

	UFUNCTION( Server, Reliable )
	void DeleteSaveFileRequest( const FGuid& RequestID, const FSaveHeader& SaveGame );

	UFUNCTION( Client, Reliable )
	void DeleteSaveFileResponse( const FGuid& RequestID, bool Success );

	UFUNCTION( Server, Reliable )
	void DeleteSaveSessionRequest( const FGuid& RequestID, const FSessionSaveStruct& Session );

	UFUNCTION( Client, Reliable )
	void DeleteSaveSessionResponse( const FGuid& RequestID, bool Success );

	friend class AFGServerBeaconHostObject;
	UFUNCTION( Client, Reliable )
	void Notify_SavesCollectionChanged();
	
	UPROPERTY()
	TScriptInterface<class IFGDedicatedServerUIProxy> mUIProxy;
	
	int mPasswordsAttemptsLeft = 5;

	void PasswordPrompt( EPrivilegeLevel MinimumTargetPrivilege );

	FOnJoinRequestAccepted mOnJoinRequestAccepted;
	TMap< FGuid, TPair<FString, FOnServerCommandExecuted > > mCommandExecutedDelegates;
	TMap< FGuid, FOnEnumerateSaveGamesComplete > mEnumerateSavegamesDelegates;
	TMap< FGuid, TPair< FOnEnumerateSessionsComplete, void* > > mEnumerateSessionsCompleteDelegates;
	TMap< FGuid, TPair<FOnDeleteSaveGameComplete, void*> > mDeleteSaveRequestDelegates;
	TMap< FGuid, FOnServerOperationCompleted > mPendingOperationsDelegates; 
	
	/// Authentication token. Contains level of privilege. 
	FServerAuthenticationToken mAuthenticationToken;

	FServerCancelOperationCallback mCancelOperationCallback;
	/// Large data transfers that are ongoing
	TArray<FLargeDataTransfer> mLargeDataTransfers;

	UPROPERTY()
	class UFGServerObject *mServerInfoObject = nullptr;
};

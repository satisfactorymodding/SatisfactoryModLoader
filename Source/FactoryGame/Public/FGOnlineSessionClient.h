// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "FGOnlineSessionSettings.h"
#include "OnlineSessionClient.h"
#include "FGOnlineSessionClient.generated.h"

USTRUCT(BlueprintType)
struct FPendingInvite
{
	GENERATED_BODY();
public:
	FORCEINLINE bool IsValid() const{ return Receiver.IsValid() && Sender.IsValid(); }

#if !UE_BUILD_SHIPPING
	FString ToDebugString() const;
#endif

	/** Who was the invite intended to, mostly redundant, as we don't support splitscreen */
	TSharedPtr<const FUniqueNetId> Receiver;

	/** Id of the sender of the invite */
	TSharedPtr<const FUniqueNetId> Sender;

	/** Session the invite was sent from */
	//TSharedPtr<const FUniqueNetId> SendFromSession;

	/** Information about the session the user is playing in */
	FOnlineSessionSearchResult SearchResult;
};

bool operator == ( const FPendingInvite& a, const FPendingInvite& b );

#if !UE_BUILD_SHIPPING
FORCEINLINE FString VarToFString( FPendingInvite var ){ return FString::Printf( TEXT( "%s" ), *var.ToDebugString() ); }
#endif

FORCEINLINE uint32 GetTypeHash( const FPendingInvite& invite )
{
	if( invite.IsValid() )
	{
		return HashCombine( GetTypeHash( invite.Sender.ToSharedRef() ), GetTypeHash( invite.Receiver.ToSharedRef() ) );
	}	

	return 0;
}

UENUM(BlueprintType)
enum class ECreateSessionState : uint8
{
	CSS_NotCreateingSession,
	CSS_CreatingSession,
	CSS_DestroyingOldSession,
	CSS_UpdatingPresence,
	CSS_WaitingForPresenceToUpdate,
	CSS_WaitingForLogin
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCreateSessionStateChanged, ECreateSessionState, newState );
DECLARE_DELEGATE_OneParam( FOnOnlineSessionCreated, FOnlineSession* );

struct FSessionInformation
{
	FSessionInformation() :
		MapName(TEXT("")),
		Options(TEXT("")),
		SaveSessionName(TEXT("")),
		IsSessionCreationInFlight(false),
		IsOfflineGame( false )
	{
	}

	void Init( const FString& InMapName, const FString& InOptions, const FString& InSessionName, ESessionVisibility InVisibility );
	void SendAnalytics( UWorld* world  );

	void MarkAsOffline();

	void Done()
	{
		IsSessionCreationInFlight = false;
	}

	void SetState( ECreateSessionState newState, FOnCreateSessionStateChanged& createSessionChanged );

	ECreateSessionState GetState() const { return State; }
	
	/** Map we want to travel to */
	FString MapName;
	
	/** Options when starting map */
	FString Options;
	
	/** Name of the session */
	FString SaveSessionName;
	
	/** Session visibility */
	ESessionVisibility Visibility;

	/** The name of the visiblity string passed */
	static const TCHAR* VisibilityOptionName;
	static const TCHAR* IpSocketString;

	/** If true, we are creating a session and won't try to create any other at the same time */
	bool IsSessionCreationInFlight;

	/** If true, then we are creating a offline game */
	bool IsOfflineGame;

	FOnOnlineSessionCreated OnOnlineSessionCreated;
private:
	ECreateSessionState State;
};

/**
 * @OSS: responsibility
 * - HandleInvites
 * Will detect that we receive a invite and expose functionality to join invites and react to the invite
 */
UCLASS()
class UFGOnlineSessionClient : public UOnlineSessionClient
{
	GENERATED_BODY()
public:
	UFGOnlineSessionClient();
	//~Begin UOnlineSession interface
	virtual void RegisterOnlineDelegates() override;
	virtual void ClearOnlineDelegates();
	virtual void HandleDisconnect( UWorld* world, UNetDriver* netDriver ) override;
	//~End UOnlineSession interface

	/** Get invites that hasn't been accepted yet */
	void GetPendingInvites( TArray<FPendingInvite>& out_invites );

	/** Accept a invite */
	void AcceptInvite( const FPendingInvite& invite );

	/** Properly join a game session and destroy existing session */
	void JoinGameSession( const FOnlineSessionSearchResult& gameSession );

	/** Discard a invite from our pending invites */
	void DiscardInvite( const FPendingInvite& invite );

	void OnSessionInviteAccepted(bool bWasSuccess, int32 controllerId, TSharedPtr<const FUniqueNetId> userId, const FOnlineSessionSearchResult& inviteResult);

	/// Set up a game session and traver to map
	void SetupServerAndTravelToMap( const FString& mapName, const FString& options, const FString& sessionName, ESessionVisibility visibility, FOnOnlineSessionCreated SessionCreatedCallback = {} );

protected:
	/** Called when the session state has changed when creating a online game */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnCreateSessionStateChanged mOnCreateSessionStateChanged;

private:
	//* Ends the current session. If successfully ended session it will call DestroyCurrentSession_SetupServer, otherwise throw an error */
	void EndCurrentSession_SetupServer( FName sessionName );

	//* Destroys the current session. If successfully destroyed session it will call OnPreviousSessionCleanedup_SetupServer, otherwise throw an error */
	void DestroyCurrentSession_SetupServer( FName sessionName );
	
	void OnPreviousSessionCleanedup_SetupServer( FName sessionName, bool wasSuccessful );
	void OnSessionCreated_SetupServer( FName sessionName, bool wasSuccessful );

	/** Create a offline session */
	UFUNCTION()
	void CreateOfflineSession_SetupServer( bool startOffline );

	/** Called on end of SetupServer-chain, waiting for presence to be properly updated */
	UFUNCTION()
	void OpenMap_WaitForPresence();

	/** Called on end of SetupServer-chain, waiting for presence to be properly updated */
	UFUNCTION()
	void OpenMap_WaitForProductUserId();

	/** Pulls the current state of creating a session */
	UFUNCTION(BlueprintPure,Category="FactoryGame|Session")
	ECreateSessionState GetCurrentCreateSessionState() const;

	/** Exits current setup of server and throws an error message popup */
	void FailedToSetupServer();

	/** the map that's setup in progress */
	void OpenMap();

	/** Make sure we broadcast information about a recevied invite when we get enough info about it */
	void BroadcastInviteReceived( int32 localUserNum, const FPendingInvite& invite );

	int32 GetLocalUserId() const;
	void OnQueryUserInfoComplete( int32 localUserNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorStr );

	/** ~Begin session callbacks */
	void OnSessionInviteReceived( const FUniqueNetId& userId, const FUniqueNetId& fromId, const FString& appId, const FOnlineSessionSearchResult& inviteResult );
	void OnJoinSessionComplete( FName sessionName, EOnJoinSessionCompleteResult::Type joinResult );
	/** ~End session callbacks */

	class UFGLocalPlayer* GetLocalPlayer();

	/** ~Begin session delegates handles */
	FDelegateHandle mOnSessionInviteReceivedHandle;
	FDelegateHandle mOnSessionInviteReceivedHandleSecondary;
	FDelegateHandle mOnSessionUserInviteAcceptedHandleSecondary;
	FDelegateHandle mOnQueryUserInfoCompleteHandle;
	FDelegateHandle mOnQueryUserInfoCompleteHandleSecondary;
	/** ~End session delegates handles */

	/** Clear out all the presence data from our current players presence */
	void ClearPresenceKeys();

	// Invites with enough information to accept
	TArray<FPendingInvite> mPendingInvites;

	// Invites that we don't have enough information to be able to accept, waiting for data from OSS
	TArray<FPendingInvite> mUninitializedInvites;

	/** Information about the current session that we are setting up */
	FSessionInformation mCurrentSessionInformation;

	//only need one for session related stuff
	FDelegateHandle mSetupServer_OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle mSetupServer_OnPresenceReceivedCompleteDelegateHandle;

	class UFGLocalPlayer *mLocalPlayer = nullptr;
};

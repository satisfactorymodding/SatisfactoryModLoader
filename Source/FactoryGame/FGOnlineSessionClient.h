#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "UObject/Class.h"

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

UCLASS()
class UFGOnlineSessionClient : public UOnlineSessionClient
{
	GENERATED_BODY()
public:
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
protected:
	/** Make sure we broadcast information about a recevied invite when we get enough info about it */
	void BroadcastInviteReceived( int32 localUserNum, const FPendingInvite& invite );

	int32 GetLocalUserId() const;
	void OnQueryUserInfoComplete( int32 localUserNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorStr );

	/** ~Begin session callbacks */
	void OnSessionInviteReceived( const FUniqueNetId& userId, const FUniqueNetId& fromId, const FString& appId, const FOnlineSessionSearchResult& inviteResult );
	void OnJoinSessionComplete( FName sessionName, EOnJoinSessionCompleteResult::Type joinResult );
	/** ~End session callbacks */
protected:
	/** ~Begin session delegates handles */
	FDelegateHandle mOnSessionInviteReceivedHandle;
	FDelegateHandle mOnQueryUserInfoCompleteHandle;
	/** ~End session delegates handles */

	/** Clear out all the presence data from our current players presence */
	void ClearPresenceKeys();

	// Invites with enough information to accept
	TArray<FPendingInvite> mPendingInvites;

	// Invites that we don't have enough information to be able to accept, waiting for data from OSS
	TArray<FPendingInvite> mUninitializedInvites;
};

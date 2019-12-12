// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/World.h"
#include "Array.h"
#include "UnrealString.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGOnlineSessionSettings.h"
#include "FGOnlineSessionClient.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystemTypes.h"
#include "Online.h"
#include "FGErrorMessage.h"
#include "CoreOnline.h"
#include "FGLocalPlayer.generated.h"


UCLASS()
class UFGEM_LoggedOutFromOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_LoggedOutFromOnlineService();
};

UCLASS()
class UFGEM_LostConnectionWithOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_LostConnectionWithOnlineService();
};

UCLASS()
class UFGEM_FailedToLoginToOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_FailedToLoginToOnlineService();
};

enum EFrindsListState
{
	FLS_Invalid,
	FLS_Querying,
	FLS_Valid
};

UENUM(BlueprintType)
enum ELoginState
{
	LS_NotLoggedIn		UMETA(DisplayName="NotLoggedIn"),
	LS_LoggingIn		UMETA(DisplayName="LoggingIn"),
	LS_LoggedIn			UMETA(DisplayName="LoggedIn"),
	LS_FailedToLogin	UMETA(DisplayName="FailedToLogin")
};

USTRUCT(BlueprintType)
struct FFGOnlineFriend
{
	GENERATED_BODY()

	FFGOnlineFriend();
	FFGOnlineFriend( TSharedRef<FOnlineFriend> onlineFriend );

	FORCEINLINE bool IsValid() const{ return Friend.IsValid(); }

	FORCEINLINE bool operator==( const FFGOnlineFriend& other ) const
	{
		// If their valid check differs, then we know they are different
		if( IsValid() != other.IsValid() )
		{
			return false;
		}

		// If both are invalid, then we are equal
		if( !IsValid() && !other.IsValid() )
		{
			return true;
		}

		return Friend->GetUserId() == other.Friend->GetUserId();
	} 

	/** Internal friend data */
	TSharedPtr<FOnlineFriend> Friend;
};

FORCEINLINE FString VarToFString( const FFGOnlineFriend& f ){ return FString::Printf( TEXT(/*"%s"), *VarToFString(f.Friend->GetUserId()) MODDING EDIT*/ "")); }

FORCEINLINE uint32 GetTypeHash( const FFGOnlineFriend& onlineFriend )
{
	// WTF! WHY DOES THIS FAIL?
	if( onlineFriend.IsValid() )
	{
		return GetTypeHash( onlineFriend.Friend->GetUserId() );
	}	

	return 0;
}

struct FSessionInformation
{
	FSessionInformation() :
		MapName(TEXT("")),
		Options(TEXT("")),
		SessionName(TEXT("")),
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
	
	/** Map we want to travel to */
	FString MapName;
	/** Options when starting map */
	FString Options;
	/** Name of the session */
	FString SessionName;
	/** Session visibility */
	ESessionVisibility Visibility;

	/** The name of the visiblity string passed */
	static const TCHAR* VisibilityOptionName;

	/** If true, we are creating a session and won't try to create any other at the same time */
	bool IsSessionCreationInFlight;

	/** If true, then we are creating a offline game */
	bool IsOfflineGame;
};

// Workaround as it seems like you can't have a TArray<FFGOnlineFriends> exposed to a Dynamic multicast delegate
USTRUCT(BlueprintType)
struct FUpdatedFriends
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FFGOnlineFriend> Friends;
};


/** Called when the friends list is done with it's initial query */
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFriendsListQueried);

//DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFriendsListUpdated);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendsListUpdated, FUpdatedFriends, updatedFriends);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFriendPresenceUpdated, const FUniqueNetIdRepl&, updatedId);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameInviteReceived, const FPendingInvite&, receivedInvite);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnLoginStateChanged, ELoginState, oldState, ELoginState, newState );

// @todosession: Listen for session updates
 
/**
 * 
 */
UCLASS(BlueprintType)
class FACTORYGAME_API UFGLocalPlayer : public ULocalPlayer
{
	GENERATED_BODY()
public:
	UFGLocalPlayer();

	//~Begin ULocalPlayer interface
	virtual void PlayerAdded( class UGameViewportClient* inViewportClient, int32 inControllerID ) override;
	virtual void PlayerRemoved() override;
	//~End ULocalPlayer interface

	/** Get in what state our login is */
	UFUNCTION(BlueprintPure,Category="Online")
	FORCEINLINE TEnumAsByte<ELoginState> GetLoginState() const{ return mLoginState; }

	/** Get in what state our login is */
	UFUNCTION(BlueprintPure,Category="Online")
	FString GetUsername() const;

	/**
	 * Get the list of friends of the current user
	 * @param out_friends - the list of the friends if this returns true
	 * @return true if we have access to the list of friends, if false, then the list will be empty, then wait for mOnFriendListQueried to trigger and it will be populated
	 */
	UFUNCTION(BlueprintCallable)
	bool GetFriendList( TArray<FFGOnlineFriend>& out_friends );

	/** Try to autologin to online service, don't try again if we have failed */
	UFUNCTION(BlueprintCallable,Category="Online")
	void AutoLogin();

	// @todo: Potentially move to UFGOnlineSessionClient
	void SetupServerAndTravelToMap( const FString& mapName, const FString& options, const FString& sessionName, ESessionVisibility visibility );

	/** Make sure our session presence patches the specified presence */
	void CopySessionPresence( const TSharedRef<FOnlineUserPresence>& presence );

	/** Called regularly to update the users presence, can also be called to force update presence and delays the next presence update */
	UFUNCTION()
	void UpdatePresence();

	/** Called when we have received a invite and gotten full information about it */
	void OnInviteReceived( const FPendingInvite& invite );
protected:
	//~Begin Online Delegates
	//~Begin OnlineIdentity delegates
	void OnLoginStatusChanged( int32 localUserNum, ELoginStatus::Type previous, ELoginStatus::Type current, const FUniqueNetId& userId );
	void OnLoginComplete( int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error );
	void OnAutoLoginComplete( int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error );
	void OnConnectionStatusChanged( const FString& serviceName, EOnlineServerConnectionStatus::Type lastConnectionState, EOnlineServerConnectionStatus::Type connectionState );
	//~End OnlineIdentity delegates

	//~Begin OnlineFriends delegates
	void OnReadFriendsListComplete( int32 localUserNum, bool wasSuccessful, const FString& listName, const FString& errorStr );
	void OnFriendsChange();
	//~End OnlineFriends delegates

	//~Begin OnlineUser delegates
	//void OnQueryUserInfoComplete( int32 localUSerNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorString );
	void OnQueryUserInfoForFriendListComplete( int32 localUSerNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorString );
	//~End OnlineUnser delegates

	//~Begin OnlinePresence delegates
	void OnPresenceReceived( const class FUniqueNetId& userId, const TSharedRef<FOnlineUserPresence>& presence );
	//~End OnlinePresence deleages

	void OnSessionCleanup_SetupServer( FName sessionName, bool wasSuccessful );
	void OnSessionCreated_SetupServer( FName sessionName, bool wasSuccessful );
	void OnPresenceUpdated_SetupServer( const class FUniqueNetId& userId, const TSharedRef<FOnlineUserPresence>& presence );

	void UpdateLoginState();

	/** Create a offline session */
	UFUNCTION()
	void CreateOfflineSession_SetupServer( bool startOffline );
	//~End Online Delegates

	// @return true if we are able to autologin
	bool CanAutoLogin() const;

	/** Get the presence string we should show to other users */
	virtual FString GetPresenceString() const;

	/** Convert a login status to a login state */
	ELoginState FromLoginStatus( ELoginStatus::Type from ) const;

	/** Called on end of SetupServer-chain, opening the map */
	UFUNCTION()
	void OpenMap_SetupServer();

	// Get the unique net id of the current local player
	TSharedPtr<const FUniqueNetId> GetPlayerId() const;
protected:
	void SetLoginState( ELoginState newLoginState );

	void GetUsersWithNoData( TArray<TSharedRef<const FUniqueNetId>>& out_usersWithNoData );
private:
	// Return true if our presence has session id set
	bool PresenceHasSessionId() const;

	/** Push error and autosave the game */
	void PushErrorAndAutosave( TSubclassOf<class UFGErrorMessage> errorMessage );
protected:
	friend class UFGCheatManager;

	//~Begin OnlineFriends delegates
	FDelegateHandle mOnFriendsChangeHandle;
	//~End OnlineFriends delegates
	//~Begin OnlineIdentity delegates
	FDelegateHandle mOnLoginStatusChangeHandle;
	FDelegateHandle mOnLoginCompleteHandle;
	// Special delegate that is just setup during autologin
	FDelegateHandle mOnAutoLoginCompleteHandle;
	//~End OnlineIdentity delegates
	//~Begin OnlineUser delegates
	FDelegateHandle mOnQueryUserInfoForFriendListCompleteHandle;
	FDelegateHandle mOnPresenceReceived;

	FDelegateHandle mSetupServer_OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle mSetupServer_OnPresenceReceivedCompleteDelegateHandle;

	//~~End OnlineUser delegates

	// Handle for updating presence info
	FTimerHandle mPresenceUpdateHandle;

	// For detecting player disconnects from services
	FDelegateHandle mOnConnectionStatusChangedHandle;

	// The status of our logins
	ELoginState mLoginState;

	UPROPERTY(BlueprintAssignable,Category="Online")
	FOnLoginStateChanged mOnLoginStateChanged;

	/** Called when the friendslist has been updated (that is, a user is has added/removed you as a friend) */
	UPROPERTY(BlueprintAssignable,Category="Online")
	FOnFriendsListUpdated mOnFriendsListUpdated;

	/** Called when the friendslist has been updated (that is, a user is has added/removed you as a friend) */
	//UPROPERTY(BlueprintAssignable)
//	FOnFriendsUpdated mOnFriendsUpdated;

	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="Online")
	FOnFriendPresenceUpdated mOnFriendsPresenceUpdated;

	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="Online")
	FOnGameInviteReceived mOnInviteReceived;

	/** Current state of the friends list */
	EFrindsListState mFriendsListState;

	/** Information about the current session that we are setting up */
	FSessionInformation mCurrentSessionInformation;

	TArray<FFGOnlineFriend> mCachedFriends;

	/** If true, then we have failed to autologin, and won't try to autologin again */
	bool mFailedAutologin;
};

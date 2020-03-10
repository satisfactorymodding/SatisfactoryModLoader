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
class FACTORYGAME_API UFGEM_LoggedOutFromOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_LoggedOutFromOnlineService();

public:
	FORCEINLINE ~UFGEM_LoggedOutFromOnlineService() = default;
};

UCLASS()
class FACTORYGAME_API UFGEM_LostConnectionWithOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_LostConnectionWithOnlineService();

public:
	FORCEINLINE ~UFGEM_LostConnectionWithOnlineService() = default;
};

UCLASS()
class FACTORYGAME_API UFGEM_FailedToLoginToOnlineService : public UFGErrorMessage
{
	GENERATED_BODY()
public:
	UFGEM_FailedToLoginToOnlineService();

public:
	FORCEINLINE ~UFGEM_FailedToLoginToOnlineService() = default;
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

USTRUCT(BlueprintType)
struct FACTORYGAME_API FFGOnlineFriend
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

public:
	FORCEINLINE ~FFGOnlineFriend() = default;
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnCreateSessionStateChanged, ECreateSessionState, newState );

struct FACTORYGAME_API FSessionInformation
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

	void SetState( ECreateSessionState newState, FOnCreateSessionStateChanged& createSessionChanged );

	ECreateSessionState GetState() const { return State; }
	
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
	static const TCHAR* IpSocketString;

	/** If true, we are creating a session and won't try to create any other at the same time */
	bool IsSessionCreationInFlight;

	/** If true, then we are creating a offline game */
	bool IsOfflineGame;
private:
	ECreateSessionState State;

public:
	FORCEINLINE ~FSessionInformation() = default;
};

// Workaround as it seems like you can't have a TArray<FFGOnlineFriends> exposed to a Dynamic multicast delegate
USTRUCT(BlueprintType)
struct FACTORYGAME_API FUpdatedFriends
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TArray<FFGOnlineFriend> Friends;

public:
	FORCEINLINE ~FUpdatedFriends() = default;
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
 * @OSS: Responsibility:
 * - Login to OSS
 * EpicGameLauncher passes a access token, artifact started and a few other parameters required to be able to login. AutoLogin checks if these a valid and
 * logs in to EGS automatically when main menu starts. Note that this isn't blocking. So the user might try to start a game before he has managed
 * to properly login.
 * - UserInterface
 * This is fetching information from the backend about a online user
 * - Presence
 * Updating our presence based on what we are doing. A timer is called regurlarly, where we can update our current "PresenceString" (See UFGLocalPlayer::UpdatePresence)
 * @todo: We should most likely update this in the chain where we are trying to setup a game
 * - Copy host presence to clients
 * Whenever a client receives a presence update, it will check if it's the host of the current game, if yes, then it will copy information about that
 * game to it's own presence
 * - Friends
 * - MapTravel and Sessions:
 * (SetupServerAndTravelToMap) Tears down current session and ensures that we are in a good state for map travel. Also ensures that we are properly logged in and that all data is
 * properly propagated to the backend servers.
 * @IMPORTANT that loading games should always be done through AFGAdminInterface::LoadGame, as that handles travel on dedicated servers.
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

	/** Get the username of the current user */
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

	/** Checks if last logged in user id matches the current logged in user and if not updates the cached value */
	void RefreshRecentRegisteredEpicIdLogin();

	// Return true if we have received the Product User Id needed for hosting the game
	bool HasReceivedProductUserId() const;

	// Get the unique net id of the current local player
	TSharedPtr<const FUniqueNetId> GetPlayerId() const;
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
	UFUNCTION()
	void OnLoginFailed_OpenMap( bool confirmClicked );
	UFUNCTION()
	void OnPresenceFailedToUpdate_OpenMap( bool confirmClicked );

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

	/** Called on end of SetupServer-chain, waiting for presence to be properly updated */
	UFUNCTION()
	void OpenMap_WaitForPresence();

	/** Called on end of SetupServer-chain, waiting for presence to be properly updated */
	UFUNCTION()
	void OpenMap_WaitForProductUserId();

	/** the map that's setup in progress */
	void OpenMap();

	/** Pulls the current state of creating a session */
	UFUNCTION(BlueprintPure,Category="FactoryGame|Session")
	ECreateSessionState GetCurrentCreateSessionState() const;
protected:
	// Called whenever we get logged in
	void OnLoggedIn();
	
	// Set the login state of the local player and broadcast it
	void SetLoginState( ELoginState newLoginState );

	// Get friends that we don't have any presence data or similar for
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

	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnLoginStateChanged mOnLoginStateChanged;

	/** Called when the friendslist has been updated (that is, a user is has added/removed you as a friend) */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnFriendsListUpdated mOnFriendsListUpdated;
	
	/** Called when the session state has changed when creating a online game */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnCreateSessionStateChanged mOnCreateSessionStateChanged;

	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnFriendPresenceUpdated mOnFriendsPresenceUpdated;

	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnGameInviteReceived mOnInviteReceived;

	/** Current state of the friends list */
	EFrindsListState mFriendsListState;

	/** Information about the current session that we are setting up */
	FSessionInformation mCurrentSessionInformation;

	TArray<FFGOnlineFriend> mCachedFriends;

	/** If true, then we have failed to autologin, and won't try to autologin again */
	bool mFailedAutologin;

public:
	FORCEINLINE ~UFGLocalPlayer() = default;
};

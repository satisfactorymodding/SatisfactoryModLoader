// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGOnlineSessionSettings.h"
#include "FGOnlineSessionClient.h"
#include "Engine/LocalPlayer.h"
#include "OnlineSubsystemTypes.h"
#include "FGErrorMessage.h"
#include "UObject/CoreOnline.h"
#include "EOSAccountHelpers.h"
#include "FindSessionsCallbackProxy.h"
#include "EOSSDKForwards.h"
#include "PlayerPresenceState.h"
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
	LS_NotLoggedIn		UMETA(DisplayName = "NotLoggedIn"), 
	LS_FailedToLogin	UMETA(DisplayName = "FailedToLogin"),
	LS_LoggingIn		UMETA(DisplayName="LoggingIn"),
	LS_LoggedIn			UMETA(DisplayName="LoggedIn")
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

FORCEINLINE FString VarToFString( const FFGOnlineFriend& f ){ return FString::Printf( TEXT("%s"), *VarToFString(f.Friend->GetUserId()) ); }

FORCEINLINE uint32 GetTypeHash( const FFGOnlineFriend& onlineFriend )
{
	// WTF! WHY DOES THIS FAIL?
	if( onlineFriend.IsValid() )
	{
		return GetTypeHash( onlineFriend.Friend->GetUserId() );
	}	

	return 0;
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnMultiplayerStatusUpdated );
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams( FOnAccountConnectionComplete, const FName, currentPlatform, EEosAccountConnectionResult, result );


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

	/** Listen to option changes we care about */
	void SubscribeToOptionUpdates();
	
	/** Triggered when Maintain Y Axis FOV option have changed */
	UFUNCTION()
    void OnMaintainYAxisFOVUpdated( FString updatedCvar );

	/** Get in what state our login is */
	UFUNCTION(BlueprintPure,Category="Online")
	TEnumAsByte<ELoginState> GetLoginState() const;
	
	/** Get in what state our epic login is */
	UFUNCTION( BlueprintPure, Category = "Online" )
	FORCEINLINE TEnumAsByte<ELoginState> GetLoginStateEpic() const{ return mLoginStateEpic; }
	
	/** Get in what state our Steam login is */
	UFUNCTION( BlueprintPure, Category = "Online" )
	FORCEINLINE TEnumAsByte<ELoginState> GetLoginStateSteam() const{ return mLoginStateSteam; }

	/** Get the username of the current user (from the first logged in platform)*/
	UFUNCTION(BlueprintPure,Category="Online")
	FString GetUsername() const;

	/** Get the username of the current user for the specified platform (empty string if not logged in)*/
	UFUNCTION(BlueprintPure, Category = "Online")
	FString GetUsernameEpic() const;

	/** Get the username of the current user for the specified platform (empty string if not logged in)*/
	UFUNCTION(BlueprintPure, Category = "Online")
	FString GetUsernameSteam() const;

	/** Are we waiting for an response from EOS connect login */
	UFUNCTION(BlueprintPure, Category = "Online")
    bool IsWaitingForEOSConnectLoginResponse() const { return mIsWaitingForEOSConnectLogin; }

	/** Did we press continue without multiplayer in the connection popup? */
	UFUNCTION(BlueprintPure, Category = "Online")
    bool GetContinueWithoutMultiplayer() const { return mContinueWithoutMultiplayer; }

	void SetupServerAndTravelToMap( const FString& mapName, const FString& options, const FString& sessionName, ESessionVisibility visibility );

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

	/** Make sure our session presence patches the specified presence */
	void CopyPresenceDataToLocalPresenceAndPushToServer( const TSharedRef<FOnlineUserPresence>& presence );

	/** Called regularly to update the users presence, can also be called to force update presence and delays the next presence update */
	UFUNCTION()
	void UpdatePresence();

	UFUNCTION()
	void CheckForStartupArguments();

	void TestSteamCommandLineArgs(FString &sessionId);

	/** Called regularly to update the users presence, can also be called to force update presence and delays the next presence update */
	UFUNCTION()
	void SetNextUpdatePresenceTime(float timeTillNextUpdate);

	/** Called when we have received a invite and gotten full information about it */
	void OnInviteReceived( const FPendingInvite& invite );

	/** Checks if last logged in user id matches the current logged in user and if not updates the cached value */
	void RefreshRecentRegisteredSocialAccountID();

	// Return true if we have received the Product User Id needed for hosting the game
	bool HasReceivedProductUserId() const;

	// Get the unique net id of the current local player
	TSharedPtr<const FUniqueNetId> GetPlayerId() const;
	TSharedPtr<const FUniqueNetId> GetPlayerIdSteam() const;


	//~ Begin Account Connection Functions //
	/** Connect two logged in accounts */
	void ConnectAccount( const FName currentPlatform );

	//Log out epic, then wait till the logout compelts and use the contiue token to create a new connection.
	void LogOutEpicAndCreateNewAccountConnection(const FName currentPlatform);

	/** Create a new account connection without connection to an existing account */
	void CreateNewAccountConnection( const FName currentPlatform );

	void BroadcastAccountConnectionStepResult(const FName currentPlatform, EEosAccountConnectionResult result);

	/** Prompt the user to login and link that account */
	void LoginAndConnectAccount( const FName currentPlatform );

	/** Continue without linking an account to our current one */
	void ContinueWithoutConnectingAccount( const FName currentPlatform );

	virtual void SwitchController(class APlayerController* PC) override;

	/** Logout current account and login to a epic account and connect */
	void LoginAndConnectOtherEpicAccount();

	/** Logout current account and login to a epic account and connect */
	void ContinueWithAndHookUpSteamToEOSAfterEpicLogout();

	/** Logout current account and continue */
	void LogoutEpicAccountAndContinue();

	//~ End Account Connection Functions //

	UFUNCTION( BlueprintCallable )
	void LoginEpicAccountPortal();

	UFUNCTION( BlueprintCallable )
	void LogoutEpicAccountPortal();

	void ContinueWithoutMultiplayer();

protected:
	//~Begin Online Delegates
	//~Begin OnlineIdentity delegates
	void OnLoginStatusChanged( int32 localUserNum, ELoginStatus::Type previous, ELoginStatus::Type current, const FUniqueNetId& userId );
	void OnLoginStatusChangedSteam(int32 localUserNum, ELoginStatus::Type previous, ELoginStatus::Type current, const FUniqueNetId& userId);

	void SteamTaskRetryWaiter();
	void StartSteamEOSConnect();

	void OnLoginComplete(int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error);
	void OnLoginCompleteSteam(int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error);
	void OnAutoLoginComplete(int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error);
	void OnAutoLoginCompleteSteam(int32 localUserNum, bool wasSuccessful, const FUniqueNetId& userId, const FString& error);
	void OnConnectionStatusChanged(const FString& serviceName, EOnlineServerConnectionStatus::Type lastConnectionState, EOnlineServerConnectionStatus::Type connectionState);
	void OnConnectionStatusChangedSteam(const FString& serviceName, EOnlineServerConnectionStatus::Type lastConnectionState, EOnlineServerConnectionStatus::Type connectionState);
	//~End OnlineIdentity delegates

	//~Begin OnlineFriends delegates
	void OnReadFriendsListComplete( int32 localUserNum, bool wasSuccessful, const FString& listName, const FString& errorStr );
	void OnReadFriendsListCompleteSteam(int32 localUserNum, bool wasSuccessful, const FString& listName, const FString& errorStr);
	void OnFriendsChange();
	void OnFriendsChangeSteam();
	//~End OnlineFriends delegates

	//~Begin OnlineUser delegates
	//void OnQueryUserInfoComplete( int32 localUSerNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorString );
	void OnQueryUserInfoForFriendListComplete( int32 localUSerNum, bool wasSuccessful, const TArray< TSharedRef<const FUniqueNetId> >& userIds, const FString& errorString );
	//~End OnlineUnser delegates

	//~Begin OnlinePresence delegates
	void OnPresenceReceived( const class FUniqueNetId& userId, const TSharedRef<FOnlineUserPresence>& presence );
	void OnPresenceReceivedSteam(const class FUniqueNetId& userId, const TSharedRef<FOnlineUserPresence>& presence);
	//~End OnlinePresence deleages

	void UpdateLoginState();

	//~End Online Delegates

	// @return true if we are able to autologin
	bool CanAutoLoginEpic() const;

	bool CanAutoLoginSteam() const;
	/** Get the presence string we should show to other users */
	virtual FString GetPresenceString() const;

	void GetPresenceState(FPlayerPresenceState& outState) const;

	/** Convert a login status to a login state */
	ELoginState FromLoginStatus( ELoginStatus::Type from ) const;

	// Called whenever we get logged in
	void OnLoggedIn();
	
	// Set the login state of the local player and broadcast it
	void SetLoginStateEpic( ELoginState newLoginState );

	void SetLoginStateSteam(ELoginState newLoginState);
	// Get friends that we don't have any presence data or similar for
	void GetFriendsWithNoData( TArray<TSharedRef<const FUniqueNetId>>& out_usersWithNoData );
private:

	/** Push error and autosave the game */
	void PushErrorAndAutosave( TSubclassOf<class UFGErrorMessage> errorMessage );

	/** Set waiting variable and broadcast changes with delegate */
	void SetIsWaitingForEOSConnectLogin( bool waiting );

public:
	/** Called when the when we have a result from connection accounts */
	FOnAccountConnectionComplete mOnAccountConnectionComplete;

	/** Called when the state of waiting for EOS connect login response changed or we continued playing without multiplayer*/
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnMultiplayerStatusUpdated mOnMultiplayerStatusUpdated;

	UFUNCTION()
	void OnComandlineInviteSearchComplete(FBlueprintSessionResult result);
protected:
	friend class UFGCheatManager;

	//~Begin OnlineFriends delegates
	FDelegateHandle mOnFriendsChangeHandle;
	FDelegateHandle mOnFriendsChangeHandleSteam;
	//~End OnlineFriends delegates
	//~Begin OnlineIdentity delegates
	FDelegateHandle mOnLoginStatusChangeHandle;
	FDelegateHandle mOnLoginCompleteHandle;
	FDelegateHandle mOnLoginStatusChangeHandleSteam;
	FDelegateHandle mOnLoginCompleteHandleSteam;
	// Special delegate that is just setup during autologin
	FDelegateHandle mOnAutoLoginCompleteHandle;
	FDelegateHandle mOnAutoLoginCompleteHandleSteam;
	//~End OnlineIdentity delegates
	//~Begin OnlineUser delegates
	FDelegateHandle mOnQueryUserInfoForFriendListCompleteHandle;
	FDelegateHandle mOnPresenceReceived;
	FDelegateHandle mOnQueryUserInfoForFriendListCompleteHandleSteam;
	FDelegateHandle mOnPresenceReceivedSteam;

	//~~End OnlineUser delegates

	// Handle for updating presence info
	FTimerHandle mPresenceUpdateHandle;
	FTimerHandle mPresenceUpdateHandleSteam;
	FTimerHandle mSteamConnectyAccountDelayHandle;

	FTimerHandle mCheckStartupArgumentsHanlde;

	// For detecting player disconnects from services
	FDelegateHandle mOnConnectionStatusChangedHandle;
	FDelegateHandle mOnConnectionStatusChangedHandleSteam;

	// The status of our logins
	ELoginState mLoginStateEpic;
	// The status of our logins
	ELoginState mLoginStateSteam;

	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnLoginStateChanged mOnLoginStateChanged;

	/** Called when the friendslist has been updated (that is, a user is has added/removed you as a friend) */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnFriendsListUpdated mOnFriendsListUpdated;
	
	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnFriendPresenceUpdated mOnFriendsPresenceUpdated;

	/** Called a friends presence is updated */
	UPROPERTY(BlueprintAssignable,Category="FactoryGame|Online")
	FOnGameInviteReceived mOnInviteReceived;

	/** Current state of the friends list */
	EFrindsListState mFriendsListState;

	TArray<FFGOnlineFriend> mCachedFriends;

	//Used while setting up account linking with EOS. Need to be kept from a result and used with potential continuance actions.
	EOS_ContinuanceToken mCurrentContinuanceToken = nullptr;

	/** If true, then we have failed to autologin, and won't try to autologin again */
	bool mFailedAutologinEpic;

	/** If true, then we have failed to autologin, and won't try to autologin again */
	bool mFailedAutologinSteam;

	enum class ESteamTaskRetryState: uint8
	{
		STRS_StopTimer,
		STRS_Continue,
		STRS_TriggerRetry
	};
	ESteamTaskRetryState mSteamRetryState;
	bool mContinueWithoutMultiplayer = false;
	bool mIsWaitingToConnectSteamAccount = false;
	bool mIsWaitingForEOSConnectLogin = false;
	bool mIsWaitingForEpicLogout = false;
	bool mIsWaitingForEpicAccountSwap = false;
	bool mHasTriedConnectingSteam = false;
	bool mStartedAccountConnectionProcess = false;
	bool mHastTriedLoggingIn = false;
	bool mAutoSignedOutEpicDueToIncompatibility = false;
};

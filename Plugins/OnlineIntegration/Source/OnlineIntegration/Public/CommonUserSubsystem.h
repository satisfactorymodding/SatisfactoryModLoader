// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "Online/Connectivity.h"
#include "OnlineIntegrationTypes.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameplayTagContainer.h"
#include "OnlineIntegrationSubsystem.h"
#include "LocalUserInfo.h"
#include "Engine/GameViewportClient.h"
#include "CommonUserSubsystem.generated.h"

class UOnlineAsyncOperation;

namespace UE {namespace Online
{
struct FPresenceUpdated;
struct FAuthPendingAuthExpiration;
}}

DECLARE_LOG_CATEGORY_EXTERN(LogCommonUser, Log, All);

class FNativeGameplayTag;

/** List of tags used by the common user subsystem */
struct ONLINEINTEGRATION_API FCommonUserTags
{
	// General severity levels and specific system messages

	static FNativeGameplayTag SystemMessage_Error;   // SystemMessage.Error
	static FNativeGameplayTag SystemMessage_Warning; // SystemMessage.Warning
	static FNativeGameplayTag SystemMessage_Display; // SystemMessage.Display

	/** All attempts to initialize a player failed, user has to do something before trying again */
	static FNativeGameplayTag SystemMessage_Error_InitializeLocalPlayerFailed; // SystemMessage.Error.InitializeLocalPlayerFailed


	// Platform trait tags, it is expected that the game instance or other system calls SetTraitTags with these tags for the appropriate platform

	/** This tag means it is a console platform that directly maps controller IDs to different system users. If false, the same user can have multiple controllers */
	static FNativeGameplayTag Platform_Trait_RequiresStrictControllerMapping; // Platform.Trait.RequiresStrictControllerMapping

	/** This tag means the platform has a single online user and all players use index 0 */
	static FNativeGameplayTag Platform_Trait_SingleOnlineUser; // Platform.Trait.SingleOnlineUser
};

/** Delegates when initialization processes succeed or fail */
DECLARE_DELEGATE_OneParam(FCommonUserOnInitializeComplete, const UE::Online::TOnlineResult<FInitializeLocalUser>& Result);
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnCommonUserInitializeComplete, ULocalUserInfo*, UserInfo, bool, bSuccess, FText, Error);

UENUM(BlueprintType)
enum class ECommonUserLoginType: uint8
{
	None,
	Auto,
	PersistentAuth,
	AccountPortal
};

/** Parameter struct for initialize functions, this would normally be filled in by wrapper functions like async nodes */
USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FCommonUserInitializeParams
{
	GENERATED_BODY()

	/** What local player index to use, can specify one above current if can create player is enabled */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	int32 LocalPlayerIndex = 0;

	/** Deprecated method of selecting platform user and input device */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	int32 ControllerId = -1;

	/** Primary controller input device for this user, they could also have additional secondary devices */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	FInputDeviceId PrimaryInputDevice;

	/** Specifies the logical user on the local platform */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	FPlatformUserId PlatformUser;

	/** Generally either CanPlay or CanPlayOnline, specifies what level of privilege is required */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	ECommonUserPrivilege RequestedPrivilege = ECommonUserPrivilege::CanPlay;

	/** What specific online context to log in to, game means to login to all relevant ones */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	EOnlineIntegrationUnmappedContext OnlineContext = EOnlineIntegrationUnmappedContext::Platform;

	/** True if this is allowed to create a new local player for initial login */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bCanCreateNewLocalPlayer = false;

	UPROPERTY(BlueprintReadWrite)
	TArray<ECommonUserLoginType> AllowedLoginTypes;

	/** True if this player can be a guest user without an actual online presence */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bCanUseGuestLogin = false;

	/** True if we should not show login errors, the game will be responsible for displaying them */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bSuppressLoginErrors = false;

	UPROPERTY(BlueprintReadWrite, Category = Default)
	FOnCommonUserInitializeComplete OnCommonUserInitializeComplete;
	
	FCommonUserOnInitializeComplete OnUserInitializeComplete_Native;
};

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLocalUserInfoCreated, ULocalUserInfo*, UserInfo);

/**
 * Game subsystem that handles queries and changes to user identity and login status.
 * One subsystem is created for each game instance and can be accessed from blueprints or C++ code.
 * If a game-specific subclass exists, this base subsystem will not be created.
 */
UCLASS(BlueprintType, Config=Game)
class ONLINEINTEGRATION_API UCommonUserSubsystem : public UOnlineIntegrationComponent
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	/** Async future for when a local user info with a certain player index gets created. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLocalUserInfoCreated_Native, ULocalUserInfo*);

	UFUNCTION(BlueprintCallable)
	void WhenLocalUserInfoIsCreated(FOnLocalUserInfoCreated Delegate, int32 PlayerIndex);
	void WhenLocalUserInfoIsCreated_Native(FOnLocalUserInfoCreated_Native::FDelegate Delegate, int32 PlayerIndex);
	
	/** Sets the maximum number of local players, will not destroy existing ones */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual void SetMaxLocalPlayers(int32 InMaxLocalPLayers);

	/** Gets the maximum number of local players */
	UFUNCTION(BlueprintPure, Category = CommonUser)
	int32 GetMaxLocalPlayers() const;

	/** Gets the current number of local players, will always be at least 1 */
	UFUNCTION(BlueprintPure, Category = CommonUser)
	int32 GetNumLocalPlayers() const;

	/** Returns the user info for a given local player index in game instance, 0 is always valid in a running game */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	ULocalUserInfo* GetUserInfoForLocalPlayerIndex(int32 LocalPlayerIndex) const;

	/** Returns the primary user info for a given platform user index. Can return null */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	ULocalUserInfo* GetUserInfoForPlatformUser(FPlatformUserId PlatformUser) const;

	/** Returns the user info for a unique net id. Can return null */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	const ULocalUserInfo* GetUserInfoForUniqueNetId(const FUniqueNetIdRepl& NetId) const;

	/** Deprecated, use InputDeviceId when available */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	const ULocalUserInfo* GetUserInfoForControllerId(int32 ControllerId) const;

	/** Returns the user info for a given input device. Can return null */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	const ULocalUserInfo* GetUserInfoForInputDevice(FInputDeviceId InputDevice) const;

	/** Returns the user info for a given input device. Can return null */
	UFUNCTION(BlueprintCallable, BlueprintPure = False, Category = CommonUser)
	ULocalUserInfo* GetUserInfoForLocalPlayer(ULocalPlayer* LocalPlayer) const;

	/**
	 * Creates a new online authentication sequence if there's isn't already a pending one for the given platform user id
	 */
	UFUNCTION(BlueprintCallable)
	UOnlineAsyncOperation *CreateAuthenticationSequence(TScriptInterface<IOnlineAuthenticationHandler> Handler, FPlatformUserId PlatformUserId);

	ULocalUserInfo* GetUserInfoForAccountId(const UE::Online::FAccountId AccountId, EOnlineIntegrationUnmappedContext Context) const;

	/**
	 * Tries to start the process of creating or updating a local player, including logging in and creating a player controller.
	 * When the process has succeeded or failed, it will broadcast the OnUserInitializeComplete delegate.
	 *
	 * @param LocalPlayerIndex	Desired index of LocalPlayer in Game Instance, 0 will be primary player and 1+ for local multiplayer
	 * @param PrimaryInputDevice The physical controller that should be mapped to this user, will use the default device if invalid
	 * @param bCanUseGuestLogin	If true, this player can be a guest without a real Unique Net Id
	 *
	 * @returns true if the process was started, false if it failed before properly starting
	 */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual bool TryToInitializeForLocalPlay(int32 LocalPlayerIndex, FInputDeviceId PrimaryInputDevice, bool bCanUseGuestLogin);

	/**
	 * Starts the process of taking a locally logged in user and doing a full online login including account permission checks.
	 * When the process has succeeded or failed, it will broadcast the OnUserInitializeComplete delegate.
	 *
	 * @param LocalPlayerIndex	Index of existing LocalPlayer in Game Instance
	 *
	 * @returns true if the process was started, false if it failed before properly starting
	 */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual bool TryToLoginForOnlinePlay(int32 LocalPlayerIndex);

	/**
	 * Starts a general user login and initialization process, using the params structure to determine what to log in to.
	 * When the process has succeeded or failed, it will broadcast the OnUserInitializeComplete delegate.
	 * AsyncAction_CommonUserInitialize provides several wrapper functions for using this in an Event graph.
	 *
	 * @returns true if the process was started, false if it failed before properly starting
	 */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual bool TryToInitializeUser(FCommonUserInitializeParams Params);

	/** 
	 * Starts the process of listening for user input for new and existing controllers and logging them.
	 * This will insert a key input handler on the active GameViewportClient and is turned off by calling again with empty key arrays.
	 *
	 * @param AnyUserKeys		Listen for these keys for any user, even the default user. Set this for an initial press start screen or empty to disable
	 * @param NewUserKeys		Listen for these keys for a new user without a player controller. Set this for splitscreen/local multiplayer or empty to disable
	 * @param Params			Params passed to TryToInitializeUser after detecting key input
	 */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual void ListenForLoginKeyInput(TArray<FKey> AnyUserKeys, TArray<FKey> NewUserKeys, FCommonUserInitializeParams Params);

	/** Attempts to cancel an in-progress initialization attempt, this may not work on all platforms but will disable callbacks */
	// UFUNCTION(BlueprintCallable, Category = CommonUser)
	// virtual bool CancelUserInitialization(int32 LocalPlayerIndex);

	/** Logs a player out of any online systems, and optionally destroys the player entirely if it's not the first one */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual bool TryToLogOutUser(int32 LocalPlayerIndex, bool bDestroyPlayer = false);

	/** Returns true if this this could be a real platform user with a valid identity (even if not currently logged in)  */
	virtual bool IsRealPlatformUserIndex(int32 PlatformUserIndex) const;

	/** Returns true if this this could be a real platform user with a valid identity (even if not currently logged in) */
	virtual bool IsRealPlatformUser(FPlatformUserId PlatformUser) const;

	/** Converts index to id */
	virtual FPlatformUserId GetPlatformUserIdForIndex(int32 PlatformUserIndex) const;

	/** Converts id to index */
	virtual int32 GetPlatformUserIndexForId(FPlatformUserId PlatformUser) const;

	/** Gets the user for an input device */
	virtual FPlatformUserId GetPlatformUserIdForInputDevice(FInputDeviceId InputDevice) const;

	/** Gets a user's primary input device id */
	virtual FInputDeviceId GetPrimaryInputDeviceForPlatformUser(FPlatformUserId PlatformUser) const;

	/** Checks to see if we should display a press start/input confirmation screen at startup. Games can call this or check the trait tags directly */
	UFUNCTION(BlueprintPure, Category=CommonUser)
	virtual bool ShouldWaitForStartInput() const;

	/** Returns the current login status for a player on the specified online system, only works for real platform users */
	ELoginStatusType GetLocalUserLoginStatus(FPlatformUserId PlatformUser,
		EOnlineIntegrationUnmappedContext Context = EOnlineIntegrationUnmappedContext::Platform) const;

	/** Returns the unique net id for a local platform user */
	FUniqueNetIdRepl GetLocalUserNetId(FPlatformUserId PlatformUser,
		EOnlineIntegrationUnmappedContext Context = EOnlineIntegrationUnmappedContext::Platform) const;
	FUniqueNetIdRepl GetLocalUserNetId(FPlatformUserId PlatformUser, EOnlineIntegrationMappedContext Context = EOnlineIntegrationMappedContext::Session) const;

	/** Convert a user id to a debug string */
	FString PlatformUserIdToString(FPlatformUserId UserId);

	/** Returns human readable string for privilege checks */
	virtual FText GetPrivilegeDescription(ECommonUserPrivilege Privilege) const;
	virtual FText GetPrivilegeResultDescription(ECommonUserPrivilegeResult Result) const;

	/** 
	 * Starts the process of login for an existing local user, will return false if callback was not scheduled 
	 * This activates the low level state machine and does not modify the initialization state on user info
	 */
	DECLARE_DELEGATE_FiveParams(FOnLocalUserLoginCompleteDelegate, const ULocalUserInfo* /*UserInfo*/, ELoginStatusType /*NewStatus*/,
		FUniqueNetIdRepl /*NetId*/, const TOptional<FOnlineErrorType>& /*Error*/, EOnlineIntegrationUnmappedContext /*Type*/);
	TFuture<UE::Online::TOnlineResult<UE::Online::FAuthLogin>> LoginLocalUser(ULocalUserInfo* UserInfo, FCommonUserInitializeParams Params);
	 
	/** Assign a local player to a specific local user and call callbacks as needed */
	virtual void SetLocalPlayerUserInfo(ULocalPlayer* LocalPlayer, const ULocalUserInfo* UserInfo);

	FName GetServicesProvider(EOnlineIntegrationUnmappedContext Context);

	// Temporary functionality to refresh crossplay login
	void SetupLoginForCrossplayRefreshTimer(FPlatformUserId InPlatformUserId);
	void RefreshLoginForCrossplay(FPlatformUserId InPlatformUserId);
protected:

	/** Create a new user info object */
	virtual ULocalUserInfo* CreateLocalUserInfo(int32 LocalPlayerIndex);

	/** Deconst wrapper for const getters */
	FORCEINLINE ULocalUserInfo* ModifyInfo(const ULocalUserInfo* Info)
	{
		return const_cast<ULocalUserInfo*>(Info);
	}

	/** Bind online delegates */
	virtual void OnOnlineContextCreated() override;

	/** Forcibly logs out and deinitializes a single user */
	virtual void LogOutLocalUser(FPlatformUserId PlatformUser);

	TFuture<UE::Online::TOnlineResult<UE::Online::FAuthLogin>> LoginForContext(ULocalUserInfo* LocalUserInfo, EOnlineIntegrationUnmappedContext Context, TArray<ECommonUserLoginType> AllowedLoginTypes);
	TFuture<UE::Online::TOnlineResult<UE::Online::FAuthLogin>> LoginForCrossPlay(ULocalUserInfo* LocalUserInfo);

	/** OSS-specific functions */
	static ECommonUserPrivilege ConvertOnlineServicesPrivilege(UE::Online::EUserPrivileges Privilege);
	static UE::Online::EUserPrivileges ConvertOnlineServicesPrivilege(ECommonUserPrivilege Privilege);
	static ECommonUserPrivilegeResult ConvertOnlineServicesPrivilegeResult(UE::Online::EUserPrivileges Privilege, UE::Online::EPrivilegeResults Results);

	void CacheConnectionStatus(EOnlineIntegrationUnmappedContext Context);
	TSharedPtr<UE::Online::FAccountInfo> GetOnlineServiceAccountInfo(UE::Online::IAuthPtr AuthService, FPlatformUserId InUserId) const;

	/** Callbacks for OSS functions */
	virtual void HandleAuthLoginStatusChanged(const UE::Online::FAuthLoginStatusChanged& EventParameters, EOnlineIntegrationUnmappedContext Context);
	virtual void HandlePendingAuthExpiration(const UE::Online::FAuthPendingAuthExpiration& PendingAuthExpiration, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleNetworkConnectionStatusChanged(const UE::Online::FConnectionStatusChanged& EventParameters, EOnlineIntegrationUnmappedContext Context);
	virtual void HandlePresenceUpdated(const UE::Online::FPresenceUpdated& PresenceUpdated, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionInviteReceived(const UE::Online::FSessionInviteReceived& InviteReceived, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionJoined(const UE::Online::FSessionJoined& SessionJoined, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionLeft(const UE::Online::FSessionLeft& SessionLeft, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionUpdated(const UE::Online::FSessionUpdated& SessionUpdated, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleUISessionJoinRequested(const UE::Online::FUISessionJoinRequested& SessionJoinRequested, EOnlineIntegrationUnmappedContext Context);
	/**
	 * Callback for when an input device (i.e. a gamepad) has been connected or disconnected. 
	 */
	virtual void HandleInputDeviceConnectionChanged(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId,
		FInputDeviceId InputDeviceId);

	/** Callback for handling press start/login logic */
	virtual bool OverrideInputKeyForLogin(FInputKeyEventArgs& EventArgs);


	/** Previous override handler, will restore on cancel */
	FOverrideInputKeyHandler WrappedInputKeyHandler;

	/** List of keys to listen for from any user */
	TArray<FKey> LoginKeysForAnyUser;

	/** List of keys to listen for a new unmapped user */
	TArray<FKey> LoginKeysForNewUser;

	/** Params to use for a key-triggered login */
	FCommonUserInitializeParams ParamsForLoginKey;

	/** Maximum number of local players */
	int32 MaxNumberOfLocalPlayers = 0;

	/** True if this is a dedicated server, which doesn't require a LocalPlayer */
	bool bIsDedicatedServer = false;

	/** Information about each local user, from local player index to user */
	UPROPERTY()
	TMap<int32, TObjectPtr<ULocalUserInfo>> LocalUserInfos;

	UPROPERTY()
	TMap<int32, TObjectPtr<UOnlineAsyncOperation>> PendingAuthenticationSequences;

	TMap<int32, FOnLocalUserInfoCreated_Native> LocalUserInfoCreatedDelegates;
	FTimerHandle RefreshLoginForCrossplayTimerHandle;

	friend ULocalUserInfo;
};

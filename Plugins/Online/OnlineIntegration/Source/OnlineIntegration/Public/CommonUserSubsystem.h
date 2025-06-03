// Copyright Coffee Stain Studios. All Rights Reserved.
#pragma once

#include "Async/Future.h"
#include "CoreMinimal.h"
#include "Engine/GameViewportClient.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameplayTagContainer.h"
#include "LocalUserInfo.h"
#include "Online/Connectivity.h"
#include "Online/Stats.h"
#include "OnlineIntegrationTypes.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "CommonUserSubsystem.generated.h"

class UAddOnEntitlement;
class IOnlineUserRegistryExtension;
class UDataTable;
struct FGameplayEvent;
class UOnlineAsyncOperation;

namespace UE {namespace Online
{
struct FPresenceUpdated;
struct FAuthPendingAuthExpiration;
}}

DECLARE_LOG_CATEGORY_EXTERN(LogCommonUser, Log, All);

// <FL> [ZimmermannA]
UENUM(BlueprintType)
enum class EOnlineSessionFeatureType : uint8
{
	OSFT_OnlineMultiplayer = 0,	   // Displayed as 'None' on the debug screen
	OSFT_Crossplay,
	// OSFT_EngineSpectate currently not used or implemented, but would need to be extended here
	OSFT_Off,	 
};

// //Event that is being called when login process is being started or when it ended.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnEOSLoginProcessUpdated, bool, hasStarted);
// Event that is being called when the platform telemetry tracking feature should be called.
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnOnlineTelemetryUpdated, EOnlineSessionFeatureType, sessionFeatureType );
// </FL> [ZimmermannA] 

//<FL>[KonradA]
UENUM(BlueprintType)
enum class EUserJoinSessionFailureReason : uint8
{
	None,
	NoPremium,
	CrossPlayFailure,
	NoEOS
};
//</FL>

class FNativeGameplayTag;

/** List of tags used by the common user subsystem */
struct ONLINEINTEGRATION_API FCommonUserTags
{
	// Platform trait tags, it is expected that the game instance or other system calls SetTraitTags with these tags for the appropriate platform

	/** This tag means it is a console platform that directly maps controller IDs to different system users. If false, the same user can have multiple controllers */
	static FNativeGameplayTag Platform_Trait_RequiresStrictControllerMapping; // Platform.Trait.RequiresStrictControllerMapping

	/** This tag means the platform has a single online user and all players use index 0 */
	static FNativeGameplayTag Platform_Trait_SingleOnlineUser; // Platform.Trait.SingleOnlineUser

	static FNativeGameplayTag OnlineError;
};

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

	/** True if this is allowed to create a new local player for initial login */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bCanCreateNewLocalPlayer = false;

	/** True if this player can be a guest user without an actual online presence */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Default)
	bool bCanUseGuestLogin = false;
};

USTRUCT( BlueprintType )
struct FAggregatedOnlineStat
{
	GENERATED_BODY()
	
	UPROPERTY( BlueprintReadOnly )
	FString StatId;

	UPROPERTY( BlueprintReadOnly )
	TArray< FString > AggregatedStats;
};

USTRUCT(BlueprintType)
struct FOnlineActivityData : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FString ActivityId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FGameplayTag ActivityToEndAfterThis;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FGameplayTag ActivityToStartAfterThis;
};

USTRUCT(BlueprintType)
struct FOnlineActivityDataRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FGameplayTag GameplayEvent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FOnlineActivityData Data;
};

USTRUCT(BlueprintType)
struct FOnlineStatToActivityRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FGameplayTag StatTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=OnlineActivity)
	FGameplayTag ActivityTag;
};

//<FL>[KonradA] Blueprint for a confirmation query code branch. Bind 2 functions and allow blueprint/widgets/modals to select which function to call, since we don't have access to
// modal window frameworks in this plugin we use this to allow FactoryGame context to handle a code branch in the user subsystem however it wants.
UCLASS(BlueprintType)
class UOnlineCrossplayConfirmationQuery : public UObject
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void Confirm()
	{
		OnConfirm();
	}

	UFUNCTION(BlueprintCallable)
	void Deny()
	{
		OnDeny();
	}

	TFunction<void()> OnConfirm;
	TFunction<void()> OnDeny;
};
//</FL>

DECLARE_DYNAMIC_DELEGATE_OneParam(FOnLocalUserInfoCreated, ULocalUserInfo*, UserInfo);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalUserFailedSessionJoin, ULocalUserInfo*, UserInfo, EUserJoinSessionFailureReason, Reason);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLocalUserQueriesJoinCrossplay, ULocalUserInfo*, UserInfo, UOnlineCrossplayConfirmationQuery*, ConfirmationQuerySender);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnActivityChanged, const FName& /*Activity*/); // <FL> [TranN] PS5 Activity



/**
 * Game subsystem that handles queries and changes to user identity and login status.
 * One subsystem is created for each game instance and can be accessed from blueprints or C++ code.
 * If a game-specific subclass exists, this base subsystem will not be created.
 */
UCLASS(Config=Engine)
class ONLINEINTEGRATION_API UCommonUserSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

//<FL>[KonradA]
	UPROPERTY(BlueprintAssignable)
	FOnLocalUserFailedSessionJoin OnLocalUserFailedSessionJoin;

	UPROPERTY(BlueprintAssignable)
	FOnLocalUserQueriesJoinCrossplay OnLocalUserQueriesJoinCrossplay;
//</FL>
	/** Async future for when a local user info with a certain player index gets created. */
	DECLARE_MULTICAST_DELEGATE_OneParam(FOnLocalUserInfoCreated_Native, ULocalUserInfo*);

	UFUNCTION(BlueprintCallable)
	void WhenLocalUserInfoIsCreated(FOnLocalUserInfoCreated Delegate, int32 PlayerIndex);
	void WhenLocalUserInfoIsCreated_Native(FOnLocalUserInfoCreated_Native::FDelegate Delegate, int32 PlayerIndex);
	FDelegateHandle AddOnLocalUserInfoCreatedDelegate(FOnLocalUserInfoCreated_Native::FDelegate Delegate);
	void RemoveOnLocalUserInfoCreatedDelegate(FDelegateHandle DelegateHandle);
	
	UFUNCTION()
	void NotifyUserJoinFailure(ULocalUserInfo* User, EUserJoinSessionFailureReason Reason);
//<FL>[KonradA]
	void QueryUserTryJoinCrossplay(ULocalUserInfo* User, TFunction<void()> OnConfirm, TFunction<void()> OnDeny);
	UFUNCTION(BlueprintCallable)
	bool IsProcessingAuthenticationSequences();	   
	//</FL>
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
	//<FL>[KonradA] Adding a parameter to suppress ui erroring out of the routine
	UOnlineAsyncOperation *CreateAuthenticationSequence(FPlatformUserId PlatformUserId, FName SequenceName, bool bSuppressErrors = false);

	UFUNCTION(BlueprintCallable)
	void EnqueueAuthenticationSequence(UOnlineAsyncOperation* InAsyncOp);

	// <FL> [TranN]
	void SetPendingAuthenticationSequence(UOnlineAsyncOperation* InAsyncOp);
	void ExecutePendingAuthenticationSequence();
	void CancelPendingAuthenticationSequence();
	// </FL>

	ULocalUserInfo* GetUserInfoForAccountId(const UE::Online::FAccountId AccountId) const;
	
	UFUNCTION(BlueprintCallable)
	FString GetAccountIdStringForUserBackend(UOnlineUserBackendLink* BackendLink);

	/**
	 * Starts a general user login and initialization process, using the params structure to determine what to log in to.
	 * When the process has succeeded or failed, it will broadcast the OnUserInitializeComplete delegate.
	 * AsyncAction_CommonUserInitialize provides several wrapper functions for using this in an Event graph.
	 *
	 * @returns true if the process was started, false if it failed before properly starting
	 */
	UFUNCTION(BlueprintCallable, Category = CommonUser)
	virtual ULocalUserInfo* TryToInitializeUser(FCommonUserInitializeParams Params);

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

	/** Convert a user id to a debug string */
	FString PlatformUserIdToString(FPlatformUserId UserId);

	/** Returns human readable string for privilege checks */
	virtual FText GetPrivilegeDescription(ECommonUserPrivilege Privilege) const;
	virtual FText GetPrivilegeResultDescription(ECommonUserPrivilegeResult Result) const;

	/** 
	 * Starts the process of login for an existing local user, will return false if callback was not scheduled 
	 * This activates the low level state machine and does not modify the initialization state on user info
	 */
	TFuture<UE::Online::TOnlineResult<UE::Online::FAuthLogin>> LoginLocalUser(ULocalUserInfo* UserInfo, FCommonUserInitializeParams Params);

	/** Used to enable / disable achievements. */
	void SetAchievementsEnabled(bool Enabled);

	/** Used to stop stat updates from being sent to the backends. */
	FORCEINLINE void SetStatUpdatesBlocked(bool Blocked) { bStatUpdatesBlocked = Blocked; }
	FORCEINLINE bool ShouldBlockStatUpdates() const { return bStatUpdatesBlocked; }
	
	/**
	 * Registers all the stats in the given data table with the subsystem. After registration, these stats will be updated in the backend whenever their
	 * corresponding gameplay events are triggered.
	 */
	void RegisterStats(UDataTable* StatTable);

	void RegisterActivities(UDataTable* ActivityTable, UDataTable* StatToActivityTable);

#if !UE_BUILD_SHIPPING
	/** Used in development to reset stats / achievements of the specified local user. */
	void ResetLocalUserStats(ULocalUserInfo* LocalUser);
#endif

	UOnlineUserBackendLink* GetOrCreateBackendLink(UE::Online::FAccountId AccountId);
	UOnlineUserBackendLink* FindBackendLink(UE::Online::FAccountId AccountId);

	/**
	 * Registers a new account id -> backend link mapping. This has to be used for local users, for whom backend links are created before their account ids
	 * are known. The account id is read from the backend link.
	 */
	void RegisterAccountIdToBackendLinkMapping(UOnlineUserBackendLink* BackendLink);

	TFuture<UOnlineUserInfo*> ResolveOnlineUser(ULocalUserInfo* LocalUser, UOnlineUserBackendLink* BackendLink);
	TFuture<UOnlineUserInfo*> ResolveOnlineUser(ULocalUserInfo* LocalUser, UE::Online::FAccountId AccountId);
	
	/** Looks up an already existing online user for the passed in account id and returns it, or nullptr if none exist */
	UOnlineUserInfo* GetOnlineUser(UE::Online::FAccountId AccountId);

	void RegisterExtension(TScriptInterface<IOnlineUserRegistryExtension> Extension);
	void RegisterBackendLinkConnection(UOnlineUserBackendLink* Link1, UOnlineUserBackendLink* Link2);
	TFuture<bool> QueryUserInfo(ULocalUserInfo* LocalUser, UOnlineUserBackendLink* BackendLink);
	TFuture<void> QueryEntitlements(ULocalUserInfo* LocalUser, const TArray<UAddOnEntitlement*>& Entitlements);
	
	UOnlineUserInfo* CreateOnlineUserForLink(UOnlineUserBackendLink* BackendLink);

	const TMap<FGameplayTag, FString>& GetTrackedStats() const { return TrackedStatMap; }
	const TArray<FAggregatedOnlineStat>& GetTrackedAggregatedStats() const { return TrackedAggregatedStats; }

	void UpdateAllAggregatedStats(const UE::Online::FAccountId& AccountId, UOnlineIntegrationBackend* Backend);

	/** Helper function that converts an accountId (v2) to a UniqueNetId (v1).*/
	FUniqueNetIdPtr ConvertAccountIdToNetId(UE::Online::FAccountId accountId);

	UFUNCTION(BlueprintCallable)
	void RefreshFriends();

	// <FL> [TranN] PS5 Activity
	FOnActivityChanged OnActivityStarted;
	FOnActivityChanged OnActivityEnded;
	// </FL>

	// <FL> [ZimmermannA] 
	UPROPERTY(BlueprintAssignable, Category = "Network", DisplayName = "OnEOSLoginProcessUpdated")
	FOnEOSLoginProcessUpdated mOnEOSLoginProcessUpdated;
	
	UPROPERTY(BlueprintAssignable, Category = "Network", DisplayName = "OnOnlineTelemetryUpdated")
	FOnOnlineTelemetryUpdated mOnOnlineTelemetryUpdated;
	// </FL>

	
	//<FL>[KonradA]
	void ResetAuthenticationQueue_Unsafe();
	//</FL>

	//<FL>[BGR]
	int8 GetRefreshFriendsQueryID() const { return RefreshFriendsQueryID; }
	//</FL>

	UOnlineIntegrationSubsystem* GetOnlineIntegration() const;
protected:
	/**
	 * Handles Gameplay events. Most likely that means a backend stat update
	 */
	void OnGameplayEventTriggered(const FGameplayEvent& GameplayEvent);
	
	/** Create a new user info object */
	virtual ULocalUserInfo* CreateLocalUserInfo(int32 LocalPlayerIndex);

	/**
	 * These are all the stats that the subsystem tracks. Every time a gameplay event is triggered that maps to a stat id, it will lead to a stat update in all
	 * the backends that the event instigator/s are fully authenticated for.
	 */
	TMap<FGameplayTag, FString> TrackedStatMap;

	TMap<FGameplayTag, FOnlineActivityData> TrackedActivities;
	TMap<FGameplayTag, FGameplayTag> StatToActivityMap;

	TArray< FAggregatedOnlineStat > TrackedAggregatedStats;

	/** Deconst wrapper for const getters */
	FORCEINLINE ULocalUserInfo* ModifyInfo(const ULocalUserInfo* Info)
	{
		return const_cast<ULocalUserInfo*>(Info);
	}

	/** Bind online delegates */
	virtual void BindDelegates();
	void BindDelegates(UOnlineIntegrationBackend* Backend);

	/** Forcibly logs out and deinitializes a single user */
	virtual void LogOutLocalUser(FPlatformUserId PlatformUser);

	/** OSS-specific functions */
	static ECommonUserPrivilege ConvertOnlineServicesPrivilege(UE::Online::EUserPrivileges Privilege);
	static UE::Online::EUserPrivileges ConvertOnlineServicesPrivilege(ECommonUserPrivilege Privilege);
	static ECommonUserPrivilegeResult ConvertOnlineServicesPrivilegeResult(UE::Online::EUserPrivileges Privilege, UE::Online::EPrivilegeResults Results);

	void CacheConnectionStatus(UOnlineIntegrationBackend* Backend);
	TSharedPtr<UE::Online::FAccountInfo> GetOnlineServiceAccountInfo(UE::Online::IAuthPtr AuthService, FPlatformUserId InUserId) const;

	/** Callbacks for OSS functions */
	virtual void HandleAuthLoginStatusChanged(const UE::Online::FAuthLoginStatusChanged& EventParameters, UOnlineIntegrationBackend* Backend);
	virtual void HandleNetworkConnectionStatusChanged(const UE::Online::FConnectionStatusChanged& EventParameters, UOnlineIntegrationBackend* Backend);
	virtual void HandlePresenceUpdated(const UE::Online::FPresenceUpdated& PresenceUpdated, UOnlineIntegrationBackend* Backend);
	virtual void HandleUISessionJoinRequested(const UE::Online::FUISessionJoinRequested& SessionJoinRequested, UOnlineIntegrationBackend* Backend);
	virtual void HandleStatsUpdated(const UE::Online::FStatsUpdated& EventParameters, UOnlineIntegrationBackend* Backend);
	/**
	 * Callback for when an input device (i.e. a gamepad) has been connected or disconnected. 
	 */
	virtual void HandleInputDeviceConnectionChanged(EInputDeviceConnectionState NewConnectionState, FPlatformUserId PlatformUserId,
		FInputDeviceId InputDeviceId);

	/** Callback for handling press start/login logic */
	virtual bool OverrideInputKeyForLogin(FInputKeyEventArgs& EventArgs);

	void UpdateAggregatedStat(FAggregatedOnlineStat& AggregatedStat, const UE::Online::FAccountId& AccountId, UOnlineIntegrationBackend* Backend);

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
	TArray<TObjectPtr<UOnlineAsyncOperation>> AuthenticationSequenceQueue;

	UPROPERTY()
	TObjectPtr<UOnlineAsyncOperation> PendingAuthenticationSequence;

	/**
	 * All the user backend links this registry knows about. Stored in bulk for the GC to know of these references
	 */
	UPROPERTY()
	TSet<TObjectPtr<UOnlineUserBackendLink>> UserBackendLinks;

	/**
	 * All the online users that we know about.
	 */
	UPROPERTY()
	TSet<TObjectPtr<UOnlineUserInfo>> OnlineUsers;

	UPROPERTY()
	TArray<TScriptInterface<IOnlineUserRegistryExtension>> RegistryExtensions;

	/**
	 *
	 */
	TMap<UE::Online::FAccountId, UOnlineUserBackendLink*> BackendLinkAccountIdLookup;

	TMap<UOnlineUserBackendLink*, UOnlineUserInfo*> BackendLinkUserLookup;
	
	TMap<UE::Online::FAccountId, TArray<TPromise<UOnlineUserInfo*>>> PendingUserInfoResolves;
	TMap<UE::Online::FAccountId, TSharedRef<TPromise<bool>>> PendingUserInfoQueries;

	UFUNCTION()
	void AuthenticationSequenceFinished(UOnlineAsyncOperation* InAsyncOp);

	TMap<int32, FOnLocalUserInfoCreated_Native> LocalUserInfoCreatedDelegates;
	FOnLocalUserInfoCreated_Native OnLocalUserInfoCreated_Native;
	TArray<UE::Online::FOnlineEventDelegateHandle> DelegateHandles;

	bool bStatUpdatesBlocked = false;
	
	friend ULocalUserInfo;

	// <FL> [BGR] To identify request results from different request turns
	int8 RefreshFriendsQueryID = 0; // it's ok if they overflow
	// </FL>
};

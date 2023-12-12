// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "OnlineIntegrationTypes.h"
#include "GameFramework/OnlineReplStructs.h"
#include "OnlineFriendTypes.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "LocalUserInfo.generated.h"

namespace UE::Online
{
struct FPresenceUpdated;
struct FRelationshipUpdated;
}

class UOnlineFriend;

DECLARE_MULTICAST_DELEGATE_TwoParams(FOnPlayerLoginStateChanged, TSharedRef<UE::Online::FAccountInfo> AccountInfo, EOnlineIntegrationUnmappedContext Context);

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API ULocalUserInfoBackend: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	void Initialize(FName InServiceProvider, EOnlineIntegrationUnmappedContext InContext, FOnlineIntegrationInternalAccessKey&&);
	void SetNickname(const FString& InNickname, FOnlineIntegrationInternalAccessKey&&);
	void SetLoginStatus(ECommonUserLoginStatus InLoginStatus, FOnlineIntegrationInternalAccessKey&&);
	void SetAvatar(const FPlayerAvatar& InAvatar, FOnlineIntegrationInternalAccessKey&&);
	void SetPendingLoginStateChange(bool bInPendingLoginStateChange, FOnlineIntegrationInternalAccessKey&&);
	void SetAccountId(UE::Online::FAccountId InAccountId, FOnlineIntegrationInternalAccessKey&&);
	void MarkBackendAsUsed(FOnlineIntegrationInternalAccessKey&&);
	
	[[nodiscard]] FName GetServiceProvider() const;
	[[nodiscard]] EOnlineIntegrationUnmappedContext GetContext() const;
	[[nodiscard]] ECommonUserLoginStatus GetLoginStatus() const;
	[[nodiscard]] const FPlayerAvatar& GetAvatar() const;
	[[nodiscard]] const FString& GetNickname() const;
	[[nodiscard]] uint32 IsPendingLoginStateChange() const;
	[[nodiscard]] UE::Online::FAccountId GetAccountId() const;

protected:
	UPROPERTY(BlueprintReadOnly)
	EOnlineIntegrationUnmappedContext Context;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FName ServiceProvider;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserLoginStatus LoginStatus = ECommonUserLoginStatus::NotLoggedIn;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FPlayerAvatar Avatar;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	uint8 bPendingLoginStateChange: 1 = true;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	uint8 bIsBackendInUse: 1 = false;
	
	UE::Online::FAccountId AccountId;
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API ULocalUserInfo: public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	explicit ULocalUserInfo(const FObjectInitializer&);

	/** Returns true if this user has successfully logged in */
	UFUNCTION(BlueprintCallable, Category = UserInfo)
	bool IsLoggedIn(EOnlineIntegrationUnmappedContext Context) const;

	UFUNCTION(BlueprintCallable, Category = UserInfo)
	ECommonUserLoginStatus GetLoginStatus(EOnlineIntegrationUnmappedContext Context) const;

	/** Returns the net id for the given context */
	UFUNCTION(BlueprintCallable, Category = UserInfo)
	FUniqueNetIdRepl GetNetId(EOnlineIntegrationMappedContext Context) const;

	FUniqueNetIdRepl GetNetId(EOnlineIntegrationUnmappedContext Context) const;

	/** Returns the user's human readable nickname */
	UFUNCTION(BlueprintCallable, Category = UserInfo)
	FString GetMappedContextNickname(EOnlineIntegrationMappedContext Context) const;

	UFUNCTION(BlueprintCallable, Category = UserInfo)
	FString GetUnmappedContextNickname(EOnlineIntegrationUnmappedContext Context) const;

	/** Returns an internal debug string for this player */
	UFUNCTION(BlueprintCallable, Category = UserInfo)
	FString GetDebugString() const;

	/** Accessor for platform user id */
	FPlatformUserId GetPlatformUserId() const;

	/** Gets the platform user index for older functions expecting an integer */
	int32 GetPlatformUserIndex() const;

	// Internal data, only intended to be accessed by online subsystems

	/** Looks up cached data using resolution rules */
	ULocalUserInfoBackend* GetCachedData(EOnlineIntegrationMappedContext Context);
	const ULocalUserInfoBackend* GetCachedData(EOnlineIntegrationMappedContext Context) const;

	ULocalUserInfoBackend* GetCachedData(EOnlineIntegrationUnmappedContext Context);
	const ULocalUserInfoBackend* GetCachedData(EOnlineIntegrationUnmappedContext Context) const;

	/** Return the subsystem this is owned by */
	class UCommonUserSubsystem* GetSubsystem() const;

	FDelegateHandle BindOnFriendAddedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle BindOnFriendRemovedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle AddOnLoginStateChangeDelegate(const FOnPlayerLoginStateChanged::FDelegate& Delegate) const;

	void RemoveLoginStatenChangeDelegate(FDelegateHandle &Handle) const;
	
	UFUNCTION(BlueprintCallable, Category=Default)
	UOnlineFriendList* CreateFriendList();
	
	virtual void HandlePresenceUpdated(const UE::Online::FPresenceUpdated& PresenceUpdated, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionInviteReceived(const UE::Online::FSessionInviteReceived& InviteReceived, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionJoined(const UE::Online::FSessionJoined& SessionJoined, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionLeft(const UE::Online::FSessionLeft& SessionLeft, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleSessionUpdated(const UE::Online::FSessionUpdated& SessionUpdated, EOnlineIntegrationUnmappedContext Context);
	virtual void HandleUISessionJoinRequested(const UE::Online::FUISessionJoinRequested& SessionJoinRequested, EOnlineIntegrationUnmappedContext Context);

	void SetPresenceJoinability(EOnlineUserPresenceJoinability Joinability, FOnlineIntegrationInternalAccessKey&&) const;
	void SetPresenceValue(const FString& Key, const FString& Value) const;
	void ClearPresenceProperty(const FString& Key) const;
	void SetPresenceString(const FString& InPresenceString) const;

	int32 GetLocalPlayerIndex() const { return LocalPlayerIndex; }

	UFUNCTION(BlueprintCallable)
	void UnlinkExternalAccount();

	UFUNCTION(BlueprintCallable)
	void LogoutExternalAccount(bool bForgetCachedAuth);

	UFUNCTION(BlueprintCallable)
	void LoginExternalAccount();

	TSharedPtr<UE::Online::FAccountInfo> GetAccountInfo(EOnlineIntegrationUnmappedContext Context) const;

	void SetGameSession(const FCommonSession &Session, FOnlineIntegrationInternalAccessKey&&);
	void SetNATType(const ECommonUserNATType InNATType, FOnlineIntegrationInternalAccessKey&&);
	void SetCurrentAuthenticationSequence(class UOnlineAuthenticationSequence* AuthenticationSequence, FOnlineIntegrationInternalAccessKey&&);
	void SetHasLinkedAccount(bool bHasLinkedAccount, FOnlineIntegrationInternalAccessKey&&);
	void SetCanPlayPrivilegeAvailability(const ECommonUserPrivilegeAvailability &Availability, FOnlineIntegrationInternalAccessKey&&);
	void SetCanPlayOnlinePrivilegeAvailability(const ECommonUserPrivilegeAvailability &Availability, FOnlineIntegrationInternalAccessKey&&);

	ECommonUserNATType GetNATType() const { return NATType; }
	FCommonSession GetGameSession() const { return GameSession; }

protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<ULocalUserInfoBackend> PrimaryBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<ULocalUserInfoBackend> SecondaryBackend;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<class UOnlineAuthenticationSequence> PendingAuthenticationSequence;

	TMap<EOnlineIntegrationUnmappedContext, TObjectPtr<ULocalUserInfoBackend>> ContextBackendMap;

	/** Primary controller input device for this user, they could also have additional secondary devices */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	FInputDeviceId PrimaryInputDevice;

	/** Specifies the logical user on the local platform, guest users will point to the primary user */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	FPlatformUserId PlatformUser;

	/** If this user is assigned a LocalPlayer, this will match the index in the GameInstance localplayers array once it is fully created */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	int32 LocalPlayerIndex = -1;
	
	/** Overall state of the user's initialization process */
	// UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	// ECommonUserInitializationState InitializationState = ECommonUserInitializationState::Invalid;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserNATType NATType = ECommonUserNATType::Unknown;

	/** If true, this user is allowed to be a guest */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	uint32 bCanBeGuest: 1 = false;

	/** If true, this is a guest user attached to primary user 0 */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	uint32 bIsGuest: 1 = false;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	uint32 bPlatformAccountLinkedToSecondaryAccount: 1 = false;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FCommonSession GameSession;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserPrivilegeAvailability CanPlayPrivilegeAvailability;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	ECommonUserPrivilegeAvailability CanPlayOnlinePrivilegeAvailability;

	friend class UCommonUserSubsystem;
	void OnLoginStatusChanged(TSharedRef<UE::Online::FAccountInfo> AccountInfo, EOnlineIntegrationUnmappedContext Context, FOnlineIntegrationInternalAccessKey&&);

	// A bunch of native delegates, which should be preferred when binding from native code
	FOnOnlineFriendListChangeNative OnFriendAddedNative;
	FOnOnlineFriendListChangeNative OnFriendRemovedNative;
	mutable FOnPlayerLoginStateChanged OnLoginStateChangedNative;

	UPROPERTY(BlueprintAssignable, Category = UserInfo)
	FOnOnlineFriendRelationshipChanged OnFriendRelationshipChanged;

	UPROPERTY(BlueprintAssignable, Category = UserInfo)
	FOnOnlineFriendListChange OnFriendAdded;

	UPROPERTY(BlueprintAssignable, Category = UserInfo)
	FOnOnlineFriendListChange OnFriendRemoved;

	void NotifyFriendPresenceUpdated(UOnlineFriend* OnlineFriend);

	UPROPERTY()
	TArray<TObjectPtr<UOnlineFriend>> Friends;
	TMap<UE::Online::FAccountId, TWeakObjectPtr<UOnlineFriend>> FriendLookup;

	void RelationshipUpdated(const UE::Online::FRelationshipUpdated& RelationshipUpdated, EOnlineIntegrationUnmappedContext Context);

	void QueryPlayerInfo(EOnlineIntegrationUnmappedContext Context);
	TFuture<void> QueryFriends(EOnlineIntegrationUnmappedContext Context);

	DECLARE_DELEGATE_TwoParams(FOnFriendInfoQueryComplete, UOnlineFriend* Friend, bool Success);
	void FetchFriendInfoAsync(UOnlineFriend* Friend, FOnFriendInfoQueryComplete OnQueryComplete);

	TMap<EOnlineIntegrationUnmappedContext, UE::Online::FOnlineEventDelegateHandle> RelationshipUpdatedDelegateHandles;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "OnlineFriend.h"
#include "OnlineIntegrationBackend.h"
#include "OnlineIntegrationTypes.h"
#include "User/OnlineUserBackendLink.h"
#include "User/OnlineUserInfo.h"

#include "LocalUserInfo.generated.h"

class USessionInformation;
namespace UE::Online
{
struct FPresenceUpdated;
struct FRelationshipUpdated;
}

class UOnlineFriend;
class UOnlineIntegrationBackend;
class UOnlineAuthenticationSequence;

struct ONLINEINTEGRATION_API FLocalUserInfoTags
{
	static FNativeGameplayTag IsPendingLoginStateChange;
};

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPlayerLoginStateChanged, ULocalUserInfo* UserInfo, TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend);

UCLASS(BlueprintType, Abstract)
class ONLINEINTEGRATION_API ULocalUserInfo: public UMVVMViewModelBase
{
	GENERATED_BODY()
	friend class UCommonUserSubsystem;
public:
	explicit ULocalUserInfo(const FObjectInitializer&);

	/** Accessor for platform user id */
	FPlatformUserId GetPlatformUserId() const;

	/** Gets the platform user index for older functions expecting an integer */
	int32 GetPlatformUserIndex() const;

	UFUNCTION(BlueprintCallable)
	ECommonUserLoginStatus GetLoginStatusForBackend(UOnlineIntegrationBackend* Backend) const;

	UOnlineUserBackendLink* GetUserBackend(const UOnlineIntegrationBackend* Backend);
	const UOnlineUserBackendLink* GetUserBackend(const UOnlineIntegrationBackend* Backend) const;
	UOnlineUserBackendLink* GetPlatformBackend();
	const UOnlineUserBackendLink* GetPlatformBackend() const;
	UOnlineUserBackendLink* GetBackendByIndex(int32 Index) const;
	UOnlineUserBackendLink* GetUserBackendByProvider(FName ProviderName) const;
	TArray<UOnlineUserBackendLink*> GetUserBackends() const;
	UOnlineUserInfo& GetOnlineUserInfo() const;
	
	int32 NumBackends() const;

	/** Return the subsystem this is owned by */
	class UCommonUserSubsystem* GetSubsystem() const;

	FDelegateHandle BindOnFriendAddedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle BindOnFriendRemovedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle AddOnLoginStateChangeDelegate(const FOnPlayerLoginStateChanged::FDelegate& Delegate) const;

	void RemoveLoginStatenChangeDelegate(FDelegateHandle &Handle) const;
	
	void SetPresenceValue(const FString& Key, const FString& Value) const;
	void SetPresenceValues(const TMap<FString, FString>& Value) const;
	void ClearPresenceProperty(const FString& Key) const;
	void SetPresenceString(const FString& InPresenceString) const;

	int32 GetLocalPlayerIndex() const { return LocalPlayerIndex; }

	USessionInformation* GetGameSession() const { return GameSession; }

	/** Shows the external friends UI for the platform backend, if any */
	void ShowExternalFriendsUI() const;

	TArray<UOnlineFriend*> GetFriends() const;
protected:
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineUserInfo> OnlineUserInfo;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineAuthenticationSequence> PendingAuthenticationSequence;

	UPROPERTY(FieldNotify, BlueprintReadOnly)
	TObjectPtr<UOnlineUserBackendLink> PrimaryBackend;
	
	UPROPERTY(FieldNotify, BlueprintReadOnly)
	TObjectPtr<UOnlineUserBackendLink> SecondaryBackend;
	
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
	// ECommonUserInitializationState InitializationState = ECommonUserInitializationState::In valid;

	/** If true, this user is allowed to be a guest */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	uint32 bCanBeGuest: 1 = false;

	/** If true, this is a guest user attached to primary user 0 */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	uint32 bIsGuest: 1 = false;

	/** The game session this player is currently in, if any. */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = UserInfo)
	TObjectPtr<USessionInformation> GameSession;

	/**
	 * All of this user's friends. The list is continuously updated as new backends are logged in or as friends are added/removed.
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = UserInfo)
	TArray<TObjectPtr<UOnlineFriend>> Friends;

	/**
	 * Map with the login status for each backend.
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify, Category = UserInfo)
	TMap<TObjectPtr<UOnlineIntegrationBackend>, ECommonUserLoginStatus> LoginStatusMap; 
	
	// A bunch of native delegates, which should be preferred when binding from native code
	FOnOnlineFriendListChangeNative OnFriendAddedNative;
	FOnOnlineFriendListChangeNative OnFriendRemovedNative;
	mutable FOnPlayerLoginStateChanged OnLoginStateChangedNative;

	UPROPERTY(BlueprintAssignable, Category = UserInfo)
	FOnOnlineFriendRelationshipChanged OnFriendRelationshipChanged;
	
	TMap<UE::Online::FAccountId, TWeakObjectPtr<UOnlineFriend>> FriendLookup;

	void RelationshipUpdated(const UE::Online::FRelationshipUpdated& RelationshipUpdated, UOnlineIntegrationBackend* Backend);

	void QueryFriends(UOnlineIntegrationBackend* Backend);

	TFuture<bool> FetchFriendInfoAsync(UOnlineFriend* Friend, UOnlineIntegrationBackend* Backend);
	
	TMap<TWeakObjectPtr<UOnlineIntegrationBackend>, UE::Online::FOnlineEventDelegateHandle> RelationshipUpdatedDelegateHandles;
};

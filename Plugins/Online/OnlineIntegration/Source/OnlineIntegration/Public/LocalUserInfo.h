// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "GameFramework/OnlineReplStructs.h"
#include "GameplayTagAssetInterface.h"
#include "GameplayTagContainer.h"
#include "NativeGameplayTags.h"
#include "Online/OnlineAsyncOpHandle.h"
#include "Online/Privileges.h"
#include "OnlineFriend.h"
#include "OnlineIntegrationBackend.h"
#include "OnlineIntegrationTypes.h"
#include "User/OnlineUserBackendLink.h"
#include "User/OnlineUserInfo.h"
#include <optional>

#include "LocalUserInfo.generated.h"

class UOnlinePrivilegeObserver;
class USessionDefinition;
class USessionInformation;
namespace UE::Online
{
struct FPresenceUpdated;
struct FRelationshipUpdated;
}

class UOnlineFriend;
class UOnlineIntegrationBackend;
class UOnlineAuthenticationSequence;
class UOnlineUserBackendLinkPrivate;

typedef UE::Online::EPrivilegeResults EPrivilegeResults;
typedef UE::Online::EUserPrivileges EUserPrivilege;
typedef UE::Online::FAccountId FOnlineAccountId;


struct ONLINEINTEGRATION_API FLocalUserInfoTags
{
	static FNativeGameplayTag IsPendingLoginStateChange;
};

/**
 * Brings together a session definition and a privilege observer for that session.
 */
USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FTrackedSessionDefinition
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<const USessionDefinition> SessionDefinition;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UOnlinePrivilegeObserver> PrivilegeObserver;
};


//<FL>[KonradA] Utility struct to quickly aggregate lightweight data  for player identification
USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FLocalUserNetIdBundle
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, SaveGame)
	FString AssociatedAccountIdString;
	UPROPERTY(BlueprintReadOnly, SaveGame)
	FString DisplayName;
	UPROPERTY(BlueprintReadOnly, SaveGame) 
	FString BackendName;


	friend FArchive& operator<<(FArchive& Ar, FLocalUserNetIdBundle& data)
	{
		Ar << data.AssociatedAccountIdString;
		Ar << data.DisplayName;
		Ar << data.BackendName;
		return Ar;

	}
	// Convert FAccID to string for network transport and serialization while respecting the OnlineServicesType and appending it
	void SetAssociatedAccountId(UE::Online::FAccountId id)
	{
		TArray<uint8> ReplicationData = UE::Online::FOnlineIdRegistryRegistry::Get().ToReplicationData(id);
		ReplicationData.Insert(static_cast<uint8>(id.GetOnlineServicesType()), 0);
		AssociatedAccountIdString = BytesToHex(ReplicationData.GetData(), ReplicationData.Num());	
	}

	// Convert String to FAccID for network transport and serialization while respecting that it was serialized with the OnlineServicesType at the 
	// end of the byte stream
	UE::Online::FAccountId DeserializeGetAccountId()
	{
		UE::Online::FAccountId OutAccountId;
		// First recreate the account id
		if (AssociatedAccountIdString == TEXT("INVALID") || AssociatedAccountIdString == "")
		{
			OutAccountId = UE::Online::FAccountId{};
		}
		else
		{
			TArray<uint8> ReplicationData;
			ReplicationData.AddUninitialized(AssociatedAccountIdString.Len());
			ReplicationData.SetNum(HexToBytes(AssociatedAccountIdString, ReplicationData.GetData()));

			const UE::Online::EOnlineServices OnlineServicesType = static_cast<UE::Online::EOnlineServices>(ReplicationData[0]);
			ReplicationData.RemoveAt(0);

			OutAccountId = UE::Online::FOnlineIdRegistryRegistry::Get().ToAccountId(OnlineServicesType, ReplicationData);
		}
		return OutAccountId;
	}

};


typedef TArray<FLocalUserNetIdBundle> FUserNetIdBundles;

//</FL>

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnPlayerLoginStateChanged, ULocalUserInfo* UserInfo, TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend);
//<FL>[KonradA] Adding delegates to help the forced nuclear friend list re-cache
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendListReset, ULocalUserInfo* UserInfo);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnQueryFriendsAllCompleted, ULocalUserInfo* UserInfo);
//</FL>
DECLARE_DELEGATE_OneParam(FOnPrivilegeQueryDone, EPrivilegeResults privilegeResult)

DECLARE_MULTICAST_DELEGATE(FOnQueryAllBlockedUsersDone)

// <FL> [ZimmermannA] 
UENUM(BlueprintType)
enum class EPrivilegeCheckResult : uint8
{
	PCR_NoPrivilege = 0,
	PCR_InvalidResult,
	PCR_HasPrivilege
};
// </FL> 

DECLARE_DYNAMIC_DELEGATE_OneParam(FUserHasPremiumAccountDelegate, bool, hasPremium);
// [TranN] FOnShowStoreUIClosedDelegate is in OnlineExternalUIInterface.h
// If I include OnlineExternalUIInterface.h here, it would cause a lot of compiling errors due to ambiguous FOnlineError definition.
// So FOnShowStoreUIClosedDelegate2 is just the same delegate without the need to include that header.
DECLARE_DELEGATE_OneParam(FOnShowStoreUIClosedDelegate2, bool /*bPurchased*/);
// </FL>

UCLASS(BlueprintType, Abstract)
class ONLINEINTEGRATION_API ULocalUserInfo : public UMVVMViewModelBase
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
	UFUNCTION(BlueprintCallable)
	UOnlineUserBackendLink* GetPlatformBackend();
	const UOnlineUserBackendLink* GetPlatformBackend() const;
	UOnlineUserBackendLink* GetBackendByIndex(int32 Index) const;
	UOnlineUserBackendLink* GetUserBackendByProvider(FName ProviderName) const;
	TArray<UOnlineUserBackendLink*> GetUserBackends() const;
	UOnlineUserInfo& GetOnlineUserInfo() const;
	
	UFUNCTION(BlueprintCallable)
	UOnlineUserBackendLink* GetUserBackendEpic() const;
	
	int32 NumBackends() const;

	FOnQueryAllBlockedUsersDone OnQueryAllBlockedusersDone;
	UPROPERTY()
	TArray<UOnlineIntegrationBackend*> BackendsToQueryBlockedUsersQueue = TArray<UOnlineIntegrationBackend*>();

	/** Return the subsystem this is owned by */
	class UCommonUserSubsystem* GetSubsystem() const;

	FDelegateHandle BindOnFriendAddedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle BindOnFriendRemovedDelegate(const FOnOnlineFriendListChangeNative::FDelegate& Delegate);
	FDelegateHandle AddOnLoginStateChangeDelegate(const FOnPlayerLoginStateChanged::FDelegate& Delegate) const;
//<FL>[KonradA]
	FDelegateHandle AddOnResetFriendlistDelegate(const FOnFriendListReset::FDelegate& Delegate);
	FDelegateHandle AddOnQueryFriendsAllCompleted(const FOnQueryFriendsAllCompleted::FDelegate& Delegate);
	void RemoveOnQueryFriendsAllCompleted(FDelegateHandle handle);
//</FL>

//<FL>[ZimmermannA]	
	UFUNCTION(BlueprintCallable, BlueprintPure)
	bool IsSessionHost();
//</FL>

	void RemoveLoginStatenChangeDelegate(FDelegateHandle &Handle) const;
	
	void SetPresenceValue(const FString& Key, const FString& Value) const;
	void SetPresenceValues(const TMap<FString, FString>& Value) const;
	void ClearPresenceProperty(const FString& Key) const;
	void SetPresenceString(const FString& InPresenceString) const;

	int32 GetLocalPlayerIndex() const { return LocalPlayerIndex; }

	USessionInformation* GetGameSession() const { return GameSession; }

	/** Shows the external friends UI for the platform backend, if any */
	void ShowExternalFriendsUI() const;

	// <FL> [MartinC] Shows the external invite UI for the platform backend, if any
	UFUNCTION(BlueprintCallable)
	void ShowExternalInviteUI() const;

	TArray<UOnlineFriend*> GetFriends() const;
	
	//<FL> [ZimmermannA] [KonradA:extended for different privilege types]
	bool GetPrivilegeResult(EPrivilegeResults& privileges, EUserPrivilege Privilege) const;

	/**
	 * Queries the availability of a privilege for this user on a given backend. 
	 */
	TFuture<ECommonUserPrivilegeResult> FetchPrivilegeResultForBackend(UOnlineIntegrationBackend* Backend, ECommonUserPrivilege Privilege) const;
	
	UFUNCTION()
	void UpdateCrossplayUGCPrivileges();
	void UpdatePrivileges();

	//<FL>[KonradA]
	UFUNCTION(BlueprintCallable)
	TArray<FLocalUserNetIdBundle> GetUserNetIdBundles();
	//</FL>
	
	// privilege checking
	void PollHasPremiumPrivilege(FUserHasPremiumAccountDelegate completeDelegate);

	UFUNCTION(BlueprintCallable) 
	void UserCanCrossPlay(EPrivilegeCheckResult& privilegeResult);

	UFUNCTION(BlueprintCallable) 
	void UserCanSeeUGC(EPrivilegeCheckResult& privilegeResult);

	UFUNCTION(BlueprintCallable)
	void UserHasNoTextCommunicationRestrictions(EPrivilegeCheckResult& privilegeResult);


	void UserHasPrivilegeGeneric(EUserPrivilege Privilege, EPrivilegeCheckResult& privilegeResult) const;
	// ~ privilege checking
	//</FL>

	void QueryFriends(); // <FL> [TranN]
	void ResetFriends(); // <FL> [KonradA]
	void QueryFriendsAll(); //<FL> [KonradA]

	UOnlinePrivilegeObserver* GetPrivilegeObserverForSession(const USessionDefinition* SessionDefinition) const;
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
	 * All the session definitions this user *might* be able to use. Each specific entry will track availability on its own.
	 */
	UPROPERTY(BlueprintReadOnly, Category = UserInfo)
	TArray<FTrackedSessionDefinition> TrackedSessionDefinitions;
	
	// A bunch of native delegates, which should be preferred when binding from native code
	FOnOnlineFriendListChangeNative OnFriendAddedNative;
	FOnOnlineFriendListChangeNative OnFriendRemovedNative;
	mutable FOnPlayerLoginStateChanged OnLoginStateChangedNative;
//<FL>[KonradA]
	FOnFriendListReset OnFriendListReset;
	FOnQueryFriendsAllCompleted OnQueryFriendsAllCompleted;
//</FL>


	UPROPERTY(BlueprintAssignable, Category = UserInfo)
	FOnOnlineFriendRelationshipChanged OnFriendRelationshipChanged;
	
	TMap<UE::Online::FAccountId, TWeakObjectPtr<UOnlineFriend>> FriendLookup;

	void RelationshipUpdated(const UE::Online::FRelationshipUpdated& RelationshipUpdated, UOnlineIntegrationBackend* Backend);

	void QueryBlocked(UOnlineIntegrationBackend* Backend);

	TFuture<bool> FetchFriendInfoAsync(UOnlineFriend* Friend, UOnlineIntegrationBackend* Backend);
	
	TMap<TWeakObjectPtr<UOnlineIntegrationBackend>, UE::Online::FOnlineEventDelegateHandle> RelationshipUpdatedDelegateHandles;


	TArray<UOnlineIntegrationBackend*> BackendsToQueryFriends; // <FL> [TranN]

	//<FL>[KonradA]
	bool IsQueryingBlocked;
	UOnlineIntegrationBackend* NextBackendToQueryBlocked;

	static double sLastPrivilegeUpdateTime;
	//</FL>

	
	//<FL> [ZimmermannA] [KonradA: added support for all privilege query types and a function that receives an outer callback]
public:
	// Queries a privilege check. Returns false if query request was not successful.
	bool RetrievePrivileges(TOptional<EPrivilegeResults>& Result, EUserPrivilege PrivilegeToQuery) const;
	bool RetrievePrivileges(TOptional<EPrivilegeResults>& PrivilegeResult, EUserPrivilege PrivilegeToQuery, FOnPrivilegeQueryDone Callback) const;
	void DisplayPremiumInformation(const FOnShowStoreUIClosedDelegate2& OnShowStoreUIClosedDelegate = FOnShowStoreUIClosedDelegate2()) const;

private:
	bool bUsesMultiplayerFeature = false;
	//</FL> 
public:

	//<FL>[KonradA]
	bool HasUserBlocked(FUserNetIdBundles userBundlesToCheck);
	void QueryBlockedAll();

	//</FL

protected:
	
	TOptional<EPrivilegeResults> mPrivilegeResultCanPlayOnline;
	TOptional<EPrivilegeResults> mPrivilegeResultCanCrossPlay;
	TOptional<EPrivilegeResults> mPrivilegeResultCanUseUserGeneratedContent;
	TOptional<EPrivilegeResults> mPrivilegeResultIsSocialRestricted;
	bool bDisableCrossplayGlobally = false;

	//</FL>
};

#pragma once

#include "CommonSessionTypes.h"
#include "EngineMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationTypes.h"
#include "OnlinePresenceTypes.h"
#include "OnlineFriendTypes.generated.h"


/**
 * Social relationship status
 */
UENUM()
enum class EOnlineRelationship : uint8
{
	/* Friend */
	Friend,
	/* Not friend */
	NotFriend,
	/* Invite Sent to User */
	InviteSent,
	/* Invite Received from User */
	InviteReceived,
	/* Local user has Blocked the other user */
	Blocked
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnOnlineFriendRelationshipChanged, class UOnlineFriend*, Friend, EOnlineRelationship, OldRelationship,
	EOnlineIntegrationUnmappedContext, Context);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendListChange, class UOnlineFriend*, Friend);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineFriendRelationshipChangedNative, class UOnlineFriend* Friend, EOnlineRelationship OldRelationship,
	EOnlineIntegrationUnmappedContext Context);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendListChangeNative, class UOnlineFriend* Friend);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendPresenceUpdatedNative, class UOnlineFriend* Friend);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPresenceQueryComplete, class UOnlineFriend*, Friend, bool, bSuccess);

struct FOnlineIntegrationInternalAccessKey;

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineFriendBackend: public UMVVMViewModelBase
{
	GENERATED_BODY()
public:

protected:
	UE::Online::FAccountId AccountId;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineRelationship Relationship;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FPlayerAvatar Avatar;
};

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineFriend : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	bool IsEffectivelyOnline() const;

	UFUNCTION(BlueprintCallable)
	bool IsPlayingThisGame() const;

	UFUNCTION(BlueprintCallable)
	ECommonUserNATType GetAdvertisedNATType() const;

	UFUNCTION(BlueprintCallable)
	bool IsPresenceJoinable() const;

	class UCommonUserSubsystem* GetSubsystem() const;
	
	UFUNCTION(BlueprintPure)
	class ULocalUserInfo* GetLocalUserInfo() const;
	
	UFUNCTION(BlueprintCallable)
	void InviteToSession();

	UFUNCTION(BlueprintCallable)
	void AcceptGameInvite();

	UFUNCTION(BlueprintCallable)
	void RejectGameInvite();

	UFUNCTION(BlueprintCallable)
	void JoinGame();

	UOnlineUserPresence* GetPresence() const;

	[[nodiscard]] UE::Online::FAccountId GetAccountId() const;
	[[nodiscard]] FString GetDisplayName() const;
	[[nodiscard]] FString GetNickname() const;
	[[nodiscard]] EOnlineRelationship GetRelationship() const;
	[[nodiscard]] EOnlineIntegrationUnmappedContext GetContext() const;
	[[nodiscard]] FCommonSession GetGameSession() const;
	[[nodiscard]] UTexture2D* GetAvatar() const;
	[[nodiscard]] bool IsHasIncomingInvite() const;
	void SetAccountId(const UE::Online::FAccountId& AccountId, FOnlineIntegrationInternalAccessKey&&);
	void SetDisplayName(const FString& DisplayName, FOnlineIntegrationInternalAccessKey&&);
	void SetNickname(const FString& Nickname, FOnlineIntegrationInternalAccessKey&&);
	void SetRelationship(const EOnlineRelationship Relationship, FOnlineIntegrationInternalAccessKey&&);
	void SetContext(const EOnlineIntegrationUnmappedContext Context, FOnlineIntegrationInternalAccessKey&&);
	void SetGameSession(const FCommonSession& GameSession, FOnlineIntegrationInternalAccessKey&&);
	void SetAvatar(UTexture2D* InAvatar, FOnlineIntegrationInternalAccessKey&&);
	void SetHasIncomingInvite(const bool bHasIncomingInvite, FOnlineIntegrationInternalAccessKey&&);

protected:
	virtual void PostInitProperties() override;
	
	UE::Online::FAccountId AccountId;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString DisplayName;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FString Nickname;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	EOnlineRelationship Relationship;

	UPROPERTY(BlueprintReadOnly)
	EOnlineIntegrationUnmappedContext Context;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<class UOnlineUserPresence> Presence;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FCommonSession GameSession;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UTexture2D> Avatar;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	FSlateBrush AvatarBrush;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	bool bHasIncomingInvite = false;

	/**
	 * The primary backend for this player. Will be one of @PlatformBackendInfo or @ExternalBackendInfo
	 * Essentially if both backends are relevant this will point to the platform backend, otherwise it will point to the relevant backend.
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineFriendBackend> PrimaryBackendInfo;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineFriendBackend> PlatformBackendInfo;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineFriendBackend> ExternalBackendInfo;
};

DECLARE_MULTICAST_DELEGATE(FOnOnlineFriendListSortedNative);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOnlineFriendListSortedK2);

UCLASS(BlueprintType)
class ONLINEINTEGRATION_API UOnlineFriendList : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category=Default)
	void SetSearchTerm(const FString& InSearchTerm);

	UFUNCTION(BlueprintCallable, Category=Default)
	void MakeContextRelevant(EOnlineIntegrationUnmappedContext Context);

	UFUNCTION(BlueprintCallable, Category=Default)
	bool MatchesFilters(UOnlineFriend* Friend) const;

	const TArray<TObjectPtr<UOnlineFriend>>& GetFriends() const
	{
		return Friends;
	}

	FDelegateHandle AddOnFriendListSortedDelegate(FOnOnlineFriendListSortedNative::FDelegate&& Delegate);
	void RemoveOnFriendListSortedDelegate(FDelegateHandle DelegateHandle);

protected:
	friend class ULocalUserInfo;
	void FriendAdded(UOnlineFriend* Friend);
	void FriendRemoved(UOnlineFriend* Friend);
	void RebuildFilteredArray();

	UPROPERTY(BlueprintAssignable, Category=Default)
	FOnOnlineFriendListChange OnFriendAdded;

	UPROPERTY(BlueprintAssignable, Category=Default)
	FOnOnlineFriendListChange OnFriendRemoved;

	UPROPERTY(BlueprintAssignable, Category=Default)
	FOnOnlineFriendListSortedK2 OnFriendListSorted_K2;
	FOnOnlineFriendListSortedNative OnFriendListSorted;
	void NotifySorted() const;

	/**
	 * @brief The friend list once all the filtration mechanisms were applied.
	 */
	UPROPERTY(BlueprintReadOnly, Category=Default)
	TArray<TObjectPtr<UOnlineFriend>> Friends;

	TArray<TObjectPtr<UOnlineFriend>> UnfilteredFriendList;

	FString SearchTerm;
	TArray<EOnlineIntegrationUnmappedContext, TInlineAllocator<2>> RelevantContexts;

	TWeakObjectPtr<ULocalUserInfo> UserInfoPtr;
};

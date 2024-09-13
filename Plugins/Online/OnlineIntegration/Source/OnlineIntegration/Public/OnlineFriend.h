#pragma once

#include "CommonSessionTypes.h"
#include "CoreMinimal.h"
#include "GameFramework/OnlineReplStructs.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationTypes.h"
#include "Styling/SlateBrush.h"

#include "OnlineFriend.generated.h"

class UOnlineUserInfo;
class UTexture2D;
class UOnlineUserPresence;
class USessionInformation;

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
	UOnlineIntegrationBackend*, Backend);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendListChange, class UOnlineFriend*, Friend);

DECLARE_MULTICAST_DELEGATE_ThreeParams(FOnOnlineFriendRelationshipChangedNative, class UOnlineFriend* Friend, EOnlineRelationship OldRelationship,
	UOnlineIntegrationBackend* Backend);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendListChangeNative, class UOnlineFriend* Friend);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineFriendPresenceUpdatedNative, class UOnlineFriend* Friend);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnPresenceQueryComplete, class UOnlineFriend*, Friend, bool, bSuccess);

UCLASS(BlueprintType, Abstract, NotBlueprintable, Within=LocalUserInfo)
class ONLINEINTEGRATION_API UOnlineFriend : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	
	UFUNCTION(BlueprintCallable)
	bool IsPlayingThisGame() const;
	
	class UCommonUserSubsystem* GetSubsystem() const;
	
	UFUNCTION(BlueprintPure)
	class ULocalUserInfo* GetLocalUserInfo() const;

	UFUNCTION(BlueprintPure)
	UOnlineUserPresence* GetPresence(UOnlineIntegrationBackend* Backend) const;

	[[nodiscard]] USessionInformation* GetGameSession() const;
	
	UFUNCTION(BlueprintPure)
	EOnlineRelationship GetRelationshipForBackend(UOnlineIntegrationBackend* Backend) const;
	
	[[nodiscard]] UOnlineUserInfo* GetOnlineUser() const;

	UFUNCTION(BlueprintPure)
	EOnlineUserPresenceStatus GetPresenceStatus(UOnlineIntegrationBackend* Backend) const;
	
	UFUNCTION(BlueprintPure)
	EOnlineUserPresenceJoinability GetPresenceJoinability(UOnlineIntegrationBackend* Backend) const;

	UFUNCTION(BlueprintPure)
	EOnlineUserPresenceGameStatus GetPresenceGameStatus(UOnlineIntegrationBackend* Backend) const;

protected:
	
	UE::Online::FAccountId AccountId;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TMap<TObjectPtr<UOnlineIntegrationBackend>, EOnlineRelationship> RelationshipMap;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TMap<TObjectPtr<UOnlineIntegrationBackend>, TObjectPtr<UOnlineUserPresence>> PresenceMap;
	
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<USessionInformation> GameSession;

	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineUserInfo> OnlineUser;
};

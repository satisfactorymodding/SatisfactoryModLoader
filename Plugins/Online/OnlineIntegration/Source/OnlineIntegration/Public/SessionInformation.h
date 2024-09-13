// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CommonSessionTypes.h"
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "OnlineIntegrationBackend.h"
#include "OnlineKeyValuePair.h"
#include "OnlineSessionBackendLink.h"

#include "SessionInformation.generated.h"

class USessionDefinition;
class USessionMemberInformation;
class AGameSession;
class UOnlineUserInfo;
class UOnlineSessionBackendLink;

USTRUCT(BlueprintType)
struct ONLINEINTEGRATION_API FCustomOnlineSessionSetting
{
	GENERATED_BODY()

	UPROPERTY()
	FName Name;
	
	UE::Online::FSchemaVariant Data;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineSessionAttributesAdded, const TArray<FCustomOnlineSessionSetting>& NewAttributes);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineSessionAttributesRemoved, const TArray<FName>& RemovedAttributes);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnOnlineSessionAttributesUpdated, const TArray<FCustomOnlineSessionSetting>& UpdatedAttributes);

/**
 * A model that can be used for accessing and modifying session information. An object of this type will be created for every session created by this plugin,
 * online, IP or offline. For non online sessions, there will be no session backend link objects. Objects of this type will also be created on clients
 * when sessions are joined. 
 */
UCLASS(Abstract, NotBlueprintable)
class ONLINEINTEGRATION_API USessionInformation : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	TArray<UOnlineSessionBackendLink*> GetBackends() const
	{
		return Backends;
	}

	UOnlineSessionBackendLink* GetHostingBackendLink() const
	{
		return SessionBackend;
	}

	UOnlineSessionBackendLink* GetSessionBackendLink(UOnlineIntegrationBackend* OnlineBackend) const;

	UFUNCTION(BlueprintPure)
	FCommonSession GetSessionHandle() const;

	/**
	 * Will update this session's custom settings on all of its backends but only as long as the Player requesting this update is the sessions host and is a
	 * local player.
	 * @param Player
	 * @param UpdatedCustomSettings Array of custom settings that will be updated. Entries not present in this array will remain unchanged
	 */
	UFUNCTION(BlueprintCallable)
	void UpdateCustomSettings(APlayerController *Player, const TArray<FCustomOnlineSessionSetting>& UpdatedCustomSettings);

	UFUNCTION(BlueprintCallable)
	void AddSessionMember(APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable)
	void RemoveSessionMember(APlayerState* PlayerState);

	UFUNCTION(BlueprintCallable)
	bool GetCustomSetting(FName SettingName, FCustomOnlineSessionSetting& OutSetting);

	UFUNCTION(BlueprintCallable)
	virtual void RefreshCachedData(FDateTime UpdateTimestampUtc);

	FName GetCurrentProfile() const;
	int32 GetNumMaxConnections() const;

	FDateTime GetLastUpdateTimestampUtc() const;

	ECommonSessionJoinPolicy GetJoinPolicy() const;

	FDelegateHandle AddOnSessionAttributesAddedDelegate(FOnOnlineSessionAttributesAdded::FDelegate Delegate);
	FDelegateHandle AddOnSessionAttributesRemovedDelegate(FOnOnlineSessionAttributesRemoved::FDelegate Delegate);
	FDelegateHandle AddOnSessionAttributesUpdatedDelegate(FOnOnlineSessionAttributesUpdated::FDelegate Delegate);

	void RemoveOnSessionAttributesAddedDelegate(FDelegateHandle DelegateHandle);
	void RemoveOnSessionAttributesRemovedDelegate(FDelegateHandle DelegateHandle);
	void RemoveOnSessionAttributesUpdatedDelegate(FDelegateHandle DelegateHandle);

	void ApplyProfile(FName ProfileName);
	void ApplyAllowNewMembers(bool AllowNewMembers);
protected:
	void UpdatePresenceForSessionMembers() const;
	
	/**
	 * Finds any session member that has this account id.
	 * @param AccountId
	 * @return
	 */
	USessionMemberInformation* FindMember(UE::Online::FAccountId AccountId);
	int32 FindMemberIndex(UE::Online::FAccountId AccountId);
	
	/**
	 * Points to the main backend that actually hosts this session.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineSessionBackendLink> SessionBackend;

	/**
	 * Backend information for all the backends this session exists for. This includes the main session and any potential mirror sessions.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TArray<TObjectPtr<UOnlineSessionBackendLink>> Backends;

	/**
	 * The hosting player. 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<USessionMemberInformation> Host;

	/**
	 * All session members. This array will include the host as well as all other clients. 
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TArray<TObjectPtr<USessionMemberInformation>> Members;

	/**
	 * A ptr to the game session actor. Will only be valid if the session is hosted locally.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<AGameSession> GameSessionActor;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	FGameplayTagContainer SessionTags;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TMap<FName, FCustomOnlineSessionSetting> CustomSettings;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	ECommonSessionJoinPolicy JoinPolicy;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	int32 NumMaxConnections = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	FDateTime LastUpdateTimestampUtc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	FName CurrentProfile;

	/**
	 * The session definition that was used to create this session. Only valid available on the host.
	 */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<USessionDefinition> SessionDefinition;

	FOnOnlineSessionAttributesAdded OnSessionAttributesAdded;
	FOnOnlineSessionAttributesRemoved OnSessionAttributesRemoved;
	FOnOnlineSessionAttributesUpdated OnSessionAttributesUpdated;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Online/CoreOnline.h"
#include "MVVMViewModelBase.h"

#include "OnlineUserInfo.generated.h"

class UGameplayTagContainerViewModel;
class UOnlineUserBackendLink;
class UOnlineIntegrationBackend;

/**
 * Online information for a user, be it a local user or a remote user. This can include friends, party members, players in the same session, and so on.
 */
UCLASS(Abstract, NotBlueprintable)
class ONLINEINTEGRATION_API UOnlineUserInfo : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UOnlineUserInfo();
	
	UOnlineUserBackendLink* GetUserBackend(const UOnlineIntegrationBackend* Backend);
	const UOnlineUserBackendLink* GetUserBackend(const UOnlineIntegrationBackend* Backend) const;
	UOnlineUserBackendLink* GetPrimaryBackendLink();
	const UOnlineUserBackendLink* GetPrimaryBackendLink() const;
	UOnlineUserBackendLink* GetBackendByIndex(int32 Index);
	UOnlineUserBackendLink* GetUserBackendByProvider(FName ProviderName);
	TArray<UOnlineUserBackendLink*> GetUserBackendLinks() const;
	int32 NumBackendLinks() const;
	const UGameplayTagContainerViewModel& GetTagContainer() const;

	/**
	 * If any of this user's backends have this account it, it'll be found by this function. Can be used to simply tell if an online user has a specific
	 * account id
	 */
	UOnlineUserBackendLink* GetUserBackendLinkForAccountId(UE::Online::FAccountId AccountId) const;
protected:
	/**
	 * All backends we know this user exists on.
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TArray<TObjectPtr<UOnlineUserBackendLink>> BackendLinks;

	/**
	 * The primary backend of this online user, in relation to the local environment. Thus, if the user has a link to the platform online backend,
	 * that will be it's primary backend link. Otherwise if it doesn't, it will be another arbitrary backend link. This should always have a valid value.
	 */
	UPROPERTY(BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineUserBackendLink> PrimaryBackendLink;

	UPROPERTY(BlueprintReadOnly, FieldNotify, Category="Online User")
	TObjectPtr<UGameplayTagContainerViewModel> UserTagsContainer;
};

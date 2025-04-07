// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineUserBackendLink.h"

#include "OnlineUserBackendLinkPrivate.generated.h"

struct FGameplayTag;
class UOnlineIntegrationBackendPrivate;
/**
 * The private counterpart of a UOnlineUserBackendLink. Set up as a private class to only allow access from within the plugin
 */
UCLASS(Hidden)
class UOnlineUserBackendLinkPrivate : public UOnlineUserBackendLink
{
	GENERATED_BODY()
public:
	void Initialize(UOnlineIntegrationBackend* OnlineBackend);

	void SetLoginStatus(ECommonUserLoginStatus InLoginStatus);
	void SetNickname(const FString& InNickname);
	void SetAvatar(const FPlayerAvatar& InAvatar);
	void SetAccountId(UE::Online::FAccountId InAccountId);
	void SetOnlineUser(UOnlineUserInfo* InUserInfo);

	void SetDisplayPictureURL(const FString& InPictureURL);

	UOnlineIntegrationBackendPrivate* GetOnlineBackendPrivate() const;
	UGameplayTagContainerViewModel& GetMutableTagContainer();
};

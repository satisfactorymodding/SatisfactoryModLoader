// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineUserInfo.h"

#include "OnlineUserInfoPrivate.generated.h"

class UOnlineUserBackendLinkPrivate;
/**
 *
 */
UCLASS(Hidden)
class UOnlineUserInfoPrivate : public UOnlineUserInfo
{
	GENERATED_BODY()
public:
	void RegisterBackendLink(UOnlineUserBackendLink* BackendLink);
	UGameplayTagContainerViewModel& GetMutableTagContainer();
};

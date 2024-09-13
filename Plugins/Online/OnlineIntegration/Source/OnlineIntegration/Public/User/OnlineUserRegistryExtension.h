// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "CoreMinimal.h"
#include "Interface.h"
#include "Online/CoreOnline.h"

#include "OnlineUserRegistryExtension.generated.h"

class UCommonUserSubsystem;
class ULocalUserInfo;
class UOnlineUserBackendLink;
class UOnlineUserInfo;

UINTERFACE()
class ONLINEINTEGRATION_API UOnlineUserRegistryExtension : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class ONLINEINTEGRATION_API IOnlineUserRegistryExtension
{
	GENERATED_BODY()

public:
	/**
	 * Tries to resolve a user from a backend link.
	 * @param BackendLink the backend link that is connected to this user
	 * @return a future user info if this extension can resolve the user info
	 */
	virtual TOptional<TFuture<UOnlineUserInfo*>> ResolveOnlineUser(ULocalUserInfo* LocalUser, UOnlineUserBackendLink* BackendLink);

	virtual void UserBackendLinkInitialized(UOnlineUserBackendLink* UserBackendLink);
};

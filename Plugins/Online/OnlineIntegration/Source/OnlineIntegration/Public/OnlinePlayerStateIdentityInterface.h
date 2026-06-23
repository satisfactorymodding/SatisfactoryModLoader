// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Online/CoreOnline.h"
#include "OnlinePlayerStateIdentityInterface.generated.h"

UINTERFACE(MinimalAPI)
class UOnlinePlayerStateIdentityInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * Interface that can be implemented by the PlayerState to allow retrieval of online information from the player state, such as
 * secondary player identities and their currently logged in platform account ID
 */
class ONLINEINTEGRATION_API IOnlinePlayerStateIdentityInterface
{
	GENERATED_BODY()
public:
	/**
	 * Returns the platform account ID for the player,
	 * e.g. the account that the player is currently logged in to their primary backend
	 * This is different from PlayerState GetUniqueId, which will be a crossplay (e.g. Epic) account ID
	 * that the player will initiate the connection to the server with (since platforms do not know how to authorize native platform IDs of other platforms)
	 */
	virtual UE::Online::FAccountId GetPlatformAccountId() const = 0;

	/** Returns the nickname for the player platform. This cannot be retrieved from cross play identity because platforms do not know how to handle native platform IDs of other platforms) */
	virtual FString GetPlatformNickname() const { return FString{}; }

	/** Returns the Avatar URL for the player platform. This cannot be retrieved from cross play identity because platforms do not know how to handle native platform IDs of other platforms) */
	virtual FString GetPlatformAvatarURL() const { return FString{}; }
};

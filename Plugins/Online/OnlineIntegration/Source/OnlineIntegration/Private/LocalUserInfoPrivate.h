// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "LocalUserInfo.h"
#include "Presence.h"

#include "LocalUserInfoPrivate.generated.h"

class UOnlineUserInfoPrivate;
class UOnlineUserBackendLinkPrivate;
class ULocalUserInfoBackendPrivate;

/**
 * 
 */
UCLASS(Hidden)
class ULocalUserInfoPrivate : public ULocalUserInfo
{
	GENERATED_BODY()
	friend class UCommonUserSubsystem;
public:

	void SetLoginStatusForBackend(ECommonUserLoginStatus InLoginStatus, UOnlineIntegrationBackend* Backend);
	void SetPresenceJoinability(UE::Online::EUserPresenceJoinability Joinability) const;
	void SetGameSession(USessionInformation* InSession);
	void SetCurrentAuthenticationSequence(class UOnlineAuthenticationSequence* AuthenticationSequence);
	void OnLoginStatusChanged(TSharedRef<UE::Online::FAccountInfo> AccountInfo, UOnlineIntegrationBackend* Backend);

	void HandlePresenceUpdated(const UE::Online::FPresenceUpdated& PresenceUpdated, UOnlineIntegrationBackend* Backend);
	void HandleUISessionJoinRequested(const UE::Online::FUISessionJoinRequested& SessionJoinRequested, UOnlineIntegrationBackend* Backend);

	UOnlineUserBackendLinkPrivate* GetBackendPrivate(UOnlineIntegrationBackend* Backend);
	UOnlineUserInfoPrivate& GetOnlineUserInfoPrivate();
};

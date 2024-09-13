// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "OnlineFriend.h"
#include "CoreMinimal.h"

#include "OnlineFriendPrivate.generated.h"

namespace UE::Online
{
struct FPresenceUpdated;
struct FUserPresence;
}
/**
 * 
 */
UCLASS(Hidden)
class ONLINEINTEGRATION_API UOnlineFriendPrivate : public UOnlineFriend
{
	GENERATED_BODY()
public:

	void SetRelationshipForBackend(const EOnlineRelationship Relationship, UOnlineIntegrationBackend* Backend);
	void SetGameSession(USessionInformation* GameSession);
	void SetOnlineUser(UOnlineUserInfo* InOnlineUser);

	void HandlePresenceUpdated(const UE::Online::FPresenceUpdated& PresenceUpdated, UOnlineIntegrationBackend* Backend);
	void InitPresence(TSharedRef<const UE::Online::FUserPresence> PresenceRef, UOnlineIntegrationBackend* Backend);

private:
	void EnsureSessionUpToDate(UOnlineUserPresence* Presence);
};

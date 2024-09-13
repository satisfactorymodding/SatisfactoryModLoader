// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineSessionBackendLink.h"

#include "OnlineSessionBackendLinkPrivate.generated.h"

class UCommonSessionSubsystem;

/**
 * The private counterpart of an online session backend link. They may only be created by the UCommonSessionSubsystem class so that it may effectively keep
 * track of all instances
 */
UCLASS(Hidden)
class UOnlineSessionBackendLinkPrivate : public UOnlineSessionBackendLink
{
	GENERATED_BODY()
	friend class USessionInformationPrivate;
public:
	void Initialize(UOnlineIntegrationBackend* InOnlineBackend, UE::Online::FOnlineSessionId InSessionId, UCommonSessionSubsystem& CommonSessionSubsystem);

private:
	void SetOnlineSession(USessionInformation* InSession);
};

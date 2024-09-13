// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineIntegrationState.h"
#include "OnlineIntegrationStatePrivate.generated.h"

/**
 * 
 */
UCLASS(Hidden)
class UOnlineIntegrationStatePrivate : public UOnlineIntegrationState
{
	GENERATED_BODY()
public:
	void RegisterBackend(UOnlineIntegrationBackend* InBackend);
	void RegisterSessionDefinition(USessionDefinition* InSessionDefinition);
	void SetFirstLocalUserInfo(ULocalUserInfo* LocalUserInfo);
	void SetPendingSessionMigrationSequence(USessionMigrationSequence* SessionMigrationSequence);

	UGameplayTagContainerViewModel& GetMutableTagContainer();
};

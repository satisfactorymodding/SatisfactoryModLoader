// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/OnlineSession.h"

#include "OnlineIntegrationSession.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEINTEGRATION_API UOnlineIntegrationSession : public UOnlineSession
{
	GENERATED_BODY()
protected:
	virtual void HandleDisconnect(UWorld* World, UNetDriver* NetDriver) override;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Async/Future.h"
#include "UObject/Interface.h"
#include "OnlineIntegrationSettings.h"
#include "OnlineIntegrationTypes.h"
#include "OnlineAuthenticationHandler.generated.h"


UINTERFACE()
class ONLINEINTEGRATION_API UOnlineAuthenticationHandler : public UInterface
{
	GENERATED_BODY()
};

class ONLINEINTEGRATION_API IOnlineAuthenticationHandler
{
	GENERATED_BODY()
	friend class UOnlineAuthenticationSequence;
protected:
	virtual void ConfigureOnlineIntegration(TPromise<FOnlineIntegrationPlatformSettings> &&Promise) = 0;
	virtual void QueryOnlineIntegrationModePreference(TPromise<EOnlineIntegrationMode> &&Promise) = 0;
	virtual void AuthenticationSequenceComplete() = 0;
	
	virtual void ProgressUpdate(const FText& Status);
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "OnlineIntegrationBackend.h"
#include "OnlineIntegrationBackendPrivate.generated.h"

/**
 * Private parts of an online integration backend for internal use only.
 */
UCLASS(MinimalAPI, Hidden)
class UOnlineIntegrationBackendPrivate : public UOnlineIntegrationBackend
{
	GENERATED_BODY()
public:
	/** Resets state, important to clear all shared ptrs */
	void Reset()
	{
		ServicesPtr.Reset();
		ConnectionStatus = EOnlineBackendConnectionStatus::NotConnected;
	}

	bool Initialize();
	
	void SetConnectionStatus(EOnlineBackendConnectionStatus InStatus);
protected:
	// Begin UObject interface
	virtual void OverridePerObjectConfigSection(FString& SectionName) override;
	// End UObject interface
};

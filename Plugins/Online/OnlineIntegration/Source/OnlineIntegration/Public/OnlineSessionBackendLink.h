// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Online/CoreOnline.h"

#include "OnlineSessionBackendLink.generated.h"

class USessionInformation;
class UOnlineIntegrationBackend;
/**
 *
 */
UCLASS(Abstract, NotBlueprintable)
class ONLINEINTEGRATION_API UOnlineSessionBackendLink : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	UE::Online::FOnlineSessionId GetSessionId() const
	{
		return SessionId;
	}

	UOnlineIntegrationBackend* GetOnlineBackend() const
	{
		return OnlineBackend;
	}

	USessionInformation* GetOnlineSession() const
	{
		return OnlineSession;
	}
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<UOnlineIntegrationBackend> OnlineBackend;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, FieldNotify)
	TObjectPtr<USessionInformation> OnlineSession;

	UE::Online::FOnlineSessionId SessionId;
};

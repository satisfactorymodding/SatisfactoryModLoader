// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGClientRequestBase.h"
#include "Networking/FGClientAPIManager.h"
#include "FGClientDebugRequester.generated.h"

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientDebugRequester : public UFGClientRequestBase
{
	GENERATED_BODY()
public:
	UFUNCTION( FGServerRequest, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	FFGPendingClientRequest Request_DebugReturnServerAPIError();
};

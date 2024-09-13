// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGServerControllerBase.h"
#include "Server/FGDSSharedTypes.h"
#include "FGServerDebugController.generated.h"

UCLASS()
class FACTORYDEDICATEDSERVER_API UFGServerDebugController : public UFGServerControllerBase
{
	GENERATED_BODY()
public:
	UFUNCTION( FGServerRequestHandler, FGServerRequestPrivilegeLevel = "NotAuthenticated" )
	static FFGServerErrorResponse Handler_DebugReturnServerAPIError();
};

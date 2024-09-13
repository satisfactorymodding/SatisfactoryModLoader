// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Networking/FGServerAPIManager.h"
#include "FGServerControllerBase.generated.h"

/**
 * Base class for Server Controllers, which host API entry points for managing the server state.
 */
UCLASS( Abstract )
class FACTORYDEDICATEDSERVER_API UFGServerControllerBase : public UObject
{
	GENERATED_BODY()
public:
	class UFGServerSubsystem* GetOwnerSubsystem() const;
};

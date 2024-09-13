// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FGClientAPIContext.generated.h"

class UFGClientAPIManager;

// This interface should be implemented on all objects willing to send Server API bound requests and receive responses
UINTERFACE()
class FACTORYDEDICATEDCLIENT_API UFGClientAPIContext : public UInterface
{
	GENERATED_BODY()
};

class FACTORYDEDICATEDCLIENT_API IFGClientAPIContext : public IInterface
{
	GENERATED_BODY()
public:
	// Returns the API manager that should be used for sending requests to the server API
	virtual UFGClientAPIManager* GetClientAPIManager() const;
};
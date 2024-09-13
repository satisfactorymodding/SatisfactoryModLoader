// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Networking/FGClientAPIContext.h"
#include "UObject/Object.h"
#include "FGClientRequestBase.generated.h"

UCLASS()
class FACTORYDEDICATEDCLIENT_API UFGClientRequestBase : public UObject, public IFGClientAPIContext
{
	GENERATED_BODY()
public:
	
	class UFGServerObject* GetServerObject() const;

	virtual UFGClientAPIManager* GetClientAPIManager() const override;

};

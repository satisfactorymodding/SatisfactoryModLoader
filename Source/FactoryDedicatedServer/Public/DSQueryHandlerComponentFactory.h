// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "HandlerComponentFactory.h"
#include "DSQueryHandlerComponentFactory.generated.h"

UCLASS()
class FACTORYDEDICATEDSERVER_API UDSQueryHandlerComponentFactory : public UHandlerComponentFactory
{
	GENERATED_BODY()

	virtual TSharedPtr<HandlerComponent> CreateComponentInstance(FString& Options) override;
};

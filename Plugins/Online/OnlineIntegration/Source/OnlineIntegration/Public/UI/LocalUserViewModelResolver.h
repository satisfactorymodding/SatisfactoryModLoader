// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelContextResolver.h"

#include "LocalUserViewModelResolver.generated.h"

/**
 * 
 */
UCLASS()
class ONLINEINTEGRATION_API ULocalUserViewModelResolver : public UMVVMViewModelContextResolver
{
	GENERATED_BODY()
protected:

	virtual UObject* CreateInstance(const UClass* ExpectedType, const UUserWidget* UserWidget, const UMVVMView* View) const override;
};

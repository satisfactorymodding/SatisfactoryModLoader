// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "FGMVVMViewModelBase.generated.h"

/**
 * Base class for MVVM viewmodel in FactoryGame. Supports widget notifications like destruct 
 */
UCLASS()
class FACTORYGAME_API UFGMVVMViewModelBase : public UMVVMViewModelBase
{
	GENERATED_BODY()
public:
	UFGMVVMViewModelBase(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintImplementableEvent)
	void OnDestruct();
};

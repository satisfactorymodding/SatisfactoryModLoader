// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GameplayTaskResource.h"
#include "FGGameplayResource_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGameplayTaskResource_Attack : public UGameplayTaskResource
{
	GENERATED_BODY()
	
#if !(UE_BUILD_SHIPPING || UE_BUILD_TEST)
		virtual FString GenerateDebugDescription() const override;
#endif // !(UE_BUILD_SHIPPING || UE_BUILD_TEST)	
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGAnimNotify.h"
#include "FGAnimNotify_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimNotify_Attack : public UFGAnimNotify
{
	GENERATED_BODY()
public:
	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	//~ End UAnimNotify interface
	
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Animation/AnimNotifies/AnimNotify.h"
#include "FGAnimNotify_Attack.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimNotify_Attack : public UAnimNotify
{
	GENERATED_BODY()
public:
	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) override;
	//~ End UAnimNotify interface
	
};

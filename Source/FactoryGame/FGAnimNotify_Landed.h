#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Animation/AnimNotifies/AnimNotify.h"
#include "FGAnimNotify_Landed.generated.h"

UCLASS()
class UFGAnimNotify_Landed : public UAnimNotify
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAnimNotify_Landed();

	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) override;
	//~ End UAnimNotify interface
};
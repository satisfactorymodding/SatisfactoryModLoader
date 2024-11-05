// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGAnimNotify.h"
#include "FGAnimNotify_FootDown.generated.h"

UCLASS()
class FACTORYGAME_API UFGAnimNotify_FootDown : public UFGAnimNotify
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAnimNotify_FootDown();

	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference ) override;
	//~ End UAnimNotify interface
protected:
	/** Foot */
	UPROPERTY( EditAnywhere, Category="Foot" )
	int32 mFootIndex;

	/** Should play a sound.  */
	UPROPERTY( EditAnywhere, Category = "Foot" )
	bool mPlaySound;
};
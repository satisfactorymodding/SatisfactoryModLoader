#pragma once
#include "UnrealString.h"
#include "UObject/Class.h"

#include "Animation/AnimNotifies/AnimNotify.h"
#include "FGAnimNotify_FootDown.generated.h"

UCLASS()
class UFGAnimNotify_FootDown : public UAnimNotify
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAnimNotify_FootDown();

	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) override;
	//~ End UAnimNotify interface
protected:
	/** Foot */
	UPROPERTY( EditAnywhere, Category="Foot" )
	int32 mFootIndex;

	/** Should play a sound.  */
	UPROPERTY( EditAnywhere, Category = "Foot" )
	bool mPlaySound;
};
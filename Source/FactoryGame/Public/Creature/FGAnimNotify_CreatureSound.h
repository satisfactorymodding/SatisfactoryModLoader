// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AkAudioEvent.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "FGAnimNotify_CreatureSound.generated.h"

class AFGCreature;

USTRUCT(BlueprintType)
struct FCreatureSound
{
	GENERATED_BODY()

	/** What class of creature is required for this sound to fire? */
	UPROPERTY(EditAnywhere)
	TSoftClassPtr<AFGCreature> CreatureClass;

	/** If checked, will check if the creature is a child of this class. Useful as an option as the last entry for "default" sounds. */
	UPROPERTY(EditAnywhere)
	bool OrChildOf = false;

	/** Audio event to play */
	UPROPERTY(EditAnywhere)
	UAkAudioEvent* AudioEvent;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAnimNotify_CreatureSound : public UAnimNotify
{
	GENERATED_BODY()

	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) final override;
	//~ End UAnimNotify interface

private:
	/** Array of creature sounds and classes association */
	UPROPERTY(EditAnywhere)
	TArray<FCreatureSound> mCreatureSounds;

	/** Should the audio event be attached to a bone or just spawned at the location of that bone at that frame. */
	UPROPERTY(EditAnywhere)
	bool bFollowBone;

	/** Bone or Socket name that we will use on the skeletal mesh to spawn the audio event. */
	UPROPERTY(EditAnywhere)
	FName mBoneName;
};

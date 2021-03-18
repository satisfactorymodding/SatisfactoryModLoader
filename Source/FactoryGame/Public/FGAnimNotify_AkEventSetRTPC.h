// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FGAnimNotify_AkEventSetRTPC.generated.h"

/**
 * Almost an identical copy of UAnimNotify_AkEvent but with added RTPC variables that can be used to set values between spawning/getting and post of AK event
 * Meant to work as a base class for different anim notifies with specific use cases for setting RTPC factory values
 */
UCLASS( abstract )
class FACTORYGAME_API UFGAnimNotify_AkEventSetRTPC : public UAnimNotify
{
	GENERATED_BODY()
public:
	UFGAnimNotify_AkEventSetRTPC();
	
	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	virtual void Notify( USkeletalMeshComponent* meshComp, UAnimSequenceBase* animation ) override;
	//~ End UAnimNotify interface

protected:
	/** Set the RTPC value on the relevant ak component. Can be overridden in derived classes if we want to use it for other things than current potential */
	virtual void SetRTPCValueOnAkComponent(  USkeletalMeshComponent* meshComp, class UAkComponent* component );

	protected:
	/** The RTPC object we want to set. RTPC Value Has priority over RTPC name */
	UPROPERTY( EditAnywhere, Category="Audio" )
	class UAkRtpc const* mRTPCValue;
	
	/** The name of the RTPC we want to set. RTPC Value Has priority over RTPC name */
	UPROPERTY( EditAnywhere, Category="Audio" )
	FString mRTPC;

	/** Duration during which the Game Parameter is interpolated towards Value (in ms) */
	UPROPERTY( EditAnywhere, Category="Audio" )
	int32 mInterpolationTimeMs;
	
	/** The socket or bone name we want to attach the event to */
	UPROPERTY( EditAnywhere, Category="Audio" )
	FName mSocketName;

	/** Event to post when this event is triggered */
	UPROPERTY( EditAnywhere, Category="Audio" )
	class UAkAudioEvent* mAudioEvent;

	/** If true, then we attach the event to the socket/actor, else it stays in the world where it was posted (true is more expensive) */
	UPROPERTY( EditAnywhere, Category="Audio" )
	bool mFollow;
	
};

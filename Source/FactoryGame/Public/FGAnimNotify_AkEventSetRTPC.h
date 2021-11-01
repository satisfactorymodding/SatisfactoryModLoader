// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "FGAnimNotify_AutoAkEvent.h"
#include "FGAnimNotify_AkEventSetRTPC.generated.h"

/**
 * Almost an identical copy of UAnimNotify_AkEvent but with added RTPC variables that can be used to set values between spawning/getting and post of AK event
 * Meant to work as a base class for different anim notifies with specific use cases for setting RTPC factory values
 */
UCLASS( abstract )
class FACTORYGAME_API UFGAnimNotify_AkEventSetRTPC : public UFGAnimNotify_AutoAkEvent
{
	GENERATED_BODY()
public:
	UFGAnimNotify_AkEventSetRTPC();
	
	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	//~ End UAnimNotify interface

protected:
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
};

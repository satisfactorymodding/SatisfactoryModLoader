// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAnimNotify_AkEventSetRTPC.h"
#include "FGAnimNotify_AkEventCurrentPotential.generated.h"

/**
 * Similar to UAnimNotify_AkEvent but sets RTPC variables based on current potential of the factory building
 */
UCLASS( meta = ( DisplayName = "Post Ak Event Current Potential" ) )
class FACTORYGAME_API UFGAnimNotify_AkEventCurrentPotential : public UFGAnimNotify_AkEventSetRTPC
{
	GENERATED_BODY()
public:
	//~ Begin UAnimNotify interface
	virtual FString GetNotifyName_Implementation() const override;
	//~ End UAnimNotify interface

protected:
	/** Set the RTPC value on the relevant ak component. Empty implementation in base class */
	virtual void SetRTPCValueOnAkComponent(  USkeletalMeshComponent* meshComp, class UAkComponent* component ) override;

};

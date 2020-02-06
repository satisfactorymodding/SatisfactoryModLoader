// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGRadioactiveActor.generated.h"


/**
 * An actor that is radioactive.
 */
UCLASS( Blueprintable )
class FACTORYGAME_API AFGRadioactiveActor : public AActor
{
	GENERATED_BODY()
public:	
	AFGRadioactiveActor();

protected:
	virtual void BeginPlay() override;

private:
	/**
	 * How much radiation this item gives out in the number of nucleus that decays per second.
	 * 0 means no radiation and 1 is 10^15 (1 quadrillion) decays/s.
	 * Good values are in the range 0 to 1.
	 */
	UPROPERTY( EditInstanceOnly, Category = "Radioactivity" )
	float mRadioactiveDecay;
};

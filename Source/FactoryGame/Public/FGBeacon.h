// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Replication/FGStaticReplicatedActor.h"
#include "FGBeacon.generated.h"

UCLASS()
class FACTORYGAME_API AFGBeacon : public AFGStaticReplicatedActor
{
	GENERATED_BODY()
public:
	AFGBeacon();

	/** Pickup the beacon by the provided player */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Beacon" )
	void PickUpBeacon( class AFGCharacterPlayer* player );
	
};

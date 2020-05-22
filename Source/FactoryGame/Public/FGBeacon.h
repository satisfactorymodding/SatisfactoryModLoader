// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGBeacon.generated.h"

UCLASS()
class FACTORYGAME_API AFGBeacon : public AActor
{
	GENERATED_BODY()
public:
	AFGBeacon();

	/** Pickup the beacon by the provided player */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category = "Beacon" )
	void PickUpBeacon( class AFGCharacterPlayer* player );
	

public:
	FORCEINLINE ~AFGBeacon() = default;
};

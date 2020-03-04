// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
#include "FGDowsingStick.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGDowsingStick : public AFGEquipment
{
	GENERATED_BODY()
public:
	AFGDowsingStick();


	virtual void Tick( float DeltaSeconds ) override;

	/** Location of closest water volume */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Dowsing" )
	FORCEINLINE FVector GetWaterLocation() { return mClosestWaterLocation; }
private:
	/** How many water volumes to check distance to per frame */
	UPROPERTY( EditDefaultsOnly, Category = "FactoryGame|Dowsing" )
	int32 mNumVolumesPerTick;

	UPROPERTY()
	TArray< AActor* > mWaterVolumes;

	FVector mClosestWaterLocation;

	int32 mCounter;

	int32 mClosestVolumeIndex;
	float mClosestDistanceSq;

public:
	FORCEINLINE ~AFGDowsingStick() = default;
};

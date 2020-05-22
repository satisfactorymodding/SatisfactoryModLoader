// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGTrainPlatformHologram.h"
#include "FGFactoryBuildingHologram.h"
#include "FGTrainStationHologram.generated.h"


UCLASS()
class FACTORYGAME_API AFGTrainStationHologram : public AFGTrainPlatformHologram
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	
	// Begin AFGHologram interface
	virtual void CheckValidPlacement() override;
	virtual void SpawnChildren( AActor* hologramOwner, FVector spawnLocation, APawn* hologramInstigator ) override;
	virtual AActor* Construct( TArray< AActor* >& out_children, FNetConstructionID netConstructionID ) override;
	// End AFGHologram interface

protected:
	// Begin AFGHologram interface
	virtual USceneComponent* SetupComponent( USceneComponent* attachParent, UActorComponent* componentTemplate, const FName& componentName ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	// End AFGHologram interface

public:
	FORCEINLINE ~AFGTrainStationHologram() = default;
};

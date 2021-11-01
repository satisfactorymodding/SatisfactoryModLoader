// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGDroneVehicle.h"
#include "FGDroneTransport.generated.h"

// TODO: Reparent blueprint class to AFGBuildableDrone and remove this class
UCLASS()
class FACTORYGAME_API AFGDroneTransport : public AFGDroneVehicle
{
	GENERATED_BODY()

	// Begin IFGActorRepresentationInterface
	virtual FRotator GetRealActorRotation() override;
	virtual ERepresentationType GetActorRepresentationType() override;
	virtual EFogOfWarRevealType GetActorFogOfWarRevealType() override;
	// End IFGActorRepresentationInterface

};

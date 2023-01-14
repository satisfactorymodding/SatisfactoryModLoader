// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FGFlyingBabyCrab.generated.h"

UCLASS()
class FACTORYGAME_API AFGFlyingBabyCrab : public AActor
{
	GENERATED_BODY()
	
public:	
	AFGFlyingBabyCrab();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;

	virtual void PostNetReceiveLocationAndRotation() override;

	UFUNCTION()
	void OnClientSubsystemsValid();
};

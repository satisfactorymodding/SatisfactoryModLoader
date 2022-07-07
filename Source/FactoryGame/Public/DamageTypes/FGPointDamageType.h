// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "DamageTypes/FGDamageType.h"
#include "Engine/EngineTypes.h"

#include "FGPointDamageType.generated.h"

/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGPointDamageType : public UFGDamageType
{
	GENERATED_BODY()

public:
	virtual void ProcessDamage( const FHitResult& hitResult, AController* instigator, AActor* damageCauser, float damageAmount, TArray<AActor*> ignoredActors ) override;
};

// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGDamageType.h"
#include "Engine/EngineTypes.h"
#include "GameFramework/Actor.h"

#include "FGPointDamageType.generated.h"

class URadialIntMask;
class UUniformVector;
class UCullingField;
class UPhysicsFieldComponent;

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

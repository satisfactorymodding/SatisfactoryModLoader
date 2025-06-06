// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGDamageType.h"
#include "FGFoliageRemovalSubsystem.h"
#include "Engine/EngineTypes.h"

#include "FGRadialDamageType.generated.h"

class UHierarchicalInstancedStaticMeshComponent;
/**
 *
 */
UCLASS()
class FACTORYGAME_API UFGRadialDamageType : public UFGDamageType
{
	GENERATED_BODY()
public:
	virtual void ProcessDamage( const struct FHitResult& hitResult, AController* instigator, AActor* damageCauser, float damageAmount, TArray<AActor*> ignoredActors ) override;

	/** radius in which the damage of this type will be dealt */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType" )
	float mDamageRadius = 100;

	/** Should this damage remove foliage when applied? */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "DamageType" )
	bool mShouldRemoveFoliage = false;

	/** Falloff for the damage impulse. Based on the Damage Radius */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "RigidBody" )
	float mDamageImpulseFalloff = 1.0f;

	/** Falloff for the destructible impulse. Based on the Damage Radius */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Destruction" )
	float mDestructibleImpulseFalloff = 1.0f;

	/* Default "trunk" search radius for foliage. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Destruction" )
	FBoxSphereBounds mDestructionDefaultRadius = FBoxSphereBounds(FVector(0), FVector(50,50,50),50.f);
	
	/* Minimum "trunk" search radius for foliage. */
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category = "Destruction" )
	float mDestructionMinimumRadius = 25;
};

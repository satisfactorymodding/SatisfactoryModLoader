// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAmmoTypeInstantHit.h"
#include "FGAmmoTypeLaser.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeLaser : public UFGAmmoTypeInstantHit
{
	GENERATED_BODY()

public:
	UFGAmmoTypeLaser();

	virtual float GetTotalHitDamageAmount_Implementation( const FHitResult& hitResult, const UFGDamageType* damageType ) override;

protected:

	/** Adds an extra % of damage on top of the normal amount based on the current charge of the laser. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Laser" )
	float mBonusChargeDamagePercentage;
};

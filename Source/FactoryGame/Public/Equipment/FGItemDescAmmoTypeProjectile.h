// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"

#include "FGProjectile.h"
#include "Equipment/FGItemDescAmmoType.h"
#include "FGItemDescAmmoTypeProjectile.generated.h"

/**
 * Ammo type that spawns a projectile when fired. (i.e Rebar gun)
 */
UCLASS()
class FACTORYGAME_API UFGItemDescAmmoTypeProjectile : public UFGItemDescAmmoType
{
	GENERATED_BODY()

public:
	virtual void FireAmmunition_Implementation() override;

	/** apply config on projectile */
	void GetProjectileData( FProjectileData& out_data );

protected:
	/** Spawns the projectile*/
	void ProjectileFire();

private:
	/** weapon config */
	UPROPERTY( EditDefaultsOnly, Category = "Weapon" )
	FProjectileData mProjectileData;
};

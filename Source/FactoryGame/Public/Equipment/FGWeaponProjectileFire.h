// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGWeapon.h"
#include "../DamageTypes/FGDamageType.h"
#include "FGWeaponProjectileFire.generated.h"

USTRUCT()
struct FACTORYGAME_API FProjectileData
{
	GENERATED_USTRUCT_BODY()

	/** projectile class */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	TSubclassOf< class AFGProjectile > ProjectileClass;

	/** life time */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	float ProjectileLifeSpan;

	/** How long the projectile will live after it has gotten stuck to something */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	float ProjectileStickSpan;

	/** damage at impact point */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	int32 ExplosionDamage;

	/** radius of damage */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	float ExplosionRadius;

	/** Damage dealt to actor that get hit or impacted by this projectile */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	int32 ImpactDamage;

	/** If we impact something, should this projectile explode so that it deals radius damage? */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	bool ShouldExplodeOnImpact;

	/** Indicates if we should explode if we are taking damage from same actor class as ourselves */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	bool CanTriggerExplodeBySameClass;

	/** Should the projectile explode when it dies of lifespan? */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	bool ExplodeAtEndOfLife;

	/** type of damage used for impact damage*/
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	TSubclassOf< UFGDamageType > DamageType;

	/** type of damage used for detonation */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	TSubclassOf< UFGDamageType > DamageTypeExplode;

	/** defaults */
	FProjectileData()
	{
		ProjectileClass = NULL;
		ProjectileLifeSpan = 10.0f;
		ProjectileStickSpan = 5.0f;
		ExplosionDamage = 100;
		ExplosionRadius = 300.0f;
		ImpactDamage = 0.0f;
		ShouldExplodeOnImpact = true;
		CanTriggerExplodeBySameClass = true;
		ExplodeAtEndOfLife = false;
		DamageType = UFGDamageType::StaticClass();
		DamageTypeExplode = UFGDamageType::StaticClass();
	}

public:
	FORCEINLINE ~FProjectileData() = default;
};

/**
 * Weapon that fires client side projectiles.
 */
UCLASS()
class FACTORYGAME_API AFGWeaponProjectileFire : public AFGWeapon
{
	GENERATED_BODY()
	
public:

	AFGWeaponProjectileFire();

	virtual void FireAmmunition_Implementation() override;

	/** apply config on projectile */
	void GetProjectileData( FProjectileData& out_data );
protected:
	/** Spawns the projectile*/
	void ProjectileFire( const FVector& shootDir, const FVector& origin );

protected:
	/** weapon config */
	UPROPERTY( EditDefaultsOnly, Category = "Weapon" )
	FProjectileData mProjectileData;

public:
	FORCEINLINE ~AFGWeaponProjectileFire() = default;
};

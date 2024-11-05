// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "FGAmmoTypeHomingBase.h"
#include "FGProjectile.h"
#include "FGAmmoTypeProjectile.generated.h"

/**
 * Ammo type that spawns a projectile when fired. (i.e Rebar gun)
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeProjectile : public UFGAmmoTypeHomingBase
{
	GENERATED_BODY()

public:
	UFGAmmoTypeProjectile();
	virtual void FireAmmunition_Implementation() override;

	/** apply config on projectile */
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Ammunition")
	void SetupProjectile(AFGProjectile* projectile);

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE TArray<UFGDamageType*> GetDamageTypesEndOfLife() const { return mDamageTypesAtEndOfLife; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE TSubclassOf<AFGProjectile> GetProjectileClass() const { return mProjectileClass; }

	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetInitialSpeedOverride() const { return mInitialProjectileSpeedOverride; }
	
protected:
	/** Spawns the projectile*/
	void ProjectileFire();

	/** Class of the projectile this magazine will spawn upon firing */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile")
	TSubclassOf<AFGProjectile> mProjectileClass = nullptr;

	/** Overrides the initial speed of the projectile. <0 uses default projectile values. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile" )
	float mInitialProjectileSpeedOverride = -1.0f;

	/** Overrides the projectile maximum speed. <0 uses default projectile values. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile" )
	float mProjectileMaxSpeedOverride = -1.0f;

	/** Overrides the projectile's health. <0 uses default projectile values. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile" )
	float mProjectileHealthOverride = -1.0f;

	/** Projectile's lifespan before it self destructs if not hitting anything. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile")
	float mProjectileLifespan = 10.0f;

	/** Time the projectile will stick to something before ending its life. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile")
	float mProjectileStickspan = 5.0f;

	/** Can this projectile take damage from the same class or any of its child classes. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|Projectile")
	bool mCanTakeDamageBySameProjectileOrChild = true;

	/** Types and values of damages dealt at the end of life of the projectile. Includes FX setup. */
	UPROPERTY( SaveGame, EditDefaultsOnly, Instanced, Category = "Ammunition|Damage" )
	TArray< UFGDamageType* > mDamageTypesAtEndOfLife;

	/** Types and values of damages dealt upon projectile impact. Includes FX setup. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	FRuntimeFloatCurve mGravityScaleOverLifespan;

	/** Should this projectile be homing? */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	bool mHomingProjectile = false;

	/** Whether or not the homing functionality needs a valid target. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	bool mHomingNeedsValidTarget = false;

	/** Maximum homing acceleration. higher values = stronger homing. Max speed of the projectile is not affected by this value. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	float mMaxHomingAccelerationMagnitudeOverride = -1.0f;

	/** 0-1 on x/y curve to drive the homing strength over the projectile's lifespan. Multiplied to the max homing acceleration magniture and magnitude over distance at runtime.
	 * An empty curve will return a constant value of 1. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	FRuntimeFloatCurve mHomingMagnitudeMultiplierOverLifespan;

	/** 0-1 on x/y curve to drive the homing strength over the projectile's distance to its target. Multiplied to the max homing acceleration magniture and magnitude over lifespan at runtime.
	 * An empty curve will return a constant value of 1. */
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition|Projectile" )
	FRuntimeFloatCurve mHomingMagnitudeMultiplierOverDistanceToTarget;
};

// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Equipment/FGItemDescAmmoType.h"
#include "FGItemDescAmmoTypeInstantHit.generated.h"

/**
 * Ammo type for weapons requiring instant-hit/trace type of behavior (i.e rifle)
 */
UCLASS()
class FACTORYGAME_API UFGItemDescAmmoTypeInstantHit : public UFGItemDescAmmoType
{
	GENERATED_BODY()

public:
	virtual void FireAmmunition_Implementation() override;

	/** Returns the VFX played at the impact point */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE UParticleSystem* GetImpactVFX() const { return mHitImpactVFX; }

	/** Returns the damage of the ammo type */
	UFUNCTION( BlueprintPure, Category="Ammunition" )
	FORCEINLINE float GetHitDamage() const { return mHitDamage; }

protected:
	/** Does the trace and hit */
	void InstantFire();

	/** Preforms the trace to find what we hit */
	void CalcWeaponFire( FVector startTrace, FVector endTrace, FHitResult& out_hitResult ) const;

	/** Calls take damage on hit actor */
	virtual void ProcessInstantHit( const FHitResult& hitResult );

	/** server notified of hit from client to verify */
	UFUNCTION( Reliable, Server )
	void Server_NotifyHit( const FHitResult& hitResult );

	/** server notified of miss to show trail FX */
	UFUNCTION( Unreliable, Server )
	void Server_NotifyMiss();

	/** continue processing the instant hit, as if it has been confirmed by the server */
	virtual void ProcessInstantHit_Confirmed( const FHitResult& hitResult );

	/** check if weapon should deal damage to actor */
	bool ShouldDealDamage( AActor* testActor ) const;

	/** handle damage */
	void DealDamage( const FHitResult& hitResult );

	/** Plays the impact effect at the impact location */
	void PlayImpactEffect( const FHitResult& hitResult );

private:
	/** Damage dealt per ammunition */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition" )
	float mHitDamage = 10.0f;

	/** VFX played upon ammunition impact */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition" )
	UParticleSystem* mHitImpactVFX = nullptr;
};

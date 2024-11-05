// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGAmmoType.h"
#include "FGAmmoTypeInstantHit.generated.h"

/**
 * Ammo type for weapons requiring instant-hit/trace type of behavior (i.e rifle)
 */
UCLASS()
class FACTORYGAME_API UFGAmmoTypeInstantHit : public UFGAmmoType
{
	GENERATED_BODY()

public:
	UFGAmmoTypeInstantHit();
	
	virtual void FireAmmunition_Implementation() override;

protected:
	/** Does the trace and hit */
	void InstantFire();

	/** Preforms the trace to find what we hit */
	void CalcWeaponFire( FVector startTrace, FVector endTrace, FHitResult& out_hitResult ) const;

	/** Called on server to process the hit when fired. */
	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|InstantHit")
	void ProcessHit( const FHitResult& hitResult );

	/** Called on server to process the hit when fired. */
	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|InstantHit")
	float GetTotalHitDamageAmount( const FHitResult& hitResult, const class UFGDamageType* damageType );

	/** Called on all clients. */
	UFUNCTION( NetMulticast, Unreliable )
	void NetMulticast_PlayEffects( const FHitResult& hitResult );

	/** Called on both server and client whenever we hit something. */
	UFUNCTION( BlueprintNativeEvent, Category = "Ammunition|InstantHit" )
	void PlayEffects( const FHitResult& hitResult );

	/** handle damage */
	void DealDamage( const FHitResult& hitResult );

protected:
	/** Whether or not to play fire effects on the weapon when firing a shot. */
	UPROPERTY( EditDefaultsOnly, Category = "Ammunition|InstantHit" )
	bool mPlayFireEffects;

	/** The noise to make at the location we hit. */
    UPROPERTY( EditDefaultsOnly, Category = "Ammunition|InstantHit" )
    TSubclassOf< class UFGNoise > mHitNoise;
};

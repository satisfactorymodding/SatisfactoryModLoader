// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "FGWeapon.h"
#include "FGWeaponInstantFire.generated.h"

UCLASS()
class FACTORYGAME_API AFGWeaponInstantFire : public AFGWeapon
{
	GENERATED_BODY()

public:
	/**ctor*/
	AFGWeaponInstantFire();
	
	virtual void FireAmmunition_Implementation() override;

protected:
	/** Does the trace and hit */
	void InstantFire();

	/** Preforms the trace to find what we hit */
	void CalcWeaponFire( FVector startTrace, FVector endTrace, FHitResult& out_hitResult );

	/** Calls take damage on hit actor */
	virtual void ProcessInstantHit( const FHitResult& hitResult );

	/** server notified of hit from client to verify */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_NotifyHit( const FHitResult& hitResult );

	/** server notified of miss to show trail FX */
	UFUNCTION( Unreliable, Server, WithValidation )
	void Server_NotifyMiss( );

	/** continue processing the instant hit, as if it has been confirmed by the server */
	virtual void ProcessInstantHit_Confirmed( const FHitResult& hitResult );

	/** check if weapon should deal damage to actor */
	bool ShouldDealDamage( AActor* testActor ) const;

	/** handle damage */
	void DealDamage( const FHitResult& hitResult );

	/** Plays the impact effect at the impact location */
	void PlayImpactEffect( const FHitResult& hitResult );

public:
	/** Instant hit damage */
	UPROPERTY( EditDefaultsOnly )
	float mInstantHitDamage;

	/** How far we should trace for the weapon*/
	UPROPERTY( EditDefaultsOnly )
	float mWeaponTraceLength;

	/** The particle to use when hitting the ground */
	UPROPERTY( EditDefaultsOnly )
	class UParticleSystem* mHitParticleEffect;
};
// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "FactoryGame.h"
#include "DamageTypes/FGDamageType.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "FGProjectile.generated.h"

/** Projectile data used to initialize new projectiles */
USTRUCT()
struct FProjectileData
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

	UPROPERTY( SaveGame )
	FRuntimeFloatCurve DamageFalloffCurve;

	UPROPERTY( SaveGame )
	float EffectiveRange;

	UPROPERTY( SaveGame )
	float WeaponDamageMultiplier;

	/** defaults */
	FProjectileData()
	{
		ProjectileClass = nullptr;
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
		EffectiveRange = 0;
		WeaponDamageMultiplier = 1.0f;
	}
};

UCLASS( config=Game )
class FACTORYGAME_API AFGProjectile : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGProjectile();

	virtual void Tick( float DeltaSeconds ) override;

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** initial setup */
	virtual void PostInitializeComponents() override;

	//** Save Game Interface. Default is to not save, but the save interface is implemented here to allow for enabling in children (eg. FGNobeliskExplosive) */
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	//** End Save Game Interface */

	// Start AActor interface
	virtual float TakeDamage( float DamageAmount, const struct FDamageEvent& DamageEvent, class AController* EventInstigator,
							AActor* DamageCauser ) override;

	/** Called when the lifespan of an actor expires (if he has one). */
	virtual void LifeSpanExpired() override;
	// End AActor interface

	/** handle hit */
	UFUNCTION()
	virtual void OnImpact( const FHitResult& hitResult );

	/** handle bounce */
	UFUNCTION()
	virtual void OnBounce( const FHitResult& hitResult, const FVector& hitVelocity );

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return mCollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return mProjectileMovement; }

	/** Returns the location we are aiming for ( if any ) */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	FORCEINLINE FVector GetProjectileTargetLocation() { return mTargetLocation; }

	/** Returns the location we are aiming for ( if any ) */
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetTargetLocation( FVector targetLocation ) { mTargetLocation = targetLocation; }

	/** Function to set up explosion effects in Blueprint */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayExplosionEffects();

	/** Function to set the internal data of the projectile before finishing spawning it */
	void SetProjectileData( FProjectileData projectileData );

	/** Called when we attach this actor to something like the world, a factory, a character */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayAttachEffect();

	/** Returns the collision sphere */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	FORCEINLINE USphereComponent* GetCollisionSphere() { return mCollisionComp; }

	/** Sets the initial velocity so that it can be replicated to clients */
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetInitialVelocity( FVector inVelocity );

	/** To trigger the secondary action of the projectile (i.e explosion on Sticky Projectiles) */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	virtual void TriggerSecondary();

	/** To trigger the secondary */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	virtual void TriggerSecondaryWithDelay( float delayTime );

	/** Assigns the rotation rate to rotating movement component, scaling the mThrowRotation by the scale parameter */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	void SetAndEnableRotation( float scale );

protected:
	/** trigger explosion */
	virtual void DealExplosionDamage( const FHitResult& impact );

	/** Deal damage from the impact */
	virtual void DealImpactDamage( const FHitResult& impact );

	/** shutdown projectile and prepare for destruction */
	void DisableAndSetLifeSpan();

	/** [client] explosion happened */
	UFUNCTION()
	void OnRep_Exploded();

	/** Virtual function for any additional client side effect handling in child classes*/
	virtual void OnNotifiedExploded();

	/** attach this projectile to an enemy or alike */
	bool AttachProjectileToImpactActor( const FHitResult& impact );

	UFUNCTION()
	void OnRep_InitialVelocity();
public:
	/** This projectile is just used for cosmetics and shouldn't deal damage. Like on remote clients */
	bool mIsCosmeticProjectile;
protected:
	/** Rotating component for projectiles that need rotation when thrown */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	class URotatingMovementComponent* mRotatingMovementComp;

	/** Initial rotation to apply to the projectile at launch */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	FRotator mThrowRotation;

	/** projectile data */
	UPROPERTY( SaveGame, EditDefaultsOnly, Replicated, Category = "Projectile" )
	FProjectileData mProjectileData;

	/** did it explode? */
	UPROPERTY( Transient, ReplicatedUsing = OnRep_Exploded )
	bool mHasExploded;

	/** Used to get the velocity over to clients */
	UPROPERTY( ReplicatedUsing = OnRep_InitialVelocity )
	FVector mInitialVelocity;

	/** Distance traveled by the projectile since spawn. */
	UPROPERTY( SaveGame )
	float mTraveledDistance;

	UPROPERTY( SaveGame )
	FTimerHandle mSecondaryTriggerDelayTimer;
private:
	/** Sphere collision component */
	UPROPERTY( VisibleDefaultsOnly, Category = "Projectile" )
	class USphereComponent* mCollisionComp;

	/** Projectile movement component */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true") )
	class UProjectileMovementComponent* mProjectileMovement;

	/** Location we are aiming at ( if any ) */
	UPROPERTY( Replicated )
	FVector mTargetLocation;

	/** Indicates if we should explode if we are taking damage from same actor class as ourselves */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	bool mCanTriggerExplodeBySameClass;

	/** Should the projectile explode when it dies of lifespan? */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	bool mExplodeAtEndOfLife;

	/** Caching the PC so that we can do damage even without a valid weapon */
	UPROPERTY()
	class AFGPlayerController* mCachedPC;

	/** Was projectile fired by a weapon */
	bool mWasFiredByWeapon;
};

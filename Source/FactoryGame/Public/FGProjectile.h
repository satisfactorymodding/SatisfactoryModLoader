// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Array.h"
#include "UObject/Class.h"
#include "GameFramework/Actor.h"
#include "Equipment/FGWeaponProjectileFire.h"
#include "FGProjectile.generated.h"

UCLASS(config=Game)
class FACTORYGAME_API AFGProjectile : public AActor, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGProjectile();

	/** Decide on what properties to replicate */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	/** initial setup */
	virtual void PostInitializeComponents() override;

	//** Save Game Interface. Default is to not save, but the save interface is implemented here to allow for enabling in children (eg. FGNobeliskExplosive) */
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	//** End Save Game Interface */

	// Start AActor interface
	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser );

	/** Called when the lifespan of an actor expires (if he has one). */
	virtual void LifeSpanExpired();
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
	UFUNCTION( BlueprintImplementableEvent, BlueprintCosmetic, Category = "Projectile" )
	void PlayExplosionEffects();

	void SetProjectileData( FProjectileData projectileData );

	/** Called when we attach this actor to something like the world, a factory, a character */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayAttachEffect();

	/** Returns the collision sphere */
	UFUNCTION( BlueprintPure, Category = "Projectile" ) 
	FORCEINLINE USphereComponent* GetCollisionSphere(){ return mCollisionComp; }

	/** Sets the initial velocity so that it can be replicated to clients */
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetInitialVelocity( FVector inVelocity );

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

	/** projectile data */
	UPROPERTY( SaveGame, EditDefaultsOnly, Category = "Projectile" )
	FProjectileData mProjectileData;

	/** did it explode? */
	UPROPERTY( Transient, ReplicatedUsing = OnRep_Exploded )
	bool mHasExploded;

	/** Used to get the velocity over to clients */
	UPROPERTY( ReplicatedUsing = OnRep_InitialVelocity )
	FVector mInitialVelocity;
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

public:
	FORCEINLINE ~AFGProjectile() = default;
};
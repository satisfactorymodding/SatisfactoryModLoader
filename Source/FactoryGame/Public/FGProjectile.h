// Copyright 2016-2021 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Curves/CurveFloat.h"
#include "DamageTypes/FGDamageType.h"
#include "FGSaveInterface.h"
#include "GameFramework/Actor.h"
#include "FGProjectile.generated.h"

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

	virtual void PostNetReceiveLocationAndRotation() override;

	//** Save Game Interface. Default is to not save, but the save interface is implemented here to allow for enabling in children (eg. FGNobeliskExplosive) */
	virtual bool ShouldSave_Implementation() const override;
	virtual bool NeedTransform_Implementation() override;
	virtual void PostLoadGame_Implementation(int32 saveVersion, int32 gameVersion) override;
	//** End Save Game Interface */

	// Start AActor interface
	virtual float TakeDamage( float DamageAmount, const struct FDamageEvent& DamageEvent, class AController* EventInstigator,
							AActor* DamageCauser ) override;

	/** Called when the lifespan of an actor expires (if he has one). */
	virtual void LifeSpanExpired() override;
	// End AActor interface

	/** handle hit */
	UFUNCTION()
	virtual void OnImpact_Native( const FHitResult& hitResult );

	/** Called to handle impact on all clients when an impact happens on the server. */
	UFUNCTION( NetMulticast, Reliable )
	virtual void Multicast_OnImpact( const FHitResult& hitResult, bool wasAttached );

	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void OnImpact( const FHitResult& hitResult );

	/** handle bounce */
	UFUNCTION()
	virtual void OnBounce_Native( const FHitResult& hitResult, const FVector& hitVelocity );
	
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void OnBounce( const FHitResult& hitResult, const FVector& hitVelocity );

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return mCollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UFGProjectileMovementComponent* GetProjectileMovement() const { return mProjectileMovement; }

	/** Returns the location we are aiming for ( if any ) */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	const FVector& GetProjectileTargetLocation() const { return mTargetLocation; }

	/** Whether or not this projectile can be hit by homing ammo. */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	FORCEINLINE bool CanBeHitByHomingAmmo() const { return mCanBeHitByHomingAmmo; }

	/** Gets the initial throw rotation velocity. */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	const FRotator& GetThrowRotation() const { return mThrowRotation; }

	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetSourceAmmoDescriptor( class UFGAmmoTypeProjectile* ammoDescriptor );
	
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetImpactDamageTypes( TArray<UFGDamageType*> impactDamageTypes ) { mDamageTypesOnImpact = impactDamageTypes; }

    UFUNCTION( BlueprintCallable, Category = "Projectile" )    
    void SetEndOfLifeDamageTypes( TArray<UFGDamageType*> endOfLifeDamageTypes) { mDamageTypesAtEndOfLife = endOfLifeDamageTypes; }

	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetCurveGravityScaleOverLifespan(const FRuntimeFloatCurve& newCurve) { mGravityScaleOverLifespan = newCurve; }

	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetCurveHomingStrengthOverLifespan(const FRuntimeFloatCurve& newCurve) { mHomingStrengthOverLifespan = newCurve; }

	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetCurveHomingStrengthOverDistanceToTarget(const FRuntimeFloatCurve& newCurve) { mHomingStrengthOverDistanceToTarget = newCurve; }
	
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetTargetLocation( const FVector& targetLocation );

	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetTargetActor( AActor* actor );
	
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetIsHomingProjectile( bool isHoming );

	/** Function to set up explosion effects in Blueprint */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayExplosionEffects();

	/** Called when we attach this actor to something like the world, a factory, a character */
	UFUNCTION( BlueprintImplementableEvent, Category = "Projectile" )
	void PlayAttachEffect();

	/** Returns the collision sphere */
	UFUNCTION( BlueprintPure, Category = "Projectile" )
	FORCEINLINE USphereComponent* GetCollisionSphere() { return mCollisionComp; }

	/** Sets the initial velocity so that it can be replicated to clients */
	UFUNCTION( BlueprintCallable, Category = "Projectile" )
	void SetInitialVelocity( const FVector& inVelocity );

	/** To trigger the secondary action of the projectile (i.e explosion on Sticky Projectiles) */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	virtual void TriggerSecondary();

	/** To trigger the secondary */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	virtual void TriggerSecondaryWithDelay( float delayTime );

	/** Assigns the rotation rate to rotating movement component, scaling the mThrowRotation by the scale parameter */
	UFUNCTION( BlueprintCallable, Category="Projectile" )
	void SetAndEnableRotation( float scale );

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnImpactDamageEffects( FHitResult const& hitResult );

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_SpawnEndOfLifeDamageEffects( FHitResult const& hitResult );

	UFUNCTION(BlueprintCallable, Category = "Projectile" )
	void SetInitialHealth(float newHealth);

	UFUNCTION(BlueprintCallable, Category = "Projectile" )
	void SetMaximumHomingAccelerationMagnitude(float newHomingAccelerationMagnitude);

	UFUNCTION(BlueprintNativeEvent, Category="Projectile")
	void OnSpawnedAsClusterProjectile();

protected:
	/** trigger explosion */
	virtual void DealEndOfLifeDamages( const FHitResult& impact );

	/** Deal damage from the impact */
	virtual void DealImpactDamages( const FHitResult& impact );

	/** shutdown projectile and prepare for destruction */
	void DisableAndSetLifeSpan();

	/** Called when lifespan of the projectile expires. */
	UFUNCTION()
	void OnRep_Exploded();

	/** Called on both server and client when the lifespan of the projectile expires. */
	UFUNCTION( BlueprintNativeEvent, Category = "Projectile" )
	void OnExplode();

	/** attach this projectile to an enemy or alike */
	bool AttachProjectileToImpactActor( const FHitResult& impact );

	UFUNCTION()
	void OnRep_InitialVelocity();

	UFUNCTION()
	void OnRep_TargetActor();

	UFUNCTION()
	void OnRep_TargetLocation();

	UFUNCTION()
	void OnRep_IsHomingProjectile();

	UFUNCTION()
	void OnRep_MaxHomingAccelerationMagnitude();
	
public:
	/** Indicates if we should explode if we are taking damage from same actor class as ourselves */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	bool mCanTriggerExplodeBySameClass;

	/** Time the projectile can live before actually being destroyed if not hitting anything */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Projectile" )
	float mProjectileLifespan;

	/** Time the projectile sticks to target before going poof. */
	UPROPERTY( EditDefaultsOnly, Replicated, Category = "Projectile" )
	float mProjectileStickspan;

	UPROPERTY( SaveGame, EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	FLinearColor mProjectileColor;

	UPROPERTY( SaveGame, EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	float mProjectileScale;
	
protected:
	/** Whether or not this projectile can be hit by homing ammo. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	bool mCanBeHitByHomingAmmo;
	
	/** Rotating component for projectiles that need rotation when thrown */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	class URotatingMovementComponent* mRotatingMovementComp;

	/** What class to use for spawning cluster projectiles. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Cluster" )
	TSubclassOf< AFGProjectile > mClusterProjectileClass;

	/** How many cluster projectiles to spawn. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Cluster" )
	FInt32Interval mNumClusterProjectiles;

	/** Cluster projectiles are spread out in a clockwise pattern, using this value as the step between each one. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Cluster" )
	FFloatInterval mClusterProjectileSpreadIntervalAngle;

	/** How fast the cluster projectiles should go sideways when launched. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Cluster" )
	FFloatInterval mClusterProjectileSidewaysLaunchSpeed;
	
	/** How fast the cluster projectiles should go vertically when launched. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Cluster" )
	FFloatInterval mClusterProjectileVerticalLaunchSpeed;

	/** Custom up vector for the clustering to happen around. Default is FVector::UpVector */
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite, Category = "Projectile|Cluster" )
	FVector mClusterUpVector;

	/** Initial rotation to apply to the projectile at launch */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile" )
	FRotator mThrowRotation;
	
	/** The target of the projectile. */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing = OnRep_TargetActor, Category = "Projectile" )
	AActor* mTargetActor;
	
	/** Location we are aiming at ( if any ) */
	UPROPERTY( BlueprintReadOnly, ReplicatedUsing = OnRep_TargetLocation, Category = "Projectile" )
	FVector mTargetLocation;

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, ReplicatedUsing = OnRep_IsHomingProjectile, Category = "Projectile" )
	bool mIsHomingProjectile;

	UPROPERTY( BlueprintReadOnly, Replicated, SaveGame, Category = "Projectile" )
	class UFGAmmoTypeProjectile* mSourceAmmoDescriptor;

	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Damage" )
	TArray< UFGDamageType* > mDamageTypesOnImpact;

	UPROPERTY( EditDefaultsOnly, Instanced, Category = "Damage" )
	TArray< UFGDamageType* > mDamageTypesAtEndOfLife;

	UPROPERTY( EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	FRuntimeFloatCurve mGravityScaleOverLifespan;

	UPROPERTY( EditDefaultsOnly, ReplicatedUsing = OnRep_MaxHomingAccelerationMagnitude, BlueprintReadOnly, Category = "Projectile" )
	float mMaxHomingAccelerationMagnitude;
	
	UPROPERTY( EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	FRuntimeFloatCurve mHomingStrengthOverLifespan;

	UPROPERTY( EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	FRuntimeFloatCurve mHomingStrengthOverDistanceToTarget;

	UPROPERTY( EditDefaultsOnly, Replicated, BlueprintReadOnly, Category = "Projectile" )
	float mProjectileStartingHealth;

	UPROPERTY( SaveGame, BlueprintReadWrite, Category = "Projectile" )
	float mProjectileCurrentHealth;
	
	/** The noise to make on impact. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Noise" )
	TSubclassOf< class UFGNoise > mImpactNoise;
	
	/** The noise to make when the projectile explodes. */
	UPROPERTY( EditDefaultsOnly, Category = "Projectile|Noise" )
	TSubclassOf< class UFGNoise > mExplodeNoise;
	
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

	bool mShouldAttachOnImpact = false;
	
private:
	
	/** Sphere collision component */
	UPROPERTY( VisibleDefaultsOnly, Category = "Projectile" )
	class USphereComponent* mCollisionComp;

	/** Projectile movement component */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true") )
	class UFGProjectileMovementComponent* mProjectileMovement;

	/** Was projectile fired by a weapon */
	bool mWasFiredByWeapon;
};

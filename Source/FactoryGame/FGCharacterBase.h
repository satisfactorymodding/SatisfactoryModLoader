// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "GameFramework/Character.h"
#include "FGSaveInterface.h"
#include "AkAudioDevice.h"
#include "FGCharacterBase.generated.h"

USTRUCT( BlueprintType )
struct FFootstepEffect
{
	GENERATED_BODY()

	/** Remove all events from this effect */
	void Reset();

	/** The particle to use when hitting the ground */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	class UParticleSystem* Particle;

	/** UNIMPLEMENTED: The decal to place on the ground when walking around */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	class UMaterialInterface* GroundDecal;
};

USTRUCT( BlueprintType )
struct FFootstepEffectSurface
{
	GENERATED_BODY()

	/** The surface the foot hit */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	TEnumAsByte<EPhysicalSurface> Surface;

	/** The effect we want to play when hitting the surface */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep", meta = ( ShowOnlyInnerProperties ) )
	FFootstepEffect Effect;
};

USTRUCT( BlueprintType )
struct FFootstepEffectWater
{
	GENERATED_BODY()

	/** When at this minimum water depth, then use this footstep effect instead */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	float MinWaterDepth;

	/** The effect we want to play when hitting the surface */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep", meta = ( ShowOnlyInnerProperties ) )
	FFootstepEffect Effect;
};


UCLASS()
class AFGCharacterBase : public ACharacter, public IFGSaveInterface
{
	GENERATED_BODY()
public:
	AFGCharacterBase( const FObjectInitializer& ObjectInitializer );

	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float deltaTime ) override;

	virtual float TakeDamage( float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser );
	// End AActor interface

	/** Apply momentum caused by damage. */
	virtual void ApplyDamageMomentum( float DamageTaken, FDamageEvent const& DamageEvent, APawn* PawnInstigator, AActor* DamageCauser );

	/**
	* Called when this Pawn is possessed. Only called on the server (or in standalone).
	*	@param C The controller possessing this pawn
	*/
	virtual void PossessedBy( AController* NewController );

	// Begin IFGSaveInterface
	virtual void PreSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostSaveGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PreLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	virtual void GatherDependencies_Implementation( TArray< UObject* >& out_dependentObjects ) override;
	virtual bool NeedTransform_Implementation() override;
	virtual bool ShouldSave_Implementation() const override;
	// End IFSaveInterface

	/** Called when we died, need to be UFUNCTION as it's bound as a delegate */
	UFUNCTION()
	virtual void Died( AActor* thisActor );

	/** Blueprint version of when we died */
	UFUNCTION( BlueprintCallable, BlueprintImplementableEvent, Category="Damage", Meta=(DisplayName="Died"))
	void ReceiveDied();

	/** We have taken damage, called after controller has gotten a chance to response to the damage */
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = (DisplayName = "OnTakeDamage") )
	void NotifyOnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** Notify from our health component*/
	UFUNCTION()
	virtual void OnTakeDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/** We have taken damage, called after controller has gotten a chance to response to the damage*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = (DisplayName = "OnTakePointDamage") )
	void NotifyOnTakePointDamage( AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const class UDamageType* damageType, AActor* damageCauser );

	/** We have taken a weakspot hit */
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = ( DisplayName = "OnWeakspotHit" ) )
	void NotifyOnWeakspotHit();

	/** Notify from our health component*/
	UFUNCTION()
	virtual void OnTakePointDamage( AActor* damagedActor, float damage, class AController* instigatedBy, FVector hitLocation, class UPrimitiveComponent* hitComponent, FName boneName, FVector shotFromDirection, const class UDamageType* damageType, AActor* damageCauser );

	/** Notify from our health component*/
	UFUNCTION()
	virtual void OnTakeRadialDamage( AActor* damagedActor, float damage, const class UDamageType* damageType, FVector hitLocation, FHitResult hitInfo, class AController* instigatedBy, AActor* damageCauser );

	/** We have taken radial damage, called after controller has gotten a chance to response to the damage*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage", meta = (DisplayName = "OnTakeRadialDamage") )
	void NotifyOnTakeRadialDamage( AActor* damagedActor, float damage, class AController* instigatedBy, const class UDamageType* damageType, AActor* damageCauser );
	
	/** Called when landing, used for fall damage */
	virtual void Landed( const FHitResult& Hit ) override;

	/** Calculate damage we take from a fall */
	UFUNCTION( BlueprintNativeEvent, Category = "Fall Damage" )
	int32 CalculateFallDamage( float zSpeed ) const;

	/** Assign override to fall damage */
	UFUNCTION( BlueprintCallable, Category = "Fall Damage" )
	void SetFallDamageOverride( UCurveFloat* fallDamageCurveOverride );

	/** Play effects for when landing */
	virtual void PlayLandEffects();

	/** Get our current health component */
	UFUNCTION( BlueprintPure, Category = "Health" )
	FORCEINLINE class UFGHealthComponent* GetHealthComponent() const{ return mHealthComponent; }

	/** Get mFallDamageDamageType */
	UFUNCTION( BlueprintPure, Category = "Fall Damage" )
	FORCEINLINE TSubclassOf< class UFGDamageType > GetFallDamageDamageType() const{ return mFallDamageDamageType; }

	/** Sound played when pawn takes damage */
	UFUNCTION( BlueprintPure, Category = "Sound" )
	FORCEINLINE class UAkAudioEvent* GetTakeDamageSound() const{ return mTakeDamageSound; }

	/** Sound played when pawn dies */
	UFUNCTION( BlueprintPure, Category = "Sound" )
	FORCEINLINE class UAkAudioEvent* GetDeathSound() const{ return mDeathSound; }

	/** Get mTakeDamageParticle */
	UFUNCTION( BlueprintPure, Category = "VFX" )
	FORCEINLINE class UParticleSystem* GetTakeDamageParticle() const{ return mTakeDamageParticle; }

	/** @returns true if this character is alive and well, no health components means yes */
	UFUNCTION( BlueprintPure, Category="Health")
	bool IsAliveAndWell() const;

	/** Player has collided with a vehicle and has received a push. This may be better as a general case function instead of specifically being for vehicles but it is what it is for now. */
	UFUNCTION()
	void PushedByVehicle( class AFGVehicle* vehicle, FVector pushVelocity );

	/**
	 * Plays the footstep effect of this character, default is: Audio, Particle and Decal
	 *
	 * @param footDown - the index specified in UFGAnimNotify_FootDown
	 **/
	UFUNCTION( BlueprintNativeEvent, Category = "Footstep" )
	void PlayFootstepEffect( int32 footDown, bool playSound );

	/**
	 * Traces for the ground, and checks also if we need to go through water to find the ground
	 *
	 * @param traceStart - from where the trace should start
	 * @param traceEnd - where the trace should end end
	 * @param out_hitResult - the hit on the ground
	 * @param out_waterDepth - if > 0, then it's how deep the water was before we hit the ground
	 *
	 * @return true if we hit something
	 */
	UFUNCTION( BlueprintCallable, Category="Effect")
	bool TraceForGround( FVector traceStart, FVector traceEnd, FHitResult& out_hitResult, float& out_waterDepth ) const;

	/**
	 * Get the footstep effect for the hit
	 *
	 * @return nullpeter if there exist no footstep effect
	 */
	virtual const FFootstepEffect& GetFootstepEffect( const FHitResult& hitResult ) const;
	
	/** returns true if mesh is ragdolled */
	UFUNCTION( BlueprintPure, Category = "Ragdoll" )
	bool IsRagdolled() { return mIsRagdolled; }

	/**
	* if newRagdoll is true this function will ragdoll the player
	* @Note: ONLY does something if called from the server.
	*/
	UFUNCTION( BlueprintCallable, Category = "Ragdoll" )
	void RagdollCharacter( bool newRagdoll );

	/** Returns Mesh3P subobject **/
	UFUNCTION( BlueprintPure, Category = "Mesh" )
	virtual USkeletalMeshComponent* GetMesh3P() const;

	/** Check if fall damage should be applied */
	void CheckFallDamage( float zSpeed );
protected:
	/**
	 * Get the audio event for the foot down
	 * 
	 * @param footDown - the foot index specified in the anim blueprint
	 **/
	virtual class UAkAudioEvent* GetFootstepEvent( int32 footDown ) const;

	/**
	* Bound function to our healthcomponent that cares about when we receive damage, passes it on to other AdjustDamage for BP
	*/
	UFUNCTION()
	virtual float AdjustDamage( AActor* damagedActor, float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/**
	* Called whenever we receive damage and gives us a chance to adjust it
	* SERVER ONLY
	*
	* @param damageAmount - how much damage we receive
	* @param damageType - what damage type the damage is that we receive
	* @param instigatedBy - who instigated the damage (Controller)
	* @param damageCauser - the actor who damaged us
	* @return the adjusted damage 
	*/
	UFUNCTION( BlueprintImplementableEvent, Category = "Damage",DisplayName="AdjustDamage" )
	int32 ReceivedAdjustDamage( float damageAmount, const class UDamageType* damageType, class AController* instigatedBy, AActor* damageCauser );

	/**
	 * Play the audio effect for when the character puts a feet down on the ground. Won't do anything if the leg doesn't have any sound
	 *
	 * @param footIndex - the index passed from UFGAnimNotify_FootDown::Notify in the animation
	 * @param hitInfo - information about how the hit looks when playing the effect
	 * @param waterDepth - how deep into the water the foot is when hitting the ground
	 */
	void PlayFootstepAudio( int32 footIndex, const FHitResult& hitInfo, float waterDepth );

	/**
	 * Play a particle effect for when the character puts a feet down on the ground. Won't do anything if we don't have any particle
	 *
	 * @param hitInfo - information about how the hit looks when playing the effect
	 * @param precalculatedEffect - precalculatedEffect fetched effect with what sound we should play
	 * @param socketRotation - the rotation we should have of our effect
	 */
	void PlayFootstepParticle( const FHitResult& hitInfo, const FFootstepEffect& precalculatedEffect, FRotator socketRotation );

	/**
	 * Put a decal on the ground when the character puts a feet down on the ground. Won't do anything if the character doesn't have any decal material specified
	 *
	 * @param hitInfo - information about how the hit looks when playing the effect
	 * @param precalculatedEffect - precalculatedEffect fetched effect with what material we should put on the ground
	 * @param socketRotation - the rotation we should have of our effect
	 */
	void PlaceFootstepDecal( const FHitResult& hitInfo, const FFootstepEffect& precalculatedEffect, FRotator socketRotation );

	/**
	 * Get the effects associated with the depth of water
	 *
	 * @param waterEffects - effects that we should search for a good effect for when walking around in water
	 * @param waterDepth - distance from water to bottom of the water puddle
	 * @param out_footstepEffect - the footstep effect, only valid if returning true
	 *
	 * @return true if we found a suiteable effect
	 */
	bool GetWaterFootstepEffect( const TArray< FFootstepEffectWater >& waterEffects, float waterDepth, FFootstepEffect& out_footstepEffect ) const;

	/** Called regularly after we have been killed, will destroy us eventually */
	UFUNCTION()
	void CheckIfShouldDestroy();

	/** this is what actually activates/deactivates the ragdoll */
	virtual void DoRagdoll_Internal();

	/** this is called when the timer ticks down, and the character gets up from ragdoll if they are still alive */
	void TryGetUpFromRagdoll();

	/** syncs ragdoll mesh and physics velocity */
	virtual void SyncRagdoll();

	/** Setup we we should start checking of we should be destroyed */
	void SetupDestroyTimer();
private:
	UFUNCTION()
	void OnRep_IsRagdolled();

	FVector FindSafePlaceToGetUp();

protected:
	/** When receiving FootDown on index 2, then we will trace from mFeetNames[2] socket for ground */
	UPROPERTY( EditDefaultsOnly, Category="Footstep" )
	TArray< FName > mFeetNames;

	/** Default effects to play when a foot hits the ground when the material doesn't exist in mFootstepEffects */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	FFootstepEffect mDefaultFootstepEffect;

	/** Effects to play when a foot hits the ground */
	UPROPERTY( EditDefaultsOnly, Category="Footstep" )
	TArray< FFootstepEffectSurface > mFootstepEffect;

	/** Audio event to play (where index in array is the feet index passed from AnimNotify_FootDown) */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep|Audio" )
	TArray<class UAkAudioEvent*> mFootstepAudioEvents;

	/** Maximum distance we want to play footstep particles at */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	float mMaxFootstepParticleSpawnDistance;

	/** Maximum distance we want to spawn footsteps decals at */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	float mMaxFootstepDecalSpawnDistance;

	/** Size of footstep decals */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	FVector mFootstepDecalSize;

	/** Lifetime of footstep decals */
	UPROPERTY( EditDefaultsOnly, Category = "Footstep" )
	float mFootstepDecalLifetime;

	/** Keeps track of our current health */
	UPROPERTY( VisibleAnywhere, BlueprintReadOnly, SaveGame, Replicated )
	class UFGHealthComponent* mHealthComponent;

	/** How much damage to take falling with a given velocity */
	UPROPERTY( EditDefaultsOnly, Category = "FallDamage" )
	UCurveFloat* mFallDamageCurve;

	/** Overrides the default fall damage curve, utilized by Equipment */
	UPROPERTY()
	UCurveFloat* mFallDamageCurveOverride;

	/** @todo: This should not be specified for each pawn */
	UPROPERTY( EditDefaultsOnly, Category = "Fall Damage" )
	TSubclassOf< class UFGDamageType > mFallDamageDamageType;

	/** Handle, for removing the character from the game after it has died */
	FTimerHandle mDeathRemovalHandle;

	/** The maximum time after death (in seconds) the pawn will stay in the world, so it will be removed even if it's in sight after this time */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mMaxDeathStayTime;

	/** How often will we check if the pawn is in sight of any player */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mDeathRemoveCheckTime;

	/** Multiplier for targeting desirability */
	UPROPERTY( EditDefaultsOnly, Category = "Aggro" )
	float mEnemyTargetDesirability;

	/** World time when we died */
	float mDeathTimestamp;

	/** Sound played when pawn takes damage */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mTakeDamageSound;

	/** Sound played when pawn dies */
	UPROPERTY( EditDefaultsOnly, Category = "Audio" )
	class UAkAudioEvent* mDeathSound;

	/** Event posted when landing */
	UPROPERTY( EditDefaultsOnly, Category = "Audio")
	class UAkAudioEvent* mLandEvent;

	/** Particle for when pawn takes damage */
	UPROPERTY( EditDefaultsOnly, Category = "VFX" )
	class UParticleSystem* mTakeDamageParticle;

	/** Min push velocity required to start ragdoll */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mMinVehiclePushVelocityForRagdoll;

	/** time in seconds until character gets up from ragdoll if alive */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mTimeToGetUpFromRagdoll;

	/** the furthest distance we can move during ragdoll before we are considered still enough to stand up from ragdoll */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mMaxDistanceMovedToGetUp;

	/** handle for the get up timer */
	FTimerHandle mGetUpFromRagdollHandle;
	
	/** true if ragdolled */
	UPROPERTY( ReplicatedUsing = OnRep_IsRagdolled )
	bool mIsRagdolled;
	
	/** Used to avoid playing landing effect twice */
	bool mShouldPlayLandEffect:1;

	/** Velicty we have when falling, updaten all the time when falling, never cleared */
	FVector mFallVelocity;

	UPROPERTY( Replicated )
	FVector mRagdollMeshLoc;

	UPROPERTY( Replicated )
	FVector mRagdollMeshVelocity;
	
	/** Name of the bone we take mesh location from */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	FName mRagdollMeshLocBoneName;

	/** Name of the bone we take physics velocity from */
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	FName mRagdollMeshPhysicsBoneName;

	/**
	* The maximum sync error distance between the current body location
	* and the synced location before we teleport the ragdoll
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Ragdoll" )
	float mSyncBodyMaxDistance;

	/** Stores the default mesh relative transform for ragdolling purposes */
	FTransform mDefaultMeshRelativeTransform;

	/** squared distance moved during last frame when ragdolled. Used to detect if we are "not moving" and can get up */
	float mSqDistMovedDuringRagdoll;

	/** True if we have a blueprint version of some functions */
	uint8 mHave_PlayFootstepEffect:1;
	uint8 mHave_AdjustDamage:1;

	/** Some things should auto destroy on death. Some shouldnt. */
	bool mCanBeRevived;

	/** Should the auto momentum be applied when taking damage? */
	UPROPERTY( EditDefaultsOnly, Category = "Movement" )
	bool mApplyDamageMomentum;

	/** Damage types that this character is immune to */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" ) 
	TArray< TSubclassOf< class UDamageType > > mIgnoredDamageTypes;

	/** How much more damage should be dealt when taking a weakspot hit */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	float mWeakspotMultiplier;

	/** Bone names that result in a weakspot hit */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	TArray< FName > mWeakspotBoneNames;

	/** Multiplier for this creature and normal damage taken */
	UPROPERTY( EditDefaultsOnly, Category = "Damage" )
	float mNormalDamageMultiplier;
};
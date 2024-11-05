// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimatedBase.h"
#include "FGCreatureActionLeapAttack.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGCreatureActionLeapAttack : public UFGCreatureActionAnimatedBase
{
	GENERATED_BODY()

public:
	UFGCreatureActionLeapAttack( const FObjectInitializer& ObjectInitializer );
	
	// Begin UFGAction Interface
	virtual void PerformAction_Implementation() override;
	virtual bool CanPerformAction_Implementation() const override;
	virtual void CleanupAction_Implementation( bool actionSuccess ) override;
	virtual void ActionTick_Implementation( float DeltaTime ) override;
	// End UFGAction Interface

	/** True if the leap attack is active. */
	UFUNCTION( BlueprintPure, Category = "LeapAttack" )
	FORCEINLINE bool IsLeapAttackActive() const { return mLeapAttackIsActive; }

protected:
	void StartLeapAttack();

	// Begin UFGCreatureActionAnimatedBase Interface
	virtual void OnAnimationFinished_Implementation( class UAnimMontage* montage, bool WasInterrupted  ) override;
	virtual void OnAnimationBlendingOut_Implementation( class UAnimMontage* montage, bool WasInterrupted ) override;
	// End UFGCreatureActionAnimatedBase Interface

	UFUNCTION()
	void OnCreatureLandedCallback( const FHitResult& hitResult );

	UFUNCTION( BlueprintNativeEvent, Category = "LeapAttack" )
	void OnCreatureLanded( const FHitResult& hitResult );

	/** Called on both server and client when the leap attack starts. */
	UFUNCTION( BlueprintNativeEvent, Category = "LeapAttack" )
	void OnLeapStarted();

	UFUNCTION( BlueprintCallable, Category = "LeapAttack" )
	bool LaunchToTarget( AActor* target );

	UFUNCTION( BlueprintCallable, Category = "LeapAttack" )
	bool LaunchToLocation( const FVector& destination );

	/** Called for every character hit by the leap attack. */
	UFUNCTION( BlueprintNativeEvent, Category = "LeapAttack" )
	void ProcessHit( class AFGCharacterBase* character, const FHitResult& hitResult );

	/** Called for every character hit by the slam attack when landing. */
	UFUNCTION( BlueprintNativeEvent, Category = "LeapAttack|Slam" )
	void ProcessSlamHit( class AFGCharacterBase* character, const FHitResult& hitResult );

	/** Clear the list of hit characters, allowing them to be hit again. */
	UFUNCTION( BlueprintCallable, Category = "LeapAttack" )
	void ClearAllHitCharacters();

	/** Remove a character from the hit actor list, allowing them to be hit again. */
	UFUNCTION( BlueprintCallable, Category = "LeapAttack" )
	void ClearHitCharacter( class AFGCharacterBase* character );

	/** Called whenever a hit character gets cleared from the list, useful for cleaning up logic tied to being a "hit character". */
	UFUNCTION( BlueprintNativeEvent, Category = "LeapAttack" )
	void OnHitCharacterCleared( class AFGCharacterBase* character );

private:	
	void ProcessHit_Internal( class AFGCharacterBase* character, const FHitResult& hitResult );

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_OnLeapStarted();

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_OnCreatureLanded( const FHitResult& hitResult );

protected:
	/** The montage to play when starting the leap. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Animation" )
	class UAnimMontage* mLeapStartMontage;

	/** The montage to play when actively in the leap. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Animation" )
	class UAnimMontage* mLeapLoopMontage;

	/** The montage to play when landing. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Animation" )
	class UAnimMontage* mLeapLandMontage;

	/** The radius of the leap attack while it's active. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackRadius;
	
	/** The amount of knockback to apply when hitting a target with the leap. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackKnockbackAmount;

	/** The amount of vertical knockback to apply when hitting a target with the leap. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackVerticalKnockbackAmount;

	/** How much to scale the creature's gravity while the leap attack is active. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackGravityScale;

	/** Arc parameter for the projectile velocity calculation. 0-1 value where 1 means a higher arc. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackArcParam;

	/** 0-1 value which decides how much influence the target prediction has over the final velocity. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack", meta = (ClampMin = "0.0", UIMin = "0.0", ClampMax = "1.0", UIMax = "1.0") )
	float mLeapAttackPredictionParam;

	/** Launch velocity will be clamped to not go above this value. Will be ignored if less than or equal to zero. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack" )
	float mLeapAttackMaxVelocity;

	/** List of characters which have been hit by the attack. */
	UPROPERTY()
	TArray< class AFGCharacterBase* > mHitCharacters;

	/** What damage we should do when we hit a target while leaping. */
	UPROPERTY( EditDefaultsOnly, Instanced, Category= "LeapAttack" )
	TArray < UFGDamageType* > mLeapAttackDamageTypes;

	/** Whether or not the slam attack can hit targets which have already been hit by the leap itself. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Slam" )
	bool mLeapAttackSlamCanHitPreviousTargets;
	
	/** How big the radius of the slam attack is when landing. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Slam" )
	float mLeapAttackSlamRadius;
	
	/** How much knockback to apply when the leap attack hits a target when landing. */
	UPROPERTY( EditDefaultsOnly, Category = "LeapAttack|Slam" )
	float mLeapAttackSlamKnockbackAmount;

	/** What damage we should apply with the slam attack when landing. */
	UPROPERTY( EditDefaultsOnly, Instanced, Category= "LeapAttack|Slam" )
	TArray < UFGDamageType* > mLeapAttackSlamDamageTypes;

private:
	/** True if the leap attack is active. */
	bool mLeapAttackIsActive;
	
	float mOldGravityScale;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimated.h"
#include "FGCreatureActionMeleeAttack.generated.h"

USTRUCT()
struct FACTORYGAME_API FFGMeleeAttackHit
{
	GENERATED_BODY()
	
	UPROPERTY()
	class AFGCharacterBase* HitCharacter;

	UPROPERTY()
	FHitResult HitResult;
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGCreatureActionMeleeAttack : public UFGCreatureActionAnimated
{
	GENERATED_BODY()
public:
	UFGCreatureActionMeleeAttack( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual bool CanPerformAction_Implementation() const override;
	virtual void PerformAction_Implementation() override;
	virtual void ActionTick_Implementation( float DeltaTime ) override;
	virtual void CleanupAction_Implementation( bool ActionSuccess ) override;
	// End UFGAction Interface

protected:

	// Begin UFGCreatureActionAnimated Interface
	virtual void OnAnimNotify_Implementation( const UFGAnimNotify* Notify ) override;
	// End UFGCreatureActionAnimated interface

	/** Called for every character hit by the attack. */
	UFUNCTION( BlueprintNativeEvent, Category = "Attack" )
	void ProcessHit( class AFGCharacterBase* HitCharacter, const FHitResult& HitResult );

	/** Called whenever the melee attack starts. */
	UFUNCTION( BlueprintNativeEvent, Category = "Attack" )
	void StartMeleeAttack();

	UFUNCTION()
	void OnTargetReached( FAIRequestID RequestID, EPathFollowingResult::Type Result );
	
	EPathFollowingRequestResult::Type MoveToTarget();

private:
	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_ProcessHits( const TArray< FFGMeleeAttackHit >& hits );

	void ProcessHits( const TArray< FFGMeleeAttackHit >& hits );

protected:
	/** Whether or not ProcessHit should be run on client as well. Should be false if there's no necessary clientside processing. */
	UPROPERTY( EditDefaultsOnly, Category= "Attack|Optimization" )
	bool mProcessHitsOnClient;
	
	/** How far we're able to reach with the attack. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mAttackRange;

	/** How close we need to get in order to start the attack. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mMinRange;

	/** Targets need to be within this angle in order to be hit by the attack. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack", meta=( UIMin="0.0", UIMax="360.0", ClampMin="0.0", ClampMax="360.0" ) )
	float mAttackAngle;

	/** How fast the creature is allowed to rotate while the attack is in progress. Will use the creature's default turn rate if less than 0. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mRotationRate;

	/** How much we should knock the target back when we hit them. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mKnockbackAmount;

	/** How much we should knock the target up into the air when we hit them. */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mVerticalKnockbackAmount;
	
	/** What damage we should deal to whatever we hit. */
	UPROPERTY( EditDefaultsOnly, Instanced, Category= "Attack" )
	TArray < UFGDamageType* > mDamageTypes;

private:
	float mOldRotationRate;
};

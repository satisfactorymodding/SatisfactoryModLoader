// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGCreatureActionAnimatedBase.h"
#include "Curves/CurveFloat.h"
#include "FGCreatureActionCharge.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class FACTORYGAME_API UFGCreatureActionCharge : public UFGCreatureActionAnimatedBase
{
	GENERATED_BODY()

public:
	UFGCreatureActionCharge( const FObjectInitializer& ObjectInitializer );

	// Begin UFGAction Interface
	virtual void PerformAction_Implementation() override;
	virtual void ActionTick_Implementation( float DeltaTime ) override;
	virtual void CleanupAction_Implementation( bool ActionSuccess ) override;
	// End UFGAction Interface

	/** Whether or not the charge is currently active. */
	UFUNCTION( BlueprintPure, Category = "Charge" )
	FORCEINLINE bool IsCharging() const { return mIsCharging; }

	// Begin UFGCreatureActionAnimatedBase Interface
	virtual void OnAnimationBlendingOut_Implementation( class UAnimMontage* montage, bool WasInterrupted ) override;
	// End UFGCreatureActionAnimatedBase Interface

protected:
	/** Called when we begin the charge. */
	UFUNCTION( BlueprintNativeEvent, Category = "Charge" )
	void BeginCharge();

	/** Called when we end the charge. */
	UFUNCTION( BlueprintNativeEvent, Category = "Charge" )
	void EndCharge();

	/** Called for every character hit by the charge. */
	UFUNCTION( BlueprintNativeEvent, Category = "Charge" )
	void ProcessHit( class AFGCharacterBase* HitCharacter, const FHitResult& HitResult );

	virtual void OnMovementModeChanged( ACharacter* character, EMovementMode previousMode, uint8 prevCustomMode ) override;

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_BeginCharge();

	UFUNCTION( NetMulticast, Reliable )
	void NetMulticast_EndCharge();

	/** Called when the creature has been falling for X amount of time. */
	void OnFall();

protected:
	/** Whether or not we should stop charging once we hit a target. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	bool mStopOnImpact;

	/** How much we should knock the target back when we hit them. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	float mKnockbackAmount;

	/** How much we should knock the target up into the air when we hit them. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	float mVerticalKnockbackAmount;

	/** How big the sphere overlap for detecting targets should be. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	float mChargeSphereTriggerRadius;

	/** How fast we should move when charging. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	float mChargeMovementSpeed;

	/** How much time needs to pass before a target can be hit again. */
	UPROPERTY( EditDefaultsOnly, Category = "Charge" )
	float mTargetHitCooldown;

	/** What damage we should deal to whatever we hit. */
    UPROPERTY( EditDefaultsOnly, Instanced, Category= "Charge" )
    TArray < UFGDamageType* > mDamageTypes;

	/** How the turnrate should be affected by the distance to the target. */
	UPROPERTY( EditDefaultsOnly, Category= "Charge" )
	FRuntimeFloatCurve mDistanceTurnrateCurve;

	/** The montage to play before charging. */
	UPROPERTY( EditDefaultsOnly, Category= "Charge|Animation" )
	class UAnimMontage* mChargeStartMontage;
	
	/** The montage to play while charging. */
	UPROPERTY( EditDefaultsOnly, Category= "Charge|Animation" )
	class UAnimMontage* mChargeMontage;

	/** The montage to play when the charge hits something. */
	UPROPERTY( EditDefaultsOnly, Category= "Charge|Animation" )
	class UAnimMontage* mChargeHitMontage;

	/** Recently hit actors and the timestamp of when they were hit. */
	UPROPERTY()
	TMap< AActor*, float > mRecentlyHitActors;

private:
	float mOldRotationRate;
	float mOldMaxWalkSpeed;

	FTimerHandle mFallingRagdollTimer;

	bool mIsCharging;
};

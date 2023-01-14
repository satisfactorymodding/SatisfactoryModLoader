// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Equipment/FGEquipment.h"
#include "FGEquipmentStunSpear.generated.h"

class UFGDamageType;
/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEquipmentStunSpear : public AFGEquipment
{
	GENERATED_BODY()

public:

	AFGEquipmentStunSpear();

	/** Add custom bindings for this equipment */
	virtual void AddEquipmentActionBindings() override;

	/** Called when the player clicks to "fire" */
	UFUNCTION( BlueprintImplementableEvent, Category = "Stun Spear" )
	void PlayStunEffects();

	UFUNCTION( BlueprintImplementableEvent, Category = "Stun Spear" )
	void PlayHitEffects(const TArray<FHitResult> &hitResults);
	
	/** Getter for mShouldPlaySecondSwing */
	UFUNCTION( BlueprintPure, Category = "Stun Spear" )
	FORCEINLINE bool GetShouldPlaySecondSwing(){ return mShouldPlaySecondSwing; }

	/** Start the damage chain */
	UFUNCTION( BlueprintCallable, Category = "Stun Spear" )
	void DoAttack();
	
	UFUNCTION( BlueprintNativeEvent, Category = "Hit Response" )
	void OnHitTarget();

protected:
	/** server notified of hit from client to verify */
	UFUNCTION( Reliable, Server, WithValidation )
	void Server_ShockEnemy( FVector attackDirection );

	UFUNCTION( Reliable, NetMulticast )
	void Multicast_PlayHitEffects(const TArray<FHitResult> &hitResults);
private:
	/** Key binded functions */
	virtual void OnFirePressed();
private:
	/** Sphere collision component */
	UPROPERTY( VisibleDefaultsOnly, Category = "Stun Spear" )
	class USphereComponent* mCollisionComp;

	UPROPERTY( EditDefaultsOnly, Instanced, Category= "Stun Spear")
	TArray < UFGDamageType* > mDamageTypes;
	
	/** The noise to make when attacking with the spear. */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	TSubclassOf< class UFGNoise > mAttackNoise;

public:
	/** Timer started */
	float mFirstSwingTime;
	
	/** The max amount of time between the first swing that will still trigger the second swing */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mSecondSwingMaxTime;

	/** Indicates if we should do the second swing */
	bool mShouldPlaySecondSwing;

	/** Timestamp when cooldown began */
	float mCoolDown;

	/** The max amount of time between the first swing that will still trigger the second swing */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mSecondSwingCooldDownTime;

	/** How much inf ront of character the attack is */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mAttackDistance;

	/** Defined half-width of the attack in front of the instigator */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mAttackSweepRadius;
};

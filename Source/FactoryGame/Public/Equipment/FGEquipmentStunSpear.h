// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGEquipment.h"
#include "FGEquipmentStunSpear.generated.h"

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
	void Server_ShockEnemy();
private:
	/** Key binded functions */
	virtual void OnFirePressed();
private:
	/** Sphere collision component */
	UPROPERTY( VisibleDefaultsOnly, Category = "Stun Spear" )
	class USphereComponent* mCollisionComp;

	/** Damage type to use when hitting others */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	TSubclassOf< class UFGDamageType > mDamageTypeClass;	
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

	/** Damage amount */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	int32 mDamage;

	/** How much inf ront of character the attack is */
	UPROPERTY( EditDefaultsOnly, Category = "Stun Spear" )
	float mAttackDistance;

public:
	FORCEINLINE ~AFGEquipmentStunSpear() = default;
};

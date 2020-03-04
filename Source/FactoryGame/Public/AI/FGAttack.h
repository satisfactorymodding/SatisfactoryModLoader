#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "FGAttack.generated.h"


UCLASS( abstract, BlueprintType )
class FACTORYGAME_API UFGAttack : public UObject
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAttack();

	/**
	/ Handles the attack logic, differs depending on type of attack ( ex melee, ranged etc )                                                                   
	*/
	virtual void PerformAttack( TScriptInterface< class IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) PURE_VIRTUAL( UFGAttack::PerformAttack, );

	/** Get attack range */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static float GetAttackRange( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mAttackRange; }

	/** Get attack activation distance ( returns the attack range if the activation distance has not been set ) */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static float GetAttackActivationDistance( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mAttackActivationDistance <= 0 ? inClass->GetDefaultObject< UFGAttack >()->mAttackRange : inClass->GetDefaultObject< UFGAttack >()->mAttackActivationDistance; }

	/** Get damage this attack does */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static int32 GetDamage( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mDamage; }

	/** Get angle needed for this attack to hit */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static float GetAttackAngle( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mAttackAngle; }

	/** Get damage type for this attack */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static TSubclassOf< class UDamageType > GetDamageType( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mDamageType; }

	/** Get for stop movement */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static bool GetStopsMovement( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mStopsMovement; }

	/** Get attack montage */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static UAnimMontage* GetAttackMontage( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttack >()->mAttackMontage; }
protected:
	/** Animation to play when attacking */
	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* mAttackMontage;

	/** True if this attack stops movement */
	UPROPERTY( EditDefaultsOnly )
	bool mStopsMovement;

	/** How far can we attack */
	UPROPERTY( EditDefaultsOnly )
	float mAttackRange;

	/** How far can we attack */
	UPROPERTY( EditDefaultsOnly )
	float mAttackActivationDistance;

	/** How much damage to do when hitting */
	UPROPERTY( EditDefaultsOnly )
	int32 mDamage;

	/** Damage type that this attack uses */
	UPROPERTY( EditDefaultsOnly )
	TSubclassOf< class UDamageType > mDamageType;

	/** Angle that target must be within in order to hit with attack ( 180 = full circle hit area ) */
	UPROPERTY( EditDefaultsOnly )
	float mAttackAngle;

public:
	FORCEINLINE ~UFGAttack() = default;
};
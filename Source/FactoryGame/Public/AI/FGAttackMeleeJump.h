// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGAttackMelee.h"
#include "FGAttackMeleeJump.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGAttackMeleeJump : public UFGAttackMelee
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGAttackMeleeJump();
	/**
	/ Handles the attack logic, differs depending on type of attack ( ex melee, ranged etc )
	*/
	virtual void PerformAttack( TScriptInterface< IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) override;

	/** Range of the jump attack */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static float GetJumpRange( TSubclassOf< UFGAttackMeleeJump > inClass ) { return inClass->GetDefaultObject< UFGAttackMeleeJump >()->mJumpRange; }

	/** Get Velocity when jumping ( excluding the Z velocity which is handled by the Jump() in Character */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static FVector GetJumpVelocity( TSubclassOf< UFGAttackMeleeJump > inClass ) { return inClass->GetDefaultObject< UFGAttackMeleeJump >()->mJumpVelocity; }

	/** Get pre jump montage */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Enemy|Attack" )
	static UAnimMontage* GetPreJumpMontage( TSubclassOf< UFGAttack > inClass ) { return inClass->GetDefaultObject< UFGAttackMeleeJump >()->mPreJumpMontage; }
protected:
	/** From where in relation to the target should the jump start */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	float mJumpRange;

	/** Velocity when jumping ( excluding the Z velocity which is handled by the Jump() in Character */
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	FVector mJumpVelocity;

	/** Animation to play before jumping */
	UPROPERTY( EditDefaultsOnly )
	class UAnimMontage* mPreJumpMontage;

public:
	FORCEINLINE ~UFGAttackMeleeJump() = default;
};

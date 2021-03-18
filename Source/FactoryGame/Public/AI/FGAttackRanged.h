// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "AI/FGAttack.h"
#include "FGAttackRanged.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGAttackRanged : public UFGAttack
{
	GENERATED_BODY()
public:
	/**
	/ Handles the attack logic, differs depending on type of attack ( ex melee, ranged etc )
	*/
	virtual void PerformAttack( TScriptInterface< class IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) override;

	/** Has the actual logic for spawning projectiles ( so that we can override in blueprint */
	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|Enemy|Attack" ) 
	void SpawnProjectile( class AActor* targetActor, class AFGEnemy* sourceActor );
public:
	UPROPERTY( EditDefaultsOnly, Category = "Attack" )
	TSubclassOf< class AFGProjectile > mProjectileClass;
};

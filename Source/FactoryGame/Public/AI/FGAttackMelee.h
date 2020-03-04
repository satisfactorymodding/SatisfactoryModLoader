// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

#include "FGAttack.h"
#include "FGAttackMelee.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class FACTORYGAME_API UFGAttackMelee : public UFGAttack
{
	GENERATED_BODY()
	
public:
	/**
	/ Handles the attack logic, differs depending on type of attack ( ex melee, ranged etc )
	*/
	virtual void PerformAttack( TScriptInterface< IFGAggroTargetInterface >	aggroTarget, class AFGEnemy* sourceActor ) override;

public:
	FORCEINLINE ~UFGAttackMelee() = default;
};

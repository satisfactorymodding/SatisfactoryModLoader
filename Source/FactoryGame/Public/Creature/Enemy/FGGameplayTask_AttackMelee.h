// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGGameplayTask_Attack.h"
#include "FGGameplayTask_AttackMelee.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameplayTask_AttackMelee : public UFGGameplayTask_Attack
{
	GENERATED_BODY()
public: 
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;

	/** @todoai: document */
	virtual TScriptInterface< class IFGAggroTargetInterface > GetAttackTarget() const{ return mAttackTarget; }

	/** @todoai: document */
	UFUNCTION( BlueprintCallable, Category = "Tasks", meta = ( DefaultToSelf = "Controller", BlueprintInternalUseOnly = "TRUE", DisplayName = "Attack Target" ) )
	static UFGGameplayTask_AttackMelee* Attack( AFGEnemy* enemy, TScriptInterface< class IFGAggroTargetInterface > attackTarget, TSubclassOf< class UFGAttack > attackClass );
protected:
	virtual void Activate() override;

	/** Called when attack animation ended */
	UFUNCTION()
	void OnMontageEnded( class UAnimMontage* montage, bool interrupted );

	/** Called when attack animation starts to blend out */
	UFUNCTION()
	void OnMontageBlendingOut( class UAnimMontage* montage, bool interrupted );
protected:
	UPROPERTY( BlueprintAssignable )
	FGenericGameplayTaskDelegate mOnAttackFinished;

	UPROPERTY( BlueprintAssignable )
	FGenericGameplayTaskDelegate mOnAttackFailed;

	/** The target we are attacking */
	UPROPERTY( BlueprintReadOnly, Replicated )
	TScriptInterface< class IFGAggroTargetInterface > mAttackTarget;

	/** Called when attack animation ended */
	FOnMontageEnded mOnMontageEnded;

	/** Called when attack animation starts to blend out */
	FOnMontageBlendingOutStarted mOnMontageBlendingOut;
};

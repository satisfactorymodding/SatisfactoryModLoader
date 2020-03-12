// Copyright 2016-2018 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "FGGameplayTask_Attack.h"
#include "FGGameplayTask_Attackjump.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameplayTask_AttackJump : public UFGGameplayTask_Attack
{
	GENERATED_BODY()
public:
	/** ctor */
	UFGGameplayTask_AttackJump( const FObjectInitializer& ObjectInitializer );

	/** Starts the task of doing a jump attack */
	UFUNCTION( BlueprintCallable, Category = "Tasks", meta = ( DefaultToSelf = "Controller", BlueprintInternalUseOnly = "TRUE", DisplayName = "Jump attack" ) )
	static UFGGameplayTask_AttackJump* StartJump( AFGEnemy* enemy, TSubclassOf< class UFGAttackMeleeJump > attackClass, bool startJump );
protected:
	virtual void Activate() override;
	virtual void OnDestroy( bool bInOwnerFinished ) override;

	/** Called when pre jump animation ended */
	UFUNCTION()
	void OnMontageEnded( class UAnimMontage* montage, bool interrupted );

	UFUNCTION()
	void OnLandedCallback( const FHitResult& Hit );
protected:
	
	UPROPERTY( BlueprintAssignable )
	FGenericGameplayTaskDelegate mOnJumpAttackFinished;

	UPROPERTY( BlueprintAssignable )
	FGenericGameplayTaskDelegate mOnJumpAttackFailed;

	/** Called when attack animation ended */
	FOnMontageEnded mOnMontageEnded;
public:
	/** Should jump logic be handled in the task */
	UPROPERTY()
	bool mDoJump;

	/** Saving previous stepheight */
	float mPrevStepHeight; 

public:
	FORCEINLINE ~UFGGameplayTask_AttackJump() = default;
};


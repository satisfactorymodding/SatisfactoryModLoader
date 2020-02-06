// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "Animation/AnimInstance.h"
#include "FGGameplayTask_Base.h"
#include "../../AI/FGAttack.h"
#include "FGGameplayTask_Attack.generated.h"


/**
 * 
 */
UCLASS()
class FACTORYGAME_API UFGGameplayTask_Attack : public UFGGameplayTask_Base
{
	GENERATED_BODY()
public:
	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray< class FLifetimeProperty > & OutLifetimeProps ) const override;

	virtual void InitSimulatedTask( UGameplayTasksComponent& InGameplayTasksComponent );

	/** @todoai: document */
	virtual TScriptInterface< class IFGAggroTargetInterface > GetAttackTarget() const{ return nullptr; }

	/** ctor */
	UFGGameplayTask_Attack( const FObjectInitializer& ObjectInitializer );
	
	/** Gets the attack class */
	UFUNCTION( BlueprintPure, Category = "Attack" )
	TSubclassOf< class UFGAttack > GetAttackClass() const{ return mAttackClass; }
protected:
	virtual void Activate() override;
	virtual void OnDestroy( bool bInOwnerFinished ) override;
protected:
	UPROPERTY( Replicated )
	TSubclassOf< class UFGAttack > mAttackClass;
};

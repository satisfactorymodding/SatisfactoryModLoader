// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "GameFramework/Actor.h"
#include "UObject/Class.h"

#include "../../FGUseableInterface.h"
#include "../FGCreature.h"
#include "FGEnemy.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGEnemy : public AFGCreature
{
	GENERATED_BODY()
public:
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;

	/** ctor */
	AFGEnemy( const FObjectInitializer& ObjectInitializer );

	/** Returns the location we want to originate an attack from */
	UFUNCTION( BlueprintNativeEvent, Category = "Enemy" )
	FVector GetAttackLocation();

	/** Returns the current attack task ( can be nullptr ) */
	UFUNCTION( BlueprintPure, Category = "Attack" )
	FORCEINLINE class UFGGameplayTask_Attack* GetCurrentAttackTask(){ return mCurrentAttack; }

	/** Hook for us to be able to go to blueprrint in order to do the custom radial attack */
	UFUNCTION( BlueprintNativeEvent, Category = "Attack" ) 
	void PerformCustomRadialAttack();

	/** Sets aggro target */
	void SetCurrentAggroTarget( AActor* newTarget );
	
	/** Get aggrotarget  */
	UFUNCTION( BlueprintPure, Category = "Enemy" )
	FORCEINLINE AActor* GetCurrentAggroTarget(){ return mCurrentAggroTarget; }

	/** Called on both server and client when aggro target has changed */
	UFUNCTION( BlueprintNativeEvent, Category = "Enemy" )
	void OnCurrentAggroTargetReplicated();
protected: 
	/** Replicating mCurrentAggroTarget */
	UFUNCTION()
	void OnRep_CurrentAggroTarget();
public: 
	/** The current attack that the pawn is issuing @todoai: Verify if clients need this replicated or if the task get a activate on clients too */
	UPROPERTY( Replicated )
	class UFGGameplayTask_Attack* mCurrentAttack;
private:
	UPROPERTY( ReplicatedUsing = OnRep_CurrentAggroTarget )
	AActor* mCurrentAggroTarget;
};


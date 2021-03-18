// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGAggroTargetInterface.generated.h"

/**
 * Interface for actors that can be aggroed by enemies.
 */
UINTERFACE( Blueprintable )
class FACTORYGAME_API UFGAggroTargetInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class FACTORYGAME_API IFGAggroTargetInterface
{
	GENERATED_IINTERFACE_BODY()

	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	bool ShouldAutoregisterAsTargetable() const;

	UFUNCTION(BlueprintNativeEvent,Category="FactoryGame|AI|Aggro")
	void RegisterIncomingAttacker( class AFGEnemyController* forController );

	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	void UnregisterAttacker( class AFGEnemyController* forController );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	AActor* GetActor();

	/**
	 * Primitive component that we will try to attack
	 */
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	class UPrimitiveComponent* GetTargetComponent();

	UFUNCTION( BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	float GetEnemyTargetDesirability( class AFGEnemyController* forController );

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	bool IsAlive() const;

	UFUNCTION( BlueprintCallable, BlueprintNativeEvent, Category = "FactoryGame|AI|Aggro" )
	FVector GetAttackLocation() const;


	/*virtual float GettAttackRangeOffset() = 0;

	UFUNCTION()
	virtual void RegisterAttacker( class AFGEnemyController* forController ) = 0;

	UFUNCTION()
	virtual void UnregisterIncomingAttacker( class AFGEnemyController* forController ) = 0;

	virtual bool IsDynamic() = 0;*/
};
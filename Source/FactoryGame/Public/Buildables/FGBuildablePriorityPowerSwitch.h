// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildableCircuitSwitch.h"
#include "FGBuildablePriorityPowerSwitch.generated.h"

/**
 * Building that connects two circuits, allowing them to act as one single circuit when the switch is turned on.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePriorityPowerSwitch : public AFGBuildableCircuitSwitch
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPriorityChanged, int, priority );

public:
	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	//~ End AActor interface
	
	//~ Begin AFGBuildableCircuitSwitch interface
	virtual void AcceptCircuitGroup( class UFGPowerCircuitGroup* circuitGroup ) override;
	//~ End AFGBuildableCircuitSwitch interface

	/**
	* @returns the priority with which this switch will be turned off automatically in case of power shortage.
	* A higher number will be turned off before a lower number. 0 (or less) means this switch will never be turned off automatically.
	*/
	UFUNCTION( BlueprintPure, Category = "CircuitSwitch" )
	int GetPriority() const { return mPriority; }

	/**
	* @param priority the priority with which this switch will be turned off automatically in case of power shortage.
	* A higher number will be turned off before a lower number. 0 (or less) means this switch will never be turned off automatically.
	*/
	UFUNCTION( BlueprintCallable, Category = "CircuitSwitch" )
	void SetPriority( int priority );

	/**
	 * Broadcast when the priority of this switch changes.
	 */
	UPROPERTY( BlueprintAssignable, Category = "CircuitSwitch" )
	FOnPriorityChanged OnPriorityChanged;

protected:
	/**
	 * Called when the priority of this switch changes.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "CircuitSwitch" )
	void PriorityChanged( int priority );

private:
	UFUNCTION()
	void OnRep_Priority();

private:
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Priority )
	int mPriority = 0;

	TWeakObjectPtr< UFGPowerCircuitGroup > mCircuitGroup;
};

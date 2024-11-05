// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGBuildableCircuitSwitch.h"
#include "FGPriorityPowerSwitchInfo.h"
#include "FGBuildablePriorityPowerSwitch.generated.h"

/**
 * Building that connects two circuits, allowing them to act as one single circuit when the switch is turned on.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePriorityPowerSwitch : public AFGBuildableCircuitSwitch
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPriorityChanged, int32, priority );

public:
	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	//~ End AActor interface
	
	//~ Begin AFGBuildableCircuitSwitch interface
	virtual void AcceptCircuitGroup( class UFGPowerCircuitGroup* circuitGroup ) override;
	//~ End AFGBuildableCircuitSwitch interface
	
	/** Get the always relevant info for this switch. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitch" )
	class AFGPriorityPowerSwitchInfo* GetInfo() const { return mInfo; }
	
	/**
	 * @returns the priority with which this switch will be turned off automatically in case of power shortage.
	 * A higher number will be turned off before a lower number. 0 (or less) means this switch will never be turned off automatically.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Power|PrioritySwitch" )
	int32 GetPriority() const { return mPriority; }

	/**
	 * @param priority the priority with which this switch will be turned off automatically in case of power shortage.
	 * A higher number will be turned off before a lower number. 0 (or less) means this switch will never be turned off automatically.
	 */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Power|PrioritySwitch" )
	void SetPriority( int32 priority );

	/**
	 * Broadcast when the priority of this switch changes.
	 */
	UPROPERTY( BlueprintAssignable, Category = "CircuitSwitch" )
	FOnPriorityChanged mOnPriorityChanged;

protected:
	/**
	 * Called when the priority of this switch changes.
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "CircuitSwitch" )
	void OnPriorityChanged( int32 priority );

private:
	void EnsureInfoCreated();
	
	UFUNCTION()
	void OnRep_Priority();

private:
	/**
	 * The priority with which this switch will be turned off automatically in case of power shortage.
	 * A higher number will be turned off before a lower number. 0 (or less) means this switch will never be turned off automatically.
	 */
	UPROPERTY( SaveGame, ReplicatedUsing = OnRep_Priority )
	int32 mPriority = 0;

	/** The circuit group this switch is part of. */
	TWeakObjectPtr< UFGPowerCircuitGroup > mCircuitGroup;

	/** Always relevant info storing info about this switch that should be accessible from anywhere. */
	UPROPERTY( Replicated )
	AFGPriorityPowerSwitchInfo* mInfo;
};

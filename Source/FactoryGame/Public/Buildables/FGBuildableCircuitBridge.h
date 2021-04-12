// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "FGBuildableCircuitBridge.generated.h"

/**
 * Building that connects two circuits, allowing them to act as one single circuit. Intended as base for switches and similar buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCircuitBridge : public AFGBuildable
{
	GENERATED_BODY()
public:
	AFGBuildableCircuitBridge();

	//~ Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	//~ End AActor interface

	/**
	 * @returns true if this bridge is turned on, false otherwise
	*/
	virtual bool IsBridgeActive() const { return true; }

	/**
	 * @returns true if this bridge is connected to two circuits, false otherwise
	*/
	bool IsBridgeConnected() const;

	/**
	 * Re-calculate the value of mIsBridgeConnected
	 */
	void CalculateBridgeConnected();

	int32 GetFirstCircuitID() const;
	int32 GetSecondCircuitID() const;

	/** Called when the circuit group collection has been rebuilt by the circuit subsystem */
	void OnCircuitGroupCreated();

	//~ Begin UFGCircuitGroup -> AFGBuildableCircuitBridge visitor pattern
	/** Called after a visit to the newly created circuit group that this bridge belongs to. */
	virtual void AcceptCircuitGroup( class UFGCircuitGroup* circuitGroup ) { }
	/** Called after a visit to the newly created circuit group that this bridge belongs to. */
	virtual void AcceptCircuitGroup( class UFGPowerCircuitGroup* circuitGroup ) { }
	//~ End UFGCircuitGroup -> AFGBuildableCircuitBridge visitor pattern

protected:

	virtual void OnCircuitsChanged();

private:
	UFUNCTION()
	virtual void OnRep_IsBridgeConnected() { }

private:
	UPROPERTY( ReplicatedUsing = OnRep_IsBridgeConnected )
	bool mIsBridgeConnected;

	/** The connection on this building. */
	UPROPERTY()
	TArray< class UFGCircuitConnectionComponent* > mConnections;

	FDelegateHandle mOnCircuitsChangedDelegateHandle;
};

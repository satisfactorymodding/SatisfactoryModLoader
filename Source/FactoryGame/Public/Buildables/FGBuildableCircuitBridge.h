// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildable.h"
#include "FGBuildableCircuitBridge.generated.h"

/**
 * Building that connects two circuits, allowing them to act as one single circuit. Intended as base for switches and similar buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildableCircuitBridge : public AFGBuildable
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnCircuitsChanged );

public:
	AFGBuildableCircuitBridge();

	//~ Begin AActor interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	//~ End AActor interface

	/** @returns true if this bridge is turned on, false otherwise. */
	virtual bool IsBridgeActive() const { return true; }

	/** @returns true if this bridge is connected to two circuits, false otherwise. */
	bool IsBridgeConnected() const;

	/** Re-calculate the value of mIsBridgeConnected */
	void CalculateBridgeConnected();

	/** @return Get the circuit ID we are connected to at our first connection, -1 if disconnected. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Bridge" )
	int32 GetCircuitID0() const;
	
	/** @return Get the circuit ID we are connected to at our second connection, -1 if disconnected. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Bridge" )
	int32 GetCircuitID1() const;

	/** @return The first connection component, cannot be null. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Bridge" )
	class UFGCircuitConnectionComponent* GetConnection0() { return mConnections[ 0 ]; }
	/** @return The second connection component, cannot be null. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|Bridge" )
	class UFGCircuitConnectionComponent* GetConnection1() { return mConnections[ 1 ]; }

	/** Called when the circuit group collection has been rebuilt by the circuit subsystem */
	void OnCircuitGroupCreated();
	
	/** Called when one or more circuits have changed. */
	virtual void OnCircuitsRebuilt();

	//~ Begin UFGCircuitGroup -> AFGBuildableCircuitBridge visitor pattern
	/** Called after a visit to the newly created circuit group that this bridge belongs to. */
	virtual void AcceptCircuitGroup( class UFGCircuitGroup* circuitGroup ) { }
	virtual void AcceptCircuitGroup( class UFGPowerCircuitGroup* circuitGroup ) { }
	//~ End UFGCircuitGroup -> AFGBuildableCircuitBridge visitor pattern

	/**
	 * Broadcast when any of the connected circuits or circuit groups changes, called on server.
	 */
	UPROPERTY( BlueprintAssignable, Category = "CircuitBridge" )
	FOnCircuitsChanged mOnCircuitsChanged;

private:
	UFUNCTION()
	virtual void OnRep_IsBridgeConnected() { }

private:
	/**
	 * If this bridge is connected to two circuits.
	 * If it is then it can bridge those to circuits if activated.
	 */
	UPROPERTY( ReplicatedUsing = OnRep_IsBridgeConnected )
	bool mIsBridgeConnected;

	/** The connections on this building. */
	UPROPERTY()
	TArray< class UFGCircuitConnectionComponent* > mConnections;
};

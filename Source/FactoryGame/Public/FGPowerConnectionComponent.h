// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGCircuitConnectionComponent.h"
#include "FGPowerConnectionComponent.generated.h"


/**
 * Special type of circuit connection that provides a connection to the power grid.
 */
UCLASS( ClassGroup = ( Custom ), meta = ( BlueprintSpawnableComponent ) )
class FACTORYGAME_API UFGPowerConnectionComponent : public UFGCircuitConnectionComponent
{
	GENERATED_BODY()
public:
	UFGPowerConnectionComponent();

	/** Set the power info for this connection. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Circuits|PowerConnection" )
	void SetPowerInfo( class UFGPowerInfoComponent* powerInfo );

	/** Get the power info from which to get the consumption/production. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerConnection" )
	FORCEINLINE class UFGPowerInfoComponent* GetPowerInfo() const { return mPowerInfo; }

	/**
	 * @return The circuit this is connected to; nullptr if not connected.
	 * @note This can be changed/removed at any time so do not save copies to it.
	 */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerConnection" )
	class UFGPowerCircuit* GetPowerCircuit() const;
	
	/** @returns true if the power production in the circuit connected to this component is above zero, false otherwise. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Circuits|PowerConnection" )
	bool HasPower() const { return mHasPower; }

	/** Delegate that will fire whenever mHasPower has changed */
	DECLARE_DELEGATE_OneParam( FOnHasPowerChanged, bool )
	FOnHasPowerChanged OnHasPowerChanged;

protected:
	// Begin UFGCircuitConnectionComponent interface
	virtual void OnCircuitIDChanged() override;
	// End UFGCircuitConnectionComponent interface

private:
	void SetHasPower( bool hasPower );
	void OnCircuitHasPowerChanged( bool hasPower );

private:
	/**
	 * The power info for this connection.
	 * Should be unique for each connection or a race condition can occur for setting the circuit ID on the power info.
	 */
	UPROPERTY()
	class UFGPowerInfoComponent* mPowerInfo;

	/** true if the power production the circuit connected to this is above zero, false otherwise. */
	UPROPERTY()
	bool mHasPower;

	int32 mPreviousCircuitID = INDEX_NONE;
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "UObject/Class.h"

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

protected:
	// Begin UFGCircuitConnectionComponent interface
	virtual void OnCircuitIDChanged() override;
	// End UFGCircuitConnectionComponent interface

private:
	/**
	 * The power info for this connection.
	 * Should be unique for each connection or a race condition can occur for setting the circuit ID on the power info.
	 */
	UPROPERTY()
	class UFGPowerInfoComponent* mPowerInfo;

public:
	FORCEINLINE ~UFGPowerConnectionComponent() = default;
};

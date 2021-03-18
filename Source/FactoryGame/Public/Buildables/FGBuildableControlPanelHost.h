// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableCircuitBridge.h"
#include "FGBuildableControlPanelHost.generated.h"

/**
 * Building that collects buildables connected to the downstream power connection and presents them for user interaction
 */
UCLASS()
class FACTORYGAME_API AFGBuildableControlPanelHost : public AFGBuildableCircuitBridge
{
	GENERATED_BODY()
public:
	DECLARE_DYNAMIC_MULTICAST_DELEGATE( FOnPropertyChanged );

	AFGBuildableControlPanelHost();

	//~ Begin AActor interface
	virtual void BeginPlay() override;
	//~ End AActor interface

	/** Get a list of the buildables controlled by this host. @param outputType should correspond to the class default Controlled Buildable Type */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Buildable|ControlPanelHost", Meta = ( DeterminesOutputType = "outputType" ) )
	TArray< AFGBuildable* >& GetControlledBuildables( TSubclassOf< AFGBuildable > outputType );
	
protected:
	/**
	 * Called when this building is connected or disconnected from the circuit containing the buildables controlled by this host
	 */
	UFUNCTION( BlueprintImplementableEvent, Category = "ControlPanelHost" )
	void ControlledBuildablesChanged();

private:
	virtual void OnCircuitsChanged() override;
	
	void SearchDownstreamCircuit();

public:
	/** Broadcast when this building is connected or disconnected from the circuit. */
	UPROPERTY( BlueprintAssignable, Category = "FactoryGame|Buildable|ControlPanelHost" )
	FOnPropertyChanged mOnControlledBuildablesChanged;
	
private:
	/** The connection to the circuit containing the buildables controlled by this host. */
	UPROPERTY()
	class UFGCircuitConnectionComponent* mDownstreamConnection;

	UPROPERTY( EditDefaultsOnly, Category = "ControlPanelHost" )
	TSubclassOf< AFGBuildable > mControlledBuildableType;

	UPROPERTY()
	TArray< AFGBuildable* > mControlledBuildables;
};

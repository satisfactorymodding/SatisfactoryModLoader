// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FGPowerCircuitWidget.generated.h"

/**
 * Base for widgets thats observes a power circuit.
 */
UCLASS()
class FACTORYGAME_API UFGPowerCircuitWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	/** Delegate for getting the power circuit to display. */
	DECLARE_DYNAMIC_DELEGATE_RetVal( class UFGPowerCircuit*, FGetPowerCircuit );

	/** @return Get the power circuit to display info for, may be null. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	class UFGPowerCircuit* GetPowerCircuit() const { return mPowerCircuit; }

protected:
	virtual void NativeTick( const FGeometry& myGeometry, float inDeltaTime ) override;

public:
	/** Delegate for getting the number of items to display. */
	UPROPERTY( EditAnywhere, Category = "Events", DisplayName = "GetPowerCircuitEvent", meta = ( IsBindableEvent = "True" ) )
	FGetPowerCircuit mGetPowerCircuitEvent;

private:
	/** Power circuit we're observing. */
	UPROPERTY()
	class UFGPowerCircuit*  mPowerCircuit;
};

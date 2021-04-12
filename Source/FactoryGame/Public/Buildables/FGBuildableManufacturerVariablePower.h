// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableManufacturer.h"
#include "Curves/CurveFloat.h"
#include "FGBuildableManufacturerVariablePower.generated.h"

UCLASS( Blueprintable )
class FACTORYGAME_API AFGBuildableManufacturerVariablePower : public AFGBuildableManufacturer
{
	GENERATED_BODY()

public:
	AFGBuildableManufacturerVariablePower();

	// Begin AActor interface
	virtual void BeginPlay() override;
	// End AActor interface

	// Begin AFGBuildableFactory interface
	FORCEINLINE virtual bool Factory_RunsOnPower() const override
	{
		return true;
	}
	
	virtual float GetProducingPowerConsumptionBase() const override { return mVariablePowerConsumption; }
	virtual void Factory_StartProducing() override;
	virtual void Factory_TickProducing( float dt ) override;
	// End AFGBuildableFactory interface
	
	/** @returns the minimum power this building can consume, in MW */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetMinPowerConsumption() const { return mMinPowerConsumption; }
	
	/** @returns the maximum power this building can consume, in MW */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetMaxPowerConsumption() const { return mMaxPowerConsumption; }

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual void OnRep_CurrentPotential() override;
	virtual void OnRep_IsProducing() override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableManufacturer interface
	virtual void OnRep_CurrentRecipe() override;
	// End AFGBuildableManufacturer interface

private:
	void UpdateVariablePowerConsumption();
	void UpdatePowerConsumptionLimits();
	float ApplyRecipePowerModifications( float curveValue );
	
public:
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mEstimatedMininumPowerConsumption;

	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mEstimatedMaximumPowerConsumption;

protected:
	/**
	*	The curve that determines the power variation of this manufacturer.
	*	The domain (the input values it is defined for) must cover the whole set [0.0, 1.0], since those are the values that define the production cycle.
	*	The range (all possible output values) should also cover [0.0, 1.0] (@see "Power Consumption Constant" and "Power Consumption Factor" from FGRecipe).
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	UCurveFloat* mPowerConsumptionCurve;

private:
	float mVariablePowerConsumption = 0.0f;
	float mMinPowerConsumption = 0.0f;
	float mMaxPowerConsumption = 0.0f;
};

// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildableGenerator.h"
#include "FGBuildableGeneratorGeoThermal.generated.h"

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGBuildableGeneratorGeoThermal : public AFGBuildableGenerator
{
	GENERATED_BODY()
public:
	// Replication
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;

	// Begin AActor interface
	virtual void BeginPlay() override;
	virtual void Destroyed() override;
	// End AActor interface 

	// Begin Save Interface
	virtual void PostLoadGame_Implementation( int32 saveVersion, int32 gameVersion ) override;
	// End Save Interface

	/** Set the extractable resource interface for this generator */
	void SetExtractableResource( TScriptInterface< class IFGExtractableResourceInterface > extractableResource );
	
	/** @returns the minimum power this generator can produce, in MW */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetMinPowerProduction() const { return mMinPowerProduction; }
	
	/** @returns the maximum power this generator can produce, in MW */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetMaxPowerProduction() const { return mMaxPowerProduction; }

protected:
	// Begin Factory_ interface
	virtual void Factory_Tick( float dt ) override;
	// End Factory_ interface

	// Begin AFGBuildableFactory interface
	virtual void OnRep_IsProducing() override;
	// End AFGBuildableFactory interface

	// Begin AFGBuildableGenerator interface
	virtual bool CanStartPowerProduction_Implementation() const override;
	virtual void Factory_StartPowerProduction_Implementation() override;
	virtual void Factory_TickPowerProduction_Implementation( float dt ) override;
	virtual void Factory_StopPowerProduction_Implementation() override;
	// End AFGBuildableGenerator interface

	TScriptInterface< IFGExtractableResourceInterface > GetExtractableResource() const { return mExtractableResource; }

private:
	void OnExtractableResourceSet();
	void UpdatePowerProduction();
	float CalculateCurrentPowerProduction() const;
	float CalculatePowerProduction( float curveValue ) const;

private:
	/** DEPRECATED - Use mExtractableResource instead. This exists for save functionality
	*	This is the geyser this generator is placed on
	*/
	UPROPERTY( SaveGame )
	class AFGResourceNode* mExtractResourceNode;

	UPROPERTY( SaveGame, Replicated )
	AActor* mExtractableResource;

	/**
	 * The curve determining the power variation, preferably with its domain (defined input) normalized to [0.0, 1.0]
	 * and its range (possible output) within [0.0, 1.0].
	*/
	UPROPERTY( Replicated )
	UCurveFloat* mPowerOutputCurve;
	
	/**
	*	Added to the variable power production. If the power-production curve's range (all possible output values)
	*	is normalized to [0.0, 1.0], this constant can be thought of as a power-production minimum.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mVariablePowerProductionConstant = 100.0f;

	/**
	*	Multiplied into the variable power production. If the power-production curve's range (all possible output values)
	*	is normalized to [0.0, 1.0], this value added to the power-production constant can be thought of as a power-production maximum.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mVariablePowerProductionFactor = 200.0f;

	/**
	*	The elapsed time is divided by this value and the remaining fraction is used as an input to the power-output curve.
	*	If the power-production curve's domain (all defined input values) is normalized to [0.0, 1.0],
	*	this constant can be thought of as the length of the power-production cycle, in seconds.
	*/
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mVariablePowerProductionCycleLength = 60.0f;

	UPROPERTY( Replicated )
	float mMinPowerProduction;

	UPROPERTY( Replicated )
	float mMaxPowerProduction;

	UPROPERTY( SaveGame, Replicated )
	float mVariablePowerProductionCycleOffset;
};

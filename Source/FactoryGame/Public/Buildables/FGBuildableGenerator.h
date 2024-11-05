// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableFactory.h"
#include "FGBuildableGenerator.generated.h"

/**
 * Base for all generators, i.e. coal, fuel, nuclear etc.
 */
UCLASS( Abstract )
class FACTORYGAME_API AFGBuildableGenerator : public AFGBuildableFactory
{
	GENERATED_BODY()
public:
	AFGBuildableGenerator();
	
	/** Decide on what properties to replicate */
	virtual void GetConditionalReplicatedProps(TArray<FFGCondReplicatedProperty>& outProps) const override;

	// Begin AFGBuildableFactory interface
	virtual bool CanProduce_Implementation() const override;
	virtual bool Factory_HasPower() const override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	/** Get the current load of this generator in the range [0,1]. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetLoadPercentage() const { return mLoadPercentage; }

	/** The power this generator can produce. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetPowerProductionCapacity() const;

	/** The default amount power this generator can produce. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float GetDefaultPowerProductionCapacity() const;

	/** Calculate the power this generator can produce with a given potential. */
	UFUNCTION( BlueprintPure, Category = "Power" )
	float CalcPowerProductionCapacityForPotential( float potential ) const;

	/** Called to check if power production can be started. */
	UFUNCTION( BlueprintNativeEvent, CustomEventUsing=mHas_CanStartPowerProduction, BlueprintPure, Category = "Generator" )
	bool CanStartPowerProduction() const;

protected:
	// Begin AFGBuildableFactory interface
	virtual void Factory_TickProducing( float dt ) override;
	virtual void Factory_StartProducing() override;
	virtual void Factory_StopProducing() override;
	// End AFGBuildableFactory interface

	/** Called when we start producing fuel. */
	UFUNCTION( BlueprintNativeEvent,CustomEventUsing=mHas_Factory_StartPowerProduction, Category = "Generator" )
	void Factory_StartPowerProduction();

	/** Called when we stop producing fuel. */
	UFUNCTION( BlueprintNativeEvent,CustomEventUsing=mHas_Factory_StopPowerProduction, Category = "Generator" )
	void Factory_StopPowerProduction();

	/**
	 * Tick the power production, consume any fuel, update base and dynamic production.
	 * @param dt - Time since last tick.
	 */
	UFUNCTION( BlueprintNativeEvent,CustomEventUsing=mHas_TickPowerProduction, Category = "Generator" )
	void Factory_TickPowerProduction( float dt );

protected:
	/** Amount of power this generator produces in MW. */
	UPROPERTY( EditDefaultsOnly, Category = "Power" )
	float mPowerProduction;

private:
	/** Current load of this generator in the range [0,1]. */
	UPROPERTY( meta = ( FGReplicated ) )
	float mLoadPercentage;

	/* if true these functions have a blueprint implemented version, otherwise call native. */
	uint8 mHas_CanStartPowerProduction:1;
	uint8 mHas_Factory_StartPowerProduction:1;
	uint8 mHas_Factory_StopPowerProduction:1;
	uint8 mHas_TickPowerProduction:1;
};

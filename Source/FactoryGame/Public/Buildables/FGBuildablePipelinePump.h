// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "Buildables/FGBuildablePipelineAttachment.h"
#include "FGBuildablePipelinePump.generated.h"

/**
 * Struct containing quantized fluid content for a more optimized replication.
 */
USTRUCT()
struct FQuantizedPumpIndicatorData
{
	GENERATED_BODY()
public:
	void SetFlowPct( float pct );
	float GetFlowPct() const;

	void SetPressurePct( float pct );
	float GetPressurePct() const;

private:
	/** See setters for how this data is packed. */
	UPROPERTY()
	int8 PackedFlow = 0;
	UPROPERTY()
	uint8 PackedPressure = 0;
};

/**
 * Base class for all attachable pipeline pumps.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelinePump : public AFGBuildablePipelineAttachment
{
	GENERATED_BODY()
public:
	AFGBuildablePipelinePump();

	// Begin AActor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void Tick( float dt ) override;
	// End AActor Interface

	// Begin AFGBuildableFactory interface
	virtual void Factory_Tick( float dt ) override;
	virtual bool CanProduce_Implementation() const override;
	virtual void OnBuildEffectFinished() override;
	virtual EProductionStatus GetProductionIndicatorStatus() const override;
	// End AFGBuildableFactory interface

	// Begin Fluid Integrant Interface
	virtual void OnFluidDescriptorSet() override;
	// End Fluid Integrant Interface

	// Begin IFGDismantleInterface 
	virtual void StopIsLookedAtForDismantle_Implementation( class AFGCharacterPlayer* byCharacter ) override;
	// End IFGDismantleInterface

	/**
	 * ---- DISCLAIMER ----
	 * So here is the tricky part, in our fluid model, pump pressure is measured in meters.
	 * That unit is called the pump head in the real world.
	 * Our calculations are simplified for pressure to only account for the height of the fluid column.
	 * That is why in the calculations we refer to it as pressure, as that is the real world phenomena we want to model in a simplified way.
	 * But that is confusing when talking about pumps that are measured in pressure [psi, bar] and head [meters, feet].
	 * So we have a split terminology in our code here for it to make sense in the different contexts. And the pump is the place where the pressure becomes the head.
	 */

	/** Set the maximum out pressure for this pump. */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes|Pump" )
	void SetMaxHeadLift( float design, float max );

	/** Get the absolute maximum amount of meters up this pump can push fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetMaxHeadLift() const;

	/** Get the amount of meters up this pump is designed to push fluid. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetDesignHeadLift() const;
	
	/** Set the limited flow through this pump. Set this to -1 to use the max limit, i.e. valve is fully opened. [m3/s] */
	UFUNCTION( BlueprintCallable, Category = "FactoryGame|Pipes|Pump" )
	void SetUserFlowLimit( float rate );

	/** Get the limited flow through this pump. -1 if max is used, i.e. valve is fully opened. [m3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
    float GetUserFlowLimit() const { return mUserFlowLimit; }

	/** Get the limited flow through this pump. [m3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetFlowLimit() const;
	
	/** Get the limited flow through this pump in percent of the max. [0,1]  */
    UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
    float GetFlowLimitPct() const;

	/** Get the set maximum flow rate through this pump. [m3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
    float GetDefaultFlowLimit() const { return mDefaultFlowLimit; }

	/** Get the replicated flow rate through this pump from 0 to MAX in the range. [0,1] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetIndicatorFlowPct() const;

	/** Get the replicated flow rate through this pump. [m^3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetIndicatorFlow() const;

	/** Get the replicated head lift in percent of the max. [0,1] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetIndicatorHeadLiftPct() const;

	/** Get the current head lift this pump is pushing, this can be seen as the height of the water pushing back on the pump. [meters] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pump" )
	float GetIndicatorHeadLift() const;

protected:
	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Pipes|Pipeline" )
	void BuildEffectFinishedEvent();

	UFUNCTION( BlueprintImplementableEvent, Category = "FactoryGame|Pipes|Pipeline" )
	void FluidDescriptorSetNotify( TSubclassOf< class UFGItemDescriptor > fluidDesc );

private:
	/** Updates the maximum flow limit from the neighbouring pipes. */
	void UpdateDefaultFlowLimit();
	/** Updates the flow limit on the fluid box. */
	void UpdateFlowLimitOnFluidBox();
	
private:
	/** Maximum pressure this pump applies. [meters] */
	UPROPERTY( EditDefaultsOnly, Category = "Pump" )
	float mMaxPressure;
	/** When the pump is working above this pressure, it's working outside of it's specifications, range [0, max pressure), unit [meters] */
	UPROPERTY( EditDefaultsOnly, Category = "Pump" )
	float mDesignPressure;

	/** Maximum flow rate of this pump. [m3/s] */
	UPROPERTY( SaveGame, Replicated, VisibleInstanceOnly, Category = "Pump" )
	float mDefaultFlowLimit;
	/** The user set flow limit used for this pump. If this is negative the max limit is used, otherwise the value is treated as a limit. */
	UPROPERTY( SaveGame, Replicated, VisibleInstanceOnly, Category = "Pump" )
	float mUserFlowLimit;

	/** Minimum Flow percent acceptable before entering StandBy mode on indicator */
	UPROPERTY( EditDefaultsOnly, Category = "Pump", meta = ( ClampMin = "0.0", ClampMax = "1.0" ) )
	float mMinimumFlowPercentForStandby;

	/** Quantized data used by the indicators. */
	UPROPERTY( Replicated )
	FQuantizedPumpIndicatorData mIndicatorData;

	/** Smoothed values used by the indicators/UI. */
	float mIndicatorFlowPct;
	float mIndicatorPressurePct;
};

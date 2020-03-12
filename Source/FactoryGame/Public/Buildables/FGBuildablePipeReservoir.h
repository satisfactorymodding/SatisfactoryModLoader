// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "SubclassOf.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "../FGFluidIntegrantInterface.h"
#include "Buildables/FGBuildableFactory.h"
#include "../FGSignificanceInterface.h"
#include "FGBuildablePipeReservoir.generated.h"

/**
 * Struct containing quantized fluid content for a more optimized replication.
 */
USTRUCT()
struct FACTORYGAME_API FQuantizedReservoirIndicatorData
{
	GENERATED_BODY()
public:
	void SetFlowFillPct( float pct );
	float GetFlowFillPct() const;

	void SetFlowDrainPct( float pct );
	float GetFlowDrainPct() const;

	void SetContentPct( float pct );
	float GetContentPct() const;

private:
	/** See setters for how this data is packed. */
	UPROPERTY()
	uint8 PackedFlowFill = 0;
	UPROPERTY()
	uint8 PackedFlowDrain = 0;
	UPROPERTY()
	uint8 PackedContent = 0;

public:
	FORCEINLINE ~FQuantizedReservoirIndicatorData() = default;
};

/**
 * Pipeline for transferring liquid and gases to factory buildings.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipeReservoir : public AFGBuildableFactory, public IFGFluidIntegrantInterface
{
	GENERATED_BODY()
public:
	AFGBuildablePipeReservoir();

	// Begin Actor Interface
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type endPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End Actor Interface 

	// Begin AFGBuildable interface
	virtual void Factory_Tick( float dt ) override;
	// End AFGBuildable interface

	// Begin Fluid Integrant Interface
	virtual FFluidBox* GetFluidBox() override;
	virtual TArray< class UFGPipeConnectionComponent* > GetPipeConnections() override;
	// End Fluid Integrant Interface

	/** @return The amount of fluid in this storage, may be more than maximum in case of over-pressurization. [m^3] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	float GetFluidContent() const;

	/** @return The maximum amount of fluid in this storage. [m^3] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	float GetFluidContentMax() const;

	/** @return The rate the reservoir is filling. [m^3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	float GetFlowFill() const;

	/** @return The rate the reservoir is draining. [m^3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	float GetFlowDrain() const;

	/** @return The fill/drain limit, this depends on the number of connection components. [m^3/s] */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	float GetFlowLimit() const;

	/** @return The type of fluid in this storage. */
	UFUNCTION( BlueprintPure, Category = "FactoryGame|Pipes|Pipeline|Reservoir" )
	TSubclassOf< UFGItemDescriptor > GetFluidDescriptor() const;

public:
	/** When stacking reservoirs how high above should it place */
	UPROPERTY( EditDefaultsOnly, Category = "Reservoir" )
	float mStackingHeight;

	//Fluid box used for flow calculations
	UPROPERTY( SaveGame )
	FFluidBox mFluidBox;

protected:
	/** The storage capacity in cubic meters. [m^3] */
	UPROPERTY( EditDefaultsOnly, Category = "Reservoir" )
	float mStorageCapacity;

private:
	// Cached array of connection components
	UPROPERTY()
	TArray< UFGPipeConnectionComponent* > mPipeConnections;

	/** Quantized data used by the indicators. */
	UPROPERTY( Replicated )
	FQuantizedReservoirIndicatorData mIndicatorData;

	/** Smoothed values used by the indicators/UI. */
	float mIndicatorFlowFillPct;
	float mIndicatorFlowDrainPct;
	float mIndicatorContentPct;

public:
	FORCEINLINE ~AFGBuildablePipeReservoir() = default;
};

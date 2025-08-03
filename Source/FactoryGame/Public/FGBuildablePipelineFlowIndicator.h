// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildablePipeline.h"
#include "CoreMinimal.h"
#include "FGPipelineIndicatorData.h"
#include "FGSignificanceInterface.h"
#include "FGBuildablePipelineFlowIndicator.generated.h"

/**
 * Actor for the flow indicators that are attached to pipelines.
 */
UCLASS()
class FACTORYGAME_API AFGBuildablePipelineFlowIndicator : public AFGBuildable, public IFGSignificanceInterface
{
	GENERATED_BODY()
public:	
	AFGBuildablePipelineFlowIndicator();

	// Begin AActor
	virtual void GetLifetimeReplicatedProps( TArray< FLifetimeProperty >& OutLifetimeProps ) const override;
	virtual void BeginPlay() override;
	virtual void EndPlay( const EEndPlayReason::Type EndPlayReason ) override;
	virtual void Tick( float dt ) override;
	// End AActor

	// Begin SignificanceInterface
	virtual void GainedSignificance_Implementation() override;
	virtual void LostSignificance_Implementation() override;
	virtual void GainedNetSignificance_Implementation() override;
	virtual void LostNetSignificance_Implementation() override;
	virtual float GetSignificanceRange() override;
	// End SignificanceInterface

	/** Updates whenever the pipeline indicator should presently be ticking */
	void UpdateActorTickEnabled();
	/** Updates the replication data that is used to update the visuals for the players */
	void UpdateReplicationData(bool bAllowFlushingDormancy = true);
	/** Updates the custom primitive data on the indicator mesh for the local player */
	void UpdateVisuals( float Dt );

	/** Returns the fluid descriptor currently in the pipeline */
	UFUNCTION(BlueprintPure, Category = "Pipeline Indicator")
	TSubclassOf<UFGItemDescriptor> GetFluidDescriptor() const { return mFluidDescriptor; }

	/** Get the replicated content of the pipe in the range [0, 1] */
	UFUNCTION(BlueprintPure, Category = "Pipeline Indicator")
	float GetIndicatorContentPct() const { return mPipelineIndicatorData.GetRawContentPct(); }

	/** Get the replicated flow of the pipe in the range [-1, 1] */
	UFUNCTION(BlueprintPure, Category = "Pipeline Indicator")
	float GetIndicatorFlowPct() const { return mPipelineIndicatorData.GetRawFlowPct(); }
private:
	/** Called after BeginPlay to update the replication data for the first time */
	void UpdateInitialReplicationData();

protected:
	/** Mesh for the indicator. */
	UPROPERTY( VisibleAnywhere )
	UFGColoredInstanceMeshProxy* mIndicatorComponent;

private:
	/** The pipe we are attached to. Only available on the server */
	UPROPERTY()
	AFGBuildablePipeline* mOwningPipeline;

	/** Fluid descriptor replicated from the pipeline */
	UPROPERTY(Replicated)
	TSubclassOf<UFGItemDescriptor> mFluidDescriptor;

	/** Flow indicator data */
	UPROPERTY(Replicated)
	FPipelineIndicatorData mPipelineIndicatorData;
	
	/** Cached flow and content values used for smoothing. */
	float mSmoothedContent{};
	float mSmoothedFlow{};
	bool mIsCurrentDataStale{true};

	/** True if we are significant for the networking purposes. That means we need to pull the data from the pipeline and update it */
	bool mIsServerSideSignificant{false};
	/** True if we are significant for the local player. That means we need to tick the visuals on the flow indicator */
	bool mIsLocallySignificant{false};
};

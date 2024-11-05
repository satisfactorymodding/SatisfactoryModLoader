// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "Buildables/FGBuildable.h"
#include "Buildables/FGBuildablePipeline.h"
#include "CoreMinimal.h"
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
	virtual	void LostSignificance_Implementation() override;
	virtual void GainedSignificance_Native() override;
	virtual void LostSignificance_Native() override;
	virtual float GetSignificanceRange() override;
	// End SignificanceInterface
	
	void UpdateVisuals( float Dt );

protected:
	/** Mesh for the indicator. */
	UPROPERTY( VisibleAnywhere )
	UFGColoredInstanceMeshProxy* mIndicatorComponent;

private:
	/** The pipe we belong to. */
	UPROPERTY( Replicated )
	class AFGBuildablePipeline* mOwningPipeline;

	/** Cached fluid type. */
	TSubclassOf< UFGItemDescriptor > mFluidDescriptor;
	
	UPROPERTY()
	UFGItemDescriptor* mFluidDescriptorCDO;
	
	/** Cached flow and content values used for smoothing. */
	float mSmoothedContent = 0.f;
	float mSmoothedFlow = 0.f;
};

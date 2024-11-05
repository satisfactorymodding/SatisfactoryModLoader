// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "FGFactoryHologram.h"
#include "FGPipeAttachmentHologram.h"
#include "FGPipelineAttachmentHologram.generated.h"

/**
 * Base attachment class for buildables built onto pipelines
 */
UCLASS()
class FACTORYGAME_API AFGPipelineAttachmentHologram : public AFGPipeAttachmentHologram
{
	GENERATED_BODY()

public:
	AFGPipelineAttachmentHologram();

	//Begin AActor
	virtual void BeginPlay() override;
	//End AActor

	//Begin AFGHologram
	virtual void ConfigureComponents(AFGBuildable* inBuildable) const override;
	//End AFGHologram
protected:
	/** Whether or not to display directional arrows on producer component types */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	uint8 mUseProducerDirectionalArrow : 1;

	/** Local location to place the producer directional arrow mesh if enabled */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment", meta=( EditCondition = mUseProducerDirectionArrow ) )
	FVector mProducerArrowRelativeLocation;
	
	/** Directional indicator. Added to visualize "Producer" type pipe connection components direction */
	UPROPERTY()
	TArray< class UStaticMeshComponent* > mProducerComponentArrows;
};

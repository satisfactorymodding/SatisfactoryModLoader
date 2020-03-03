// Copyright 2016-2019 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"
#include "UObject/Class.h"

#include "CoreMinimal.h"
#include "Hologram/FGFactoryHologram.h"
#include "FGPipelineAttachmentHologram.generated.h"

/**
 * Base attachment class for buildables built onto pipelines
 */
UCLASS()
class FACTORYGAME_API AFGPipelineAttachmentHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

public:
	AFGPipelineAttachmentHologram();

	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	// Begin AFGHologram Interface
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

protected:
	// Begin AFGHologram interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual int32 GetRotationStep() const override;
	virtual void CheckClearance() override;
	// End of AFGHologram interface

	// Begin AFGBuildableHologram Interface
	virtual void ConfigureComponents( class AFGBuildable* inBuildable ) const override;
	virtual void CheckValidPlacement() override;
	// End AFGBuildableHologram Interface

	/**
	 * Will attempt to find and snap to a nearby connection on a pipeline, as long as it is unconnected and is NOT SNAP_ONLY
	 *
	 * @param out_location - Current location of hologram, will be modified to the snap location if snapping is successful
	 * @param out_normal - Current forward normal of the hologram, will be modified to the connection if snapping is successful
	 * @note -	This will return the location of the component, it will not account for Local PipeComponent transform offset. 
	 *			Placing the hologram component to component must be done manually per case as the desired behavior can vary.
	 */
	void TrySnapToConnection( const float snapDistance, FVector& out_location, FVector& out_normal );

public:
	/** Name of the pass through input connection. */
	static FName mConnection0;

	/** Name of the pass through output connection. */
	static FName mConnection1;

protected:
	/** Used to limit the placement in turns. What's the maximum offset to check from center to detect the curve. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	float mMaxValidTurnOffset;

	/** Used to limit the placement in turns. What's the maximum angle. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	float mMaxValidTurnAngle;

	/** The axis to rotate around for scroll rotation */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	TEnumAsByte<EAxis::Type> mRotationAxis;

	/** Should this attachment increment its snapped connection index on Scroll? */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	bool mIncrementSnappedConnectionOnScroll;

	/** Whether or not to display directional arrows on producer component types */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	uint8 mUseProducerDirectionalArrow : 1;

	/** Local location to place the producer directional arrow mesh if enabled */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment", meta=( EditCondition = mUseProducerDirectionArrow ) )
	FVector mProducerArrowRelativeLocation;

	/** When snapping to a Wall apply this offset on the wall. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipeline Attachment" )
	FVector2D mWallSnapOffset;

	/** Directional indicator. Added to visualize "Producer" type pipe connection components direction */
	UPROPERTY()
	TArray< class UStaticMeshComponent* > mProducerComponentArrows;
	
	/** The pipeline we snapped to. */
	UPROPERTY()
	class AFGBuildablePipeline* mSnappedPipeline;

	/** Cached list of all connections in this attachment hologram */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponent* > mPipeConnectionComponents;

	/** Index of the connection component we wish to snap */
	int32 mSnapConnectionIndex;

	/** The pipeline connection Component we have snapped to. Can be NULL
	 *  Used when attempting to place the attachment at the end of a pipe that is not connected
	 */
	UPROPERTY()
	class UFGPipeConnectionComponent* mSnappedConnectionComponent;

	/** The offset we snapped on the pipeline. */
	float mSnappedPipelineOffset;

public:
	FORCEINLINE ~AFGPipelineAttachmentHologram() = default;
};

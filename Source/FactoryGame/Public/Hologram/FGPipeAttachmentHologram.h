#pragma once
#include "CoreMinimal.h"
#include "Hologram/FGBuildableHologram.h"
#include "FGFactoryHologram.h"
#include "FGPipeAttachmentHologram.generated.h"

class AFGBuildablePipeBase;

UENUM()
enum class EPipeAttachmentBuildStep : uint8
{
	PABS_PlacementAndDirection,
	PABS_AdjustRotation
};

UCLASS( )
class FACTORYGAME_API AFGPipeAttachmentHologram : public AFGFactoryHologram
{
	GENERATED_BODY()

public:
	AFGPipeAttachmentHologram();

	/** Replication */
	virtual void GetLifetimeReplicatedProps( TArray<FLifetimeProperty>& OutLifetimeProps ) const override;
	
	// Begin Actor Interface
	virtual void BeginPlay() override;
	// End Actor Interface

	// Begin AFGHologram Interface
	virtual bool IsValidHitResult( const FHitResult& hitResult ) const override;
	virtual bool DoMultiStepPlacement( bool isInputFromARelease ) override;
	virtual void SetHologramLocationAndRotation( const FHitResult& hitResult ) override;
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	virtual float GetHologramHoverHeight() const override;
	virtual void GetIgnoredClearanceActors( TArray< AActor* >& ignoredActors ) const override;
	virtual bool IsValidHitActor(AActor* hitActor) const override;
	virtual bool CanNudgeHologram() const override;
	// End AFGHologram Interface

	// Begin AFGBuildableHologram Interface
	virtual bool ShouldActorBeConsideredForGuidelines( class AActor* actor ) const override;
	// End AFGBuildableHologram Interface

protected:
	// Begin AFGHologram interface
	virtual void ScrollRotate( int32 delta, int32 step ) override;
	virtual int32 GetRotationStep() const override;
	// End of AFGHologram interface

	// Begin AFGBuildableHologram Interface
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
	/** Class of the pipeline to snap to */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	TSubclassOf<AFGBuildablePipeBase> mBasePipeClass;

	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	TSubclassOf<UInterface> mPipeAttachmentInterfaceClass;
	
	/** The current build step of the attachment. */
	UPROPERTY()
	EPipeAttachmentBuildStep mBuildStep = EPipeAttachmentBuildStep::PABS_PlacementAndDirection;

	/** Used to limit the placement in turns. What's the maximum offset to check from center to detect the curve. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	float mMaxValidTurnOffset;

	/** Used to limit the placement in turns. What's the maximum angle. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	float mMaxValidTurnAngle;

	/** The axis to rotate around for scroll rotation */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	TEnumAsByte<EAxis::Type> mRotationAxis;

	/** Should this attachment increment its snapped connection index on Scroll? */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	bool mIncrementSnappedConnectionOnScroll;
	
	/** When snapping to a Wall apply this offset on the wall. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	FVector2D mWallSnapOffset;

	/** Whether or not this hologram uses the second build step, where it rotates around the pipe. */
	UPROPERTY( EditDefaultsOnly, Category = "Pipe Attachment" )
	bool mHasPipeRotationBuildStep;

	/** Cache the upvector when switching build step, we use this to rotate around the pipe. */
	FVector mBuildStepUpVector;
	
	/** The pipeline we snapped to. */
	UPROPERTY( Replicated, CustomSerialization )
	class AFGBuildablePipeBase* mSnappedPipe;

	/** Cached list of all connections in this attachment hologram */
	UPROPERTY()
	TArray< class UFGPipeConnectionComponentBase* > mPipeConnectionComponents;

	/** Index of the connection component we wish to snap */
	UPROPERTY( Replicated, CustomSerialization )
	int32 mSnapConnectionIndex;

	/** The pipeline connection Component we have snapped to. Can be NULL
	 *  Used when attempting to place the attachment at the end of a pipe that is not connected
	 */
	UPROPERTY( Replicated, CustomSerialization )
	class UFGPipeConnectionComponentBase* mSnappedConnectionComponent;

	/** The offset we snapped on the pipe. */
	UPROPERTY( Replicated, CustomSerialization )
	float mSnappedPipeOffset;
};

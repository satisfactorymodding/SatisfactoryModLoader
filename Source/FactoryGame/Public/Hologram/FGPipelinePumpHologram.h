// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Hologram/FGPipelineAttachmentHologram.h"
#include "FGPipelinePumpHologram.generated.h"

USTRUCT( BlueprintType )
struct FPumpHeadLiftLocationPath
{
	GENERATED_BODY()
public:
	FPumpHeadLiftLocationPath();

	void SetData( const FPumpHeadLiftLocationPath& Other );
	void SetData( const class USplineComponent* pSpline, float StartOffset, float EndOffset, bool ReverseDirection );
	
	TArray<FTransform> GetTransformsAtDistance( float Distance ) const;

	float GetLongestPathLength() const;

	void Clear();

	FPumpHeadLiftLocationPath& AddNextPath( const FPumpHeadLiftLocationPath& NextPath );
	FPumpHeadLiftLocationPath& AddNextPath( const class USplineComponent* pSpline, float StartOffset, float EndOffset, bool ReverseDirection );

private:
	const class USplineComponent* Spline;

	float OffsetStart;
	float OffsetEnd;

	bool ReverseSplineDirection;

	TArray<FPumpHeadLiftLocationPath> NextPaths;
};

/**
 * 
 */
UCLASS()
class FACTORYGAME_API AFGPipelinePumpHologram : public AFGPipelineAttachmentHologram
{
	GENERATED_BODY()	
public:
	AFGPipelinePumpHologram();

	// Begin AActor Interface
	virtual void Tick( float dt ) override;
	// End AActor Interface
	
	// Begin AFGHologram Interface
	virtual bool TrySnapToActor( const FHitResult& hitResult ) override;
	// End AFGHologram Interface

	// Gets the current headlift path
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
	const FPumpHeadLiftLocationPath& GetCurrentHeadLiftPath() const { return mCurrentHeadLiftPath; }

	// Returns the longest possible length of the path.
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
	static float GetHeadLiftPathLength( const FPumpHeadLiftLocationPath& Path );
	
	// Given a distance, returns locations on the path towards all the headlift end locations
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
	static TArray<FTransform> GetTransformsAtDistanceAlongPath( const FPumpHeadLiftLocationPath& Path, float Distance );

	// Given a distance 0-1, returns locations on the path towards all the headlift end locations
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
    static TArray<FTransform> GetTransformsAtNormalizedDistanceAlongPath( const FPumpHeadLiftLocationPath& Path, float Distance );

	// Gets all the transforms of locations we are currently able to snap to, excluding the one we are currently snapped to. Based on other pumps in the network.
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
    const TArray<FTransform>& GetHeadLiftSnapTransforms() const { return mHeadLiftSnapTransforms; }

	// Gets the list of transforms representing our own headlift end locations.
	UFUNCTION( BlueprintPure, Category = "HeadLift" )
    const TArray<FTransform>& GetHeadLiftEndTransforms() const { return mHeadLiftEndTransforms; }

private:
	// Returns pipes and their offets for snapping, based on other pumps in the network
	void FindHeadLiftSnappingLocations( class AFGBuildablePipeline* StartPipeline, TMap<AFGBuildablePipeline*, float>& OutResults, TArray<FPumpHeadLiftLocationPath>& OutPaths ) const;

	// Find all offsets and pipes on the pipe network we're snapped to which exceeds a height difference, given a start location.
	void FindLocationsWithHeightDifferenceOnPipeline( TMap<AFGBuildablePipeline*, float>& OutResults, FPumpHeadLiftLocationPath& OutPath, class AFGBuildablePipeline* pPipeline, const FVector& StartLocation,
		const float HeightDifference, bool ReverseDirection, const int32 RecursionLevel, float TotalDistanceTraversed = 0.0f ) const;

private:
	FPumpHeadLiftLocationPath mCurrentHeadLiftPath;

	TArray<FTransform> mHeadLiftSnapTransforms;
	TArray<FTransform> mHeadLiftEndTransforms;

	// How many binary divisions to do in order to determine final offset location on the pump. Higher value = More precise
	UPROPERTY( EditDefaultsOnly, Category = "HeadLift" )
	int32 mOffsetEstimationBinaryDivisionCount;

	// How many junctions we're allowed to recurse through before stopping.
	UPROPERTY( EditDefaultsOnly, Category = "HeadLift" )
	int32 mMaxJunctionRecursions;

	// How far we're allowed to travel along the pipe before we stop looking for headlift end locations along the current path.
	UPROPERTY( EditDefaultsOnly, Category = "HeadLift" )
	float mMaxTraversalDistance;
};

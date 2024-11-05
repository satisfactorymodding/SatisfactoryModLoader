// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FGBuildableSpawnStrategy.h"
#include "Components/SplineComponent.h"
#include "FGBuildableSpawnStrategy_Spline.generated.h"

class UFGPowerConnectionComponent;

UENUM( BlueprintType )
enum class EFGSplineBuildableRouteStrategy : uint8
{
	Auto,
	StraightBend2D,
	StraightBend3D,
	TangentBasedSpline3D
};

// Spawn strategy specifically for spawning spline-based buildings like conveyor belts, pipes and railroad tracks
UCLASS()
class FACTORYGAME_API UFGBuildableSpawnStrategy_Spline : public UFGBuildableSpawnStrategy
{
	GENERATED_BODY()
public:
	UFGBuildableSpawnStrategy_Spline();

	virtual bool IsCompatibleWith(AFGBuildable* buildable) const override;
	virtual void PreSpawnBuildable(AFGBuildable* buildable) override;

	static EFGSplineBuildableRouteStrategy GetDefaultRouteStrategyForBuildable( const UClass* buildableClass );
	static bool RouteSpline( TArray<FSplinePointData>& out_splineData, const FVector& startPos, const FVector& startForward, const FVector& endPos, const FVector& endForward, EFGSplineBuildableRouteStrategy routeStrategy, float bendRadius );
public:
	// The strategy to use when routing the spline for the buildable. Auto determines based on the buildable type
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spline", meta = ( ExposeOnSpawn ) )
	EFGSplineBuildableRouteStrategy mSplineRouteStrategy;

	// Determines the bend radius for spline routing
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spline", meta = ( ExposeOnSpawn ) )
	float mSplineBendRadius;
	
	// Transform for the starting point of the buildable, in local space
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spline", meta = ( ExposeOnSpawn ) )
	FTransform mLocalStartTransform;

	// Transform for the ending point of the buildable, in local space
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Buildable | Spline", meta = ( ExposeOnSpawn ) )
	FTransform mLocalEndTransform;
};

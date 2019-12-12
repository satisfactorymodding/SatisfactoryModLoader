// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/StaticMesh.h"
#include "Array.h"

#include "../FSplinePointData.h"

/**
 * Shared magic between holograms
 */
struct FHologramHelpers
{
	/** 
	 * Creates a clearance component
	 *
	 * @param attachTo			Root that we want to attach the created component to
	 * @param fromBox			Box used for setting size of clearance component
	 */
	static class UStaticMeshComponent* CreateClearanceComponent( class USceneComponent* attachTo, class UBoxComponent* fromBox );

	/** Creates the connection mesh for a connection component */
	static class UStaticMeshComponent* CreateConnectionRepresentation( class UFGFactoryConnectionComponent* connectionComponent );

	/**
	 * Calculate a poles height given a hit result and the poles location.
	 */
	static float CalcPoleHeight( const struct FHitResult& aimResult, const struct FVector& poleLocation );
};

struct FSplineUtils
{
	/**
	 * Helper to make an arc with a spline.
	 * Calculates the magic multiplier for the tangents in an arc with the given angle and radius.
	 * Note: This works best for angles up to about 90-180 degrees depending on situation. Above that use multiple spline points.
	 *
	 * @param angle		Angle of the arc, in radians
	 * @param radius	Radius of the circle the arc is part of.
	 * @return			The magnitude of the tangents of the two points making up the arc.
	 */
	static float CalcArcTangentMagnitude( float angle, float radius )
	{
		// Calculate a magic magnitude number for the tangents.
		// Found through manually testing angles using a spline in the editor
		// and then finding the polynomial expression by plotting the points in a graph calculator.
		// Angle  Tangent
		// 0:     0.0
		// 45:    0.76
		// 90:    1.65
		// 120:   2.7
		// 180:   4.0
		const float clampedAngle = FMath::Clamp( angle, 0.0f, PI );
		const float magicMultiplier = 0.14f * clampedAngle * clampedAngle + 0.81f * clampedAngle + 0.01f;
		return radius * magicMultiplier;
	}

	/**
	 * Calculate an arc between the spline points given.
	 *
	 * @param startPoint		Start point in the arc.
	 * @param endPoint			End point in the arc.
	 */
	static void CalcAutoCurveSpline( struct FSplinePointData& startPoint, struct FSplinePointData& endPoint );

	/**
	 * Calculate how much of the tangent to keep in from of the split [0,1] and how much to keep at the end (1 - front) to preserve the spline.
	 */
	static float CalcTangentRatioAtSplit( const class USplineComponent* component, float split );

	/**
	 * Check if the point between to spline points are straight enough.
	 */
	static bool BuildStraightSpline(
		struct FSplineBuilder& builder,
		const FVector& endPos,
		const FVector& endForward,
		float dotTreshold );

	/**
	 * Calculates a spline with straight line which bends only at the start and end.
	 *
	 * @param builder	The spline builder to append to, this must have at least on point in it already.
	 * @param startRadius,endRadius	 Radius of the start and end bend.
	 * @param endPos		Where to end the spline.
	 * @param endForward	Where the end tangent is facing.
	 */
	static bool BuildBendStraightBendSpline(
		struct FSplineBuilder& builder,
		float startRadius,
		float endRadius,
		const FVector& endPos,
		const FVector& endForward );

	/**
	 * Calculates a spline using one bend.
	 *
	 * @param builder		The spline builder to append to, this must have at least on point in it already.
	 * @param minTurnRadius The minimum turn radius allowed.
	 * @param endPos		Where to end the spline.
	 * @param endForward	Where the end tangent is facing. 0,0,0 if it should be calculated using the start.
	 *
	 * @return false if the radius requirement could not be satisfied.
	 */
	static bool BuildCurveSpline(
		struct FSplineBuilder& builder,
		float minTurnRadius,
		const FVector& endPos,
		FVector endForward );

private:
	/** Internal helpers for building routing the splines. */
	static void CalcBendDirections(
		const FVector& startPos,
		const FVector& startForward,
		float startRadius,
		const FVector& endPos,
		const FVector& endForward,
		float endRadius,
		bool& out_isStartCW,
		bool& out_isEndCW );

	static void CalcBendAngles(
		const FVector& startPos,
		const FVector& startForward,
		float startRadius,
		bool isStartCW,
		const FVector& endPos,
		const FVector& endForward,
		float endRadius,
		bool isEndCW,
		float& out_startAngle,
		float& out_endAngle );

	static float CalcStraightTangentMagnitude( const FVector& startPos, const FVector& endPos );
};

/**
 * Small util for building splines.
 */
struct FSplineBuilder
{
	FSplineBuilder( TArray< FSplinePointData >& out_points ) : SplineData( out_points ) {}

	/**
	 * Begin with calling Start, this clears the points array and sets up the first point.
	 */
	void Start( const FVector& pos, const FVector& tan );

	/**
	 * Append a segment to the spline.
	 */
	void Segment( const FVector& pos, const FVector& tan );

	/**
	 * Modify the last placed segment.
	 */
	void ModifySegment( const FVector& pos, const FVector& tan );

public:
	TArray< FSplinePointData >& SplineData;
};

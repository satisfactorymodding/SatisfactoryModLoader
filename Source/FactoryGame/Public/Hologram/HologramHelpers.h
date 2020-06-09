// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "Engine/StaticMesh.h"
#include "Array.h"

#include "FGHologramGraphAStar.h"
#include "Components/SplineComponent.h"
#include "Stats.h"

DECLARE_STATS_GROUP( TEXT( "Hologram Helpers" ), STATGROUP_HologramHelpers, STATCAT_Advanced );

/**
 * Shared magic between holograms
 */
struct FACTORYGAME_API FHologramHelpers
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

	/**
	 * Calculate a poles height given a hit result and the poles location while also calculating the poles horizontal offset angle from the rays forward direction
	 */
	static float CalcPoleHeightAndHorisontalOffset(float& out_horisontalOffset, const struct FHitResult& aimResult, const struct FVector& poleLocation );

public:
	FORCEINLINE ~FHologramHelpers() = default;
};

struct FACTORYGAME_API FSplineUtils
{


	/**
	* Helper Data structure for all data used to create a "Start to End" curve. This can define an entire spline or a segment for splines
	* with more than two defining points. This won't handle calculations between segments so that must be handled by suppling the correct initialization data
	* when generating the curve segments as the behavior between those points is not defined and may vary between different desired curves
	*
	* To use, supply the Start and End data and call CalculateValues(). This will call the appropriate FHologramHelper functions to generate the defining angles and circles
	*
	* This is only kinda useful for one build at the moment and my plans for it kinda fell through when I started treating the pipes as more 
	* special case to get unique visuals. Investigate if this can be useful or if I should just move this to its only call place ( HorzToVert ) for pipe holograms
	*/
	struct FSplineSegmentPointData
	{
		// Default Construct, initialize all values to Zero
		FSplineSegmentPointData()
		{
			StartPos = StartForward = StartRight = FVector::ZeroVector;
			EndPos = EndForward = EndRight = FVector::ZeroVector;
			StartCircle = EndCircle = FVector::ZeroVector;
			StartAngle = EndAngle = 0.f;
		}

		// Assign the initial point data used to calculate the circles and angles
		void InitializePoints( FVector startPos, FVector startForward, FVector startRight, FVector endPos, FVector endForward, FVector endRight, float startRadius, float endRadius );

		// Assign a Debug Object for drawing debug visuals
		void AssignDebugObject( class AActor* debugActor );

		// Calculate Circles and Angles for the initialized point data
		// @param forceVerticalExceeding - Vertical rise between the two points to change calculation to assume a vertical rise along segment
		void CalculateValues( float forceVerticalExceeding = 35.f );

		// Adds segements for this spline segment into the passed builder
		void AddSegementsToBuilder( struct FSplineBuilder& builder );

		// Can the values be treated as calculated? ie. Valid point data was initialized and have the calculations been run?
		bool IsValid() { return HasInitialized && HasCalculated && StartAngle <= MAX_ANGLE && EndAngle <= MAX_ANGLE; }

		// Inputed radii
		float StartRadius;
		float EndRadius;

		// Inputed Start point Data
		FVector StartPos;
		FVector StartForward;
		FVector StartRight;

		// Inputed End point Data
		FVector EndPos;
		FVector EndForward;
		FVector EndRight;

		// Tangent and exit Data
		FVector StartBendTangent;
		FVector StraightTangent;
		FVector EndBendTangent;
		FVector StartBendExit;
		FVector EndBendExit;

		// Magnitude of bend tangents
		float StartTangentMagnitude;
		float EndTangentMagnitude;
		float StraightTangentMagnitude;

		// Calculated from input point values, are the calculations Clockwise?
		bool IsStartCW;
		bool IsEndCW;

		// 1.0f if clockwise, -1.0f if counter-clockwise
		float StartCW;
		float EndCW;

		// Calculated Circles
		FVector StartCircle;
		FVector EndCircle;

		// Calculated start and end angles for inputed point data
		float StartAngle;
		float EndAngle;
		// Tracking bools to ensure we are operating on valid data
		bool HasInitialized;
		bool HasCalculated;
		bool HasOverlapError;

		// Stored actor reference for drawing debug visuals. Not UProperty as this will only exist for the duration of on draw update.
		AActor* DebugActor;

		// Maximum angle to allow for bends. If a calculated angle exceeds this, IsValid will return false
		const float MAX_ANGLE = 185.f;
	};

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
		const float clampedAngle = FMath::Clamp( angle, 0.0f, PI*1.1f ); //[DavalliusA:Thu/30-01-2020] increased the max a little here. We should really leave the responsibility to the ones calling.
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
	static bool BuildStraightSpline2D(
		struct FSplineBuilder& builder,
		const FVector& endPos,
		const FVector& endForward,
		float dotTreshold );

	/**
	 * Check if the point between to spline points are straight enough.
	 */
	static bool BuildStraightSpline3D(
		struct FSplineBuilder& builder,
		const FVector& endPos,
		const FVector& endForward,
		float dotTreshold );


	/**
	 * Check if the point between to spline points are straight enough.
	 */
	static bool BuildTangentBasedSpline3D(
		struct FSplineBuilder& builder,
		const FVector& endPos,
		const FVector& endForward,
		float tangetStrength, UWorld* debugWorld = nullptr, FVector debugACtorLocation = FVector::ZeroVector );

	/**
	 * Calculates a spline with straight line which bends only at the start and end.
	 *
	 * @param builder	The spline builder to append to, this must have at least on point in it already.
	 * @param startRadius,endRadius	 Radius of the start and end bend.
	 * @param endPos		Where to end the spline.
	 * @param endForward	Where the end tangent is facing.
	 */
	static bool BuildBendStraightBendSpline3D(
		struct FSplineBuilder& builder,
		float startRadius,
		float endRadius,
		const FVector& endPos,
		const FVector& endForward, UWorld* debugWorld = nullptr, FVector debugACtorLocation = FVector::ZeroVector);


	static bool BuildBendStraightBendSpline2D(
		struct FSplineBuilder& builder,
		float startRadius,
		float endRadius,
		const FVector& endPos,
		const FVector& endForward );

	/**
	* Calculates a spline which consists of a 3 defining points, moving first horizontally, then pure vertical (straight up), and finally horizontal to the end point
	*
	* @param builder			The spline builder to append to, this must have at least on point already
	* @param startRadius		The start radius bend
	* @param internalRadius		The radius of bends for any internal bends ( between start and end )
	* @param endRadius			The end radius bend
	* @param endPos				Vector post of the end point in world space
	* @param endForward			The forward at the final point
	* @param horizontalFirst	Specify if the curve from the start point moves horizontally first or vertically first
	*/
	static bool BuildBendHorizontalBendVerticalBendDefinedSpline(
		struct FSplineBuilder& builder,
		float startRadius,
		float internalRadii,
		float endRadius,
		const FVector& endPos,
		const FVector& endForward,
		bool horizontalFirst = true,
		AActor* debugActor = nullptr );

	/**
	* Creates a spline from passed in hologram pathing data
	*
	* @param  pathNodes - Array of all path nodes returned from pathing AStar
	*/
	static bool BuildPathDataDefinedSpline(
		struct FSplineBuilder& builder,
		TArray< struct FHologramAStarNode >& pathNodes,
		float internalRadii,
		const FVector& startNormal,
		const FVector& endNormal,
		AActor* owner );


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

	/** Calculates an optimal magnitude for a straight line between the points. */
	static float CalcStraightTangentMagnitude( const FVector& startPos, const FVector& endPos, float targetTangetFactor = 1.0f );

private:
	/** Internal helpers for building routing the splines. */
	static void CalcBendDirections3D(
		const FVector& startPos,
		const FVector& startForward,
		float startRadius,
		const FVector& endPos,
		const FVector& endForward,
		float endRadius,
		bool& out_isStartCW,
		bool& out_isEndCW );
	static void CalcBendDirections2D(
		const FVector& startPos,
		const FVector& startForward,
		float startRadius,
		const FVector& endPos,
		const FVector& endForward,
		float endRadius,
		bool& out_isStartCW,
		bool& out_isEndCW );

	static void CalcBendAngles3D(
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

	static void CalcBendAngles2D(
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

public:
	FORCEINLINE ~FSplineUtils() = default;
};

/**
 * Small util for building splines.
 */
struct FACTORYGAME_API FSplineBuilder
{
	FSplineBuilder( TArray< FSplinePointData >& out_points ) : SplineData( out_points ) {}

	/**
	 * Begin with calling Start, this clears the points array and sets up the first point.
	 */
	void Start( const FVector& pos, const FVector& tan );

	/**
	 * Append a segment to the spline.
	 */
	void AddSegment( const FVector& pos, const FVector& tan );

	/**
	 * Append a segment to the spline at the given index 
	 */
	void InsertSegmentAfterIndex( const FVector& pos, const FVector& tan, int32 index );

	/**
	 * Modify the last placed segment.
	 */
	void ModifySegment( const FVector& pos, const FVector& tan );

	/**
	 * Modify the placed segment with the given index (needs at  lest a start and a segment added before)
	 */
	void ModifySegment( const FVector& pos, const FVector& tan, int32 index );

	bool IsValidIndex( int32 index );

	FSplinePointData& GetSegmentRef( int32 index ){ return SplineData[ index ]; }

	void RemoveSegment( int32 index );
public:
	TArray< FSplinePointData >& SplineData;

public:
	FORCEINLINE ~FSplineBuilder() = default;
};


/**
* Struct for holding Grid Cell data. Each points location and all of its connections
* Each AStar node will have one of these to define it
*/
struct FACTORYGAME_API FHologramPathingPoint
{
	FHologramPathingPoint();
	FHologramPathingPoint( FVector worldLocation, FVector gridIndex, struct FHologramPathingGrid* grid );

	// This point in world space
	FVector WorldLocation;

	// WorldLocation used for comparisons to avoid floating point errors
	// This may not be needed, but Id rather be cautionary than try to solve why path finding is returning borked results because of floats
	FIntVector IntWorldLocation;

	// Does this point overlap (its bounds) with any obstructing object? This is used to mark a point as traversal disallowed
	bool IsColliding;

	/** This points grid index */
	FVector GridIndex;

	/** Reference to the grid this point resides in */
	struct FHologramPathingGrid* Grid;

	/** Array of connecting Grid Indexes */
	TArray< FHologramPathingPoint* > Connections;

public:
	FORCEINLINE ~FHologramPathingPoint() = default;
};

/*************************************************************************
* AStar pathing for smart hologram placement
*/


// @todo - There are unused / unnecessary variables in here that come from changing the way the pathing system works so it could use a clean up pass
struct FACTORYGAME_API FHologramPathingGrid
{
	/** Default Constructor */
	FHologramPathingGrid();

	/** Constructor taking a start and end location in world space to construct the grid around
	*	@param startForward - Forward to use to construct grid transform
	*	@param startRight - Right to use to construct grid transform
	*	@param endForward - Forward of the target ( second ) point
	*	@param startLocation - Dragging conveyor from location
	*	@param endLocation - Dragging Conveyor to location
	*	@param gridCellSize - size in world space of one grid cell
	*/
	FHologramPathingGrid( const FVector& startForward, const FVector& startRight, const FVector& startLocation, const FVector& endLocation, int32 gridCellSize, class AFGHologram* hologramOwner );

public:
	/** Creates all Grid Node points */
	void InitializeGridPoints();

	/** Perform actual path find from start point to end point */
	EHologramGraphAStarResult GetHologramPath( const FVector& startLocation, const FVector& endLocation, const FVector& endNormal, TArray< struct FHologramAStarNode >& out_pathNodes );

	/** Run a collision check for all grid spaces to see if they are valid or if they overlap with collision */
	void CalculateGridNodeCollision();

	FVector GetWorldSpaceOfGridIndex( const FVector& gridIndex );

	FHologramPathingPoint& GetPathPointForWorldLocation( const FVector& worldLocation );

	bool IsValidGridIndex( const FVector& index );

	/** Static helper for determining if two points in world space and their forward vectors 
	*	can be used to generate a path finding grid. The normals dot products must be 0,1, or -1 ( perpendicular or parallel )
	*/
	static bool CanConstructGridFrom( const FVector& locationOne, const FVector& locationTwo, const FVector& forwardOne, const FVector& forwardTwo );


public:
	/** Grid size for path finding. Uses the same size as the snap grid but putting it here for clarity as well */
	static const int32 PATH_GRID_CELL_SIZE = 100;

	/** Helper constexpr to get half cell size */
	static constexpr float HALF_PATH_GRID_CELL_SIZE = PATH_GRID_CELL_SIZE * 0.5f;

	/** Tolerance to allow differing location component values between start and end points to be acceptable for grid construction */
	static const int32 MAX_LOCATION_VARIANCE = 2;

	/** Transform for the grid layout */
	FTransform GridTransform;

	/** Hologram reference owning this grid */
	AFGHologram* HologramOwner;

	/** World reference ( used for collision queries and debug drawing )*/
	UWorld* WorldRef;

	/** World Location of the Grid Center */
	FVector GridCenterLocation;

	/** World Location of the 0,0,0 grid cell (Bottom left) */
	/*	N = Number of Cells. With a center (C) at N/2 + 1 ( Odd cell count is enforced )

			Z[0,0,N]
				^	   Y[0,N,0]
				|    _/ 
				|  _/  C[N/2, N/2, N/2]
				|_/_________>
			O[0,0,0]		  X[N,0,0]      
	*/
	FVector GridOriginIndex;

	/** Grid bounds extent */
	FVector GridBoundsExtent;

	/** Dimensions of the grid */
	FVector GridDimensions;

	/** World space size of each individual cube making up the AStar grid space */
	//@todo - This is redundant, because of the fixed nature of this system this is a constant PATH_GRID_CELL_SIZE. Remove all instances of this and replace
	int32 GridCellSize;

	/** Allow Diagonal horizontal traversal through nodes? */
	bool AllowDiagonalHorizontal;

	/** Start attach point normal in world space */
	FVector StartPointNormal;

	/** End attach point normal in world space*/
	FVector EndPointNormal;

	/** Grid Index of start node */
	FVector StartIndex;

	/** Grid Index of end node */
	FVector EndIndex;

	/** 3D array or all points comprising this grid */
	TArray< TArray < TArray < struct FHologramPathingPoint > > > GridNodes;

	/** Used for drawing debug visuals */
	AActor* DebugActor;

	/** Grid Origin offset ( Translation from Center to grid location (0,0,0) */
	FVector GridTranslationOffset;


public:
	FORCEINLINE ~FHologramPathingGrid() = default;
};

/**
* Nodes comprising the 3D grid used for the A* pathfinding
*/
struct FACTORYGAME_API FHologramAStarNode
{
	// FHologramAStarNode( ); // MODDING EDIT: ambiguous call to overloaded function (This diagnostic occurred in the compiler generated function 'void FHologramAStarNode::__dflt_ctor_closure(void)')

	/** Default Constructor */
	FHologramAStarNode( int32 unused = INDEX_NONE );

	/** Constructor with grid point
	*	@param pathingPoint - The pathing point this astar node represents
	*/
	FHologramAStarNode( FHologramPathingPoint* pathingPoint );

	/** Constructor with A* node - Utilized and needed for copy construction called from GraphAStar
	*	@param pathingNode - A* pathing node to copy
	*/
	FHologramAStarNode( const FHologramAStarNode& pathingNode );

	/** Node Comparisons */
	FORCEINLINE friend bool operator==( const FHologramAStarNode& nodeA, const FHologramAStarNode& nodeB )
	{
		// If one is null, then just compare the pointers. 
		// Nullptrs are equal by C++ standards, so our nodes should be as well. otherwise, not equal. 
		if( nodeA.HologramPathingPoint == nullptr || nodeB.HologramPathingPoint == nullptr )
		{
			return nodeA.HologramPathingPoint == nodeB.HologramPathingPoint;
		}

		// Both are valid, they are considered equal if they have the same WorldSpace Location
		// @todo - This may have issues with floating point errors, 
		return nodeA.HologramPathingPoint->WorldLocation == nodeB.HologramPathingPoint->WorldLocation;
	}

	FORCEINLINE friend bool operator!=( const FHologramAStarNode& nodeA, const FHologramAStarNode& nodeB )
	{
		// If one is null, then just compare the pointers. 
		// Nullptrs are equal by C++ standards, so our nodes should be as well. otherwise, not equal. 
		if( nodeA.HologramPathingPoint == nullptr || nodeB.HologramPathingPoint == nullptr )
		{
			return nodeA.HologramPathingPoint != nodeB.HologramPathingPoint;
		}

		// Both are valid, they are considered !equal if they don't have the same WorldSpace Location
		return nodeA.HologramPathingPoint->WorldLocation != nodeB.HologramPathingPoint->WorldLocation;
	}

	/** Provide hashing for this type so it can be used as a key in TMap. */
	friend inline uint32 GetTypeHash( const FHologramAStarNode& node )
	{
		uint32 Hash = 0;
		Hash = HashCombine( Hash, GetTypeHash( node.HologramPathingPoint->WorldLocation ) );
		return Hash;
	}

public:
	/**
	* Reference to the pathing point that resides in a Hologram pathing grid
	*/
	FHologramPathingPoint* HologramPathingPoint;

public:
	FORCEINLINE ~FHologramAStarNode() = default;
};

/**
* Implemented as specified in Epic's GraphAStar.h
* Hence the spelling of "Neighbour". What did an English guy write all your code epic?
*/
struct FACTORYGAME_API FHolgramAStarHelper
{
	typedef FHologramAStarNode FNodeRef;

	/**
	* @return number of neighbours the NodeRef has
	*/
	int32 GetNeighbourCount( const FHologramAStarNode& nodeRef ) const;

	/**
	* @return is this a valid node reference?
	*/
	bool IsValidRef( const FHologramAStarNode& nodeRef ) const;

	/**
	* @return neighbour reference
	*/
	FHologramAStarNode GetNeighbour( const FHologramAStarNode& nodeRef, const int32 neighbourIndex ) const;

	/**
	* @return the normal of the direction between the two nodeRefs
	*/
	FVector GetDirectionNormal( const FHologramAStarNode& nodeA, const FHologramAStarNode& nodeB ) const;

public:
	FORCEINLINE ~FHolgramAStarHelper() = default;
};

/**
* Evaluation filter for the pathfinding algorithm.
* @todo - Heuristic and core graph code need another implementation and fairly large clean up pass. But now that I know its MOSTLY working 
*		It should definitely be done since this seems to be a good way to go for some situations.
*/
struct FACTORYGAME_API FHologramAStarFilter
{
	FHologramAStarFilter();

	/** Used as GetHeuristicCost's multiplier. */
	float GetHeuristicScale() const;

	/** Estimate of cost from startNodeRef to endNodeRef. */
	float GetHeuristicCost( const FHologramAStarNode& startNodeRef, const FHologramAStarNode& endNodeRef ) const;

	/** Get the cost for a considered move based on the previous move direction and the considered move
	*	@return value on the range from 0.f to 1.f
	*
	*	@todo - This should be moved out of its own function call along with refactoring the AStarGraph which atm is mostly just copied from
	*			Epics implementation. Instead the HologramAStarGraph should treat this as part of the heuristic with out special case calling
	*/
	float GetDirectionChangeCost( const FVector& parentNormal, const FVector& establishedNormal, const FVector& consideredNormal ) const;

	/** Real cost of traveling from startNodeRef directly to endNodeRef */
	float GetTraversalCost( const FHologramAStarNode& startNodeRef, const FHologramAStarNode& endNodeRef ) const;

	/** Whether traversing given edge is allowed. */
	bool IsTraversalAllowed( const FHologramAStarNode& nodeA, const FHologramAStarNode& nodeB ) const;

	/** Whether to accept solutions that do not reach the goal. */
	bool WantsPartialSolution() const;

public:
	/** true if a partial solution is valid; false if we only want a path if the goal is reachable. */
	bool AcceptsPartialSolution;

public:
	FORCEINLINE ~FHologramAStarFilter() = default;
};

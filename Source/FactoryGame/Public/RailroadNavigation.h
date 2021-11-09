// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "GraphAStar.h"
#include "RailroadNavigation.generated.h"

class UFGRailroadTrackConnectionComponent;
class AFGLocomotive;
class AFGBuildableRailroadStation;

/** Pathfinding result. */
UENUM()
enum class ERailroadPathFindingResult : uint8
{
	RPFR_Error = 0			UMETA( DisplayName = "Error" ),
	RPFR_Unreachable = 1	UMETA( DisplayName = "Unreachable" ),
	RPFR_Success = 2		UMETA( DisplayName = "Success" )
};

struct FACTORYGAME_API FRailroadPathPoint
{
public:
	/** The track connection to pass through or stop at if this is a station, switch, signal etc. */
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > TrackConnection = nullptr;

	/** The distance this object is from the end. 0 for the last point. */
	float Distance = 0.f;
};

/**
 * A navigation path used by the trains to get to a destination.
 */
struct FACTORYGAME_API FRailroadPath
{
	/** Path points to follow to the destination. */
	TArray< FRailroadPathPoint > PathPoints;
};

typedef TSharedPtr< struct FRailroadPath > FRailroadPathSharedPtr;
typedef TWeakPtr< struct FRailroadPath > FRailroadPathWeakPtr;

/**
 * A navigation result.
 */
struct FACTORYGAME_API FRailroadPathFindingResult
{
public:
	TWeakObjectPtr< AFGLocomotive > Locomotive = nullptr;
	TWeakObjectPtr< UFGRailroadTrackConnectionComponent > Goal = nullptr;

	/** Shared pointer to the path. */
	FRailroadPathSharedPtr Path = nullptr;

	/** Is the path valid, partial or invalid. */
	ERailroadPathFindingResult Result = ERailroadPathFindingResult::RPFR_Error;
};

/**
 * A path point along a trains route.
 */
struct FACTORYGAME_API FRailroadGraphAStarPathPoint
{
	/** Default constructor, epic passes INDEX_NONE when creating a "null" point. */
	FRailroadGraphAStarPathPoint( int32 unused = INDEX_NONE );
	FRailroadGraphAStarPathPoint( UFGRailroadTrackConnectionComponent* connection );
	FRailroadGraphAStarPathPoint( UFGRailroadTrackConnectionComponent* connection, bool ignoredStart );
	FRailroadGraphAStarPathPoint( const FRailroadGraphAStarPathPoint& point );
	
	/** Compare two nodes. */
	FORCEINLINE friend bool operator==( const FRailroadGraphAStarPathPoint& nodeA, const FRailroadGraphAStarPathPoint& nodeB )
	{
		return nodeA.TrackConnection == nodeB.TrackConnection && nodeA.IgnoredStart == nodeB.IgnoredStart;
	}
	FORCEINLINE friend bool operator!=( const FRailroadGraphAStarPathPoint& nodeA, const FRailroadGraphAStarPathPoint& nodeB )
	{
		return !( nodeA == nodeB );
	}

	/** Provide hashing for this type so it can be used as a key in TMap. */
	friend inline uint32 GetTypeHash( const FRailroadGraphAStarPathPoint& point )
	{
		uint32 Hash = 0;
		Hash = HashCombine( Hash, GetTypeHash( point.TrackConnection ) );
		return Hash;
	}

public:
	/** When navigating though a rail network, we only need to know the next connection to go to. */
	UFGRailroadTrackConnectionComponent* TrackConnection;

	/** This will ensure that this start does not match the end. */
	bool IgnoredStart;
};

/**
 * @see FGraphAStar
 */
struct FACTORYGAME_API FRailroadGraphAStarHelper
{
	typedef FRailroadGraphAStarPathPoint FNodeRef;

	/** @return number of neighbours that the graph node identified with nodeRef has. */
	int32 GetNeighbourCount( const FRailroadGraphAStarPathPoint& nodeRef ) const;
	
	/** @return whether given node identification is correct. */
	bool IsValidRef( const FRailroadGraphAStarPathPoint& nodeRef ) const;
	
	/** @return neighbour ref. */
	FRailroadGraphAStarPathPoint GetNeighbour( const FRailroadGraphAStarPathPoint& nodeRef, const int32 neighbourIndex ) const;
};

/**
 * Evaluation filter for the pathfinding algorithm.
 */
struct FACTORYGAME_API FRailroadGraphAStarFilter
{
public:
	FRailroadGraphAStarFilter();

	/** Used as GetHeuristicCost's multiplier. */
	float GetHeuristicScale() const;

	/** Estimate of cost from startNodeRef to endNodeRef. */
	float GetHeuristicCost( const FRailroadGraphAStarPathPoint& startNodeRef, const FRailroadGraphAStarPathPoint& endNodeRef ) const;

	/** Real cost of traveling from startNodeRef directly to endNodeRef */
	float GetTraversalCost( const FRailroadGraphAStarPathPoint& startNodeRef, const FRailroadGraphAStarPathPoint& endNodeRef ) const;

	/** Whether traversing given edge is allowed. */
	bool IsTraversalAllowed( const FRailroadGraphAStarPathPoint& nodeA, const FRailroadGraphAStarPathPoint& nodeB ) const;

	/** Whether to accept solutions that do not reach the goal. */
	bool WantsPartialSolution() const;

public:
	/** true if a partial solution is valid; false if we only want a path if the goal is reachable. */
	bool AcceptsPartialSolution;

	/** true if we want to ignore signals when pathing. */
	bool IgnoreSignals;
};

/** Collection of navigation functions */
struct FACTORYGAME_API FRailroadNavigation
{
public:
	/**
	 * Finds a path for the given locomotive to the given stop.
	 *
	 * @param locomotive	The locomotive to find a path for, note that a locomotive can not reverse.
	 * @param station		The station the train should find a path to.
	 * @param filter		Filter to use for the path evaluation, this contains parameters that affect the path chosen.
	 *
	 * @return Result of the pathfinding; Status code indicate if a path was found or not or if an error occured, e.g. bad params.
	 */
	static FRailroadPathFindingResult FindPathSync(
		AFGLocomotive* locomotive,
		AFGBuildableRailroadStation* station,
		FRailroadGraphAStarFilter filter = FRailroadGraphAStarFilter() );

private:
	/**
	 * Finds a path from one railroad connection to another.
	 *
	 * @param start				Next connection ahead of us.
	 * @param end				Connection we want to path find to.
	 * @param filter			Filter to use for the path evaluation, this contains parameters that affect the path chosen.
	 * @param out_pathPoints	The resulting path, empty on error.
	 *
	 * @return Result of the pathfinding. I.e. if a path was found, goal is unreachable or if an error occurred, e.g. bad params.
	 */
	static EGraphAStarResult FindPathSyncInternal(
		const FRailroadGraphAStarPathPoint& start,
		const FRailroadGraphAStarPathPoint& end,
		FRailroadGraphAStarFilter filter,
		TArray< FRailroadGraphAStarPathPoint >& out_pathPoints );
};

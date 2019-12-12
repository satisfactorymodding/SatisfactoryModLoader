// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"
#include "UObject/Class.h"

#include "FactoryGame.h"
#include "Buildables/FGBuildableRailroadTrack.h"
#include "RailroadNavigation.generated.h"


/** Pathfinding result. */
UENUM()
enum class ERailroadPathFindingResult : uint8
{
	RNQR_Error = 0			UMETA( DisplayName = "Error" ),
	RNQR_Unreachable = 1	UMETA( DisplayName = "Unreachable" ),
	RNQR_Success = 2		UMETA( DisplayName = "Success" )
};

USTRUCT(BlueprintType)
struct FRailroadPathPoint
{
	GENERATED_BODY()
public:
	/** Ctor */
	FRailroadPathPoint();

public:
	/**
	 * Object along the path, may be a connection, switch, stop, signal, sign etc.
	 * Must implement IFGRailroadInterface.
	 */
	UPROPERTY( BlueprintReadOnly )
	UObject* Object; //@todo This is UPROPERTY but I've gotten a dynamic cast crash from blueprint on this...

	/** The distance this object is from the end. 0 for the last point. */
	UPROPERTY( BlueprintReadOnly )
	float Distance;
};

/**
 * A navigation path used by the trains to get to a destination.
 */
struct FRailroadPath
{
	/** Path points to follow to the destination. */
	TArray< FRailroadPathPoint > PathPoints;
};

typedef TSharedPtr< struct FRailroadPath > FRailroadPathSharedPtr;
typedef TWeakPtr< struct FRailroadPath > FRailroadPathWeakPtr;

/**
 * A navigation result.
 */
USTRUCT(BlueprintType)
struct FRailroadPathFindingResult
{
	GENERATED_BODY()
public:
	/** Ctor */
	FRailroadPathFindingResult();

public:
	/** Shared pointer to the path. */
	FRailroadPathSharedPtr Path;

	/** Is the path valid, partial or invalid. */
	UPROPERTY( BlueprintReadOnly )
	ERailroadPathFindingResult Result;
};

/**
 * A path point along a trains route.
 */
struct FRailroadGraphAStarPathPoint
{
	/** Default constructor, epic passes INDEX_NONE when creating a "null" point. */
	FRailroadGraphAStarPathPoint( int32 unused = INDEX_NONE );
	FRailroadGraphAStarPathPoint( const FRailroadGraphAStarPathPoint& point );
	
	/** Compare two nodes. */
	FORCEINLINE friend bool operator==( const FRailroadGraphAStarPathPoint& nodeA, const FRailroadGraphAStarPathPoint& nodeB )
	{
		return nodeA.TrackConnection == nodeB.TrackConnection;
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
};

/**
 * @see FGraphAStar
 */
struct FRailroadGraphAStarHelper
{
	typedef FRailroadGraphAStarPathPoint FNodeRef;

	/** @return number of neighbours that the graph node identified with nodeRef has. */
	int32 GetNeighbourCount( const FRailroadGraphAStarPathPoint& nodeRef ) const;
	
	/** @return whether given node identification is correct. */
	bool IsValidRef( const FRailroadGraphAStarPathPoint& nodeRef ) const;
	
	/** @return neighbour ref. */
	FRailroadGraphAStarPathPoint GetNeighbour( const FRailroadGraphAStarPathPoint& nodeRef, const int32 neighbourIndex ) const;

	/**
	 * Helper used when starting up the algorithm, the start and end locations are track positions and this returns the neighbouring path point (track connection).
	 *
	 * @param position Arbitrary location along a track segment.
	 *
	 * @return The next path point on the current track segment given the position and forward direction.
	 *         If position is invalid this returns an invalid path point.
	 */
	FRailroadGraphAStarPathPoint GetNeighbour( const FRailroadTrackPosition& position ) const;
};

/**
 * Evaluation filter for the pathfinding algorithm.
 */
struct FRailroadGraphAStarFilter
{
	/** ctor */
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
};

// Copyright 2016 Coffee Stain Studios. All Rights Reserved.

#pragma once
#include "Array.h"

struct FACTORYGAME_API FHologramGraphAStarDefaultPolicy
{
	static const int32 NodePoolSize = 64;
	static const int32 OpenSetSize = 64;
	static const int32 FatalPathLength = 10000;
	static const bool bReuseNodePoolInSubsequentSearches = true;

public:
	FORCEINLINE ~FHologramGraphAStarDefaultPolicy() = default;
};

enum EHologramGraphAStarResult
{
	HologramSearchFail,
	HologramSearchSuccess,
	HologramGoalUnreachable,
	HologramSearchInfiniteLoop
};

/**
 *	Default A* node class.
 *	Extend this class and pass as a parameter to FHologramGraphAStar for additional functionality
 */
template<typename THologramGraph>
struct FACTORYGAME_API FHologramGraphAStarDefaultNode
{
	typedef typename THologramGraph::FNodeRef FGraphNodeRef;

	const FGraphNodeRef NodeRef;
	FGraphNodeRef ParentRef;
	float TraversalCost;
	float TotalCost;
	int32 SearchNodeIndex;
	int32 ParentNodeIndex;
	uint8 bIsOpened : 1;
	uint8 bIsClosed : 1;

	FHologramGraphAStarDefaultNode( const FGraphNodeRef& InNodeRef )
		: NodeRef( InNodeRef )
		, ParentRef( INDEX_NONE )
		, TraversalCost( FLT_MAX )
		, TotalCost( FLT_MAX )
		, SearchNodeIndex( INDEX_NONE )
		, ParentNodeIndex( INDEX_NONE )
		, bIsOpened( false )
		, bIsClosed( false )
	{}

	FORCEINLINE void MarkOpened() { bIsOpened = true; }
	FORCEINLINE void MarkNotOpened() { bIsOpened = false; }
	FORCEINLINE void MarkClosed() { bIsClosed = true; }
	FORCEINLINE void MarkNotClosed() { bIsClosed = false; }
	FORCEINLINE bool IsOpened() const { return bIsOpened; }
	FORCEINLINE bool IsClosed() const { return bIsClosed; }

public:
	FORCEINLINE ~FHologramGraphAStarDefaultNode() = default;
};

/**
 *	Generic graph A* implementation
 *
 *	THologramGraph holds graph representation. Needs to implement functions:
 *		int32 GetNeighbourCount(FNodeRef NodeRef) const;										- returns number of neighbours that the graph node identified with NodeRef has
 *		bool IsValidRef(FNodeRef NodeRef) const;												- returns whether given node identyfication is correct
 *      FNodeRef GetNeighbour(const FNodeRef NodeRef, const int32 NeighbourIndex) const;		- returns neighbour ref
 *
 *	it also needs to specify node type
 *		FNodeRef		- type used as identification of nodes in the graph
 *
 *	TQueryFilter (FindPath's parameter) filter class is what decides which graph edges can be used and at what cost. It needs to implement following functions:
 *		float GetHeuristicScale() const;														- used as GetHeuristicCost's multiplier
 *		float GetHeuristicCost(const FNodeRef StartNodeRef, const FNodeRef EndNodeRef) const;	- estimate of cost from StartNodeRef to EndNodeRef
 *		float GetTraversalCost(const FNodeRef StartNodeRef, const FNodeRef EndNodeRef) const;	- real cost of traveling from StartNodeRef directly to EndNodeRef
 *		bool IsTraversalAllowed(const FNodeRef NodeA, const FNodeRef NodeB) const;				- whether traversing given edge is allowed
 *		bool WantsPartialSolution() const;														- whether to accept solutions that do not reach the goal
 *
 */



template<typename THologramGraph, typename Policy = FHologramGraphAStarDefaultPolicy, typename TSearchNode = FHologramGraphAStarDefaultNode<THologramGraph> >
struct FACTORYGAME_API FHologramGraphAStar
{
	typedef typename THologramGraph::FNodeRef FGraphNodeRef;
	typedef TSearchNode FSearchNode;

	struct FNodeSorter
	{
		const TArray<FSearchNode>& NodePool;

		FNodeSorter( const TArray<FSearchNode>& InNodePool )
			: NodePool( InNodePool )
		{}

		bool operator()( const int32 A, const int32 B ) const
		{
			return NodePool[ A ].TotalCost < NodePool[ B ].TotalCost;
		}
	};

	struct FNodePool : TArray<FSearchNode>
	{
		typedef TArray<FSearchNode> Super;
		TMap<FGraphNodeRef, int32> NodeMap;

		FNodePool()
			: Super()
		{
			Super::Reserve( Policy::NodePoolSize );
		}

		FORCEINLINE FSearchNode& Add( const FSearchNode& SearchNode )
		{
			const int32 Index = TArray<FSearchNode>::Add( SearchNode );
			NodeMap.Add( SearchNode.NodeRef, Index );
			FSearchNode& NewNode = ( *this )[ Index ];
			NewNode.SearchNodeIndex = Index;
			return NewNode;
		}

		FORCEINLINE FSearchNode& FindOrAdd( const FGraphNodeRef NodeRef )
		{
			const int32* IndexPtr = NodeMap.Find( NodeRef );
			return IndexPtr ? ( *this )[ *IndexPtr ] : Add( NodeRef );
		}

		UE_DEPRECATED( 4.15, "This function is now deprecated, please use FindOrAdd instead" )
			FSearchNode& Get( const FGraphNodeRef NodeRef )
		{
			return FindOrAdd( NodeRef );
		}

		FORCEINLINE void Reset()
		{
			Super::Reset( Policy::NodePoolSize );
			NodeMap.Reset();
		}

		FORCEINLINE void ReinitNodes()
		{
			for( FSearchNode& Node : *this )
			{
				new ( &Node ) FSearchNode( Node.NodeRef );
			}
		}
	};

	struct FOpenList : TArray<int32>
	{
		typedef TArray<int32> Super;
		TArray<FSearchNode>& NodePool;
		const FNodeSorter& NodeSorter;

		FOpenList( TArray<FSearchNode>& InNodePool, const FNodeSorter& InNodeSorter )
			: NodePool( InNodePool ), NodeSorter( InNodeSorter )
		{
			Super::Reserve( Policy::OpenSetSize );
		}

		void Push( FSearchNode& SearchNode )
		{
			HeapPush( SearchNode.SearchNodeIndex, NodeSorter );
			SearchNode.MarkOpened();
		}

		int32 PopIndex( bool bAllowShrinking = true )
		{
			int32 SearchNodeIndex = INDEX_NONE;
			HeapPop( SearchNodeIndex, NodeSorter, /*bAllowShrinking = */false );
			NodePool[ SearchNodeIndex ].MarkNotOpened();
			return SearchNodeIndex;
		}

		UE_DEPRECATED( 4.15, "This function is now deprecated, please use PopIndex instead" )
			FSearchNode& Pop( bool bAllowShrinking = true )
		{
			const int32 Index = PopIndex( bAllowShrinking );
			return NodePool[ Index ];
		}
	};

	const THologramGraph& Graph;
	FNodePool NodePool;
	FNodeSorter NodeSorter;
	FOpenList OpenList;

	FHologramGraphAStar( const THologramGraph& InGraph )
		: Graph( InGraph ), NodeSorter( FNodeSorter( NodePool ) ), OpenList( FOpenList( NodePool, NodeSorter ) )
	{
		NodePool.Reserve( Policy::NodePoolSize );
	}

	/**
	 * Single run of A* loop: get node from open set and process neighbors
	 * returns true if loop should be continued
	 */
	template<typename TQueryFilter>
	bool ProcessSingleNode( const FGraphNodeRef EndNodeRef, const bool bIsBound, const TQueryFilter& Filter, int32& OutBestNodeIndex, float& OutBestNodeCost )
	{
		// Pop next best node and put it on closed list
		const int32 ConsideredNodeIndex = OpenList.PopIndex();
		FSearchNode& ConsideredNodeUnsafe = NodePool[ ConsideredNodeIndex ];
		ConsideredNodeUnsafe.MarkClosed();

		// We're there, store and move to result composition
		if( bIsBound && ( ConsideredNodeUnsafe.NodeRef == EndNodeRef ) )
		{
			OutBestNodeIndex = ConsideredNodeUnsafe.SearchNodeIndex;
			OutBestNodeCost = 0.f;
			return false;
		}

		const float HeuristicScale = Filter.GetHeuristicScale();

		// consider every neighbor of BestNode
		const int32 NeighbourCount = Graph.GetNeighbourCount( ConsideredNodeUnsafe.NodeRef );
		for( int32 NeighbourNodeIndex = 0; NeighbourNodeIndex < NeighbourCount; ++NeighbourNodeIndex )
		{
			const FGraphNodeRef NeighbourRef = Graph.GetNeighbour( NodePool[ ConsideredNodeIndex ].NodeRef, NeighbourNodeIndex );

			// validate and sanitize
			if( Graph.IsValidRef( NeighbourRef ) == false
				|| NeighbourRef == NodePool[ ConsideredNodeIndex ].ParentRef
				|| NeighbourRef == NodePool[ ConsideredNodeIndex ].NodeRef
				|| Filter.IsTraversalAllowed( NodePool[ ConsideredNodeIndex ].NodeRef, NeighbourRef ) == false )
			{
				continue;
			}

			FSearchNode& NeighbourNode = NodePool.FindOrAdd( NeighbourRef );

			// Calculate cost and heuristic.
			const float NewTraversalCost = Filter.GetTraversalCost( NodePool[ ConsideredNodeIndex ].NodeRef, NeighbourNode.NodeRef ) + NodePool[ ConsideredNodeIndex ].TraversalCost;
			const float NewHeuristicCost = bIsBound && ( NeighbourNode.NodeRef != EndNodeRef )
				? ( Filter.GetHeuristicCost( NeighbourNode.NodeRef, EndNodeRef ) * HeuristicScale )
				: 0.f;
			float NewTotalCost = NewTraversalCost + NewHeuristicCost;

			// New to the Hologram version. Adds an additional penalty for changing directions
			// Also adds a penalty for attempting to turn if we have turned in the last 2 nodes
			if( Graph.IsValidRef( NodePool[ ConsideredNodeIndex ].ParentRef ) )
			{
				FVector parentNormal = FVector::ZeroVector;

				FSearchNode& nodeParent = NodePool[ NodePool[ ConsideredNodeIndex ].ParentNodeIndex ];
				if( Graph.IsValidRef( nodeParent.ParentRef ) )
				{
					FSearchNode& nodeGrandParent = NodePool[ nodeParent.ParentNodeIndex ];
					parentNormal = Graph.GetDirectionNormal( nodeParent.NodeRef, nodeGrandParent.NodeRef );
				}
				FVector establishedNormal = Graph.GetDirectionNormal( NodePool[ ConsideredNodeIndex ].ParentRef, NodePool[ ConsideredNodeIndex ].NodeRef );
				FVector consideredNormal = Graph.GetDirectionNormal( NodePool[ ConsideredNodeIndex ].NodeRef, NeighbourNode.NodeRef );

				float directionChangeCost = Filter.GetDirectionChangeCost( parentNormal, establishedNormal, consideredNormal );
				NewTotalCost += ( directionChangeCost * NodePool[ ConsideredNodeIndex ].TraversalCost );
			}

			// check if this is better then the potential previous approach
			if( NewTotalCost >= NeighbourNode.TotalCost )
			{
				// if not, skip
				continue;
			}

			// fill in
			NeighbourNode.TraversalCost = NewTraversalCost;
			ensure( NewTraversalCost > 0 );

			NeighbourNode.TotalCost = NewTotalCost;
			NeighbourNode.ParentRef = NodePool[ ConsideredNodeIndex ].NodeRef;
			NeighbourNode.ParentNodeIndex = NodePool[ ConsideredNodeIndex ].SearchNodeIndex;
			NeighbourNode.MarkNotClosed();

			if( NeighbourNode.IsOpened() == false )
			{
				OpenList.Push( NeighbourNode );
			}

			// In case there's no path let's store information on
			// "closest to goal" node
			// using Heuristic cost here rather than Traversal or Total cost
			// since this is what we'll care about if there's no solution - this node 
			// will be the one estimated-closest to the goal
			if( NewHeuristicCost < OutBestNodeCost )
			{
				OutBestNodeCost = NewHeuristicCost;
				OutBestNodeIndex = NeighbourNode.SearchNodeIndex;
			}
		}

		return true;
	}

	/**
	 *	Performs the actual search.
	 *	@param [OUT] OutPath - on successful search contains a sequence of graph nodes representing
	 *		solution optimal within given constraints
	 */
	template<typename TQueryFilter>
	EHologramGraphAStarResult FindPath( const FGraphNodeRef StartNodeRef, const FGraphNodeRef EndNodeRef, const TQueryFilter& Filter, TArray<FGraphNodeRef>& OutPath )
	{
		if( !( Graph.IsValidRef( StartNodeRef ) && Graph.IsValidRef( EndNodeRef ) ) )
		{
			return HologramSearchFail;
		}

		if( StartNodeRef == EndNodeRef )
		{
			return HologramSearchSuccess;
		}

		if( Policy::bReuseNodePoolInSubsequentSearches )
		{
			NodePool.ReinitNodes();
		}
		else
		{
			NodePool.Reset();
		}
		OpenList.Reset();

		// kick off the search with the first node
		FSearchNode& StartNode = NodePool.Add( FSearchNode( StartNodeRef ) );
		StartNode.TraversalCost = 0;
		StartNode.TotalCost = Filter.GetHeuristicCost( StartNodeRef, EndNodeRef ) * Filter.GetHeuristicScale();

		OpenList.Push( StartNode );

		int32 BestNodeIndex = StartNode.SearchNodeIndex;
		float BestNodeCost = StartNode.TotalCost;

		EHologramGraphAStarResult Result = EHologramGraphAStarResult::HologramSearchSuccess;
		const bool bIsBound = true;

		bool bProcessNodes = true;
		while( OpenList.Num() > 0 && bProcessNodes )
		{
			bProcessNodes = ProcessSingleNode( EndNodeRef, bIsBound, Filter, BestNodeIndex, BestNodeCost );
		}

		// check if we've reached the goal
		if( BestNodeCost != 0.f )
		{
			Result = EHologramGraphAStarResult::HologramGoalUnreachable;
		}

		// no point to waste perf creating the path if querier doesn't want it
		if( Result == EHologramGraphAStarResult::HologramSearchSuccess || Filter.WantsPartialSolution() )
		{
			// store the path. Note that it will be reversed!
			int32 SearchNodeIndex = BestNodeIndex;
			int32 PathLength = 0;
			do
			{
				PathLength++;
				SearchNodeIndex = NodePool[ SearchNodeIndex ].ParentNodeIndex;
			} while( NodePool.IsValidIndex( SearchNodeIndex ) && NodePool[ SearchNodeIndex ].NodeRef != StartNodeRef && ensure( PathLength < Policy::FatalPathLength ) );

			if( PathLength >= Policy::FatalPathLength )
			{
				Result = EHologramGraphAStarResult::HologramSearchInfiniteLoop;
			}

			OutPath.Reset( PathLength );
			OutPath.AddZeroed( PathLength );

			// store the path
			SearchNodeIndex = BestNodeIndex;
			int32 ResultNodeIndex = PathLength - 1;
			do
			{
				OutPath[ ResultNodeIndex-- ] = NodePool[ SearchNodeIndex ].NodeRef;
				SearchNodeIndex = NodePool[ SearchNodeIndex ].ParentNodeIndex;
			} while( ResultNodeIndex >= 0 );
		}

		return Result;
	}

	/** Floods node pool until running out of either free nodes or open set  */
	template<typename TQueryFilter>
	EHologramGraphAStarResult FloodFrom( const FGraphNodeRef StartNodeRef, const TQueryFilter& Filter )
	{
		if( !( Graph.IsValidRef( StartNodeRef ) ) )
		{
			return SearchFail;
		}

		NodePool.Reset();
		OpenList.Reset();

		// kick off the search with the first node
		FSearchNode& StartNode = NodePool.Add( FSearchNode( StartNodeRef ) );
		StartNode.TraversalCost = 0;
		StartNode.TotalCost = 0;

		OpenList.Push( StartNode );

		int32 BestNodeIndex = StartNode.SearchNodeIndex;
		float BestNodeCost = StartNode.TotalCost;

		const FGraphNodeRef FakeEndNodeRef = StartNodeRef;
		const bool bIsBound = false;

		bool bProcessNodes = true;
		while( OpenList.Num() > 0 && bProcessNodes )
		{
			bProcessNodes = ProcessSingleNode( FakeEndNodeRef, bIsBound, Filter, BestNodeIndex, BestNodeCost );
		}

		return EHologramGraphAStarResult::HologramSearchSuccess;
	}

public:
	FORCEINLINE ~FHologramGraphAStar() = default;
};
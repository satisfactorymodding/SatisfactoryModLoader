// Copyright Coffee Stain Studios. All Rights Reserved.

#pragma once

#include "FactoryGame.h"
#include "CoreMinimal.h"
#include "GraphAStar.h"

struct FVehiclePathNavigationNode
{
	FGuid NodeGuid;
	FVector NodeLocation{ForceInit};
	TArray<int32, TInlineAllocator<4>> LeavingConnections;
};
struct FVehiclePathNavigationLink
{
	float TraversalCost{0.0f};
	uint64 VehicleTypeTraversalMask{0};
};

struct FVehiclePathNavigationGraph
{
	using FNodeRef = int32;
	using FGraphAStar = FGraphAStar<FVehiclePathNavigationGraph>;
	using FSearchNode = FGraphAStarDefaultNode<FVehiclePathNavigationGraph>;

	TArray<FVehiclePathNavigationNode> NodeData;
	TMap<TPair<int32, int32>, FVehiclePathNavigationLink> NodeLinks;

	static bool IsValidRef(FNodeRef NodeRef);
	FNodeRef GetNeighbour(const FSearchNode& NodeRef, const int32 NeighbourIndex) const;
	int32 GetNeighbourCount(const FSearchNode& NodeRef) const;

	EGraphAStarResult FindPath( int32 FromNodeIndex, int32 ToNodeIndex, int32 VehicleTypeIndex, bool bWantsPartialSolution, TArray<FGuid>& OutPath ) const;
};

struct FVehiclePathQueryFilter
{
	using FNodeRef = FVehiclePathNavigationGraph::FNodeRef;
	using FSearchNode = FGraphAStarDefaultNode<FVehiclePathNavigationGraph>;

	const FVehiclePathNavigationGraph* OwnerGraph{};
	int32 VehicleTypeIndex{0};
	bool bWantsPartialSolution{false};

	static FVector::FReal GetHeuristicScale();
	FVector::FReal GetHeuristicCost(const FSearchNode& NeighbourNode, const FSearchNode& EndNode) const;
	FVector::FReal GetTraversalCost(const FSearchNode& CurrentNode, const FSearchNode& NeighbourNode) const;
	bool IsTraversalAllowed(FNodeRef CurrentNode, FNodeRef NeighbourNode) const;
	bool WantsPartialSolution() const;
};

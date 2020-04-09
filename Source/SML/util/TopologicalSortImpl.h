#pragma once

#include "TopologicalSort.h"

template<typename T>
SML::TopologicalSort::DirectedGraph<T> reverseGraph(const SML::TopologicalSort::DirectedGraph<T>& graph) {
	SML::TopologicalSort::DirectedGraph<T> result;
	for (const T& node : graph.orderedNodes) {
		result.addNode(node);
	}
	for (const T& from : graph.orderedNodes) {
		for (const T& to : graph.edgesFrom(from)) {
			result.addEdge(to, from);
		}
	}
	return result;
}

template<typename T>
void explore(const T& node, const SML::TopologicalSort::DirectedGraph<T>& graph, TArray<T>& sortedResult, TSet<T>& visitedNodes, TSet<T>& expandedNodes) {
	// Have we been here before?
	if (visitedNodes.Contains(node)) {
		// And have completed this node before
		if (expandedNodes.Contains(node)) {
			// Then we're fine
			return;
		}
		const TSet<T> cycleList = visitedNodes.Difference(expandedNodes);
		throw SML::TopologicalSort::cycle_detected<T>("There was a cycle detected in the input graph, sorting is not possible", node, cycleList);
	}

	// Visit this node
	visitedNodes.Add(node);

	// Recursively explore inbound edges
	for (const T& inbound : graph.edgesFrom(node)) {
		explore(inbound, graph, sortedResult, visitedNodes, expandedNodes);
	}

	// Add ourselves now
	sortedResult.Add(node);
	// And mark ourselves as explored
	expandedNodes.Add(node);
}

template<typename T>
TArray<T> SML::TopologicalSort::topologicalSort(const SML::TopologicalSort::DirectedGraph<T>& graph) {
	DirectedGraph<T> rGraph = reverseGraph(graph);
	TArray<T> sortedResult;
	TSet<T> visitedNodes;
	// A list of "fully explored" nodes. Leftovers in here indicate cycles in the graph
	TSet<T> expandedNodes;
	
	for (const T& node : rGraph.orderedNodes) {
		explore(node, rGraph, sortedResult, visitedNodes, expandedNodes);
	}

	return sortedResult;
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addNode(const T& node) {
	if (graph.Contains(node)) {
		return false;
	}
	orderedNodes.Add(node);
	graph.Add(node, TSet<T>());
	return true;
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addEdge(const T& from, const T& to) {
	if (!(graph.Contains(from) && graph.Contains(to))) {
		return false;
	}
	graph.FindChecked(from).Add(to);
	return true;
}

template<typename T>
void SML::TopologicalSort::DirectedGraph<T>::removeAllReferencesTo(const T& node) {
	for (const T& otherNode : orderedNodes) {
		graph.FindChecked(otherNode).Remove(node);
	}
}

template<typename T>
const TSet<T>& SML::TopologicalSort::DirectedGraph<T>::edgesFrom(const T& node) const {
	return graph.FindChecked(node);
}

template<typename T>
size_t SML::TopologicalSort::DirectedGraph<T>::size() const {
	return orderedNodes.Num();
}

template <typename T>
const TArray<T>& SML::TopologicalSort::DirectedGraph<T>::iterator() {
	return orderedNodes;
}


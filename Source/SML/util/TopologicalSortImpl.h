#pragma once

#include "TopologicalSort.h"

template<typename T>
void reverseGraph(SML::TopologicalSort::DirectedGraph<T>& result, const SML::TopologicalSort::DirectedGraph<T>& graph) {
	/* Add all the nodes from the original graph. */
	for (auto& pair : graph.nodes) {
		const T& nodeValue = pair.Key;
		result.addNode(nodeValue);
	}
	/* Scan over all the edges in the graph, adding their reverse to the
	 * reverse graph.
	 */
	for (auto& pair : graph.nodes) {
		const T& node = pair.Key;
		for (const T& endpoint : graph.edgesFrom(node)) {
			result.addEdge(endpoint, node);
		}
	}
}

template<typename T>
TArray<T> SML::TopologicalSort::topologicalSort(const SML::TopologicalSort::DirectedGraph<T>& graph) {
	SML::TopologicalSort::DirectedGraph<T> gRev;
    reverseGraph(gRev, graph);

	/* Maintain two structures - a set of visited nodes (so that once we've
	 * added a node to the list, we don't label it again), and a list of
	 * nodes that actually holds the topological ordering.
	 */
	TArray<T> result;
	TSet<T> visited;

	/* We'll also maintain a third set consisting of all nodes that have
	 * been fully expanded.  If the graph contains a cycle, then we can
	 * detect this by noting that a node has been explored but not fully
	 * expanded.
	 */
	TSet<T> expanded;

	/* Fire off a DFS from each node in the graph. */
	for (auto& pair : gRev.nodes) {
		const T& node = pair.Key;
		explore(node, gRev, result, visited, expanded);
	}
	/* Hand back the resulting ordering. */
	return result;
}

template<typename T>
void explore(const T& node, const SML::TopologicalSort::DirectedGraph<T>& g, TArray<T>& ordering, TSet<T>& visited, TSet<T>& expanded) {
	/* Check whether we've been here before.  If so, we should stop the
	 * search.
	 */
	if (visited.Find(node) != nullptr) {
		/* There are two cases to consider.  First, if this node has
		 * already been expanded, then it's already been assigned a
		 * position in the final topological sort and we don't need to
		 * explore it again.  However, if it hasn't been expanded, it means
		 * that we've just found a node that is currently being explored,
		 * and therefore is part of a cycle.  In that case, we should report an error.
		 */
		if (expanded.Find(node) != nullptr) return;
		throw SML::TopologicalSort::cycle_detected<T>("Cycle dependency detected in a input graph", node);
	}
	/* Mark that we've been here */
	visited.Add(node);
	/* Recursively explore all of the node's predecessors. */
	const TSet<T>& set = g.edgesFrom(node);
	for (const T& predecessor : set) {
		explore(predecessor, g, ordering, visited, expanded);
	}

	/* Having explored all of the node's predecessors, we can now add this
	 * node to the sorted ordering.
	 */
	ordering.Add(node);

	/* Similarly, mark that this node is done being expanded. */
	expanded.Add(node);
}

template <typename T>
SML::TopologicalSort::DirectedGraph<T>::DirectedGraph() {}

template<typename T>
SML::TopologicalSort::DirectedGraph<T>::~DirectedGraph() {
	//delete all created set pointers there
	for (auto& entry : this->nodes) {
		delete entry.Value;
	}
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addNode(const T& node) {
	if (nodes.Find(node) != nullptr) {
		return false;
	}
	auto adjacentNodes = new TSet<T>();
	this->nodes.Add(node, adjacentNodes);
	return true;
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addEdge(const T& src, const T& dest) {
	if (nodes.Find(src) == nullptr ||
		nodes.Find(dest) == nullptr) {
		return false;
	}
	(*this->nodes.Find(src))->Add(dest);
	return true;
}

template<typename T>
const TSet<T>& SML::TopologicalSort::DirectedGraph<T>::edgesFrom(const T& node) const {
	check(nodes.Find(node) != nullptr);
	return *(*this->nodes.Find(node));
}

template<typename T>
size_t SML::TopologicalSort::DirectedGraph<T>::size() const {
	return this->nodes.Num();
}

template<typename T>
SML::TopologicalSort::DirectedGraph<T>::DirectedGraph(const SML::TopologicalSort::DirectedGraph<T> &src) {
    for (auto& pair : src.nodes) {
        const T& nodeValue = pair.first;
        addNode(nodeValue);
    }
    for (auto& pair : src.nodes) {
        const T& node = pair.first;
        for (const T& endpoint : src.edgesFrom(node)) {
            addEdge(node, endpoint);
        }
    }
}

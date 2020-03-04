#pragma once

#include <vector>

template<typename T>
void reverseGraph(SML::TopologicalSort::DirectedGraph<T>& result, const SML::TopologicalSort::DirectedGraph<T>& graph) {
	/* Add all the nodes from the original graph. */
	for (auto& pair : graph.nodes) {
		const T& nodeValue = pair.first;
		result.addNode(nodeValue);
	}
	/* Scan over all the edges in the graph, adding their reverse to the
	 * reverse graph.
	 */
	for (auto& pair : graph.nodes) {
		const T& node = pair.first;
		for (const T& endpoint : graph.edgesFrom(node)) {
			result.addEdge(endpoint, node);
		}
	}
}

template<typename T>
std::vector<T> SML::TopologicalSort::topologicalSort(const SML::TopologicalSort::DirectedGraph<T>& graph) {
	SML::TopologicalSort::DirectedGraph<T> gRev;
    reverseGraph(gRev, graph);

	/* Maintain two structures - a set of visited nodes (so that once we've
	 * added a node to the list, we don't label it again), and a list of
	 * nodes that actually holds the topological ordering.
	 */
	std::vector<T> result;
	std::unordered_set<T> visited;

	/* We'll also maintain a third set consisting of all nodes that have
	 * been fully expanded.  If the graph contains a cycle, then we can
	 * detect this by noting that a node has been explored but not fully
	 * expanded.
	 */
	std::unordered_set<T> expanded;

	/* Fire off a DFS from each node in the graph. */
	for (auto& pair : gRev.nodes) {
		const T& node = pair.first;
		explore(node, gRev, result, visited, expanded);
	}
	/* Hand back the resulting ordering. */
	return result;
}

template<typename T>
void explore(const T& node, const SML::TopologicalSort::DirectedGraph<T>& g, std::vector<T>& ordering, std::unordered_set<T>& visited, std::unordered_set<T>& expanded) {
	/* Check whether we've been here before.  If so, we should stop the
	 * search.
	 */
	if (visited.find(node) != visited.end()) {
		/* There are two cases to consider.  First, if this node has
		 * already been expanded, then it's already been assigned a
		 * position in the final topological sort and we don't need to
		 * explore it again.  However, if it hasn't been expanded, it means
		 * that we've just found a node that is currently being explored,
		 * and therefore is part of a cycle.  In that case, we should report an error.
		 */
		if (expanded.find(node) != expanded.end()) return;
		throw SML::TopologicalSort::cycle_detected<T>("Cycle dependency detected in a input graph", node);
	}
	/* Mark that we've been here */
	visited.insert(node);
	/* Recursively explore all of the node's predecessors. */
	const std::unordered_set<T>& set = g.edgesFrom(node);
	for (const T& predecessor : set) {
		explore(predecessor, g, ordering, visited, expanded);
	}

	/* Having explored all of the node's predecessors, we can now add this
	 * node to the sorted ordering.
	 */
	ordering.push_back(node);

	/* Similarly, mark that this node is done being expanded. */
	expanded.insert(node);
}

template <typename T>
SML::TopologicalSort::DirectedGraph<T>::DirectedGraph() {}

template<typename T>
SML::TopologicalSort::DirectedGraph<T>::~DirectedGraph() {
	//delete all created set pointers there
	for (auto& entry : this->nodes) {
		delete entry.second;
	}
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addNode(const T& node) {
	if (nodes.find(node) != nodes.end()) {
		return false;
	}
	auto adjacentNodes = new std::unordered_set<T>();
	this->nodes.insert({ node, adjacentNodes });
	return true;
}

template<typename T>
bool SML::TopologicalSort::DirectedGraph<T>::addEdge(const T& src, const T& dest) {
	if (nodes.find(src) == nodes.end() ||
		nodes.find(dest) == nodes.end()) {
		return false;
	}
	this->nodes.find(src)->second->insert(dest);
	return true;
}

template<typename T>
const std::unordered_set<T>& SML::TopologicalSort::DirectedGraph<T>::edgesFrom(const T& node) const {
	if (nodes.find(node) == nodes.end()) {
		//throw std::invalid_argument("src node is not in graph");
		SML::shutdownEngine(TEXT("src node is not in graph"));
	}
	auto fuck = this->nodes.find(node);
	return *fuck->second;
}

template<typename T>
size_t SML::TopologicalSort::DirectedGraph<T>::size() const {
	return this->nodes.size();
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

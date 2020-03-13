#pragma once

#include "CoreTypes.h"
#include <stdexcept>

namespace SML {
	namespace TopologicalSort {

		/**
		* Thrown by topologicalSort when there is a cycle dependency detected in a given graph
		*/
		template<typename T>
		class cycle_detected : public std::logic_error {
		public:
			const T cycleNode;
			const TSet<T> cycleList;

			explicit cycle_detected(const char *message, const T cycleNode, const TSet<T> cycleList)
				: std::logic_error(message),
				  cycleNode(cycleNode),
				  cycleList(cycleList)
			{
			}
		};

		/**
		* Represents simple directional graph of some value type
		* For memory efficiency, graph is represented via adjacent node list
		* Values passed into methods are copied internally
		*/
		template<typename T>
		class DirectedGraph {
		public:
			//use a pointer to the unordered set as value to avoid excessive copying
			TMap<T, TSet<T>> graph;
			TArray<T> orderedNodes;
		public:
			/**
			* Adds node into the graph without any adjacent nodes
			* returns false if specified node already exists in a graph
			* returns true otherwise
			*/
			bool addNode(const T& node);

			/**
			* Adds node adjacent to src into the graph
			* If either of the nodes is not in a graph, throws std::invalid_argument
			*/
			bool addEdge(const T& from, const T& to);

			void removeAllReferencesTo(const T& node);
			
			/**
			* Returns all nodes adjacent to the given one
			* Returned reference is valid as long as the this graph object is valid
			* throws std::invalid_argument if specified node is not in a graph
			*/
			const TSet<T>& edgesFrom(const T& node) const;

			const TArray<T>& iterator();
			
			/**
			* Returns amount of nodes in the graph
			*/
			size_t size() const;
		};

		/**
		* Performs topological sort on the graph
		* Returns a list of sorted elements
		*/
		template<typename T>
		TArray<T> topologicalSort(const DirectedGraph<T>& graph);
	};
};

#include "TopologicalSortImpl.h"
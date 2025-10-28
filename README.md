# Undirected Graph Implementation in C++

A comprehensive C++ implementation of an undirected weighted graph with algorithms for pathfinding and connectivity analysis.

## Overview

This project implements a robust undirected graph data structure that supports various graph operations and algorithms. The graph is constructed from an edge list CSV file and provides efficient methods for querying graph properties and computing optimal paths.

## Features

### Graph Construction
- **CSV-based initialization**: Builds an undirected graph from edge list files where each line follows the format `u,v,w` (representing an edge between nodes `u` and `v` with weight `w`)
- **Automatic edge management**: Maintains bidirectional edges for undirected graph representation
- **Dynamic node tracking**: Automatically identifies and stores all unique nodes from the edge list

### Basic Graph Properties
- `num_nodes()`: Returns the total number of nodes in the graph
- `nodes()`: Retrieves all node labels as an unordered set
- `num_edges()`: Returns the count of undirected edges
- `edge_weight(u, v)`: Queries the weight of an edge between two nodes (returns -1 if no edge exists)
- `num_neighbors(node)`: Returns the number of adjacent nodes
- `neighbors(node)`: Retrieves all neighboring nodes as an unordered set

### Algorithms

#### Dijkstra's Algorithm - Weighted Shortest Path
Computes the shortest weighted path between any two nodes in the graph.
- **Implementation**: Uses a priority queue-based approach for optimal performance
- **Returns**: A vector of tuples `(from_label, to_label, edge_weight)` representing the path
- **Edge cases**: Returns a single self-loop tuple for identical start/end nodes; returns empty vector if no path exists

#### Kruskal's Algorithm - Smallest Connecting Threshold
Finds the minimum edge weight threshold needed to establish connectivity between two nodes.
- **Implementation**: Uses Union-Find (Disjoint Set Union) data structure with path compression and union by rank
- **Use case**: Determines the smallest maximum edge weight required to connect two nodes
- **Returns**: The threshold weight, or -1 if nodes cannot be connected

## Data Structures

- **Graph representation**: Nested unordered maps for O(1) edge lookups
- **Union-Find**: Efficient disjoint set operations for connectivity queries
- **Priority queue**: Min-heap for Dijkstra's algorithm optimization
- **Edge list**: Sorted vector of edges for Kruskal's algorithm

## Technical Details

- **Language**: C++ with STL
- **Key libraries**: `<unordered_map>`, `<unordered_set>`, `<queue>`, `<algorithm>`
- **Time complexity**: 
  - Dijkstra's: O((E + V) log V) where E = edges, V = vertices
  - Kruskal's: O(E log E) for sorting edges
- **Space complexity**: O(V + E) for graph storage

## File Structure

- `Graph.h`: Class declaration with function signatures
- `Graph.cpp`: Complete implementation of all graph operations and algorithms

## Usage Example
```cpp
#include "Graph.h"

// Initialize graph from CSV file
Graph g("edges.csv");

// Query graph properties
unsigned int nodeCount = g.num_nodes();
unsigned int edgeCount = g.num_edges();
int weight = g.edge_weight("A", "B");

// Find shortest path
auto path = g.shortest_path_weighted("A", "D");

// Find smallest connecting threshold
int threshold = g.smallest_connecting_threshold("A", "D");
```

## Input Format

The edge list CSV file should contain one edge per line in the format:
```
node1,node2,weight
```

Example:
```
A,B,1
B,C,2
A,C,5
C,D,1
```

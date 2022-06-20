/**
 * Name: Linh Nguyen
 * Email: lkn001@gmail.com
 * Source: Stepik, lecture slides.
 * 
 * This file is an implementation of undirected graph to find
 * num_nodes(), nodes(), num_edges(), edge_weight(), num_neighbors(),
 * and neighbors(), together with finding a Weighted Shortest Path,
 * and Finding the Smallest Connecting Threshold
 */

#include "Graph.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>   // getline function
#include <tuple>
#include <vector>
#include <unordered_map>
#include <utility>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

/**
 * Initialize a Graph object from a given edge list CSV, where each line
 * `u,v,w` represents an edge between nodes `u` and `v` with weight `w`.
 *
 * @param edgelist_csv_fn The filename of an edge list from which to load
 * the Graph.
 */
Graph::Graph(const string &edgelist_csv_fn) {
    ifstream file(edgelist_csv_fn);
    string line;
    edges_count = 0;
    // read one line from the file
    while(getline(file, line)){
        istringstream ss(line);
        string u, v, w;
        getline(ss, u, ',');
        getline(ss, v, ',');
        getline(ss, w, ',');
        all_nodes.insert(u);
        all_nodes.insert(v);
        // adding weight to the undirected graph
        int weight = stoi(w);
        graph[u][v] = weight;
        graph[v][u] = weight;
        // increase number of edges after every iteration
        edges_count++;
        edges.push_back(make_tuple(weight, u, v));
    }
    /**
     * compare struct to compare the weight of the edges
     * @return the smaller weight
     */                                          
    struct compare{
        bool operator()(tuple<int, string, string> lhs, 
                                tuple<int, string, string> rhs) const{
            return get<0>(lhs) < get<0>(rhs);
        }
    };
    sort(edges.begin(), edges.end(), compare());
}

/**
 * Return the number of nodes in this graph.
 *
 * @return The number of nodes in this graph.
 */
unsigned int Graph::num_nodes() {
    // cout << all_nodes.size() << endl;
    return (unsigned int) all_nodes.size();
}

/**
 * Return a `vector` of node labels of all nodes in this graph.
 *
 * @return A `unordered_set` containing the labels of all nodes in this
 * graph.
 */
unordered_set<string> Graph::nodes() {
    // for(auto node : all_nodes){
    //     cout << node << endl;
    // }
    return all_nodes;
}

/**
 * Return the number of (undirected) edges in this graph.
 *
 * @return The number of (undirected) edges in this graph.
 */
unsigned int Graph::num_edges() {
    return edges_count;
}

/**
 * Return the number of neighbors of a given node.
 *
 * @param node_label The label of the query node.
 * @return The number of neighbors of the node labeled by `node_label`.
 */
unsigned int Graph::num_neighbors(string const &node_label) {
    return graph[node_label].size();
}

/**
 * Return the weight of the edge between a given pair of nodes, or -1 if
 * there does not exist an edge between the pair of nodes.
 *
 * @param u_label The label of the first node.
 * @param v_label The label of the second node.
 * @return The weight of the edge between the nodes labeled by `u_label` and
 * `v_label`, or -1 if there does not exist an edge between the pair of
 * nodes.
 */
int Graph::edge_weight(string const &u_label, string const &v_label) {
    // for(auto weight : graph){
    //     for(auto it : weight.second)
    //     if(u_label == it.first && v_label == it.first){
    //         return it.second;
    //     }
    // }
    // return -1;
    // for(auto weight : graph){
    //     for(auto it : weight.second){
    //         if(u_label == weight.first && v_label == it.first){
    //             //cout << it.second << endl;
    //             return it.second;
    //         }
    //     }
    // }
    if (graph.count(u_label) && graph[u_label].count(v_label))
        return graph[u_label][v_label];
    return -1;
}

/**
 * Return a `unordered_set` containing the labels of the neighbors of a 
 * given node.
 *
 * @param node_label The label of the query node.
 * @return An `unordered_set` containing the labels of the neighbors of the
 * node labeled by `node_label`.
 */
unordered_set<string> Graph::neighbors(string const &node_label) {
    unordered_set<string> neighbor;
    // iterating through graph to access the 
    if (graph.count(node_label)) {
        for(auto it : graph[node_label]){
            neighbor.insert(it.first);
        }
    }
    return neighbor;
}

/**
 * Return the shortest weighted path from a given start node to a given end
 * node as a `vector` of (`from_label`, `to_label`, `edge_weight`) tuples.
 * If there does not exist a path from the start node to the end node,
 * return an empty `vector`.
 *
 * @param start_label The label of the start node.
 * @param end_label The label of the end node.
 * @return The shortest weighted path from the node labeled by `start_label`
 * to the node labeled by `end_label`, or an empty `vector` if no such path
 * exists.
 */
vector<tuple<string, string, int>>
Graph::shortest_path_weighted(string const &start_label,
                              string const &end_label) {
    if (start_label == end_label) {
        vector<tuple<string, string, int>> result
            {{start_label, start_label, 0}};
        return result;
    }
    /**
     * compare struct to compare the weight of the edges
     * @return the smaller weight
     */                              
    struct compare{
        bool operator()(tuple<long, string> lhs, tuple<long, string> rhs) const{
            return get<0>(lhs) > get<0>(rhs);
        }
    };
    // intialize instance variables
    vector<tuple<string, string, int>> vec;
    priority_queue<tuple<long, string>,
        vector<tuple<long, string>>, compare> pq;
    unordered_map<string, string> prev;
    unordered_map<string,long> distance; //label, distance
    unordered_map<string, bool> done;

    // iterating through all_nodes set to initalize prev node, distance
    for(auto it : all_nodes){
        prev[it] = "empty";
        distance[it] = -1;
        done[it] = false;
    }
    
    //perform the traversal
    pq.push(make_tuple(0, start_label));
    distance[start_label] = 0;
    while(!pq.empty()){
        // dequeue (weight, v) from pq
        tuple<long, string> popped = pq.top();
        pq.pop();
        // getting the key
        string v_key = get<1>(popped); // v
        // if the vertex's min path hasn't been discovered yet
        // mark visitted node
        if(done[v_key] == false){
            done[v_key] = true;
            // (v,w,d) = edge from v to w with edge-weight d
            for(auto value : graph[v_key]){
                long c = distance[v_key] + value.second;
                // if a smaller-weight path has been found
                if(distance[value.first] == -1 || c < distance[value.first]){
                    prev[value.first] = v_key;
                    distance[value.first] = c;
                    //  enqueue (c, w) onto pq
                    pq.push(make_tuple(c, value.first));
                }
            }
        }
        
    }
    // intializing instance variables
    string currNode = end_label;
    string prevNode;
    // going backward from the graph and add elements back to the vector
    while(currNode != start_label){
        prevNode = prev[currNode];
        // adding the edges back to the vector of tuple
        vec.push_back(
            make_tuple(prevNode, currNode,
                distance[currNode] - distance[prevNode])
        );
        currNode = prevNode;
    }
    reverse(vec.begin(), vec.end());
    return vec;
}

/**
 * Find the root of the graph in which element u belongs
 * @param u the root
 * @return the parent node
 */
string Graph::find(string u){
    // if u is the root
    if (parent[u] == u)
        return u;
    // recursively find the parent until we find the root
    return parent[u] = find(parent[u]);
}

/**
 * unite function perform the union of two subgraph
 * @param u the start node
 * @param v the end node
 */
void Graph::unite(string u, string v){

    // find the root of the sets in which elements u and v belongs
    string su = find(u);
    string sv = find(v);
    // cout << "---- unite " << su << "(" << nrank[su] << ") 
    // - " << sv << "(" << nrank[sv] << ")" << endl;

    if (su != sv) {
        if (nrank[su] < nrank[sv]) {
            parent[su] = sv;
            nrank[sv] += nrank[su];
        }
        else {
            parent[sv] = su;
            nrank[su] += nrank[sv];
        }
    }
}

/**
 * Return the smallest `threshold` such that, given a start node and an end
 * node, if we only considered all edges with weights <= `threshold`, there
 * would exist a path from the start node to the end node.
 *
 * @param start_label The label of the start node.
 * @param end_label The label of the end node.
 * @return The smallest `threshold` such that, if we only considered all
 * edges with weights <= `threshold, there would exist a path connecting the
 * nodes labeled by `start_label` and `end_label`,
 * or -1 if no such threshold exists.
 */

int Graph::smallest_connecting_threshold(string const &start_label,
                                         string const &end_label) {
    if (start_label == end_label) {
        return 0;
    }

    // iterating through the graph to initialize parent and nrank
    for(auto u : graph){
        parent[u.first] = u.first;
        nrank[u.first] = 1;
    }
    int index = 0;
    int max_weight_so_far = -1;
    // while pq is not empty
    while(parent[start_label] != parent[end_label] && index < edges_count){
        // dequeue (w, u, v) fro pq
        tuple<int, string, string> popped = edges[index++];
        // union the edges 
        if (find(get<1>(popped)) != find(get<2>(popped))) {
            unite(get<1>(popped), get<2>(popped));
            if (get<0>(popped) > max_weight_so_far) {
                max_weight_so_far = get<0>(popped);
            }
        }
    }

    if (parent[start_label] == parent[end_label]){
        return max_weight_so_far;
    } else {
        return -1;
    }
}


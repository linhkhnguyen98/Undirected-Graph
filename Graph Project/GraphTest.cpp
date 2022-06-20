#include <iostream>
#include <string>
#include <chrono>
#include <limits>
#include <unordered_set>
#include "Graph.h"
#include <climits>

/* Macro to explicity print tests that are run along with colorized result. */
#define TEST(EX) (void)((fprintf(stdout, "(%s:%d) %s:", __FILE__, __LINE__,\
                 #EX)) && ((EX && fprintf(stdout, "\t\x1b[32mPASSED\x1b[0m\n"))\
                 || (fprintf(stdout, "\t\x1b[31mFAILED\x1b[0m\n")) ))

bool compare(const double& d1, const double& d2) {
    return std::abs(d1 - d2) <= std::numeric_limits<double>::epsilon();
}

int main() {
    cout << INT_MAX <<endl;
    Graph graph("example/small.csv");
    vector<tuple<string, string, int>> result {{"E", "A", 2147483647}, {"A", "B", 2147483647}, {"B", "C", 2147483647}, {"C", "D", 2147483647}};
    TEST(graph.shortest_path_weighted("E", "D") == result);
    cout << "Threshold " << graph.smallest_connecting_threshold("E", "D") << endl;
    // auto n = graph.nodes();
    // TEST(graph.nodes() == unordered_set<string>({"A", "B", "C", "D", "E", "F", "G"}));
    // TEST(graph.num_nodes() == 7);
    // TEST(graph.edge_weight("A", "B") == 1);
    // TEST(graph.edge_weight("B", "A") == 1);
    // TEST(graph.num_edges() == 6);
    // TEST(graph.neighbors("A") == unordered_set<string>({"B", "C"}));
    // TEST(graph.neighbors("B") == unordered_set<string>({"A", "C", "D"}));

    // vector<tuple<string, string, int>> result {{"A", "A", 0}};
    // // vector<tuple<string, string, int>> result {{"A", "B", 1}, {"B", "C", 1}};
    // auto start = std::chrono::steady_clock::now();
    // TEST(graph.shortest_path_weighted("A", "A") == result);
    // // TEST(graph.shortest_path_weighted("A", "C") == result);
    // auto end = std::chrono::steady_clock::now();
    // auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // TEST(elapsed.count() <= 1000.0); // microseconds

    // start = std::chrono::steady_clock::now();
    // TEST(graph.smallest_connecting_threshold("E", "C") == 1);
    // end = std::chrono::steady_clock::now();
    // elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    // TEST(elapsed.count() <= 1000.0); // microseconds
}


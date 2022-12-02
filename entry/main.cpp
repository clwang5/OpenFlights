#include <iostream>
#include "Graph.h"

int main() {
    Graph graph = Graph("../data/US_routes_contiguous.dat", "../data/US_airports_contiguous.dat");
    std::cout << std::to_string(graph.Dijkstra(328,430, true)) << std::endl;
    graph.Dijkstra(351,187, true);
    graph.Tarjan();
}
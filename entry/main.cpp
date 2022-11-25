#include <iostream>
#include "Graph.h"

int main() {
    Graph graph = Graph("../data/US_routes_contiguous.dat", "../data/US_airports_contiguous.dat");
    graph.Dijkstra(351,187);
}
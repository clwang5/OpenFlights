#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>

using namespace std;

class Graph {
    public:
        Graph() = default;
        Graph(unordered_map<int, vector<pair<int, double>>> m);
        Graph(string routes, string airports);
        // param aiports is only used for testing the algorithm, true if using airport data set, false if otherwise
        double Dijkstra(int source, int dest, bool airports); //returns shortest distance
        void BFS(int source);
    private:
        // Do we even need these, and is there a more efficient way...
        unordered_map<int, string> nodeToAirportName;
        unordered_map<string, int> airportNameToNode;

        // Graph representation
        unordered_map<int, vector<pair<int, double>>> adjList;
};
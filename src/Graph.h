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
        Graph();
        Graph(string routes, string airports);
    private:
        // Do we even need these, and is there a more efficient way...
        unordered_map<int, string> nodeToAirportName;
        unordered_map<string, int> airportNameToNode;

        // Graph representation
        unordered_map<int, vector<pair<int, double>>> adjList;
};
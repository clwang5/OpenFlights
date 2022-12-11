#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
#include <utility>
#include <stack>

using namespace std;

class Graph {
    public:
        Graph() = default;
        Graph(unordered_map<int, vector<pair<int, double>>> m);
        Graph(string routes, string airports);
        // param aiports is only used for testing the algorithm, true if using airport data set, false if otherwise
        double Dijkstra(int source, int dest, bool airports); //returns shortest distance
        vector<int> BFS(int source);
        void Tarjan();
    private:
        void TarjanHelper(int node, stack<int>& s, vector<bool>& onStack, vector<int>& disc, vector<int>& low, vector<int>& SCCs);
        unordered_map<int, string> nodeToAirportName;
        unordered_map<int, vector<pair<int, double>>> adjList;
        
};
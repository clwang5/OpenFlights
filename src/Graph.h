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
        Graph() = default; //default constructor

        Graph(unordered_map<int, vector<pair<int, double>>> m); // constructor for testing purposes, nodeToAirportName map is not used

        Graph(string routes, string airports); //constructor for OpenFlights/custom datsets

        // param aiports is only used for testing the algorithm, true if using airport data set, false if otherwise

        double Dijkstra(int source, int dest, bool airports); // returns shortest distance, populates shortestPath vector

        vector<int> BFS(int source); // returns traversal path

        vector<int> Tarjan(); // returns vector of SCCs

        unordered_map<int, string> getNodeToAirportName(); // getter for map of node to airport name

        vector<int> getShortestPath(); // getter for shortest path

    private:
        void TarjanHelper(int node, stack<int>& s, vector<bool>& onStack, vector<int>& disc, vector<int>& low, vector<int>& SCCs, int& discoveryTime, int& sccID); // helper function for Tarjan's algo

        unordered_map<int, string> nodeToAirportName; // map node to airport name for outputting purposes

        unordered_map<int, vector<pair<int, double>>> adjList; //adjacency list representation of data

        vector<int> shortestPath; // populated during Dijkstra's algorithm since Dijkstra only returns the distance, but we also want to return path for output
        
};
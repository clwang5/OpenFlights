/**
 * @file schedule.h
 * Exam scheduling using graph coloring
 */

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
        //Dijkstra's algo function
        //Tarjan's SCCs algo function
        Graph(string filename);
    private:
        unordered_map<int, vector<pair<int, double>>> adjList;
};
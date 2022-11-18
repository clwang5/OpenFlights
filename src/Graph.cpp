#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "Graph.h"
#include "utils.h"
#include <algorithm>

Graph::Graph(string routes, string airports) {
    
    // Making adjList
    vector<string> lines;
    vector<vector<string>> fields;
    string str =  file_to_string(routes);
    int count = SplitString(str, '\n', lines);
    fields.resize(count - 1);
    for (int i = 0; i < count - 1; i++) {
        SplitString(lines[i], ',', fields[i]);
    }
    for (unsigned i = 0; i < fields.size(); i++) {
        adjList[stoi(fields[i][0])].push_back(make_pair(stoi(fields[i][1]), stod(fields[i][2])));
    }

    // Mapping airport name to node and vice versa
    vector<string> otherlines;
    vector<vector<string>> otherfields;
    string otherstr = file_to_string(airports);
    int othercount = SplitString(otherstr, '\n', otherlines);
    otherfields.resize(othercount - 1);
    for (int i = 0; i < othercount - 1; i++) {
        SplitString(otherlines[i], ',', otherfields[i]);
    }
    for (unsigned i = 0; i < otherfields.size(); i++) {
        nodeToAirportName[stoi(otherfields[i][0])] = otherfields[i][1];
        airportNameToNode[otherfields[i][1]] = stoi(otherfields[i][0]);
    }
}


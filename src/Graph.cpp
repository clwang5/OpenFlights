#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <queue>
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
        adjList[stoi(fields[i][1])];
    }

    // Mapping node to airport name
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
    }
}

// Constructor for ease of making test cases 
Graph::Graph(unordered_map<int, vector<pair<int, double>>> m) {
    adjList = m;
}

double Graph::Dijkstra(int source, int dest, bool airports) {
    shortestPath.clear();
    if (adjList.empty()) {
        throw std::runtime_error("EMPTY GRAPH");
    }
    set<int> visited;
    unordered_map<int, int> prev;
    unordered_map<int, int> dist;
    if (airports) {
        for (auto p : nodeToAirportName) {
            if (p.first == source) {
                dist[p.first] = 0;
            } else {
                dist[p.first] = INT32_MAX;
            }
            prev[p.first] = -1;
        }
    } else {
        for (int i = 0; i < 50; i++) { //random constant for testing
            if (i == source) {
                dist[i] = 0;
            } else {
                dist[i] = INT32_MAX;
            }
            prev[i] = -1;
        }
    }
    
    struct Compare //used for priority queue to compare distances in pairs
    {
        bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)
        {
            return lhs.second > rhs.second;
        }
    };
    priority_queue <pair<int, int>, vector<pair<int,int>>, Compare>  q; //replace greater probably
    pair<int, int> start(source, 0);
    q.push(start);
    
    while (!q.empty() && q.top().first != dest) {
        pair<int, int> curr = q.top();
        q.pop();
        for (auto p : adjList[curr.first]) { //first is nieghbor node, second is distance from curr node
            if (visited.count(p.first) == 1) {
                continue;
            }
            if (p.second + dist[curr.first] < dist[p.first]) {
                dist[p.first] = p.second + dist[curr.first];
                prev[p.first] = curr.first;
                pair<int, int> push(p.first, dist[p.first]);
                q.push(push);
            }
        }
        visited.insert(curr.first);
    }
    if (q.empty()) { //no path from source to dest
        throw std::runtime_error("NO PATH FROM SOURCE TO DEST");
    }
    if (!airports) {
        return dist[dest];
    }
    int e = dest;
    vector<int> path;
    while (true) {
        path.push_back(e);
        if (prev[e] == -1) {
            break;
        }
        e = prev[e];
    }

    for (int i = (int) path.size() - 1; i >= 0; i--) {
        shortestPath.push_back(path[i]);
    }

    return dist[dest];
}

vector<int> Graph::getShortestPath() {
    return shortestPath;
}

unordered_map<int, string> Graph::getNodeToAirportName() {
    return nodeToAirportName;
}

vector<int> Graph::BFS(int source) {
    set<int> visited; // a set to store references to all visited nodes
    queue<int> que; // a queue to store references to nodes we should visit later
    vector<int> path;
    que.push(source);
    visited.insert(source);
    while (!que.empty()) {
        int curr = que.front();
        path.push_back(curr);
        que.pop();
        for (auto neighbor : adjList[curr]) {
            if (visited.count(neighbor.first) == 0) { // not in visited
                que.push(neighbor.first);
                visited.insert(neighbor.first);
            }
        }
    }
    return path;
}

vector<int> Graph::Tarjan() {
    int n = adjList.size();
    stack<int> s;
    vector<bool> onStack(n, false);
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    vector<int> SCCs(n, -1);

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            TarjanHelper(i, s, onStack, disc, low, SCCs);
        }
    }

    return SCCs; //all nodes with the same number in the same SCC, nodes represented by index
}

void Graph::TarjanHelper(int node, stack<int>& s, vector<bool>& onStack, vector<int>& disc, vector<int>& low, vector<int>& SCCs) {
    static int discoveryTime = 0;
    static int sccID = 0;

    s.push(node);
    onStack[node] = true;
    disc[node] = low[node] = discoveryTime;
    discoveryTime++;

    for (auto& elem : adjList[node]) {
        int adjacentNode = elem.first;
        if (disc[adjacentNode] == -1) {
            TarjanHelper(adjacentNode, s, onStack, disc, low, SCCs);
            low[node] = min(low[node], low[adjacentNode]);
        }
        else if (onStack[adjacentNode]) { // if adjacent node not on stack, represents a cross edge between node and adjacent node
                                          // so that means these two nodes are not a part of the same SCC, so do not process low[node]
            low[node] = min(low[node], disc[adjacentNode]);
        }
    }

    if (disc[node] == low[node]) {
        while(!s.empty()) {
            int p = s.top();
            s.pop();
            onStack[p] = false;
            SCCs[p] = sccID;
            if (p == node) {
                break;
            }
        }
        sccID++;
    }
}

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

void Graph::Dijkstra(int source, int dest) {
    set<int> visited;
    unordered_map<int, int> prev;
    unordered_map<int, int> dist;
    for (auto p : nodeToAirportName) {
        if (p.first == source) {
            dist[p.first] = 0;
        } else {
            dist[p.first] = INT32_MAX;
        }
        prev[p.first] = -1;
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
    
    while (q.top().first != dest) {
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
    int e = dest;
    vector<int> path;
    while (true) {
        path.push_back(e);
        if (prev[e] == -1) {
            break;
        }
        e = prev[e];
    }
    cout << "SOURCE: " + to_string(path[path.size() - 1]) + ", " + nodeToAirportName[source] << endl;
    for (size_t i = path.size() - 2; i>0; i--) {
        cout << to_string(path[i]) + ", " + nodeToAirportName[path[i]] << endl;
    }
    cout << "DESTINATION: " + to_string(path[0]) + ", " + nodeToAirportName[dest] << endl;
}

void Graph::BFS(int source) {
    set<int> visited; // a set to store references to all visited nodes
    queue<int> que; // a queue to store references to nodes we should visit later

    cout << "BFS Traversal" << endl; cout << "SOURCE: " + nodeToAirportName[source] << endl;
    que.push(source);
    visited.insert(source);
    while (!que.empty()) {
        int curr = que.front();
        que.pop();
        std::cout << to_string(curr) + " " + nodeToAirportName[curr] << std::endl;
        for (auto neighbor : adjList[curr]) {
            if (visited.count(neighbor.first) == 0) { // not in visited
                que.push(neighbor.first);
                visited.insert(neighbor.first);
            }
        }
    }
}
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
    //check if graph is empty
    if (adjList.empty()) {
        throw std::runtime_error("EMPTY GRAPH");
    }
    //create set for visited and maps for previous and distances
    set<int> visited;
    unordered_map<int, int> prev;
    unordered_map<int, int> dist;
    //airports = true means using airport IDs for the nodes and the openflights dataset
    //airports = false means testing purposes for any generic values and ids for the nodes
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
    //build min heap
    priority_queue <pair<int, int>, vector<pair<int,int>>, Compare>  q;
    pair<int, int> start(source, 0);
    q.push(start);
    //check if queue is empty or the shortest path node is in fact the destination
    while (!q.empty() && q.top().first != dest) {
        pair<int, int> curr = q.top();
        q.pop();
        for (auto p : adjList[curr.first]) { //first is nieghbor node, second is distance from curr node
            if (visited.count(p.first) == 1) {
                continue;
            }
            //check if the distance is shorter than what is listed, if it is then replace and chance previous node
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
    if (!airports) { //return here if no need for route outputting (testing purposes)
        return dist[dest];
    }
    //track back from previous and record the path from source to destination
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
        // traverse through the neighbors of every node
        for (auto neighbor : adjList[curr]) {
            if (visited.count(neighbor.first) == 0) { // if have not visited the node yet
                que.push(neighbor.first);
                visited.insert(neighbor.first);
            }
        }
    }
    return path;
}

vector<int> Graph::Tarjan() {
    int discoveryTime = 0;
    int sccID = 0;
    int n = adjList.size();

    //stack for keeping track of nodes of strongly connected components
    stack<int> s;

    // vector for O(1) check if node is on stack
    vector<bool> onStack(n, false);

    //initialize discovery and lowlinks vectors
    vector<int> disc(n, -1);
    vector<int> low(n, -1); 

    vector<int> SCCs(n, -1); //to return, keep track of which nodes belong to which SCC
                             //all nodes with the same number are in the same SCC, index represents node

    //DFS for all subgraphs, populates SCCs vector with strongly connected components of that subgraph
    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) { //if unvisited
            TarjanHelper(i, s, onStack, disc, low, SCCs,discoveryTime,sccID);
        }
    }

    return SCCs; 
}

void Graph::TarjanHelper(int node, stack<int>& s, vector<bool>& onStack, vector<int>& disc, vector<int>& low, vector<int>& SCCs, int& discoveryTime, int& sccID) {
    

    //update discovery time and lowlink value of current node, push to stack and update onStack
    s.push(node);
    onStack[node] = true;
    disc[node] = low[node] = discoveryTime;
    discoveryTime++;

    // visit neighbors of current node and update lowlink values
    for (auto& elem : adjList[node]) {
        int adjacentNode = elem.first;
        if (disc[adjacentNode] == -1) { // if unvisited, recur
            TarjanHelper(adjacentNode, s, onStack, disc, low, SCCs,discoveryTime,sccID);
            low[node] = min(low[node], low[adjacentNode]);
        }
        else if (onStack[adjacentNode]) { // if adjacent node is on stack, that means it is a part of current SCC, so update lowlink value
                                          // if adjacent node not on stack, represents a cross edge between node and adjacent node
                                          // in other words, that means these two nodes are not a part of the same SCC, so do not update lowlink value
            low[node] = min(low[node], disc[adjacentNode]);
        }
    }

    if (disc[node] == low[node]) { // condition checks for if current node is root of complete SCC
        //if true, pop stack and update sccID of each node until root is reached
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

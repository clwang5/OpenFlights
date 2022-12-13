#include <catch2/catch_test_macros.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "Graph.h"
using namespace std;

TEST_CASE("Empty Graph") {
    Graph g;
    REQUIRE_THROWS_AS(g.Dijkstra(0,5,false), std::runtime_error);
    REQUIRE_THROWS_AS(g.Dijkstra(5,5,false), std::runtime_error);
    REQUIRE_THROWS_AS(g.Dijkstra(2,-1,false), std::runtime_error);
}
TEST_CASE("Bean (undirected)") { //taken from resources page in cs225
    unordered_map<int, vector<pair<int, double>>> m;
    m[0] = vector<pair<int, double>>{pair<int, double>(1,21), pair<int, double>(2,50)}; //Siebel
    m[1] = vector<pair<int, double>>{pair<int, double>(3,57), pair<int, double>(0,21)}; //Rantoul
    m[2] = vector<pair<int, double>>{pair<int, double>(4,42), pair<int, double>(0,21)}; //Bloomington
    m[3] = vector<pair<int, double>>{pair<int, double>(5,63), pair<int, double>(4,53), pair<int, double>(1,57)}; //Kankakee
    m[4] = vector<pair<int, double>>{pair<int, double>(2,42), pair<int, double>(3,53), pair<int, double>(5,40), pair<int, double>(6,57)}; //Pontiac
    m[5] = vector<pair<int, double>>{pair<int, double>(3,57), pair<int, double>(4,40), pair<int, double>(6,51), pair<int, double>(7,1)}; //Chicago
    m[6] = vector<pair<int, double>>{pair<int, double>(4,57), pair<int, double>(5,51)}; //Bean
    m[7] = vector<pair<int, double>>{pair<int, double>(5,1)}; //Bean
    SECTION("Undirected graph") {
        Graph g(m);
        REQUIRE(g.Dijkstra(0,0, false)==0.0);
        REQUIRE(g.Dijkstra(0,1, false)==21);
        REQUIRE(g.Dijkstra(0,2, false)==50.0);
        REQUIRE(g.Dijkstra(0,3, false)==78.0);
        REQUIRE(g.Dijkstra(0,4, false)==92.0);
        REQUIRE(g.Dijkstra(0,5, false)==132.0);
        REQUIRE(g.Dijkstra(0,6, false)==149.0);
        REQUIRE(g.Dijkstra(0,7, false)==133.0);
    }
    SECTION("No path from source to dest") {
        m[8] = vector<pair<int, double>>{}; //no connections
        Graph g(m);
        REQUIRE_THROWS_AS(g.Dijkstra(0,8, false), std::runtime_error);
        REQUIRE_THROWS_AS(g.Dijkstra(8,0, false), std::runtime_error);
    }
}
TEST_CASE("Single heavy vs many light-weighted (directed)") { //taken from lecture
    unordered_map<int, vector<pair<int, double>>> m;
    m[0] = vector<pair<int, double>>{pair<int, double>(6, 8), pair<int, double>(1,1)};
    m[1] = vector<pair<int, double>>{pair<int, double>(2, 1)};
    m[2] = vector<pair<int, double>>{pair<int, double>(3, 1)};
    m[3] = vector<pair<int, double>>{pair<int, double>(4, 1)};
    m[4] = vector<pair<int, double>>{pair<int, double>(5, 1)};
    m[5] = vector<pair<int, double>>{pair<int, double>(6, 1)};
    m[6] = vector<pair<int, double>>{};
    Graph g(m);

    REQUIRE(g.Dijkstra(0,6, false) == 6); //6 instead of a direct path of 8

    m[0] = vector<pair<int, double>>{pair<int, double>(6, 4), pair<int, double>(1,1)};
    Graph graph(m);
    REQUIRE(graph.Dijkstra(0,6, false) == 4);
}
TEST_CASE("OpenFlights Dataset") {
    Graph graph = Graph("../data/US_routes_contiguous.dat", "../data/US_airports_contiguous.dat");
    REQUIRE(graph.Dijkstra(1,33, true)==1744.0); //LAX to ORD (neighboring nodes) compared using openflights data
    REQUIRE(graph.Dijkstra(328,430, true)==370.0); //CPR to HDN (not neighboring nodes), small airports that're only connected via DEN
}

TEST_CASE("BFS") { 
    // example : https://www.programiz.com/dsa/graph-bfs
    
    unordered_map<int, vector<pair<int, double>>> adjList;
    adjList[0]= vector<pair<int, double>>{pair<int, double>(1,10), pair<int, double>(3,20)};
    adjList[1]= vector<pair<int, double>>{pair<int, double>(0,5),pair<int, double>(2,5)};
    adjList[2]= vector<pair<int, double>>{pair<int, double>(0,25), pair<int, double>(1,30), pair<int, double>(4,50)};
    adjList[3]= vector<pair<int, double>>{pair<int, double>(0,5)};
    adjList[4]= vector<pair<int, double>>{pair<int, double>(2,9)};
    Graph g(adjList);
    REQUIRE(g.BFS(0)==vector<int>{0,1,3,2,4});
    REQUIRE(g.BFS(1)==vector<int>{1,0,2,3,4});
    REQUIRE(g.BFS(2)==vector<int>{2,0,1,4,3});
    REQUIRE(g.BFS(3)==vector<int>{3,0,1,2,4});
    REQUIRE(g.BFS(4)==vector<int>{4,2,0,1,3});
}

TEST_CASE("Complex, many SCCs, tests cross edge") {
    Graph graph = Graph("../data/tarjanstests/test2.dat","../data/tarjantests/dummy.dat");
    std::vector<int> output = graph.Tarjan();
    std::vector<int> expected = {0,4,3,3,3,3,2,1,5};
    REQUIRE(output == expected);
}

TEST_CASE("Taken from Wikipedia example") {
    Graph graph = Graph("../data/tarjanstests/test3.dat","../data/tarjantests/dummy.dat");
    std::vector<int> output = graph.Tarjan();
    std::vector<int> expected = {0,3,3,3,2,1,1,1,1};
    REQUIRE(output == expected);
}

TEST_CASE("Simple, multiple SCCs, one self-loop") {
    Graph graph = Graph("../data/tarjanstests/test1.dat","../data/tarjantests/dummy.dat");
    std::vector<int> output = graph.Tarjan();
    std::vector<int> expected = {0,3,3,2,2,3,1,1,2};
    REQUIRE(output == expected);
}

TEST_CASE("Complex, many directed edges and nodes, 1 SCC") {
    Graph graph = Graph("../data/tarjanstests/test6.dat", "../data/tarjantests/dummy.dat");
    vector<int> output = graph.Tarjan();
    vector<int> expected = {0,0,0,0,0,0,0,0,0,0};
    REQUIRE(output == expected);
}

TEST_CASE("Simple") {
    Graph graph = Graph("../data/tarjanstests/test5.dat", "../data/tarjantests/dummy.dat");
    vector<int> output = graph.Tarjan();
    vector<int> expected = {2,2,2,1,0};
    REQUIRE(output == expected);
}

TEST_CASE("Tarjan's with self loops and checking maximal SCC selected") {
    Graph graph = Graph("../data/tarjanstests/test4.dat", "../data/tarjantests/dummy.dat");
    vector<int> output = graph.Tarjan();
    vector<int> expected = {1,1,1,0,0,2,2,2,3};
    REQUIRE(output == expected);
}
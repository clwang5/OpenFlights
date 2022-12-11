#include <iostream>
#include <fstream>
#include "Graph.h"

//example:            ./main d ../data/US_routes_contiguous.dat ../data/US_airports_contiguous.dat 328 430 ../outputs

int main(int argc, char* argv[]) {
    if (argc < 4) {
        cout << "\nSpecific command line arguments are needed to run each algorithm. \n" << endl;
        cout << "Tarjan's Algorithm Usage: ./main t ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH OUTPUT_DIRECTORY \n" << endl;
        cout << "Dijkstra's Algorithm Usage: ./main d ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH SOURCE_NODE DESTINATION_NODE OUTPUT_DIRECTORY \n" << endl;
        cout << "BFS Algorithm  Usage: ./main b ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH SOURCE_NODE OUTPUT_DIRECTORY \n" << endl;
        cout << "Example of running Dijkstra's Algorithm on OpenFlights dataset: ./main d ../data/US_routes_contiguous.dat ../data/US_airports_contiguous.dat 328 430 ../outputs \n" << endl;
        cout << "See README for additional information on command line inputs as well as using custom datasets that do not exist in this repository. \n" << endl;
        return 1;
    }

    string algorithm = argv[1];
    string routeFilepath = argv[2];
    string airportFilepath = argv[3];
    Graph graph = Graph(routeFilepath, airportFilepath);

    if (algorithm == "t") {
        if (argc != 5) {
            cout << "Argument number is incorrect. Run './main' to see information on usage of this program." << endl;
            return 1;
        }

        vector<int> SCCs = graph.Tarjan();
        
        unordered_map<int, vector<int>> m;
        for (unsigned i = 0; i < SCCs.size(); i++) {
            m[SCCs[i]].push_back(i);
        }

        string outputDir = argv[4];
        ofstream file(outputDir + "/tarjan_result.txt");
        unsigned count = 1;
        for (const auto& elem : m) {
            file << "SCC " << count << ": " << endl;
            for (const auto& node : elem.second ) {
                file << graph.getNodeToAirportName()[node] << endl;
            }
            count++;
        }

        return 0;
    }

    if (algorithm == "d") {

        if (argc != 7) {
            cout << "Argument number is incorrect. Run './main' to see information on usage of this program." << endl;
            return 1;
        }

        string source = argv[4];
        string dest = argv[5];
        graph.Dijkstra(stoi(source), stoi(dest), true);
        vector<int> path = graph.getShortestPath();

        string outputDir = argv[6];
        ofstream file(outputDir + "/dijkstra_result.txt");
        unsigned count = 0;
        for (const auto& node : path) {
            if (count == 0) {
                file << "Source: ";
            }
            if (count == path.size() - 1) {
                file << "Destination: ";
            }
            file << graph.getNodeToAirportName()[node] << endl;
            count++;
        }

        return 0;
    }

    if (algorithm == "b") {

        if (argc != 6) {
            cout << "Argument number is incorrect. Run './main' to see information on usage of this program." << endl;
            return 1;
        }

        string source = argv[4];
        vector<int> traversal = graph.BFS(stoi(source));

        string outputDir = argv[5];
        ofstream file(outputDir + "/bfs_result.txt");
        bool flag = true;
        for (const auto& node : traversal) {
            if (flag) {
                file << "BFS Source: ";
                flag = false;
            }
            file << graph.getNodeToAirportName()[node] << endl;
        }

        return 0; 
    }
}
# CS225-OpenFlights
<p align="center">
  <a href="#presentation-video">Presentation Video</a> •
  <a href="#data">Data</a> •
  <a href="#repo-structure">Repo Structure</a> •
  <a href="#running-instructions">Running Instructions</a> •
  <a href="#creativity">Creativity</a> •
  <a href="#team">Team</a>
</p>

## [Presentation Video](https://mediaspace.illinois.edu/media/t/1_urny4ezr)

## Data
We are using the [openflights.org]([https://openflights.org/data.html](https://openflights.org/data.html)) data and focusing on the following two files:

- [Airport raw database](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
- [Route raw database](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)


## Repo Structure

### Deliverables
All major files that contain our functions and classes are in the [src directory](https://github.com/clwang5/OpenFlights/tree/main/src).

- Datasets are stored as .dat files in [`/data`](https://github.com/clwang5/OpenFlights/tree/main/data).

- Tests are in [`/tests`](https://github.com/clwang5/OpenFlights/tree/main/tests).

- All documents (Project report, development log, contract, proposal, etc.) are in [`/documents`](https://github.com/clwang5/OpenFlights/tree/main/documents). 


## Running Instructions

### Executable
Make sure you are running the program in the [Docker](https://www.docker.com/) environment.
Then do `mkdir build`,`cd build` and lastly, `cmake ..`.
All algorithms will be run through [`/entry/main`](https://github.com/clwang5/OpenFlights/blob/main/entry/main.cpp)
For output files, the directory can be specified (needs to exist) of where to put these output files.
For using custom datasets, please see <a href="#creativity">Creativity</a>.
The required inputs as well as commands for each of the functionality are as follows:\

All "Examples:" provided are using the processed data from the OpenFlights dataset. 

1. Shortest Path Between Airports (Dijkstra's): 
  - Input: starting node number (represents an airport) and destination node number (both should be integer)
  - Output: the shortest path (airports it passes through)
  - Dijkstra's Algorithm Usage: ./main d ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH SOURCE_NODE DESTINATION_NODE OUTPUT_DIRECTORY
  - Example: ./main d ../data/US_routes_contiguous.dat ../data/US_airports_contiguous.dat 328 430 ../outputs

2. Strongly Connected Components (Tarjan's):
  - Input: No input
  - Output: Groups of all strongly connected components
  - Tarjan's Algorithm Usage: ./main t ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH OUTPUT_DIRECTORY
  - Example for OpenFlights: ./main t ../data/US_routes_contiguous.dat ../data/US_airports_contiguous.dat ../outputs

3. Breadth-First-Search:
  - Input: Starting node number (represents an airport)
  - Output: Sequence of nodes in the order it is traversed
  - BFS Algorithm Usage: ./main b ROUTE_DATA_FILEPATH AIRPORT_DATA_FILEPATH SOURCE_NODE OUTPUT_DIRECTORY
  - Example for OpenFlights: ./main b ../data/US_routes_contiguous.dat ../data/US_airports_contiguous.dat 10 ../outputs

Note: All filepaths when executing ./main are relative to the build directory.

### Tests

To run the test suite, run `make test` then `./test` in the build directory.

We constructed tests cases considering things such as empty graphs, directed graphs with nodes with and without incoming and outgoing edges, directed graphs with many paths that can be taken from every node and differing weights of those paths, graphs with self loops, and graphs with mulitple SCCs, and any other scenarios where edge cases may form. Our test cases focuses on the functionality of our graph data processing, Dijkstra's algorithm, Tarjan's algorithm, and Breadth-First-Search.

## Creativity
If you want to use ur own custom datasets, please follow the format EXACTLY of edges and weights in [this file](https://github.com/clwang5/OpenFlights/blob/main/data/US_airports_contiguous.dat) and [this file](https://github.com/clwang5/OpenFlights/blob/main/data/US_routes_contiguous.dat).
Please make sure the node numbering is contiguous and starting from 0 as well as including the newline at the bottom of each file, otherwise a segfault will occur.


## Team
- Charleston Wang
- Jason Xu
- Lina Mei
- Raki Jeyaraman


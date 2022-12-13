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

- [Airport database](https://raw.githubusercontent.com/jpatokal/openflights/master/data/airports.dat)
- [Route database](https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat)


## Repo Structure

### Deliverables
All major files that contain our functions and classes are in the [src directory](https://github.com/clwang5/OpenFlights/tree/main/src).

- Datasets are stored as .dat files in [`/data`](https://github.com/clwang5/OpenFlights/tree/main/data).

- Tests are in [`/tests`](https://github.com/clwang5/OpenFlights/tree/main/tests).

- Project report, development log, contract, etc. are in [`/documents`](https://github.com/clwang5/OpenFlights/tree/main/documents). 


## Running Instructions

### Executable
Make sure you are running the program in [Docker](https://www.docker.com/).
Then do `mkdir build`,`cd build` and lastly, `cmake ..`.
All the main functions are in [`/entry/main`](https://github.com/clwang5/OpenFlights/blob/main/entry/main.cpp)
The required inputs for each of the functionality are as follows:

1. Shortest Path Between Airports (Dijkstra's): 
  - Input: starting node number (represents an airport) and destination node number (both should be integer)
  - Output: the shortest path (airports it passes through)

2. Strongly Connected Components (Tarjan's):
  - Input: No input
  - Output: Groups of all strongly connected components

3. Breadth-First-Search:
  - Input: Starting node number (represents an airport)
  - Output: Sequence of nodes in the order it is traversed

There are comments with more details about the functions as well as how to run command lines in `main.cc`.

### Tests

To run the test cases, run `make test` then `./test` in the build directory.


## Creativity
If u want to use ur own custom datasets, please follow the format of edges and weights in the US routes contiguous.dat file and the US airports contiguous.dat files.
Please make sure the node numbering is contiguous and starting from 0 and the format is followed.


## Team
- Charleston Wang
- Jason Xu
- Lina Mei
- Raki Jeyaraman

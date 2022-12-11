# CS 225 Final Report
## Algorithm Overview
### Dijkstra’s
Our implementation of Dijkstra’s algorithm takes in two node airport IDs (of the starting airport and destination airport) and outputs the shortest path between them. Our Dijkstra's algorithm uses a priority queue and has a time complexity in O(V+E logV) runtime where V is the number of airports and E is the number of edges. To test that each algorithm was working as intended, the Dijkstra algorithm includes test cases for empty graphs, undirected graphs, graphs with no path from source to destination, single-heavy weight edges vs many light-weighted edges between source and destination, mostly retrieved from the CS225 resources page. 

### Tarjan's
Our implementation of Tarjan's algorithm takes in a starting node airport. It utilizes a stack and a DFS traversal, resulting in O(V+E) time complexity where V is the number of airports and E is the number of edges. The Tarjan's algorithm find strongly connected components, which in this case finds the strongly connected airports from a starting airport.

### Breadth-First Search
Our breadth-first search algorithm takes in a single starting node and outputs a sequence of nodes in the order it is traversed. Our BFS algorithm included a test case that correctly printed out the traversal of an example graph with a smaller dataset found online.

## Leading Question

When given two airports, our team's leading question planned on finding the shortest route from one airport to another. We answered this by implementing Dijkstra's shortest path algorithm and printing the path of the shortest route. We discovered that a big airport like O'Hare International airport is more likely to have a shorter path to other airports in comparison to a small airport to another small airport. We also planned on finding the strongly connected airports which we answered by implementing Tarjan's strongly connected component algorithm.
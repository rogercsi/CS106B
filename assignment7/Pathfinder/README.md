## Pathfinder

The program constructs a graph and provides two operations: finding the shortest path between two locations (using Dijkstra's algorithm) and constructing the minimal spanning tree (using Kruskal's algorithm). Both algorithms make use of priority queue implemented as chunked list. The user chooses the graph data file for the program to read and display.

Typical graph data file markup (first list all the nodes, then all the arcs):

```
NODES
Node1
Node2
Node3
ARCS
Node1 Node2 20
Node1 Node3 25
Node2 Node3 30
```

`$ c++ -std=c++14 -Wall *.cpp -o pf && ./pf`
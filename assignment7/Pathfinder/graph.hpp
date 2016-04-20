//
//  graph.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef graph_hpp
#define graph_hpp

#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include "g_edge.hpp"
#include "g_node.hpp"

class Graph {
public:
    Graph(std::ifstream &infile);
    void printGraph() const;
    bool containsNode(const std::string &node) const { return g.find(node) != g.end(); }
    std::pair<double, std::stack<std::shared_ptr<GNode>>> dijkstra(const std::string &source, const std::string &target) const;
    std::vector<std::shared_ptr<GEdge>> kruskal() const;
private:
    Graph();
    std::unordered_map<std::string, std::shared_ptr<GNode>> g;
};

#endif /* graph_hpp */

//
//  g_node.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef g_node_hpp
#define g_node_hpp

#include <string>
#include <vector>
#include "g_edge.hpp"

struct GEdge;

struct GNode {
    GNode() = default;
    GNode(const GNode &other) = default;
    GNode(const std::string &n);
    void printNode() const;
    std::string name = "";
    std::vector<GEdge> edges = {};
};

#endif /* g_node_hpp */

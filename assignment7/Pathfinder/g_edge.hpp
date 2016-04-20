//
//  g_edge.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef g_edge_hpp
#define g_edge_hpp

#include "g_node.hpp"

struct GNode;

struct GEdge {
    GEdge() = default;
    GEdge(const GEdge &other) = default;
    GEdge(const double w, const std::shared_ptr<GNode> &o, const std::shared_ptr<GNode> &dst);
    void printEdge() const;
    double weight = 0.0;
    std::weak_ptr<GNode> origin;
    std::weak_ptr<GNode> dest;
};

#endif /* g_edge_hpp */

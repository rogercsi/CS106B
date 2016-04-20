//
//  g_edge.cpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "g_edge.hpp"
#include <iostream>

using namespace std;

// main ctor
GEdge::GEdge(const double w, const shared_ptr<GNode> &o, const shared_ptr<GNode> &dst)
: weight(w), origin(o), dest(dst) { }

// prints edge
void GEdge::printEdge() const {
    auto org_ptr = origin.lock();
    auto dest_ptr = dest.lock();
    cout << "(" << weight << ") "<< org_ptr->name << " -> " << dest_ptr->name;
}

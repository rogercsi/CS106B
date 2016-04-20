//
//  g_node.cpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 14/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "g_node.hpp"
#include <iostream>

using namespace std;

// ctor from a string
GNode::GNode(const string &n) : name(n), edges({}) { }


// prints GNode
void GNode::printNode() const {
    cout << name << ":" << endl;
    for (auto edge : edges) {
        edge.printEdge();
        cout << endl;
    }
}
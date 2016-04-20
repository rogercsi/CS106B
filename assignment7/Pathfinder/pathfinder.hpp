//
//  pathfinder.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 16/04/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef pathfinder_hpp
#define pathfinder_hpp

#include "graph.hpp"

class Pathfinder {
public:
	Pathfinder() = default;
    void loadFile();
    void start();
    void shortestPath();
    void minSpanningTree();
private:
    bool loaded = false;
    std::unique_ptr<Graph> graph_ptr = nullptr;
};

#endif /* pathfinder_hpp */

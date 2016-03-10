//
//  node.hpp
//  PQueue - ChunkList
//
//  Created by Sergey Nikiforov on 09/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <array>
#include <iostream>

// chunk size in a node, must be > 1
const size_t MAX_BLOCK_SIZE = 4;

struct Node {
    size_t block_size = 0;
    std::array<int, MAX_BLOCK_SIZE> block{};
    std::shared_ptr<Node> next = nullptr;
    void addElt(const int elt);
    void printBlock() const;
private:
    void insert(const int elt);
    void splitNode();
};

#endif /* node_hpp */

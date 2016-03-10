//
//  node.cpp
//  PQueue - ChunkList
//
//  Created by Sergey Nikiforov on 09/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "node.hpp"
#include <iostream>

using namespace std;


// recursively adds an element to a node
// if the node block is full, splits it into two nodes, and tries to add again
void Node::addElt(const int elt) {
    // add if it's the last node or it's no larger than the last element in the block
    if (next == nullptr ||elt >= block.at(block_size-1)) {
        
        // if node becomes full, create new node and try to insert again
        if (block_size == MAX_BLOCK_SIZE) {
            splitNode();
            addElt(elt);
        }
        // else add an element to block
        else insert(elt);
        
    } else next->addElt(elt);
}


// splits current Node into two, copying second half of current node in a new one
void Node::splitNode() {
    auto new_node_ptr = make_shared<Node>();
    new_node_ptr->next = next;
    next = new_node_ptr;
    
    // put the second half of the current block into new one
    for (size_t i = MAX_BLOCK_SIZE / 2, j = 0; i < MAX_BLOCK_SIZE; ++i, ++j) {
        next->block[j] = block[i];
        block_size -= 1;
        next->block_size += 1;
    }
}


// inserts an elt into a sorted block, preserving sorted invariant
// assumes array is sorted and there are at most (MAX_BLOCK_SIZE - 1) significant elements
void Node::insert(const int elt) {
    // get the pos to insert
    size_t pos = 0;
    while (pos < block_size) {
        if (elt >= block.at(pos)) break;
        pos += 1;
    }
    
    // shift everything to the right
    for (size_t i = MAX_BLOCK_SIZE - 1; i > pos; --i)
        block.at(i) = block.at(i-1);
    
    // place the element
    block.at(pos) = elt;
    block_size += 1;
}


// prints the block
void Node::printBlock() const {
    for (size_t i = 0; i < block_size; ++i)
        cout << block.at(i) << " ";
    cout << endl;
}

//
//  node.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 29/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef node_hpp
#define node_hpp

#include <array>
#include <iostream>
#include <functional>

// chunk size in a node, must be > 1
const size_t MAX_BLOCK_SIZE = 4;

template <typename ElementType, typename PriorityType>
struct PQNode {
    size_t block_size = 0;
    std::array<std::pair<ElementType, PriorityType>, MAX_BLOCK_SIZE> block{};
    std::shared_ptr<PQNode<ElementType, PriorityType>> next = nullptr;
    void addElt(const ElementType &elt, const PriorityType &p, std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> cmpFn = std::greater<PriorityType>());
    void printBlock() const;
private:
    void insert(const ElementType &elt, const PriorityType &p, std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> cmpFn = std::greater<PriorityType>());
    void splitNode();
};


// recursively adds an element to a node
// if the node block is full, splits it into two nodes, and tries to add again
template <typename ElementType, typename PriorityType>
void PQNode<ElementType, PriorityType>::addElt(const ElementType &elt, const PriorityType &p, std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> cmpFn) {
    // add if it's the last node or it's no larger than the last element in the block
    if (next == nullptr || cmpFn(p, block.at(block_size-1).second)) {
        
        // if node becomes full, create new node and try to insert again
        if (block_size == MAX_BLOCK_SIZE) {
            splitNode();
            addElt(elt, p, cmpFn);
        }
        // else add an element to block
        else insert(elt, p, cmpFn);
        
    } else next->addElt(elt, p, cmpFn);
}


// splits current Node into two, copying second half of current node in a new one
template <typename ElementType, typename PriorityType>
void PQNode<ElementType, PriorityType>::splitNode() {
    auto new_node_ptr = std::make_shared<PQNode<ElementType, PriorityType>>();
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
template <typename ElementType, typename PriorityType>
void PQNode<ElementType, PriorityType>::insert(const ElementType &elt, const PriorityType &p, std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> cmpFn) {
    // get the pos to insert
    size_t pos = 0;
    while (pos < block_size) {
        if (cmpFn(p, block.at(pos).second)) break;
        pos += 1;
    }
    
    // shift everything to the right
    for (size_t i = MAX_BLOCK_SIZE - 1; i > pos; --i)
        block.at(i) = block.at(i-1);
    
    // place the element
    block.at(pos) = std::make_pair(elt, p);
    block_size += 1;
}


// prints the block
template <typename ElementType, typename PriorityType>
void PQNode<ElementType, PriorityType>::printBlock() const {
    for (size_t i = 0; i < block_size; ++i)
        std::cout << block.at(i).first << " (p = " << block.at(i).second << ") ";
    std::cout << std::endl;
}


#endif /* node_hpp */

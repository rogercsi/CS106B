//
//  pqueue.cpp
//  PQueue - ChunkList
//
//  Created by Sergey Nikiforov on 09/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "pqueue.hpp"
#include <iostream>

using namespace std;

// default ctor
PQueue::PQueue() : q_size(0), root(make_shared<Node>()) { if (MAX_BLOCK_SIZE < 2) throw runtime_error("Please set MAX_BLOCK_SIZE > 1"); }


// adds an element to PQueue
void PQueue::enqueue(const int elt) {
    root->addElt(elt);
    ++q_size;
}


// returns max element from the queue
// throws out_of_range if dequeueing from an empty queue
int PQueue::dequeueMax() {
    if (q_size == 0)
        throw out_of_range("Queue is empty");
    
    int result = root->block.at(0);
    root->block_size -= 1;
    q_size -= 1;
    
    // if the block becomes empty, get rid of the node
    if (root->block_size == 0) {
        root = root->next;
    } else {
        // shift the remaining elements up
        for (size_t i = 0; i < MAX_BLOCK_SIZE - 1; ++i)
            root->block.at(i) = root->block.at(i + 1);
    }
    return result;
}


// prints the entire priority queue
void PQueue::printQueue() const {
    auto cur = root;
    cout << "PQueue:" << endl;
    while (cur != nullptr) {
        cur->printBlock();
        cout << endl;
        cur = cur->next;
    }
}
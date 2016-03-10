//
//  pqueue.hpp
//  PQueue - ChunkList
//
//  Created by Sergey Nikiforov on 09/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef pqueue_hpp
#define pqueue_hpp

#include "node.hpp"

class PQueue {
public:
    PQueue();
    size_t size() const { return q_size; }
    bool isEmpty() const { return q_size == 0; }
    void enqueue(const int elt);
    int dequeueMax();
    void printQueue() const;
private:
    size_t q_size = 0;
    std::shared_ptr<Node> root;
};

#endif /* pqueue_hpp */

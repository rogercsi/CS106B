//
//  pqueue.hpp
//  Pathfinder
//
//  Created by Sergey Nikiforov on 29/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef pqueue_hpp
#define pqueue_hpp


#include "node.hpp"

template <typename ElementType, typename PriorityType>
class PQueue {
public:
    PQueue();
    PQueue(std::function<bool (const PriorityType&, const PriorityType&)>);
    size_t size() const { return q_size; }
    bool isEmpty() const { return q_size == 0; }
    void enqueue(const ElementType &elt, const PriorityType &p);
    ElementType dequeueMax();
    void printQueue() const;
private:
    size_t q_size;
    std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> cmpFn;
    std::shared_ptr<PQNode<ElementType, PriorityType>> root;
};


// default ctor
template <typename ElementType, typename PriorityType>
PQueue<ElementType, PriorityType>::PQueue()
: q_size(0), cmpFn(std::greater<PriorityType>()), root(std::make_shared<PQNode<ElementType, PriorityType>>()) {
    if (MAX_BLOCK_SIZE < 2)
        throw std::runtime_error("Please set MAX_BLOCK_SIZE > 1");
}


// ctor with custom comparison function
template <typename ElementType, typename PriorityType>
PQueue<ElementType, PriorityType>::PQueue(std::function<bool (const PriorityType &lhs, const PriorityType &rhs)> f)
: q_size(0), cmpFn(f), root(std::make_shared<PQNode<ElementType, PriorityType>>()) {
    if (MAX_BLOCK_SIZE < 2)
        throw std::runtime_error("Please set MAX_BLOCK_SIZE > 1");
}


// adds an element to PQueue
template <typename ElementType, typename PriorityType>
void PQueue<ElementType, PriorityType>::enqueue(const ElementType &elt, const PriorityType &p) {
    root->addElt(elt, p, cmpFn);
    ++q_size;
}


// returns max element from the queue
// throws out_of_range if dequeueing from an empty queue
template <typename ElementType, typename PriorityType>
ElementType PQueue<ElementType, PriorityType>::dequeueMax() {
    if (q_size == 0)
        throw std::out_of_range("Queue is empty");
    
    ElementType result(root->block.at(0).first);
    root->block_size -= 1;
    q_size -= 1;
    
    // if the block becomes empty, get rid of the node
    if (root->block_size == 0) {
        // don't throw away the last remaining PQNode
        if (q_size != 0)
            root = root->next;
    } else {
        // shift the remaining elements up
        for (size_t i = 0; i < MAX_BLOCK_SIZE - 1; ++i)
            root->block.at(i) = root->block.at(i + 1);
    }
    return result;
}


// prints the entire priority queue
template <typename ElementType, typename PriorityType>
void PQueue<ElementType, PriorityType>::printQueue() const {
    auto cur = root;
    std::cout << "PQueue:" << std::endl;
    while (cur != nullptr) {
        cur->printBlock();
        std::cout << std::endl;
        cur = cur->next;
    }
}

#endif /* pqueue_hpp */

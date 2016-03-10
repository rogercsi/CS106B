//
//  main.cpp
//  PQueue - ChunkList
//
//  Created by Sergey Nikiforov on 09/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include <iostream>
#include "pqueue.hpp"
#include "pqueuetest.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    
    array<int, 12> nums = { {-29, -30, -17, 14, 14, 13, 5, 16, 31, 31, 14, 14} };
    PQueue pq;
    
    // enqueueing
    for (auto i : nums) {
        pq.enqueue(i);
        cout << "Enqueued element: " << i << endl;
        pq.printQueue();
    }
    
    // dequeueing
    for (auto i = pq.size(); i != 0; --i) {
        cout << "Dequeued max element: " << pq.dequeueMax() << endl;
        pq.printQueue();
    }
    cout << endl;
    
    // other tests
    BasicPQueueTest();
    MorePQueueTest();
    PQueueSortTest();
    
    return 0;
}

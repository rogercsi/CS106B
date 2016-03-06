//
//  heapsort.cpp
//  SortingLab
//
//  Created by Sergey Nikiforov on 04/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "heapsort.hpp"
#include <iostream>

using namespace std;


// set of ints compare function: compares by the set sum
bool intSetSumCmp(const set<int> &lhs, const set<int> &rhs) {
    int lhsSum = accumulate(lhs.cbegin(), lhs.cend(), 0);
    int rhsSum = accumulate(rhs.cbegin(), rhs.cend(), 0);
    return lhsSum > rhsSum;
}


// string compare function: first compare by length, in case of ties order by alphabet
bool strLenCmp(const string &lhs, const string &rhs) {
    return (lhs.length() == rhs.length()) ? (lhs > rhs) : (lhs.length() > rhs.length());
}


// returns index of a parent in a heap for a particluar node
// doesn't check for bounds, assumes index < vector size
size_t parent(const size_t index) {
    if (index > 0) {
        return (index - 1) / 2;
    } else throw out_of_range("It's a root node, no parents");
}


// returns index of a right child in a heap for a particular node
// checks for bounds, throws out_of_range
size_t rightChild(const size_t up_to, const size_t node_index) {
    if (node_index <= lastParent(up_to)) {
        auto result = 2 * (node_index + 1);
        if (result < up_to) {
            return result;
        } else throw out_of_range("There's no right child for this node");
    } else throw out_of_range("There's no children, it's a leaf");
}


// returns index of a left child in a heap for a particular node
// checks for bounds, throws out_of_range
size_t leftChild(const size_t up_to, const size_t node_index) {
    if (node_index <= lastParent(up_to)) {
        auto result = 2 * node_index + 1;
        if (result < up_to) {
            return result;
        } else throw out_of_range("There's no left child for this node");
    } else throw out_of_range("There's no children, it's a leaf");
}


// returns index of a last parent in a heap
// returns 0 for a vec of size < 2
size_t lastParent(const size_t size) {
    return ((size < 2) ? 0 : (size - 2) / 2);
}
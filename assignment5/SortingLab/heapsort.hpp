//
//  heapsort.hpp
//  SortingLab
//
//  Created by Sergey Nikiforov on 04/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef heapsort_hpp
#define heapsort_hpp

#include <vector>
#include <functional>
#include <string>
#include <set>
#include <numeric>

template<typename Type> void heapSort(std::vector<Type> &v, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn = std::greater<Type>());
template<typename Type> void heapify(std::vector<Type> &v, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn = std::greater<Type>());
template<typename Type> void filterDown(std::vector<Type> &v, const size_t up_to, size_t node_index = 0, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn = std::greater<Type>());
template<typename Type> void h_swap(std::vector<Type> &v, const size_t el1, const size_t el2);

bool strLenCmp(const std::string &lhs, const std::string &rhs);
bool intSetSumCmp(const std::set<int> &lhs, const std::set<int> &rhs);

size_t parent(const size_t node_index);
size_t rightChild(const size_t up_to, const size_t node_index);
size_t leftChild(const size_t up_to, const size_t node_index);
size_t lastParent(const size_t size);


// heapsort vector
template<typename Type>
void heapSort(std::vector<Type> &v, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn) {
    
    // first heapify
    heapify(v, cmpFn);
    
    // remove from the heap, filterDown the root
    for (int i = static_cast<int>(v.size()) - 1; i >= 1; --i) {
        h_swap(v, 0, i);
        filterDown(v, i, 0, cmpFn);
    }
}


// rearranges elements of a given vector making it a heap
template<typename Type>
void heapify(std::vector<Type> &v, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn) {
    if (v.size() <= 1) return;
    for (int lp = static_cast<int>(lastParent(v.size())); lp >= 0; --lp)
        filterDown(v, v.size(), lp, cmpFn);
}


// filters down element at node_index to ensure max_heap property
template<typename Type>
void filterDown(std::vector<Type> &v, const size_t up_to, size_t node_index, std::function<bool (const Type &lhs, const Type &rhs)> cmpFn) {
    // if vector size is <= 1, there's nothing to filterDown
    if (up_to <= 1 || v.size() <= 1) return;
    
    auto l_parent = lastParent(up_to);
    while (l_parent >= node_index) {
        size_t l_child = -1;
        
        // get the index of the largest child
        // out_of_range is thrown only if there's no right child
        try {
            l_child = (cmpFn(v.at(rightChild(up_to, node_index)), v.at(leftChild(up_to, node_index))) ? rightChild(up_to, node_index) : leftChild(up_to, node_index));
        } catch (const std::out_of_range &e) {
            l_child = leftChild(up_to, node_index);
        }
        
        // swap with the largest child if the child > the element, else stop filterDown
        if (cmpFn(v.at(l_child), v.at(node_index))) {
            h_swap(v, l_child, node_index);
            node_index = l_child;
        } else break;
    }
}


// swaps two elements at indexes el1 and el2 in a given vector
template<typename Type>
void h_swap(std::vector<Type> &v, const size_t el1, const size_t el2) {
    Type temp = v.at(el1);
    v.at(el1) = v.at(el2);
    v.at(el2) = temp;
}

#endif /* heapsort_hpp */

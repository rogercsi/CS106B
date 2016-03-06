//
//  main.cpp
//  SortingLab
//
//  Created by Sergey Nikiforov on 04/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include <iostream>
#include "heapsort.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    vector<int> intTest{ 1,9,8,3,2 };
    vector<string> strTest{ {"Abc", "abc", "Bcd", "Zxy", "Zy", "Mw", "N"} };
    set<int> s1{ 0,2,3,6,8 };
    set<int> s2{ 10,5,3,2,8 };
    set<int> s3{ -5,0,3,8,5,7 };
    vector<set<int>> setTest{ s1, s2, s3 };
    
    // ints
    cout << "Vector of ints:" << endl;
    for (auto i : intTest) {
        cout << i << " ";
    }
    cout << endl;
    
    heapSort(intTest);
    
    cout << "Vector of ints after heapsort:" << endl;
    for (auto i : intTest) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    // strings
    cout << "Vector of strings:" << endl;
    for (auto i : strTest) {
        cout << i << " ";
    }
    cout << endl;
    
    function<bool(const string &, const string &)> strCompare = strLenCmp;
    heapSort(strTest, strCompare);
    
    cout << "Vector of strings after heapsort with custom compare callback:" << endl;
    for (auto i : strTest) {
        cout << i << " ";
    }
    cout << endl << endl;
    
    // sets of ints
    cout << "Vector of sets of ints:" << endl;
    for (auto i : setTest) {
        cout << "Set: ";
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    
    function<bool(const set<int> &, const set<int> &)> setCompare = intSetSumCmp;
    heapSort(setTest, setCompare);
    
    cout << "Vector of sets of ints after heapsort with custom compare:" << endl;
    for (auto i : setTest) {
        cout << "Set: ";
        for (auto j : i) {
            cout << j << " ";
        }
        cout << endl;
    }
    cout << endl;
    
    return 0;
}

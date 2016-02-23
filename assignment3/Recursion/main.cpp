//
//  main.cpp
//  Recursion
//
//  Created by Sergey Nikiforov on 17/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "recursion.hpp"
#include "trie.hpp"

int main(int argc, const char * argv[]) {
    
    // binary test
    std::cout << "Print in binary test [1-4]:" << std::endl;
    for (int i = 0; i < 5; ++i) {
        printInBinary(i);
        std::cout << std::endl;
    }
    std::cout << std::endl;
    
    // subset sum
    std::cout << "Subset Sum test (10 from [3,7,1,8,-3]):" << std::endl;
    std::vector<int> test = {3, 7, 1, 8, -3};
    if (canMakeSum(test, 10)) {
        std::cout << "true" << std::endl;
    } else {
        std::cout << "false" << std::endl;
    }
    std::cout << std::endl;
    
    // countWays
    std::cout << "Count ways test [0-5] steps" << std::endl;
    for (int i = 0; i < 6; ++i) {
        std::cout << "Num steps: " << i << ", Num ways: " << countWays(i) << std::endl;
    }
    std::cout << std::endl;
    
    // count votes
    std::cout << "Critical votes test 1 vote from [9,9,7,3,1,1]:" << std::endl;
    std::vector<int> votes = {9,9,7,3,1,1};
    std::cout << "Num of critical votes: " << countCriticalVotes(votes, 4) << std::endl;
    std::cout << std::endl;
    
    // list completions
    std::cout << "List completions test [72547]:" << std::endl;
    std::ifstream infile;
    infile.open("words.txt");
    Trie dict(infile);
    infile.close();
    listCompletions("72547", dict);
    std::cout << std::endl;
    
    
    // Recursive puzzle
    std::cout << "Is puzzle { 3,6,4,1,3,4,2,5,3,0 } solvable from pos#0?:" << std::endl;
    std::vector<int> squares{ 3,6,4,1,3,4,2,5,3,0 };
    //std::vector<int> squares{ 3,1,2,3,0 };
    std::cout << ((solvable(0, squares)) ? "true" : "false") << std::endl;
    std::cout << std::endl;
    
    // Cutting pipes
    std::vector<int> requests{ 4,3,4,1,7,8 };
    //std::vector<int> requests{ 7,7,5 };
    std::cout << "Min number of stock pipes of length 10 for requests { 4,3,4,1,7,8 }: " << cutStock(requests, 10) << std::endl;
    std::cout << std::endl;
    return 0;
}

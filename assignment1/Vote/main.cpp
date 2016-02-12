//
//  main.cpp
//  assignment1
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//
#include "vote.hpp"

int main(int argc, const char * argv[]) {
    
    unsigned int num_voters = 0, num_A = 0, num_B = 0;
    double spread = 0.0, error = 0.0;
    
    // handle user input
    userInput(num_voters, spread, error);
    splitVotes(num_A, num_B, spread, num_voters);
    std::cout << num_A << " " << num_B << std::endl;
    
    // conduct 500 trials
    int invalid_count = 0;
    for (int i = 0; i < 500; ++i) {
        if (!(isVotingValid(num_A, num_B, error))) {
            ++invalid_count;
        }
    }
    
    double err_chance = double(invalid_count / 5.0);
    std::cout << "Chance of an invalid election result after 500 trials = "
    << err_chance << std::endl;
    
    return 0;
}

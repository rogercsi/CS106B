//
//  main.cpp
//  Random writing
//
//  Created by Sergey Nikiforov on 14/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//
//  main.cpp for Random writing program
//
//  The program reads a source text, builds an order k Markov model for it, and generates
//  random output that follows the frequency patterns of the model
//

#include "rand-write.hpp"

int main(int argc, const char * argv[]) {
    
    // get file stream
    std::ifstream infile;
    getFileStream(infile);
    
    // get Markov order from user
    int order = getMarkovOrder();
    
    // read from file and construct a seed_map
    std::unordered_map<std::string, std::vector<char>> seed_map;
    buildSeedMap(infile, seed_map, order);
    
    // read complete, close the file
    infile.close();
    
    // generate random text
    const unsigned int MAX_OUTPUT = 2000;
    generateRandomText(seed_map, order, MAX_OUTPUT);
    
    return 0;
}

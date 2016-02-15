//
//  rand-write.hpp
//  Random writing
//
//  Created by Sergey Nikiforov on 15/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef rand_write_hpp
#define rand_write_hpp

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <random>

void getFileStream(std::ifstream &);
int getMarkovOrder();
char getNextChar(const std::vector<char> &);
void buildSeedMap(std::ifstream &, std::unordered_map<std::string, std::vector<char>> &, const int &);
void generateRandomText(const std::unordered_map<std::string, std::vector<char>> &, const unsigned int &, const unsigned int &);
std::string getMostFrequentSeed(const std::unordered_map<std::string, std::vector<char>> &);
#endif /* rand_write_hpp */

//
//  recursion.hpp
//  Recursion
//
//  Created by Sergey Nikiforov on 17/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef recursion_hpp
#define recursion_hpp

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include "trie.hpp"

void printInBinary(unsigned int number);

bool canMakeSum(std::vector<int> &nums, int target_sum);
bool recCanMakeSum(std::vector<int> sums, std::vector<int> nums, int target_sum);

int countWays(int num_stairs);

int countCriticalVotes(std::vector<int> &blocks, int block_index);
int recCountCriticalVotes(std::vector<int> vote_a, std::vector<int> vote_b, int block_votes, int total_votes);

std::shared_ptr<std::vector<std::string>> numberToWords(const std::string &number);
void recNumberToWord(std::string prefix, std::string rest, std::shared_ptr<std::vector<std::string>> &result);

std::string digitToLetters(const char &d);
void listCompletions(const std::string &digits, Trie &dict);
void recNumberToValidWord(std::string prefix, std::string rest, Trie &dict);

bool solvable(int start, std::vector<int> &squares);
bool recSolvable(int start, std::vector<int> &squares, int running_sum);

int cutStock(std::vector<int> &requests, int stockLength);
void getMaxCut(std::vector<int> &max_cut, int &max_cut_length, std::vector<int> current_cut, std::vector<int> requests, int stockLength);
int getNumCuts(std::vector<int> requests, int stockLength);
#endif /* recursion_hpp */

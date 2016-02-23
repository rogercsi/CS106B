//
//  recursion.cpp
//  Recursion
//
//  Created by Sergey Nikiforov on 17/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "recursion.hpp"

// PRINT IN BINARY

// int -> void
// prints binary representation of non-negative integer
void printInBinary(unsigned int n) {
    if (n > 1)
        printInBinary(n/2);
    std::cout << n % 2;
}


// CAN MAKE SUM

// vector<int>, int -> bool
// returns true if a subset of vector numbers sums to target number, false otherwise
bool canMakeSum(std::vector<int> &nums, int target_sum) {
    std::vector<int> sums = {};
    return recCanMakeSum(sums, nums, target_sum);
}


// helper recursive function
bool recCanMakeSum(std::vector<int> sums, std::vector<int> nums, int target_sum) {
    if (nums.empty()) {
        return (std::accumulate(sums.cbegin(), sums.cend(), 0) == target_sum);
    } else {
        std::vector<int> new_sums = sums;
        new_sums.push_back(nums.back());
        nums.pop_back();
        return (recCanMakeSum(new_sums, nums, target_sum) || recCanMakeSum(sums, nums, target_sum));
    }
}


// COUNT WAYS

// int -> int
// takes a positive numStairs value and returns the number of different ways to climb a staircase of that height
// taking strides of one or two stairs at a time
int countWays(int num_stairs) {
    if (num_stairs <= 2) {
        return num_stairs;
    } else {
        return countWays(num_stairs - 1) + countWays(num_stairs - 2);
    }
}


// COUNT VOTES

// vector<int> &, int -> int
// The function is given a vector of block vote counts and an index within that vector.
// The function counts the number of election outcomes in which the block at the given index has a critical vote.
// calls a recursive helper function
int countCriticalVotes(std::vector<int> &blocks, int block_index) {
    std::vector<int> a_votes = {};
    std::vector<int> b_votes = blocks;
    b_votes.erase(b_votes.begin() + block_index);
    return recCountCriticalVotes(a_votes, b_votes, blocks.at(block_index), std::accumulate(blocks.cbegin(), blocks.cend(), 0));
}


// helper recursive function to countCriticalVotes
int recCountCriticalVotes(std::vector<int> vote_a, std::vector<int> vote_b, int block_votes, int total_votes) {
    if (vote_b.empty()) {
        int sum_vote_a = std::accumulate(vote_a.cbegin(), vote_a.cend(), 0);
        // return 1 if sum for A <= half the votes and 'block_votes' voting for A changes the outcome
        return (((sum_vote_a <= total_votes / 2) && (block_votes + sum_vote_a > total_votes / 2)) ? 1 : 0);
    } else {
        std::vector<int> new_vote_a = vote_a;
        new_vote_a.push_back(vote_b.back());
        vote_b.pop_back();
        return recCountCriticalVotes(new_vote_a, vote_b, block_votes, total_votes) + recCountCriticalVotes(vote_a, vote_b, block_votes, total_votes);
    }
}


// LIST COMPLETIONS

// string, Trie -> void
// prints all words from the dict that can be formed by extending the given digit sequence
void listCompletions(const std::string &digits, Trie &dict) {
    std::cout << "Valid completions for \"" << digits << "\":" << std::endl;
    recNumberToValidWord("", digits, dict);
}


// helper recursive function to listCompletions
void recNumberToValidWord(std::string prefix, std::string rest, Trie &dict) {
    if (rest.empty()) {
        auto words = dict.getWordsWithPrefix(prefix);
        for (auto word : *words) {
            std::cout << word << std::endl;
        }
    } else {
        auto options = digitToLetters(rest.at(0));
        for (auto ch : options) {
            if (dict.containsPrefix(prefix + ch)) {
                recNumberToValidWord(prefix + ch, rest.substr(1), dict);
            }
        }
    }
}


// string -> shared_ptr<vector<string>>
// given a string of digits, returns a shared_ptr to vector of all possible strings of letters
std::shared_ptr<std::vector<std::string>> numberToWords(const std::string &number) {
    auto result = std::make_shared<std::vector<std::string>>();
    recNumberToWord("", number, result);
    return result;
}


// helper recursive function to fill vector of strings pointed by shared_ptr
void recNumberToWord(std::string prefix, std::string rest, std::shared_ptr<std::vector<std::string>> &result) {
    if (rest.empty()) {
        result->push_back(prefix);
    } else {
        auto options = digitToLetters(rest.at(0));
        for (auto ch : options) {
            recNumberToWord(prefix + ch, rest.substr(1), result);
        }
    }
}


// const char -> string
// helper function
// returns string of legal letters corresponding to a given digit
std::string digitToLetters(const char &d) {
    switch (d) {
        case '0': return "0";
        case '1': return "1";
        case '2': return "abc";
        case '3': return "def";
        case '4': return "ghi";
        case '5': return "jkl";
        case '6': return "mno";
        case '7': return "pqrs";
        case '8': return "tuv";
        case '9': return "wxyz";
        default: throw "invald char";
    }
}

// SOLVABLE

// int, vector<int> -> bool
// takes a starting position of the marker along with the vector of squares
// returns true if it is possible to solve the puzzle from the starting configuration and false if it is impossible
bool solvable(int start, std::vector<int> &squares) {
    return recSolvable(start, squares, 0);
}


// recursive helper function to solvable
bool recSolvable(int start, std::vector<int> &squares, int running_sum) {
    if (start == squares.size() - 1) {
        // we are at the end
        return true;
    }
    if (running_sum + squares.at(start) == 0 || running_sum - squares.at(start) == 0) {
        // next step produces a cycle
        return false;
    }
    if (((start - squares.at(start)) < 0) && (start + squares.at(start) > squares.size() - 1)) {
        // we can't go anywhere not crossing the bounds
        return false;
    }
    if ((start - squares.at(start)) < 0) {
        // we can go only right
        return recSolvable(start + squares.at(start), squares, running_sum + squares.at(start));
    } else {
        if (start + squares.at(start) > squares.size() - 1) {
            // we can go only left
            return recSolvable(start - squares.at(start), squares, running_sum - squares.at(start));
        } else {
            // we can go either way
            return recSolvable(start + squares.at(start), squares, running_sum + squares.at(start)) || \
                   recSolvable(start - squares.at(start), squares, running_sum - squares.at(start));
        }
    }
}


// CUT STOCK

// vector<int>&, int -> int
// returns the minimum number of stock pipes needed to service all requests in the vector
int cutStock(std::vector<int> &requests, int stockLength) {
    return getNumCuts(requests, stockLength);
}


// helper function to cutStock
// recursively calls getMaxCut to cut from requests
// returns min number of cuts
int getNumCuts(std::vector<int> requests, int stockLength) {
    if (requests.empty()) {
        return 0;
    } else {
        // get max cut
        std::vector<int> max_cut{};
        int max_cut_length = 0;
        getMaxCut(max_cut, max_cut_length, std::vector<int>{}, requests, stockLength);
        
        // cut max_cut from requests
        std::sort(requests.begin(), requests.end());
        std::sort(max_cut.begin(), max_cut.end());
        std::vector<int> difference;
        std::set_difference(requests.begin(), requests.end(), max_cut.begin(), max_cut.end(), std::back_inserter(difference));
        return 1 + getNumCuts(difference, stockLength);
    }
}


// helper function to getNumCuts
// recursively finds all combinations of cuts and sets max_cut vector from a given requests vector
void getMaxCut(std::vector<int> &max_cut, int &max_cut_length, std::vector<int> current_cut, std::vector<int> requests, int stockLength) {
    if (requests.empty()) {
        auto current_cut_length = std::accumulate(current_cut.cbegin(), current_cut.cend(), 0);
        if ((current_cut_length <= stockLength) && (current_cut_length > max_cut_length)) {
            max_cut_length = current_cut_length;
            max_cut = current_cut;
        }
    } else {
        std::vector<int> new_cut = current_cut;
        new_cut.push_back(requests.back());
        requests.pop_back();
        getMaxCut(max_cut, max_cut_length, new_cut, requests, stockLength);
        getMaxCut(max_cut, max_cut_length, current_cut, requests, stockLength);
    }
}

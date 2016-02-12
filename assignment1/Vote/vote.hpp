//
//  vote.hpp
//  assignment1
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef vote_hpp
#define vote_hpp

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>

void userInput(unsigned int & n, double &s, double &e);
void splitVotes(unsigned int &a, unsigned int &b, const double &spread, const unsigned int &num_voters);
void votingMachine(std::vector<unsigned int> &votes, const double &err);
bool isVotingValid(const unsigned int &num_A, const unsigned int &num_B, const double &err);

#endif /* vote_hpp */

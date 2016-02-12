//
//  vote.cpp
//  assignment1
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "vote.hpp"

// unsigned int, double, double -> void
// handles user input for voters num, spread and error
void userInput(unsigned int & n, double & s, double & e) {
    // number of voters
    do {
        std::cout << "Enter number of voters: ";
        if (!(std::cin >> n)) {
            std::cout << "Please enter integer value" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            break;
        }
    } while(true);
    
    // spread
    do {
        std::cout << "Enter percentage spread between the candidates: ";
        if (!(std::cin >> s) || s > 1.0 || s <= 0) {
            std::cout << "Please enter non-negative float value < 1.0" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            break;
        }
    } while(true);
    
    // voting error
    do {
        std::cout << "Enter voting error percentage: ";
        if (!(std::cin >> e) || s > 1.0 || s <= 0) {
            std::cout << "Please enter non-negative float value < 1.0" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            break;
        }
    } while(true);
}


// unsigned int, unsigned int -> void
// calculates initial split in votes, num_A being the winning side
void splitVotes(unsigned int &a, unsigned int &b, const double &spread, const unsigned int &num_voters) {
    double b_percent = (1.0 - spread)/2;
    double a_percent = 1.0 - b_percent;
    a = num_voters * a_percent;
    b = num_voters - a;
}


// vector -> void
// introduces voting error to voting vector: flips votes from 1 to 0 with prob err
void votingMachine(std::vector<unsigned int> &votes, const double &err) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    for (auto &v : votes) {
        double number = distribution(gen);
        if (number < err) {
            v = 0;
        }
    }
}


// const unsigned int, const unsigned int, const double -> bool
// predicate function, returns true if voting result is the same after introducint voting machine error, false otherwise
bool isVotingValid(const unsigned int &num_A, const unsigned int &num_B, const double &err) {
    
    // create initial voters vectors
    std::vector<unsigned int> vec_A, vec_B;
    std::fill_n(std::back_inserter(vec_A), num_A, 1);
    std::fill_n(std::back_inserter(vec_B), num_B, 1);
    //std::cout << vec_A.size() << " " << vec_B.size() << std::endl;
    
    // introduce voting error
    votingMachine(vec_A, err);
    votingMachine(vec_B, err);
    
    // sum error votes
    int sum_A = std::accumulate(vec_A.cbegin(), vec_A.cend(), 0);
    int sum_B = std::accumulate(vec_B.cbegin(), vec_B.cend(), 0);
    int err_A = num_A - sum_A;
    int err_B = num_B - sum_B;
    sum_A += err_B;
    sum_B += err_A;
    //std::cout << sum_A << " " << sum_B << std::endl;
    
    // check if the result is still valid
    return (sum_A > sum_B);
}
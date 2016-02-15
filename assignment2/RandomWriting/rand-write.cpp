//
//  rand-write.cpp
//  Random writing
//
//  Created by Sergey Nikiforov on 15/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "rand-write.hpp"

// & ifstream -> void
// opens a user-specified file and associates it with an input filestream
void getFileStream(std::ifstream &input) {
    while (true) {
        std::cout << "Please enter an absolute path to a text file: ";
        std::string filename;
        getline(std::cin, filename);
        if (!filename.empty()) {
            input.open(filename.c_str());
            if (input.good()) {
                break;
            } else {
                std::cout << "Error. Try again, please." << std::endl;
            }
        }
    }
}


// void -> int
// promts user to set a Markov order in the range [1, 10]
int getMarkovOrder() {
    int order_value = 0;
    while (true) {
        std::cout << "Please enter an integer Markov Order value [1 - 10]: ";
        if (!(std::cin >> order_value) || order_value < 1 || order_value > 10) {
            std::cout << "Invalid value. Please try again" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            return order_value;
        }
    }
}


// ifstream, unordered_map<string, vector<char>>, const int -> void
// builds a seed mapping for a given Markov order value from a valid ifstream
void buildSeedMap(std::ifstream &infile, std::unordered_map<std::string, std::vector<char>> &seed_map, const int &order) {
    
    // get initial seed
    std::string seed = "";
    for (int i = 0; i < order; ++i) {
        auto c = infile.get();
        if (infile.good()) {
            seed += c;
        } else {
            //std::cout << "file is shorter than the Markov order value" << std::endl;
            throw "file is shorter than the Markov order value";
        }
    }
    
    // construct seed_map
    while (infile.good()) {
        // get next char
        auto c = infile.get();
        
        // ignore newlines
        if (c == '\n' || c == '\r') {
            c = ' ';
        }
        
        // add c to corr seed
        if (seed_map.find(seed) != seed_map.end()) {
            // break if EOF
            if (!infile.good()) break;
            
            // seed already exists
            seed_map.at(seed).push_back(c);
        } else {
            // add new seed
            seed_map.emplace(seed, std::vector<char>());
            
            // break if EOF
            if (!infile.good()) break;
            
            seed_map.at(seed).push_back(c);
        }
        
        // renew the seed
        seed += c;
        seed.erase(0, 1);
    }

}

// unordered_map<string, vector<char>> &, const int & -> void
// builds a random text for a given Markov order value of length "text_length" and prints it to stdout
void generateRandomText(const std::unordered_map<std::string, std::vector<char>> &seed_map, const unsigned int &order, const unsigned int &text_length) {
    
    // find the most frequent seed
    std::string seed = getMostFrequentSeed(seed_map);
    
    std::cout << "Most frequent seed: " << seed << std::endl;
    std::cout << "Random text for order " << order << " Markov model:" << std::endl;
    std::cout << seed;
    
    for (unsigned int i = order; i < text_length; ++i) {
        
        // break if there're no chars to choose from
        if (seed_map.at(seed).size() == 0) break;
        
        char next_char = getNextChar(seed_map.at(seed));
        
        std::cout << next_char;
        
        // renew the seed
        seed += next_char;
        seed.erase(0, 1);
    }
    std::cout << std::endl;

}


// unordered_map<string, vector<char>> & -> string
// returns a string: the key of the longest value vector (it corresponds to the most frequent seed)
std::string getMostFrequentSeed(const std::unordered_map<std::string, std::vector<char>> &seed_map) {
    std::string result = "";
    unsigned long max_freq = 0, cur_freq = 0;
    for (auto k : seed_map) {
        cur_freq = k.second.size();
        if (cur_freq > max_freq) {
            result = k.first;
            max_freq = cur_freq;
        }
    }
    return result;
}

// vector<char> -> char
// randomly selects a char from a given vector
// does not check the vector size
char getNextChar(const std::vector<char> &chvec) {
    std::random_device random_device;
    std::mt19937 engine{random_device()};
    std::uniform_int_distribution<unsigned long> dist(0, chvec.size() - 1);
    return chvec[dist(engine)];
}

//
//  main.cpp
//  soundex
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//
#include "soundex.hpp"


int main(int argc, const char * argv[]) {
    std::string surname = "", soundex_code = "";
    while (true) {
        std::cout << "Enter surname (RETURN to quit): ";
        if (!(getline(std::cin, surname))) {
            if (std::cin.eof()) {
                std::cout << std::endl;
                break;
            }
            std::cout << "Please enter a valid surname" << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
        } else {
            if (surname.empty()) {
                return 0;
            } else {
                soundex_code = soundex(surname);
                std::cout << "Soundex code for " << surname << " is " << soundex_code << std::endl;
            }
        }
    }
    return 0;
}

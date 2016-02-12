//
//  soundex.cpp
//  soundex
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "soundex.hpp"

// string -> string
// consumes a surname, returns corresponding Soundex code for it
std::string soundex(std::string name) {
    std::string result = "";
    const std::string zero = "AEIOUHWY", one = "BFPV", two = "CGJKQSXZ",\
                      three = "DT", four = "L", five = "MN", six = "R";
    const std::vector<const std::string> codes = {zero, one, two, three, four, five, six};
    
    // convert name to uppercase
    std::transform(name.begin(), name.end(), name.begin(), toupper);
    
    // 1st letter as is
    auto beg = name.cbegin();
    while (beg != name.cend()) {
        if ((bool)std::isalpha(*beg)) {
            result += *beg;
            break;
        } else {
            ++beg;
        }
    }

    // convert remaining letters to digits
    if (beg != name.cend()) {
        for (++beg; beg != name.cend(); ++beg) {
            if ((bool)std::isalpha(*beg)) {
                for (int i = 0; i != codes.size(); ++i) {
                    if (codes[i].find(*beg) != std::string::npos) {
                        result += std::to_string(i);
                        break;
                    }
                }
            }
        }
    } else {
        return std::string("Invalid surname: no alphabetic characters");
    }
    
    // remove consecutive digits
    std::string temp = "";
    temp.push_back(result.at(0));
    for (auto c = result.cbegin() + 1; c != result.cend(); ++c) {
        if (*c != *(c-1)) {
            temp += *c;
        }
    }
    result = temp;
    
    // erase zeroes
    while (true) {
        auto found = std::find(result.cbegin(), result.cend(), '0');
        if (found != result.cend()) {
            result.erase(found);
        } else {
            break;
        }
    }
    
    // check length
    if (result.size() > 4) {
        result = result.substr(0, 4);
    } else if (result.size() < 4) {
        while (result.size() != 4) {
            result.push_back('0');
        }
    }
    
    return result;
}
//
//  main.cpp
//  assignment1
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//
#include "perfect.hpp"

int main(int argc, const char * argv[]) {

    for (int i = 1; i <= 10000; ++i) {
        if (isPerfect(i)) {
            std::cout << "Found a perfect number: " << i << std::endl;
        }
    }
     
    return 0;
}

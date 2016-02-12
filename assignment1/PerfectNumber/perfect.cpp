//
//  perfect.cpp
//  assignment1
//
//  Created by Sergey Nikiforov on 10/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "perfect.hpp"

// const int & -> bool
// takes integer and returns true if it's a perfect int, false otherwise
// isPerfect(6) -> true
// isPerfect(5) -> false
bool isPerfect(const int &n) {
    unsigned int sum = 0;
    for (int i = 1; i < n; ++i) {
        if ((n % i) == 0) {
            sum += i;
        }
    }
    return (sum == n);
}

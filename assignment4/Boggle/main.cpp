//
//  main.cpp
//  Boggle
//
//  Created by Sergey Nikiforov on 25/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "boggle.hpp"

using namespace std;

int main(int argc, const char * argv[]) {
    ifstream infile;
    if (argc == 1) {
        infile.open("/Users/sergey/Dropbox/CS106B/assignments/assignment4/Boggle/Boggle/words.txt");
        if (!infile.good()) {
            cout << "Error opening a default dictionary file" << endl;
            return -1;
        }
    }
    if (argc == 2) {
        infile.open(argv[1]);
        if (!infile.good()) {
            cout << "Error opening a dictionary file" << endl;
            return -1;
        }
    }
    if (argc > 2) {
        cout << "Too many args..." << endl;
        return -1;
    }
    Boggle game(infile);
    infile.close();
    game.startGame();
    return 0;
}

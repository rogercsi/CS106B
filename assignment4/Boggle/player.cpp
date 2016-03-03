//
//  player.cpp
//  Boggle
//
//  Created by Sergey Nikiforov on 02/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "player.hpp"
#include "board.hpp"

using namespace std;


// adds a word to the player's words set, updates player's score
// no check performed if the word is valid
bool Player::addWord(const string &word) {
    auto flag = words.insert(word);
    if (flag.second) {
        score += word.length() - WORD_MIN_SIZE + 1;
        return true;
    } else {
        return false;
    }
}


// prints player's words
void Player::showWords() const {
    cout << "Your words: ";
    for (auto word : words) {
        cout << word << " ";
    }
    cout << endl;
}


// prints player's score
void Player::showScore() const {
    cout << "Your score: " << score << endl;
}


// empties the word set
void Player::emptyWordSet() {
    words.clear();
}


// zeroes the score
void Player::zeroScore() {
    score = 0;
}
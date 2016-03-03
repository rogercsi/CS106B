//
//  boggle.cpp
//  Boggle
//
//  Created by Sergey Nikiforov on 02/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "boggle.hpp"

using namespace std;


// default constructor
Boggle::Boggle() : pcscore(0), board(make_unique<Board>()), player(make_unique<Player>()) { }


// overloaded constructor
Boggle::Boggle(ifstream &infile) : pcscore(0), board(make_unique<Board>(infile)), player(make_unique<Player>()) {
    board->shuffleCubes();
}


// initialize the game
bool Boggle::initGame() {
    cout << "Welcome!  You're about to play an intense game of mind-numbing Boggle. " << endl << endl;
    
    cout << "The boggle board is a grid onto which I will randomly distribute "
    << "cubes. These 6-sided cubes have letters rather than numbers on the faces, "
    << "creating a grid of letters on which you try to form words. You go first, "
    << "entering all the words you can find that are formed by tracing adjoining "
    << "letters. Two letters adjoin if they are next to each other horizontally, "
    << "vertically, or diagonally. A letter can only be used once in the word. Words "
    << "must be at least 4 letters long and can only be counted once. You score points "
    << "based on word length: a 4-letter word is worth 1 point, 5-letters earn 2 "
    << "points, and so on. After your turn, the computer "
    << "will find all the remaining words and double or triple your score=)" << endl;
    
    while (true) {
        cout << "\nHit return when you're ready...";
        string i;
        if (!(getline(cin, i))) {
            cout << endl;
            return false;
        }
        if (i.empty()) return true;
    }
}


// choose Player's name
bool Boggle::choosePlayerName() {
    string name;
    while (true) {
        cout << "Please, enter your name: ";
        if (!(getline(cin, name))) {
            if (cin.eof()) {
                cout << endl;
                return false;
            }
            cout << "Please enter a valid name" << endl;
            cin.clear();
            cin.ignore(10000, '\n');
        } else {
            if (!name.empty()) {
                player->setName(name);
                return true;
            }
        }
    }
}


// get words from human player
bool Boggle::getPlayerInput() {
    while (true) {
        string input = "";
        cout << "Add a word [RETURN to exit]: ";
        if (!getline(cin, input)) {
            if (cin.eof()) {
                cout << endl;
                return false;
            }
        } else {
            // player hit return - end of input
            if (input.length() == 0) break;
            else {
                // input continues
                if (input.length() < 4) cout << "Word must be at least 4 characters long" << endl;
                else {
                    if (board->isValidWord(input)) {
                        if (player->addWord(input)) {
                            cout << "Correct!" << endl;
                            cout << endl;
                            board->showWord(board->getAllWords().find(input)->second);
                            cout << endl;
                            player->showWords();
                            player->showScore();
                            cout << "The board:" << endl;
                            cout << endl;
                            board->drawBoard();
                            cout << endl;
                        } else {
                            cout << "You have already entered this word..." << endl;
                        }
                    }
                    else cout << "Invalid word!" << endl;
                }
            }
        }
    }
    return true;
}


// prints PC's set of words
void Boggle::showPCWords() const {
    cout << "PC's words: ";
    for (auto word : pcwords) {
        cout << word << " ";
    }
    cout << endl;
}


// prints PC's score
void Boggle::showPCScore() const {
    cout << "PC's score: " << pcscore << endl;
}


// PC turn
void Boggle::makePCTurn() {
    cout << "Now is PC's turn" << endl;
    // play PC's part - get all words from the board, excluding those found by the player
    auto player_words = player->getWords();
    for (auto word : board->getAllWords()) {
        if (player_words.find(word.first) == player_words.end()) {
            pcwords.insert(word.first);
            pcscore += word.first.length() - WORD_MIN_SIZE + 1;
        }
    }
    // show the words & the score
    showPCWords();
    showPCScore();
}


// main loop
void Boggle::startGame() {
    if (!initGame()) return;
    if (!choosePlayerName()) return;
    bool to_game = true;
    while (to_game) {
        
        // say hello
        cout << "Welcome to the game, " << player->getName() << "!" << endl;
        
        // shuffle cubes
        board->shuffleCubes();
        
        // show the cubes
        cout << "The board:" << endl << endl;
        board->drawBoard();
        cout << endl;
        
        // make sure the player's word set is empty and the score is 0
        player->zeroScore();
        player->emptyWordSet();
        
        // get input from user
        if (!getPlayerInput()) break;
        
        // PC's turn
        makePCTurn();
        cout << endl;
        
        // show the results
        player->showScore();
        showPCScore();
        if (player->getScore() > pcscore)
            cout << "Congratulations! You won!" << endl;
        if (player->getScore() == pcscore)
            cout << "Draw!" << endl;
        if (player->getScore() < pcscore) {
            cout << "PC won!" << endl;
        }
        cout << endl;
        
        // continue?
        while (true) {
            string answ = "";
            cout << "Do you want to play once again (y/n)? ";
            if (!getline(cin, answ)) {
                if (cin.eof()) {
                    cout << endl;
                    to_game = false;
                    break;
                }
                cin.clear();
                cin.ignore(10000, '\n');
            } else {
                if (answ == "n" || answ == "N" || answ == "No" || answ == "no" || answ == "NO") {
                    cout << "Thank you for the game!" << endl;
                    to_game = false;
                    break;
                }
                if (answ == "y" || answ == "Y" || answ == "Yes" || answ == "yes" || answ == "YES") {
                    cout << "Starting again..." << endl;
                    break;
                }
            }
        }
    }
}
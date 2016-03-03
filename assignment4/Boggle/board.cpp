//
//  board.cpp
//  Boggle
//
//  Created by Sergey Nikiforov on 26/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#include "board.hpp"

using namespace std;

//array<string, 16> Board::standardCubes = {"AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS", "AOOTTW", "CIMOTU", "DEILRX", "DELRVY", "DISTTY", "EEGHNW", "EEINSU", "EHRTVW", "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"};

array<string, 16> Board::standardCubes = { {"aaeegn", "abbjoo", "achops", "affkps", "aoottw", "cimotu", "deilrx", "delrvy", "distty", "eeghnw", "eeinsu", "ehrtvw", "eiosst", "elrtty", "himnqu", "hlnnrz"} };


// default constructor
// picks the 1st letter from a cube; cubes are ordered the same as in standardCubes array
Board::Board() : lexicon(make_unique<Trie>()) {
    size_t i = 0;
    for (auto &row : cells) {
        for (auto &el : row) {
            el = standardCubes.at(i++).at(0);
        }
    }
}


// constructor from ifstream to populate lexicon Trie
Board::Board(ifstream &infile) : lexicon(make_unique<Trie>(infile)) {
    size_t i = 0;
    for (auto &row : cells) {
        for (auto &el : row) {
            el = standardCubes.at(i++).at(0);
        }
    }
}


// draws the board
void Board::drawBoard() const {
    for (auto row : cells) {
        for (auto el : row) {
            cout << el << " ";
        }
        cout << endl;
    }
}


// randomly shuffles the cubes
void Board::shuffleCubes() {
    random_device random_device;
    mt19937 engine{random_device()};
    
    // shuffle cubes
    shuffle(standardCubes.begin(), standardCubes.end(), engine);
    
    // reassign to cells, randomly selecting front cube side
    size_t i = 0;
    for (auto &row : cells) {
        for (auto &el : row) {
            uniform_int_distribution<unsigned long> dist(0, 5);
            el = standardCubes.at(i++).at(dist(engine));
        }
    }
    
    // refresh allwords
    updateAllWords();
}


// updates a map of strings to paths - valid words from the board
void Board::updateAllWords() {
    allwords.clear();
    for (auto row = 0; row < BOARD_SIZE; ++row) {
        for (auto col = 0; col < BOARD_SIZE; ++col) {
            set<pair<int, int>> visited{}, moves = getValidMoves(row, col, visited);
            vector<pair<int, int>> path{};
            recGetAllWords(allwords, cells[row][col], lexicon, visited, path, moves, row, col);
        }
    }
}


// recursive helper function to getAllWords()
// populates words map
void Board::recGetAllWords(map<string, vector<pair<int, int>>> &words, string str, const unique_ptr<Trie> &dict, set<pair<int, int>> visited, vector<pair<int, int>> path, set<pair<int, int>> moves, size_t row, size_t col) {
    // add a vertex to visited & path containers
    visited.insert(make_pair(row, col));
    path.push_back(make_pair(row, col));
    
    // accept only valid words not shorter than WORD_MIN_SIZE chars
    if (dict->containsWord(str) && str.length() >= WORD_MIN_SIZE) {
        words[str] = path;
    }
    
    // DFS through valid moves
    for (auto m : moves) {
        if (dict->containsPrefix(str + cells[m.first][m.second]) && visited.find(m) == visited.end()) {
            auto new_moves = getValidMoves(m.first, m.second, visited);
            recGetAllWords(words, str + cells[m.first][m.second], dict, visited, path, new_moves, m.first, m.second);
        }
    }
}


// returns true if a given word found in the allwords set, false otherwise
bool Board::isValidWord(const std::string &word) const {
    return (allwords.find(word) != allwords.end());
}


// prints selected word (denoted by vector of pairs) in caps
void Board::showWord(const vector<pair<int, int>> &path) const {
    auto new_cells = cells;
    for (auto letter : path)
        new_cells[letter.first][letter.second] = toupper(*new_cells[letter.first][letter.second].c_str());
    for (auto row : new_cells) {
        for (auto el : row) {
            cout << el << " ";
        }
        cout << endl;
    }
}


// helper function
// returns a set of pairs of ints - valid moves; visited cells are checked
set<pair<int, int>> getValidMoves(int row, int col, set<pair<int, int>> &visited) {
    set<pair<int, int>> result{};
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < BOARD_SIZE && j >= 0 && j < BOARD_SIZE) {
                pair<int, int> m{i, j};
                
                // add only if a vertex hasn't been visited yet
                if (visited.find(m) == visited.end())
                    result.insert(make_pair(i, j));
            }
        }
    }
    return result;
}
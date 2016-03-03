//
//  board.hpp
//  Boggle
//
//  Created by Sergey Nikiforov on 26/02/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef board_hpp
#define board_hpp

#include "trie.hpp"
#include <array>
#include <random>
#include <set>
#include <cctype>
#include <map>

const int BOARD_SIZE = 4;
const int WORD_MIN_SIZE = 4;

class Board {
public:
    Board();
    Board(std::ifstream &infile);
    void drawBoard() const;
    void shuffleCubes();
    bool isValidWord(const std::string &word) const;
    void showWord(const std::vector<std::pair<int, int>> &path) const;
    std::map<std::string, std::vector<std::pair<int, int>>> getAllWords() const { return allwords; }
    std::map<std::string, std::vector<std::pair<int, int>>> &getAllWords() { return allwords; }
private:
    std::array<std::array<std::string, BOARD_SIZE>, BOARD_SIZE> cells;
    static std::array<std::string, 16> standardCubes;
    std::map<std::string, std::vector<std::pair<int, int>>> allwords;
    std::unique_ptr<Trie> lexicon;
    void updateAllWords();
    void recGetAllWords(std::map<std::string, std::vector<std::pair<int, int>>> &words, std::string str, const std::unique_ptr<Trie> &dict, std::set<std::pair<int, int>> visited, std::vector<std::pair<int, int>> path, std::set<std::pair<int, int>> moves, size_t row, size_t col);
};

// helper functions
std::set<std::pair<int, int>> getValidMoves(int row, int col, std::set<std::pair<int, int>> &visited);
#endif /* board_hpp */

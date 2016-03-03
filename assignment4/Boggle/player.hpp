//
//  player.hpp
//  Boggle
//
//  Created by Sergey Nikiforov on 02/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef player_hpp
#define player_hpp

#include <string>
#include <set>
#include <iostream>

class Player {
public:
    Player() : name("Player"), score(0), words(std::set<std::string>{}) { }
    Player(const std::string &name) : name(name), score(0), words(std::set<std::string>{}) { }
    std::string getName() const { return name; }
    unsigned int getScore() const { return score; }
    void setName(const std::string &n) { name = n; }
    std::set<std::string> getWords() const { return words; }
    void showWords() const;
    void showScore() const;
    bool addWord(const std::string &word);
    void emptyWordSet();
    void zeroScore();
private:
    std::string name;
    unsigned int score;
    std::set<std::string> words;
};

#endif /* player_hpp */

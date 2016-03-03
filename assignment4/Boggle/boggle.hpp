//
//  boggle.hpp
//  Boggle
//
//  Created by Sergey Nikiforov on 02/03/16.
//  Copyright © 2016 Sergey Nikiforov. All rights reserved.
//

#ifndef boggle_hpp
#define boggle_hpp

#include "board.hpp"
#include "player.hpp"

class Boggle {
public:
    Boggle(std::ifstream &dictfile);
    void startGame();
private:
    Boggle();
    bool initGame();
    bool choosePlayerName();
    bool getPlayerInput();
    void makePCTurn();
    void showPCWords() const;
    void showPCScore() const;
    unsigned int pcscore;
    std::set<std::string> pcwords;
    std::unique_ptr<Board> board;
    std::unique_ptr<Player> player;
};

#endif /* boggle_hpp */

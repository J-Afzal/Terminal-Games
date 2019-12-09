//
//  TicTacToe.hpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <iostream>
#include <vector>

class TicTacToe {
public:
    //Constructors and destructor
    TicTacToe();
    TicTacToe(const TicTacToe& aTicTacToe);
    ~TicTacToe();
    
    //Custom cout function
    friend std::ostream& operator<< (std::ostream& Output, const TicTacToe& aTicTacToe);
    
    //Custom operator function
    TicTacToe& operator = (const TicTacToe& aTicTacToe);
    
    //TicTacToe specific functions
    void Play_Game(void);
    
private:
    std::vector<char> GameData;
    char CurrentPlayer;
    unsigned int NumberOfTurns;
    
    //Private member functions
    void Input(void);
    void Toggle_Player(void);
    bool Game_Winner(void);
    bool Game_Over(void);
};

#endif /* TicTacToe_hpp */

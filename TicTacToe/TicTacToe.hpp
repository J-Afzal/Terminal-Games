//
//  TicTacToe.hpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <vector>

std::vector< std::vector<int> > Get_Size_Of_Grid(void);

int Get_Number_Of_players(void);

int Get_User_X_O(void);

bool Game_Over(const std::vector< std::vector<int> >& GameData);

bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData);

void Display_Current_Game(const std::vector< std::vector<int> >& GameData);

char Toggle_Player(const int& CurrentPlayer);

std::vector< std::vector<int> > Ask_User_For_Next_Input(std::vector< std::vector<int> >& GameData, const int& CurrentPlayer);

#endif /* TicTacToe_hpp */

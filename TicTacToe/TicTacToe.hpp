//
//  TicTacToe.hpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  TicTacToe game with options to define the size of the
//  grid - which will be assumed to be square. Also options
//  for 0, 1 and 2 player modes - where 2 player = 2 human players;
//  1 player = 1 human player and one AI player; and 0 player = no
//  human players and 2 AIs. The AI are dumb and make pseudo random
//  moves. The game can be played through one function Play_TicTacToe()
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <vector>



void Play_TicTacToe(void);

void Setup_Game(unsigned int& NumberOfTurns, unsigned int& CurrentPlayer, unsigned int& NumberOfPlayers, unsigned int& UserXO, std::vector< std::vector<int> >& GameData);

std::vector< std::vector<int> > Get_Size_Of_Grid(void);

int Get_Number_Of_Players(void);

int Get_User_X_O_Choice(void);

bool Game_Over(const std::vector< std::vector<int> >& GameData);

bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData);

void Display_Current_Game(const std::vector< std::vector<int> >& GameData);

char Toggle_Player(const int& CurrentPlayer);

std::vector< std::vector<int> > Ask_User_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);

std::vector< std::vector<int> > Ask_AI_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);

void Display_Winner(const unsigned int& NumberOfTurns, const std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);



#endif /* TicTacToe_hpp */

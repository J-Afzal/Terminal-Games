//
//  Chess.hpp
//  Chess
//
//  Created by Main on 07/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#ifndef Chess_hpp
#define Chess_hpp

#include <iostream>
#include <vector>

void Setup_Game(std::vector< std::vector<std::string> >& Board, unsigned int& NumberOfPlayers, std::string& HumanPlayer, std::string& CurrentPlayer);

int Ask_User_For_Number_Of_Players(void);

bool Game_Over();

void Toggle_Player(std::string& CurrentPlayer);

void Display_Game(const std::vector< std::vector<std::string> >& Board);

std::string Ask_AI_For_Next_Move();

std::string Ask_User_For_Next_Move();

void Execute_Next_Move();

void Display_Winning_Message();

#endif /* Chess_hpp */

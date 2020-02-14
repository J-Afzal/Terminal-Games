//
//  main.cpp
//  Chess
//
//  Created by Main on 03/01/2020.
//  Copyright © 2020 Junaid Afzal. All rights reserved.
//

#include "Chess.hpp"
#include <iostream>
#include <vector>

int main(void) {
    std::vector< std::vector<std::string> > Board;
    unsigned int NumberOfPlayers;
    std::string HumanPlayer, CurrentPlayer;
    
    Setup_Game(Board, NumberOfPlayers, HumanPlayer, CurrentPlayer);
    
    while (!Game_Over())
    {
        Toggle_Player(CurrentPlayer);

        Display_Game(Board);

        std::string NextMove;

        switch (NumberOfPlayers)
        {
            case 0:
                NextMove = Ask_AI_For_Next_Move();
                break;

            case 1:
            {
                if (CurrentPlayer == HumanPlayer)
                    NextMove = Ask_User_For_Next_Move();

                else
                    NextMove = Ask_AI_For_Next_Move();

                break;
            }

            case 2:
                NextMove = Ask_User_For_Next_Move();
                break;

            default:
                std::cout << "Error in number of players switch statement" << std::endl;
                break;
        }

        Execute_Next_Move();
    }

    Display_Game(Board);

    Display_Winning_Message();
    
    return 0;
}

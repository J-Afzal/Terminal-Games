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
    
//    while (!Game_Over())
//    {
//        Toggle_Player(CurrentPlayer);
//        
        Display_Game(Board);
//
//        std::string NextMove;
//
//        switch (NumberOfPlayers)
//        {
//            case 0:
//                NextMove = Ask_AI_For_Next_Move();
//                break;
//
//            case 1:
//            {
//                if (CurrentPlayer == HumanPlayer)
//                    NextMove = Ask_User_For_Next_Move();
//
//                else
//                    NextMove = Ask_AI_For_Next_Move();
//
//                break;
//            }
//
//            case 2:
//                NextMove = Ask_User_For_Next_Move();
//                break;
//
//            default:
//                std::cout << "Error in number of players switch statement" << std::endl;
//                break;
//        }
//
//        Execute_Next_Move();
//    }
//
//    Display_Game(Board);
//
//    Display_Winning_Message();
    
    return 0;
}





//    std::cout << "\u265C \u265E \u265D \u265B \u265A \u265D \u265E \u265C" << std::endl;
//    std::cout << "\u265F \u265F \u265F \u265F \u265F \u265F \u265F \u265F" << std::endl;
//
//
//    std::cout << ". . . . . . . .\n. . . . . . . .\n. . . . . . . .\n. . . . . . . .\n";
//
//
//    std::cout << "\u2656 \u2658 \u2657 \u2655 \u2654 \u2657 \u2658 \u2656" << std::endl;
//    std::cout << "\u2659 \u2659 \u2659 \u2659 \u2659 \u2659 \u2659 \u2659" << std::endl;
    
//    "\u265A" black king   K
//    "\u265B" black queen  Q
//    "\u265C" black rook   R
//    "\u265D" black bishop B
//    "\u265E" black knight N
//    "\u265F" black pawn   P
//
//    "\u2654" white king
//    "\u2655" white queen
//    "\u2656" white rook
//    "\u2657" white bishop
//    "\u2658" white knight
//    "\u2659" white pawn

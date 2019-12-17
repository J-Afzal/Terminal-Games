//
//  main.cpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#include "Battleships.hpp"
#include <iostream>
#include <vector>



int main(void) {
    std::vector< std::vector<int> > AIBoard, UserBoardAsSeenFromAI, UserBoard, AIBoardAsSeenFromUser;
    std::string CurrentPlayer;
    
    Setup_Game(AIBoard, UserBoardAsSeenFromAI, UserBoard, AIBoardAsSeenFromUser, CurrentPlayer);
    
//    Display_Game();
//
//    while (!Winning_Conditions_Met())
//    {
//        Toggle_Player();
//
//        if (CurrentPlyaer == 'AI')
//            Ask_AI_For_Next_Turn();
//
//        else
//        {
//            Display_Game();
//            Ask_User_For_Next_Move();
//        }
//
//
//    }
//
//    Display_Winning_Message();

    return 0;
}

//The opponents board
//    std::cout << ". O . . . . . . . ." << std::endl;
//    std::cout << ". O . . . . O . . ." << std::endl;
//    std::cout << ". O . . . . O . . ." << std::endl;
//    std::cout << ". O . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . O O O . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . X . ." << std::endl;
//    std::cout << ". . . . . . . X . ." << std::endl;
//    std::cout << ". . . . . . . X . ." << std::endl;
//
//
//    //Your board
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//    std::cout << ". . . . . . . . . ." << std::endl;
//
//
//    std::cout << "\n\n\n\n";

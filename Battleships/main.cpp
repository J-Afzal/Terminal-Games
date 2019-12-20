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
#include <iomanip>



int main(void) {
    std::vector< std::vector<char> > AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard;
    std::string CurrentPlayer;
    unsigned int NumberOfTurns = 0;
    
    Setup_Game(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer);
    
    Display_Game(UserOpponentBoard, UserBoard);

    while (!Winning_Conditions_Met_For_AIBoard(AIBoard) && !Winning_Conditions_Met_For_UserBoard(UserBoard))
    {
        Toggle_Player(CurrentPlayer);
        
        if (CurrentPlayer == "AI")
        {
            int Command = Ask_AI_For_Next_Command(AIOpponentBoard);
            Execute_Next_Turn(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer, Command);
        }
        
        else
        {
            Display_Game(UserOpponentBoard, UserBoard);
            int Command = Ask_User_For_Next_Command(UserOpponentBoard);
            Execute_Next_Turn(AIBoard, AIOpponentBoard, UserBoard, UserOpponentBoard, CurrentPlayer, Command);
            Display_Game(UserOpponentBoard, UserBoard);
        }

        NumberOfTurns++;
    }

    Display_Winning_Message(CurrentPlayer, NumberOfTurns);

    return 0;
}

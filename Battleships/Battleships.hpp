//
//  Battleships.hpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>



void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, std::string& CurrentPlayer);

void Ask_AI_For_Battleship_Positions(std::vector< std::vector<char> >& AIBoard);

void Get_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const int& ShipSize);

bool Error_Checking_On_AI_Input(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints);

void Ask_User_For_Battleship_Positions(const std::vector< std::vector<char> >& UserOpponentBoard, std::vector< std::vector<char> >& UserBoard);

void Display_Game(const std::vector< std::vector<char> >& UserOpponentBoard, const std::vector< std::vector<char> >& UserBoard);

bool Error_Checking_Ordering_Orientation_On_User_Input(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const int& ShipSize, std::string& CurrentShipPositionsOrientation);

bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const int& ShipSize);

void Place_Ship(std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const char& ShipName);

bool Winning_Conditions_Met_For_UserBoard(const std::vector< std::vector<char> >& UserBoard);

bool Winning_Conditions_Met_For_AIBoard(const std::vector< std::vector<char> >& AIBoard);

void Toggle_Player(std::string& CurrentPlayer);

int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard);

void Execute_Next_Turn(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, const std::string& CurrentPlayer, const int& Command);

int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& UserOpponentBoard);

void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns);



#endif /* Battleships_hpp */

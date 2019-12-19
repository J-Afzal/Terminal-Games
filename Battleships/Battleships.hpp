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



void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<int> >& UserBoardAsSeenFromAI, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::string& CurrentPlayer);

void Ask_AI_For_Battleship_Positions(std::vector< std::vector<char> >& AIBoard);

void Ask_User_For_Battleship_Positions(const std::vector< std::vector<int> >& AIBoardAsSeenFromUser, std::vector< std::vector<char> >& UserBoard);

void Display_Game(const std::vector< std::vector<int> >& AIBoardAsSeenFromUser, const std::vector< std::vector<char> >& UserBoard);

bool Error_Checking_Ordering_Orientation_On_User_Input(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const int& ShipSize, std::string& CurrentShipPositionsOrientation);

bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const int& ShipSize);

void Place_Ship(std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const char& ShipName);


#endif /* Battleships_hpp */

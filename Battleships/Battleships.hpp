//
//  Battleships.hpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  Battleship game where a human user can play agaisnt the
//  computer. The human user is asked for grid positions for each
//  ship and then for the grid position the user next wants to attack.
//  The AI is dumb and picks random location to place and attack ships.
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>



void Play_Battleships(void);

void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, std::string& CurrentPlayer);

void Ask_AI_For_Ship_Positions(std::vector< std::vector<char> >& AIBoard);

void Get_AI_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

bool Error_Checking_On_AI_Ship_Coordinates(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints);

void Ask_User_For_Ship_Positions(const std::vector< std::vector<char> >& UserOpponentBoard, std::vector< std::vector<char> >& UserBoard);

void Display_Game(const std::vector< std::vector<char> >& UserOpponentBoard, const std::vector< std::vector<char> >& UserBoard);

bool Error_Checking_Ordering_Orientation_On_User_Input(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize, std::string& CurrentShipPositionsOrientation);

bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

void Place_Ship(std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned char& ShipName);

bool Winning_Conditions_Met_For_UserBoard(const std::vector< std::vector<char> >& UserBoard);

bool Winning_Conditions_Met_For_AIBoard(const std::vector< std::vector<char> >& AIBoard);

void Toggle_Player(std::string& CurrentPlayer);

int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard);

void Execute_Next_Turn(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, const std::string& CurrentPlayer, const unsigned int& Command);

int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& UserOpponentBoard);

void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns);



#endif /* Battleships_hpp */

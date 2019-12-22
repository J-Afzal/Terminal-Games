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
//  The game can be played through one function Play_Battleships().
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>



// Simple function to run whole game
void Play_Battleships(void);

// Setups all the varibales so that game can be played
void Setup_Game(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, std::string& CurrentPlayer);

// This only displays the boards of the human user
void Display_Game(const std::vector< std::vector<char> >& UserOpponentBoard, const std::vector< std::vector<char> >& UserBoard);

// Gets the computer to give ships positions for each ship; error checks; and then places ship on the board
void Ask_AI_For_Ship_Positions(std::vector< std::vector<char> >& AIBoard);

// Gets the computer to generate ship positions
void Get_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

// Error checking on the computer generated ship positions
bool Error_Checking_On_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints);

// Gets the user to give ships positions for each ship; error checks; and then places ship on the board
void Ask_User_For_Ship_Positions(const std::vector< std::vector<char> >& UserOpponentBoard, std::vector< std::vector<char> >& UserBoard);

// Basic error checking on the user ship positions
bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(const std::vector< std::vector<char> >& UserBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize, std::string& CurrentShipPositionsOrientation);

// Checks if the ship positions given by user can be used to place a ship on the board
bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector< std::vector<char> >& UserBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

// Overwrites SomeBoard with the ship name at the CurrentShipPositions_ints positions
void Place_Ship(std::vector< std::vector<char> >& SomeBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned char& ShipName);

// If there are any ship letter on the user's board
bool Winning_Conditions_Met_For_UserBoard(const std::vector< std::vector<char> >& UserBoard);

// If there are any ship letter on the computer's board
bool Winning_Conditions_Met_For_AIBoard(const std::vector< std::vector<char> >& AIBoard);

// Change to the other player
void Toggle_Player(std::string& CurrentPlayer);

// Asks the computer for the grid position to attack
int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard);

// Carry out the attack and update the corresponding boards
void Execute_Next_Turn(std::vector< std::vector<char> >& AIBoard, std::vector< std::vector<char> >& AIOpponentBoard, std::vector< std::vector<char> >& UserBoard, std::vector< std::vector<char> >& UserOpponentBoard, const std::string& CurrentPlayer, const unsigned int& Command);

// Asks the user for the grid position to attack
int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& UserOpponentBoard);

// Display the winning message as game is now over
void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns);



#endif /* Battleships_hpp */

//
//  Battleships.hpp
//  Battleships
//
//  Created by Main on 17/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  The classic Battleship game where human vs human is not coded
//  for as difficult to keep the board information for each user separate.
//
//  Important Points
//      - 2 users represents two human players which is not coded for
//      - 1 users represents one human player and one computer player
//      - 0 users represents zero human players and two computer players
//      - The AI is 'dumb' and picks random locations to place ships and random locations to attack ships
//      - The game is played through the function `Play_Battleships()`
//

#ifndef Battleships_hpp
#define Battleships_hpp

#include <vector>
#include <string>



// Simple function to run whole game
void Play_Battleships(void);

// Test code for Hangman where there are zero players
void Test_Battleships(void);

// Setups all the varibales so that game can be played
void Setup_Game(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerOneOpponentBoard, std::vector< std::vector<char> >& PlayerTwoBoard, std::vector< std::vector<char> >& PlayerTwoOpponentBoard, unsigned int& NumberOfPlayers, std::string& CurrentPlayer);

// Prompts user for number of players
int Ask_User_For_Number_Of_Players(void);

// Gets the user to give ships positions for each ship; error checks; and then places ship on the board
void Ask_User_For_Ship_Positions(std::vector< std::vector<char> >& PlayerOneBoard, const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// This only displays the boards of the human user
void Display_Game_For_User(std::vector< std::vector<char> >& PlayerOneBoard, const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// Displays the two AI boards (used when in 0 player mode)
void Display_Game_For_AIs(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerTwoBoard);

// Basic error checking on the user ship positions
bool Error_Checking_Ordering_Orientation_On_User_Ship_Positions(const std::vector< std::vector<char> >& PlayerOneBoard, std::string& CurrentShipPositions_string, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize, std::string& CurrentShipPositionsOrientation);

// Checks if the ship positions given by user can be used to place a ship on the board
bool Can_Ship_Be_Placed(const std::string& CurrentShipPositionsOrientation, const std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

// Overwrites SomeBoard with the ship name at the CurrentShipPositions_ints positions
void Place_Ship(std::vector< std::vector<char> >& anyBoard, const std::vector<int>& CurrentShipPositions_ints, const unsigned char& ShipName);

// Gets the computer to give ships positions for each ship; error checks; and then places ship on the board
void Ask_AI_For_Ship_Positions(std::vector< std::vector<char> >& AIBoard);

// Gets the computer to generate ship positions
void Get_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, std::string& CurrentShipPositionsOrientation, std::vector<int>& CurrentShipPositions_ints, const unsigned int& ShipSize);

// Error checking on the computer generated ship positions
bool Error_Checking_On_AI_Ship_Positions(const std::vector< std::vector<char> >& AIBoard, const std::vector<int>& CurrentShipPositions_ints);

// If there are any ship letter on the user's board
bool Winning_Conditions_Met_For_Player_One_Board(const std::vector< std::vector<char> >& PlayerOneBoard);

// If there are any ship letter on the computer's board
bool Winning_Conditions_Met_For_Player_Two_Board(const std::vector< std::vector<char> >& PlayerTwoBoard);

// Change to the other player
void Toggle_Player(std::string& CurrentPlayer);

// Asks the computer for the grid position to attack
int Ask_AI_For_Next_Command(const std::vector< std::vector<char> >& AIOpponentBoard);

// Carry out the attack and update the corresponding boards
void Execute_Next_Turn(std::vector< std::vector<char> >& PlayerOneBoard, std::vector< std::vector<char> >& PlayerOneOpponentBoard, std::vector< std::vector<char> >& PlayerTwoBoard, std::vector< std::vector<char> >& PlayerTwoOpponentBoard, const std::string& CurrentPlayer, const unsigned int& Command);

// Asks the user for the grid position to attack
int Ask_User_For_Next_Command(const std::vector< std::vector<char> >& PlayerOneOpponentBoard);

// Display the winning message as game is now over
void Display_Winning_Message(const std::string& CurrentPlayer, const unsigned int& NumberOfTurns);



#endif /* Battleships_hpp */

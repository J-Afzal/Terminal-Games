//
//  TicTacToe.hpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  The classic TicTacToe game with options to pick the number
//  of users and which player the human user would like to be (X or O)
//
//  Important Points
//  - 2 users represents two human players and thus no need to ask user which player they would like to be
//  - 1 user represents a human player vs the computer and so the human player is asked which player they would like to be (X or O)
//  - 0 users represents no human players and thus computer vs computer
//  - The AI is 'dumb' as it picks random positions
//  - The The game is played through the function `Play_TicTacToe()`

/** @file Testing Testing
*/

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <iostream>
#include <vector>

// Simple function to run whole game
void Play_TicTacToe(void);

// Test code for TicTacToe where there are zero players
void Test_TicTacToe(void);

// Sets up the variables required by prompting user for the size of the grid and the number of human players
void Setup_Game(unsigned int& NumberOfTurns, unsigned int& CurrentPlayer, unsigned int& NumberOfPlayers, unsigned int& UserXO, std::vector< std::vector<int> >& GameData);

// Prompt user for the number of human players
int Get_Number_Of_Players(void);

// If one human player then they are asked to choose an X or O counter
int Get_User_X_O_Choice(void);

// Checks if all places on grid have been occupied
bool Game_Over(const std::vector< std::vector<int> >& GameData);

// Checks if any 'x in a row'
bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData);

// Displays the current state of grid
void Display_Current_Game(const std::vector< std::vector<int> >& GameData);

// Changes to the other player
char Toggle_Player(const int& CurrentPlayer);

// Prompt user for their next move with error checking
std::vector< std::vector<int> > Ask_User_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);

// Prompt AI for their next move with error checking
std::vector< std::vector<int> > Ask_AI_For_Next_Input(std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);

// Displays the winning or losing message
void Display_Winner(const unsigned int& NumberOfTurns, const std::vector< std::vector<int> >& GameData, const unsigned int& CurrentPlayer);

#endif /* TicTacToe_hpp */

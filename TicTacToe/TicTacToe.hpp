//
//  TicTacToe.hpp
//  TicTacToe
//
//  Created by Main on 09/12/2019.
//  Copyright © 2019 Junaid Afzal. All rights reserved.
//
//  TicTacToe game with options to define the size of the
//  grid - which will be assumed to be square. Also options
//  for 0, 1 and 2 player modes - where 2 player = 2 human players;
//  1 player = 1 human player and one AI player; and 0 player = no
//  human players and 2 AIs. The AI are dumb and make pseudo random
//  moves. The game can be played through one function Play_TicTacToe()
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <iostream>



// Simple function to run whole game
void Play_TicTacToe(void);

// Sets up the variables required by prompting user for the size of the grid and the number of human players
void Setup_Game(unsigned int& NumberOfTurns, unsigned int& CurrentPlayer, unsigned int& NumberOfPlayers, unsigned int& UserXO, std::vector< std::vector<int> >& GameData);

// Prompts and error checks the user for the size of the TicTacToe gird and initialise the grid
std::vector< std::vector<int> > Get_Size_Of_Grid(void);

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

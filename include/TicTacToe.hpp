//
//  The classic TicTacToe game
//
//  Important Points
//  - 2 players represents two human players
//  - 1 player represents a human player vs the computer
//  - 0 players represents computer vs computer
//  - The computer is 'dumb' as it picks random positions
//  - system("cls") is used to clear console
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <iostream>
#include <vector>

void Play_TicTacToe(void);

// Test code uses computer vs computer option
void Test_TicTacToe(void);

// Psuedo randomly selects the player to go first; creates the board; getting the
// number of player; and getting the user's XO choice if only one human player
void Setup_Game(unsigned int& NumberOfTurns,
                unsigned int& CurrentPlayer,
                unsigned int& NumberOfPlayers,
                unsigned int& UserXO,
                std::vector< std::vector<int> >& GameData);

// Prompt user for the number of human players
int Get_Number_Of_Players(void);

// If one human player is selected then the user is asked to choose between player X or player O
int Get_User_X_O_Choice(void);

// True if all places on grid have been occupied
bool Game_Over(const std::vector< std::vector<int> >& GameData);

// Checks for three in a row for both X and O
bool Winning_Conditions_Met(const std::vector< std::vector<int> >& GameData);

// Note that system("cls") is used to clear console
void Display_Game(const std::vector< std::vector<int> >& GameData);

char Toggle_Player(const int& CurrentPlayer);

// User is prompted for their next move - repeated, if neccesarry, until a valid move is given
void Ask_User_For_Next_Input(std::vector< std::vector<int> >& GameData,
                             const unsigned int& CurrentPlayer);

// The computer randomly picks a number between, and including, one to nine
// until the number chosen hasn't already been picked previously in the game
void Ask_Computer_For_Next_Input(std::vector< std::vector<int> >& GameData,
                                 const unsigned int& CurrentPlayer);

// Displays the player that is the winner, or not if the game is a draw and how many turns it took
void Display_Game_Over_Message(const unsigned int& NumberOfTurns,
                               const std::vector< std::vector<int> >& GameData,
                               const unsigned int& CurrentPlayer);

#endif

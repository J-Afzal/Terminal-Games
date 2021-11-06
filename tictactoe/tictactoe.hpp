//
//  @File: TicTacToe.hpp
//  @Author: Junaid Afzal
//

#ifndef tictactoe_hpp
#define tictactoe_hpp

#include <vector>
#include <string>

// Pseudo randomly selects the player to go first; creates the board; gets the
// number of human players; and if one human player playing then gets the user's
// choice of being player X or player O
void Setup_Game(std::vector<std::vector<std::string>> &GameData,
                std::vector<unsigned int> &ValidMovesRemaining,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::string &CurrentPlayer);

void Display_Game(const std::vector<std::vector<std::string>> &GameData,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty);

// User is prompted for their next move and repeated, if necessary, until a valid move is given
void Get_Next_User_Command(std::vector<std::vector<std::string>> &GameData,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining);

// The AI randomly picks a number from one to nine until the number chosen
// hasn't already been picked previously in the game. A better solution would be to
// have a list of all available moves and then randomly picking from that list.
void Get_Next_AI_Command(std::vector<std::vector<std::string>> &GameData,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining);

// True if all places on grid have been occupied which occurs once nine turns have taken place
bool Game_Over(const unsigned int &NumberOfTurns);

// Checks for three in a row for both X and O
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &GameData);

// Displays the player that is the winner, or not if the game is a draw and how many turns it took
void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif

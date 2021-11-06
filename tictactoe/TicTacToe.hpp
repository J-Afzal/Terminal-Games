//
//  @File: TicTacToe.hpp
//  @Author: Junaid Afzal
//

#ifndef tictactoe_hpp
#define tictactoe_hpp

#include <vector>
#include <string>
#include <map>

// Pseudo randomly selects the player to go first; creates the board; gets the
// number of human players; and if one human player playing then gets the user's
// choice of being player X or player O
void Setup_Game(unsigned int &NumberOfTurns,
                std::string &CurrentPlayer,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::vector<std::vector<std::string>> &GameData,
                std::vector<unsigned int> &ValidMovesRemaining);

// True if all places on grid have been occupied which occurs once nine turns have taken place
bool Game_Over(const unsigned int &NumberOfTurns);

// Checks for three in a row for both X and O
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &GameData);

void Display_Game(const std::vector<std::vector<std::string>> &GameData,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty);

// User is prompted for their next move and repeated, if necessary, until a valid move is given
void Ask_User_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const std::string &CurrentPlayer,
                             std::vector<unsigned int> &ValidMovesRemaining);

// The computer randomly picks a number from one to nine until the number chosen
// hasn't already been picked previously in the game. A better solution would be to
// have a list of all available moves and then randomly picking from that list.
void Ask_Computer_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::string &CurrentPlayer,
                                 std::vector<unsigned int> &ValidMovesRemaining);

// Displays the player that is the winner, or not if the game is a draw and how many turns it took
void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif

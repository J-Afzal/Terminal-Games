//
//  @File: TicTacToe.hpp
//  @Author: Junaid Afzal
//

#ifndef TicTacToe_hpp
#define TicTacToe_hpp

#include <vector>
#include <string>
#include <map>

// Pseudo randomly selects the player to go first; creates the board; gets the
// number of human players; and if one human player playing then gets the user's
// choice of being player X or player O
void Setup_Game(unsigned int &NumberOfTurns,
                unsigned char &CurrentPlayer,
                unsigned int &NumberOfPlayers,
                unsigned char &UserXO,
                std::string &AIDifficulty,
                std::vector<std::vector<std::string>> &GameData,
                std::vector<unsigned int> &ValidMovesRemaining);

// Prompt user for the number of human players
unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &GameData);

// If one human player is selected then the user is asked to choose between player X or player O
unsigned char Get_User_X_O_Choice(const std::vector<std::vector<std::string>> &GameData,
                        const unsigned int &NumberOfPlayers);

std::string Get_AI_Difficulty (const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers);

void Capitalise_Word(std::string &aWord);

// True if all places on grid have been occupied which occurs once nine turns have taken place
bool Game_Over(const unsigned int &NumberOfTurns);

// Checks for three in a row for both X and O
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &GameData);

void Display_Game(const std::vector<std::vector<std::string>> &GameData,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty);

// Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
void Clear_Terminal(void);

void Toggle_Player(unsigned char &CurrentPlayer);

// User is prompted for their next move and repeated, if necessary, until a valid move is given
void Ask_User_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                             const unsigned int &NumberOfPlayers,
                             const std::string &AIDifficulty,
                             const unsigned char &CurrentPlayer,
                             std::vector<unsigned int> &ValidMovesRemaining);

// The computer randomly picks a number from one to nine until the number chosen
// hasn't already been picked previously in the game. A better solution would be to
// have a list of all available moves and then randomly picking from that list.
void Ask_Computer_For_Next_Input(std::vector<std::vector<std::string>> &GameData,
                                 const unsigned int &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const unsigned char &CurrentPlayer,
                                 std::vector<unsigned int> &ValidMovesRemaining);

unsigned int MiniMax_Algorithm(void);

// Displays the player that is the winner, or not if the game is a draw and how many turns it took
void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &GameData,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const unsigned char &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif

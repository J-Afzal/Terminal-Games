/**
 * @file tictactoe.hpp
 * @author Junaid Afzal
 * @brief Tic Tac Toe specific functions
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef tictactoe_hpp
#define tictactoe_hpp

#include <vector>
#include <string>
#include <Windows.h>

/**
 * @brief Game loop for Tic Tac Toe
 *
 * @param ConsoleHandle
 * @param CursorInfo
 */
void Play_Tic_Tac_Toe(const HANDLE &ConsoleHandle,
                      CONSOLE_CURSOR_INFO &CursorInfo);

/**
 * @brief The Tic Tac Toe grid and list of valid moves are created, number of
 * players are retrieved, if only one human player is present they are asked
 * which player they would like to be, if AI is involved the user is prompted
 * for the AI difficulty, and finally the current player is randomly assigned.
 *
 * @param TicTacToeGrid
 * @param ValidMovesRemaining
 * @param NumberOfPlayers
 * @param UserPlayerChoice
 * @param AIDifficulty
 * @param CurrentPlayer
 */
void Setup_Game(std::vector<std::vector<std::string>> &TicTacToeGrid,
                std::vector<unsigned int> &ValidMovesRemaining,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::string &CurrentPlayer);

/**
 * @brief Does what what you think
 *
 * @param TicTacToeGrid
 * @return unsigned int
 */
unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &TicTacToeGrid);

/**
 * @brief Does what what you think
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @return std::string
 */
std::string Get_User_Player_Choice(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                                   const unsigned int &NumberOfPlayers);

/**
 * @brief Does what what you think
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @return std::string
 */
std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                              const unsigned int &NumberOfPlayers);

/**
 * @brief The Tic Tac Toe grid is displayed, and to the right of that,
 * the number of players and the AI difficulty is displayed, and to the
 * right of that, the Tic Tac Toe matrix grid is displayed that shows
 * what each command represents on the Tic Tac Toe grid.
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @param AIDifficulty
 */
void Display_Game(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                  const std::string &NumberOfPlayers,
                  const std::string &AIDifficulty);

/**
 * @brief The user is prompted for their next command and, if necessary, repeated until
 * a valid command is given.
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @param ValidMovesRemaining
 * @param ConsoleHandle
 */
void Get_Next_User_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining,
                           const HANDLE &ConsoleHandle);

/**
 * @brief If AIDifficulty is set to easy, then a random valid location on the
 * Tic Tac Toe grid is chosen. If AIDifficulty is set to hard then the MiniMax()
 * algorithm is used.
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @param ValidMovesRemaining
 */
void Get_Next_AI_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining);

/**
 * @brief Checks if there are still empty places to play a move
 * on the Tic Tac Toe grid.
 *
 * @param NumberOfTurns
 * @return true,if more moves can be played
 * @return false, if no more moves can be played
 */
bool Game_Over(const unsigned int &NumberOfTurns);

/**
 * @brief Checks for three in a row X/O on the Tic Tac Toe grid.
 *
 * @param TicTacToeGrid
 * @return true, if three in a row exists
 * @return false, if three in a row does NOT exists
 */
bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &TicTacToeGrid);

/**
 * @brief First calls Display_Game() once more. If winning condition was met, then the winner is the current
 * player is the winner as Toggle_Player() function has not been called since most recent turn and now. If
 * no winner then it is draw. This informations is displayed to the user and _getch() is used to get a key press
 * for what the GameIsRunning should be set to (true = play another game and false = quit game).
 *
 * @param TicTacToeGrid
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CurrentPlayer
 * @param NumberOfTurns
 * @param GameIsRunning
 */
void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif

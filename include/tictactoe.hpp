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

#pragma once
#include <vector>
#include <string>
#include <Windows.h>

namespace TicTacToe
{
    /**
     * @brief Game loop for Tic Tac Toe
     *
     * @param ConsoleHandle
     * @param CursorInfo
     */
    void Play(const HANDLE &ConsoleHandle,
              CONSOLE_CURSOR_INFO &CursorInfo);

    /**
     * @brief The Tic Tac Toe grid and list of valid moves are created, number of
     * players are retrieved, if only one human player is present they are asked
     * which player they would like to be, if AI is involved the user is prompted
     * for the AI difficulty, and finally the current player is randomly assigned.
     *
     * @param TicTacToeGrid
     * @param MovesRemaining
     * @param CurrentPlayer
     * @param UserPlayerChoice
     * @param NumberOfPlayers
     * @param AIDifficulty
     * @param QuitToMainMenu
     */
    void Setup_Game(std::vector<std::vector<char>> &TicTacToeGrid,
                    std::vector<int> &MovesRemaining,
                    char &CurrentPlayer,
                    char &UserPlayerChoice,
                    int &NumberOfPlayers,
                    std::string &AIDifficulty,
                    bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param TicTacToeGrid
     * @param QuitToMainMenu
     * @return int
     */
    int Get_Number_Of_Players(const std::vector<std::vector<char>> &TicTacToeGrid,
                              bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param TicTacToeGrid
     * @param NumberOfPlayers
     * @param QuitToMainMenu
     * @return char
     */
    char Get_User_Player_Choice(const std::vector<std::vector<char>> &TicTacToeGrid,
                                const int &NumberOfPlayers,
                                bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param TicTacToeGrid
     * @param NumberOfPlayers
     * @param QuitToMainMenu
     * @return std::string
     */
    std::string Get_AI_Difficulty(const std::vector<std::vector<char>> &TicTacToeGrid,
                                  const int &NumberOfPlayers,
                                  bool &QuitToMainMenu);

    /**
     * @brief Creates a string that contains all the ASCII characters to display the current
     * state of the game.
     *
     * @param TicTacToeGrid
     * @param NumberOfPlayers
     * @param AIDifficulty
     * @return std::string
     */
    std::string Get_Game_Display(const std::vector<std::vector<char>> &TicTacToeGrid,
                                 const std::string &NumberOfPlayers,
                                 const std::string &AIDifficulty);

    /**
     * @brief Creates a new line containing text for the Tic Tac Toe game.
     *
     * @param Input
     * @return std::string
     */
    std::string New_Line(const std::string &Input);

    /**
     * @brief Creates an empty line for the Tic Tac Toe game.
     *
     * @return std::string
     */
    std::string Empty_Line(void);

    /**
     * @brief Creates the top line for the Tic Tac Toe game.
     *
     * @return std::string
     */
    std::string Top_Line(void);

    /**
     * @brief Creates the bottom line for the Tic Tac Toe game.
     *
     * @return std::string
     */
    std::string Bottom_Line(void);

    /**
     * @brief Creates the bottom bar for the Tic Tac Toe game.
     *
     * @return std::string
     */
    std::string Bottom_Bar(void);

    /**
     * @brief The user is repeatedly prompted for their next command and until a valid command is given.
     *
     * @param TicTacToeGrid
     * @param MovesRemaining
     * @param CurrentPlayer
     * @param NumberOfPlayers
     * @param AIDifficulty
     * @param ConsoleHandle
     * @param CursorInfo
     * @param QuitToMainMenu
     */
    void Get_Next_User_Command(std::vector<std::vector<char>> &TicTacToeGrid,
                               std::vector<int> &MovesRemaining,
                               const char &CurrentPlayer,
                               const int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const HANDLE &ConsoleHandle,
                               CONSOLE_CURSOR_INFO &CursorInfo,
                               bool &QuitToMainMenu);

    /**
     * @brief If AIDifficulty is set to easy, then a random valid location on the
     * Tic Tac Toe grid is chosen. If AIDifficulty is set to hard then the MiniMax()
     * algorithm is used.
     *
     * @param GameGrid
     * @param MovesRemaining
     * @param CurrentPlayer
     */
    void Get_Next_AI_Command(std::vector<std::vector<char>> &GameGrid,
                             std::vector<int> &MovesRemaining,
                             const char &CurrentPlayer);

    /**
     * @brief Checks if there are still empty places to play a move
     * on the Tic Tac Toe grid.
     *
     * @param NumberOfTurns
     * @return true,if more moves can be played
     * @return false, if no more moves can be played
     */
    bool Game_Over(const int &NumberOfTurns);

    /**
     * @brief Checks for three in a row X/O on the Tic Tac Toe grid.
     *
     * @param TicTacToeGrid
     * @return true
     * @return false
     */
    bool Winning_Conditions_Met(const std::vector<std::vector<char>> &TicTacToeGrid);

    /**
     * @brief The final state of the Tic Tac Toe grid and winner is displayed and
     * the user is promoted whether they want to restart or quit.
     *
     * @param TicTacToeGrid
     * @param CurrentPlayer
     * @param NumberOfPlayers
     * @param NumberOfTurns
     * @param AIDifficulty
     * @param GameIsRunning
     */
    void Display_Game_Over_Message(const std::vector<std::vector<char>> &TicTacToeGrid,
                                   const char &CurrentPlayer,
                                   const int &NumberOfPlayers,
                                   const int &NumberOfTurns,
                                   const std::string &AIDifficulty,
                                   bool &GameIsRunning);
}

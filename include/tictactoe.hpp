/**
 * @file tictactoe.hpp
 * @author Junaid Afzal
 * @brief Tic Tac Toe namespace functions and classes
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <array>
#include <string>
#include <vector>
#include <Windows.h>
#include "game.hpp"

/**
 * @brief Contains all the data/functions for the Tic Tac Toe game
 *
 */
class TicTacToe : public Game
{
public:
    explicit TicTacToe(const HANDLE &ConsoleHandle);

    ~TicTacToe();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Setup_Game() override;

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    /**
     * @brief
     *
     * @return true, if Execute_Next_User_Command()
     * @return false, if Execute_Next_AI_Command()
     */
    bool Next_Turn_Is_User() override;

    /**
     * @brief The user is repeatedly prompted for their next
     * command until a valid command is given.
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Execute_Next_User_Command() override;

    /**
     * @brief If AIDifficulty is set to easy, then a random valid location is chosen.
     *
     */
    void Execute_Next_AI_Command() override;

    /**
     * @override
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Display_Game_Over_Message() override;

private:
    std::array<std::array<char, 3>, 3> m_GameGrid{};
    std::vector<int> m_MovesRemaining;
    std::string m_AIDifficulty;
    int m_NumberOfTurns{}, m_NumberOfPlayers{};
    char m_CurrentPlayer{}, m_UserPlayerChoice{};
    bool m_WinningConditionsMet{};
    HANDLE m_ConsoleHandle;
    const int m_Width = 53;
    const std::string WHITE = "\x1B[1;37m", BLUE = "\x1B[1;34m"; // ANSI escape codes for bold text colours

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_Number_Of_Players();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_User_Player_Choice();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_AI_Difficulty();

    /**
     * @brief Creates a string that contains all the ASCII characters to
     * display the current state of the game.
     *
     * @return std::string
     */
    std::string Get_Game_Display();
};

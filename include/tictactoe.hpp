/**
 * @file tictactoe.hpp
 * @author Junaid Afzal
 * @brief Tic Tac Toe namespace funtions and classes
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <array>
#include <vector>
#include <string>
#include <Windows.h>

/**
 * @brief Contains all the data/functions for the Tic Tac Toe game
 *
 */
class TicTacToe
{
public:
    TicTacToe(const HANDLE &ConsoleHandle);

    ~TicTacToe();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Setup_Game(void);

    bool Game_Over(void);

    void Toggle_Current_Player(void);

    /**
     * @brief
     *
     * @return true, if Execute_Next_User_Command()
     * @return false, if Execute_Next_AI_Command()
     */
    bool Next_Turn_Is_User(void);

    /**
     * @brief The user is repeatedly prompted for their next
     * command until a valid command is given.
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Execute_Next_User_Command(void);

    /**
     * @brief If AIDifficulty is set to easy, then a random valid location is chosen.
     *
     */
    void Execute_Next_AI_Command(void);

    /**
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Display_Game_Over_Message(void);

private:
    std::array<std::array<char, 3>, 3> m_GameGrid;
    std::vector<int> m_MovesRemaining;
    std::string m_AIDifficulty;
    int m_NumberOfTurns, m_NumberOfPlayers;
    char m_CurrentPlayer, m_UserPlayerChoice;
    bool m_WinningConditionsMet;
    HANDLE m_ConsoleHandle;
    const int m_Width = 53;

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_Number_Of_Players(void);

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_User_Player_Choice(void);

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_AI_Difficulty(void);

    /**
     * @brief Creates a string that contains all the ASCII characters to
     * display the current state of the game.
     *
     * @return std::string
     */
    std::string Get_Game_Display(void);
};

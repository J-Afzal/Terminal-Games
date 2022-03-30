/**
 * @file TicTacToe.hpp
 * @author Junaid Afzal
 * @brief Tic Tac Toe game object
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include "Game.hpp"

class TicTacToe : public Game
{
public:
    explicit TicTacToe();

    ~TicTacToe() override = default;

    void Setup_Game() override;

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    /**
     * @return true if next turn is user, false if next turn is AI
     */
    bool Next_Turn_Is_User() override;

    /**
     * @brief The user is repeatedly prompted for their next
     * command until a valid command is given.
     */
    void Execute_Next_User_Command() override;

    /**
     * @brief If AIDifficulty is set to easy, then a random valid location is chosen.
     */
    void Execute_Next_AI_Command() override;

    /**
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     */
    void Display_Game_Over_Message() override;

private:
    std::array<std::array<char, 3>, 3> m_GameGrid{};
    std::vector<int> m_MovesRemaining;
    char m_CurrentPlayer{}, m_UserPlayerChoice{};
    bool m_WinningConditionsMet{};

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Difficulty();

    /**
     * @return std::string that contains all the
     * ASCII characters to display the current state of the game.
     */
    std::string Get_Game_Display();
};

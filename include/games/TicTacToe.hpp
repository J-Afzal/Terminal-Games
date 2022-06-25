/**
 * @file TicTacToe.hpp
 * @author Junaid Afzal
 * @brief The game object that runs Tic Tac Toe
 * and is run using the inherited Play() function
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include "Game.hpp"
#include "helpers/StringBuilder.hpp"

class TicTacToe : public Game
{
public:
    explicit TicTacToe();

    ~TicTacToe() override = default;

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::array<std::array<char, 3>, 3> m_GameGrid{};
    std::vector<int> m_MovesRemaining;
    std::string m_NumberOfPlayers, m_AIDifficulty;
    char m_CurrentPlayer{}, m_UserPlayerChoice{};
    int m_NumberOfTurns{}, m_AISpeed{};
    bool m_WinningConditionsMet{};
    StringBuilder m_StringBuilder;

    void Setup_Game() override;

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Speed();

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    std::string Get_Game_Over_Message() override;

    std::string Get_Game_Display();
};

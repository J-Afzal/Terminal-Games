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

#include <array>
#include <random>
#include <string>
#include <vector>

#include "Game.hpp"

class TicTacToe : public Game
{
public:
    /**
     * @brief Construct a new Tic Tac Toe object
     * @param ASCIIOnly determines whether to use ANSI escapes codes (false)
     * or just ASCII characters (true)
     */
    explicit TicTacToe(const bool& ASCIIOnly);

    ~TicTacToe() override = default;

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::array<std::array<char, 3>, 3> m_GameGrid;
    std::vector<uint32_t> m_MovesRemaining;
    std::string m_NumberOfPlayers, m_AISpeedName;
    uint32_t m_NumberOfTurns, m_AISpeed, m_AICommand;
    char m_CurrentPlayer, m_UserPlayerChoice;
    bool m_WinningConditionsMet;

    void Setup_Game() override;

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Speed();

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() const override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    std::string Get_Game_Over_Message() const override;

    std::string Get_Game_Display() const;
};

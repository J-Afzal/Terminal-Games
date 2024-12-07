/**
 * @file Battleships.hpp
 * @author Junaid Afzal
 * @brief The game object that runs Battleships
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
#include <unordered_map>
#include <vector>

#include "Game.hpp"

class Battleships : public Game
{
public:
    /**
     * @brief Construct a new Battleships object
     * @param ASCIIOnly determines whether to use ANSI escapes codes (false)
     * or just ASCII characters (true)
     */
    explicit Battleships(const bool& ASCIIOnly);

    ~Battleships() override = default;

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::array<std::array<char, 10>, 10> m_BoardOne, m_BoardTwo;
    std::vector<uint32_t> m_MovesRemainingOne, m_MovesRemainingTwo;
    std::unordered_map<char, uint32_t> m_ShipsRemainingOne, m_ShipsRemainingTwo;
    std::string m_NumberOfPlayers, m_AISpeedName, m_CurrentPlayer;
    uint32_t m_NumberOfTurns, m_PreviousCommand, m_AISpeed, m_AICommand;
    bool m_GameOver;

    void Setup_Game() override;

    void Get_Number_Of_Players();

    void Get_AI_Speed();

    void Get_User_Ship_Positions();

    void Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard);

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    void Execute_Command(std::array<std::array<char, 10>, 10> &OpponentBoard,
                         std::unordered_map<char, uint32_t> &OpponentShipsRemaining,
                         std::vector<uint32_t> &MovesRemaining,
                         const uint32_t&AICommand);

    std::string Get_Game_Over_Message() override;

    std::string Get_Game_Display();
};

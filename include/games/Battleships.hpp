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
#include "Game.hpp"
#include "helpers/StringBuilder.hpp"

class Battleships : public Game
{
public:
    explicit Battleships();

    ~Battleships() override = default;

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::array<std::array<char, 10>, 10> m_BoardOne{}, m_BoardTwo{};
    std::vector<int> m_MovesRemainingOne, m_MovesRemainingTwo;
    std::unordered_map<char, int> m_ShipsRemainingOne, m_ShipsRemainingTwo;
    std::string m_AIDifficulty, m_NumberOfPlayers, m_CurrentPlayer;
    int m_NumberOfTurns{}, m_PreviousCommand{};
    bool m_GameOver{};
    Terminal m_Terminal;
    StringBuilder m_StringBuilder;

    void Setup_Game() override;

    void Get_Number_Of_Players();

    void Get_AI_Difficulty();

    void Get_User_Ship_Positions();

    void Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard);

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    std::string Get_Game_Over_Message() override;

    std::string Get_Game_Display();
};

/**
 * @file Battleships.hpp
 * @author Junaid Afzal
 * @brief Battleship game object
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include "Game.hpp"

class Battleships : public Game
{
public:
    explicit Battleships(const HANDLE &ConsoleHandle);

    ~Battleships() override = default;

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
     * @brief If AIDifficulty is set to easy, then a random valid letter is chosen.
     */
    void Execute_Next_AI_Command() override;

    /**
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     */
    void Display_Game_Over_Message() override;

private:
    std::array<std::array<char, 10>, 10> m_BoardOne{}, m_BoardTwo{};
    std::vector<int> m_MovesRemainingOne, m_MovesRemainingTwo;
    std::unordered_map<char, int> m_ShipsRemainingOne, m_ShipsRemainingTwo;
    std::string m_CurrentPlayer, m_AIDifficulty;
    int m_NumberOfPlayers{}, m_NumberOfTurns{}, m_PreviousCommand{};
    bool m_GameOver{};
    std::default_random_engine m_RandomNumberGenerator;
    Terminal m_Terminal;

    void Get_Number_Of_Players();

    void Get_AI_Difficulty();

    /**
     * @brief The user is prompted to enter sequentially increasing/decreasing co-ordinates
     * for each ship, and repeatedly if needed, until a valid set of co-ordinates are given.
     * After passing the error checks, each set of co-ordinates is used to place a ship
     * on player one's board (as user is always player one).
     */
    void Get_User_Ship_Positions();

    /**
     * @brief The AI randomly picks the ship positions, performs error
     * checking on them, and then places them on to the AIBoard
     */
    void Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard);

    /**
     * @return std::string that contains all the
     * ASCII characters to display the current state of the game.
     */
    std::string Get_Game_Display();
};

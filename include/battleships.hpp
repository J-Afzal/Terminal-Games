/**
 * @file battleships.hpp
 * @author Junaid Afzal
 * @brief Battleship namespace funtions and classes
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <array>
#include <vector>
#include <map>
#include <string>
#include <Windows.h>
#include "game.hpp"

/**
 * @brief Contains all the data/functions for the Battleships game
 *
 */
class Battleships : public Game
{
public:
    Battleships(const HANDLE &ConsoleHandle);

    ~Battleships();

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
     * @brief The user is prompted for their next command and, if necessary,
     * repeated until a valid command is given
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Execute_Next_User_Command(void);

    /**
     * @brief If AIDifficulty is set to easy, then a random valid command is chosen.
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
    std::array<std::array<char, 10>, 10> m_BoardOne, m_BoardTwo;
    std::vector<int> m_MovesRemainingOne, m_MovesRemainingTwo;
    std::map<char, int> m_ShipsRemainingOne, m_ShipsRemainingTwo;
    std::string m_CurrentPlayer, m_AIDifficulty;
    int m_NumberOfPlayers, m_NumberOfTurns, m_PreviousCommand;
    bool m_GameOver;
    HANDLE m_ConsoleHandle;
    const int m_Width = 147;

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
    bool Get_AI_Difficulty(void);

    /**
     * @brief The user is prompted to enter sequentially increasing/decreasing co-ordinates
     * for each ship, and repeatedly if needed, until a valid set of co-ordinates are given.
     * After passing the error checks, each set of co-ordinates is used to place a ship
     * on player one's board (as user is always player one).
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_User_Ship_Positions(void);

    /**
     * @brief The AI randomly picks the ship positions, performs error
     * checking on them, and then places them on to the AIBoard
     *
     * @param AIBoard
     */
    void Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard);

    /**
     * @brief Creates a string that contains all the ASCII characters to
     * display the current state of the game.
     *
     * @return std::string
     */
    std::string Get_Game_Display(void);
};

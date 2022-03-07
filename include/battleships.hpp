/**
 * @file battleships.hpp
 * @author Junaid Afzal
 * @brief Battleship specific functions
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

namespace Battleships
{
    /**
     * @brief Game loop for Battleships
     *
     * @param ConsoleHandle
     * @param CursorInfo
     */
    void Play(const HANDLE &ConsoleHandle, CONSOLE_CURSOR_INFO &CursorInfo);

    /**
     * @brief Game class that contains all the data/functions
     * for the Battleships game
     *
     */
    class Game
    {
    public:
        Game(const HANDLE &ConsoleHandle, CONSOLE_CURSOR_INFO &CursorInfo);

        ~Game();

        /**
         * @brief The player boards, valid moves, and remaining ships for each player
         * are created. Then the number of players is retrieved - two player are not
         * allowed as impractical to hide player boards from each other while using a
         * single terminal. Then the AI difficulty and ship positions are retrieved,
         * and the current player is randomly chosen.
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Setup_Game(void);

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
         * on player one's board (Human player is always player one).
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
         * @brief Checks if there are any ship letters left on the board
         *
         * @return true, if no ship letters left on board
         * @return false, if there are ship letters left on board
         */
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
         * @brief The winner is the current player as player has not been toggled since
         * most recent turn and now. This informations is displayed to the user.
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
        CONSOLE_CURSOR_INFO m_CursorInfo;

        /**
         * @brief Both player boards are displayed, whilst the number of players, current AI difficulty,
         * and current state of all ships for both players are displayed in between. If there is only one
         * player, then only the hits and misses by player one are displayed on player two's board (as
         * human player is automatically player one).
         *
         * @return std::string
         */
        std::string Get_Game_Display(void);

        /**
         * @brief Creates a new line containing text for Battleships
         *
         * @param Input
         * @return std::string
         */
        std::string New_Line(const std::string &Input);

        /**
         * @brief Creates an empty new line for Battleships
         *
         * @return std::string
         */
        std::string Empty_Line(void);

        /**
         * @brief Creates the top line for Battleships
         *
         * @return std::string
         */
        std::string Top_Line(void);

        /**
         * @brief Creates the bottom line for Battleships
         *
         * @return std::string
         */
        std::string Bottom_Line(void);

        /**
         * @brief Creates the bottom bar for Battleships
         *
         * @return std::string
         */
        std::string Bottom_Bar(void);
    };
}

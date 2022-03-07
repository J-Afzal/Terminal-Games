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

namespace TicTacToe
{
    /**
     * @brief Game loop for Tic Tac Toe
     *
     * @param ConsoleHandle
     * @param CursorInfo
     */
    void Play(const HANDLE &ConsoleHandle);

    /**
     * @brief Game class that contains all the data/functions for the Tic Tac Toe game
     *
     */
    class Game
    {
    public:
        Game(const HANDLE &ConsoleHandle);

        ~Game();

        /**
         * @brief
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
        bool Get_User_Player_Choice(void);

        /**
         * @brief
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Get_AI_Difficulty(void);

        bool Game_Over(void);

        /**
         * @brief
         *
         * @return true, if 3 in a row detected
         * @return false, if 3 in a row NOT detected
         */
        bool Winning_Conditions_Met(void);

        /**
         * @brief Checks if there are still empty places to play a move
         * on the Tic Tac Toe grid.
         *
         * @return true,if more moves can be played
         * @return false, if NO more moves can be played
         */
        bool No_Moves_Available(void);

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

        /**
         * @brief Creates a string that contains all the ASCII characters to
         * display the current state of the game.
         *
         * @return std::string
         */
        std::string Get_Game_Display(void);

        /**
         * @brief Creates a new line containing text for the Tic Tac Toe game.
         *
         * @param Input
         * @return std::string
         */
        std::string New_Line(const std::string &Input);

        /**
         * @brief Creates an empty line for the Tic Tac Toe game.
         *
         * @return std::string
         */
        std::string Empty_Line(void);

        /**
         * @brief Creates the top line for the Tic Tac Toe game.
         *
         * @return std::string
         */
        std::string Top_Line(void);

        /**
         * @brief Creates the bottom line for the Tic Tac Toe game.
         *
         * @return std::string
         */
        std::string Bottom_Line(void);

        /**
         * @brief Creates the bottom bar for the Tic Tac Toe game.
         *
         * @return std::string
         */
        std::string Bottom_Bar(void);
    };
}

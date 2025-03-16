#pragma once

#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <vector>

#include "helpers/Globals.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @brief Used by game objects to package themselves into a format that can be used by PageBuilder to construct a sub-page
     * for the current state of the game.
     */
    struct GameInformation
    {
        /**
         * @brief Used to package the TicTacToe current game state.
         */
        struct TicTacToeGameInformation
        {
            /**
             * @brief Refer to the member data documentation in TicTacToe.
             */
            ///@{
            std::array<std::array<std::string, Globals::G_TICTACTOE_GRID_WIDTH>, Globals::G_TICTACTOE_GRID_HEIGHT> m_gameGrid;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_hasWinner;
            ///@}
        }
        /**
         * @brief Used to package the TicTacToe current game state.
         */
        m_ticTacToeGameInformation;

        /**
         * @brief Used to package the Hangman current game state.
         */
        struct HangmanGameInformation
        {
            /**
             * @brief Refer to the member data documentation in Hangman.
             */
            ///@{
            std::vector<char> m_incorrectGuesses;
            std::string m_computerSpeedName;
            std::string m_currentGuessOfWord;
            std::string m_playerCount;
            std::string m_wordToBeGuessed;
            uint32_t m_turnCount;
            char m_currentLetterSelected;
            bool m_isGameOver;
            ///@}
        }
        /**
         * @brief Used to package the Hangman current game state.
         */
        m_hangmanGameInformation;

        /**
         * @brief Used to package the Battleships current game state.
         */
        struct BattleshipsGameInformation
        {
            /**
             * @brief Refer to the member data documentation in Battleships.
             */
            ///@{
            std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerOne;
            std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerTwo;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerOne;
            std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerTwo;
            std::string m_computerSpeedName;
            std::string m_currentPlayer;
            std::string m_playerCount;
            uint32_t m_turnCount;
            bool m_isGameOver;
            ///@}
        }
        /**
         * @brief Used to package the Battleships current game state.
         */
        m_battleshipsGameInformation;
    };
}

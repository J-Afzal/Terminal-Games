#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "Game.hpp"
#include "helpers/Constants.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    class TicTacToe : public Game
    {
    public:
        /**
         * @brief Construct a new Tic Tac Toe object.
         *
         * @param onlyUseASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
         */
        explicit TicTacToe(const bool &onlyUseASCII);

    private:
        PageBuilder m_pageBuilder;
        GameInfo m_gameInfo;
        std::default_random_engine m_randomNumberGenerator;
        std::array<std::array<char, g_TICTACTOE_BOARD_WIDTH>, g_TICTACTOE_BOARD_HEIGHT> m_gameGrid;
        std::vector<std::tuple<uint32_t,uint32_t>> m_movesRemaining;
        std::string m_currentPlayer, m_playerCount, m_userPlayerChoice, m_AISpeedName;
        uint32_t m_turnCount, m_AISpeed;
        bool m_hasWinner;

        /**
         * @brief See base class function for details.
         */
        void SetupGame() override;

        /**
         * @brief See base class function for details.
         */
        void UpdateGameInfo() override;

        /**
         * @brief See base class function for details.
         */
        void GetUserOptions() override;

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select which player the will be playing the game as (only supported if playing
         * against the AI).
         */
        void GetUserPlayerChoice();

        /**
         * @brief Prompts the user to select how the speed of AI decision making (this does not affect the difficulty of
         * the AI).
         */
        void GetAISpeed();

        /**
         * @brief See base class function for details.
         */
        bool IsGameOver() override;

        /**
         * @brief See base class function for details.
         */
        void ToggleCurrentPlayer() override;

        /**
         * @brief See base class function for details.
         */
        bool IsCurrentTurnUsers() override;

        /**
         * @brief See base class function for details.
         */
        void ExecuteUserCommand() override;

        /**
         * @brief See base class function for details.
         */
        void ExecuteAICommand() override;

        /**
         * @brief
         *
         * @param command
         * @return true
         * @return false
         */
        bool ValidateCommand(const std::tuple<uint32_t, uint32_t> &command);

        /**
         * @brief
         *
         * @param command
         */
        void ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t> &command);

        /**
         * @brief See base class function for details.
         */
        void GameOver() override;
    };
} // namespace TerminalGames

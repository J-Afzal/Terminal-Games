#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "Constants.hpp"
#include "games/Game.hpp"
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
        std::array<std::array<std::string, g_TICTACTOE_BOARD_WIDTH>, g_TICTACTOE_BOARD_HEIGHT> m_gameGrid;
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemaining;
        std::tuple<uint32_t, uint32_t> m_previousCommand;
        std::string m_computerSpeedName;
        std::string m_currentPlayer;
        std::string m_playerCount;
        std::string m_userPlayerChoice;
        uint32_t m_computerSpeed;
        uint32_t m_turnCount;
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
        void ExecuteComputerCommand() override;

        /**
         * @brief See base class function for details.
         */
        void GameOver() override;

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select which player the will be playing the game as (only supported if playing against the
         * computer).
         */
        void GetUserPlayerChoice();

        /**
         * @brief Prompts the user to select how the speed of computer decision making (this does not affect the difficulty of
         * the computer).
         */
        void GetComputerSpeed();

        /**
         * @brief Checks whether the command is valid.
         *
         * @param command The command in the form of <row, column>.
         * @return true If the command is valid.
         * @return false If the command is not valid.
         */
        bool ValidateCommand(const std::tuple<uint32_t, uint32_t> &command);

        /**
         * @brief Executes the command against the game grid.
         *
         * @param command The command in the form of <row, column>.
         */
        void ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t> &command);
    };
} // namespace TerminalGames

#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "games/Game.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    class TicTacToe : public Game
    {
    public:
        /**
         * @brief Constructs a new Tic Tac Toe object.
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only ASCII characters (false).
         */
        explicit TicTacToe(const bool& p_useAnsiEscapeCodes);

    private:
        PageBuilder m_pageBuilder;
        GameInfo m_gameInfo;
        std::default_random_engine m_randomNumberGenerator;
        std::array<std::array<std::string, Globals::G_TICTACTOE_BOARD_WIDTH>, Globals::G_TICTACTOE_BOARD_HEIGHT> m_gameGrid;
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemaining;
        std::tuple<uint32_t, uint32_t> m_previousCommand;
        std::string m_computerSpeedName;
        std::string m_currentPlayer;
        std::string m_playerCount;
        std::string m_userPlayerChoice;
        uint32_t m_computerSpeed;
        uint32_t m_turnCount;
        bool m_hasSavedGameOptions;
        bool m_hasWinner;
        bool m_saveGameOptions;

        /**
         * @brief See base class function for details.
         */
        void SetupGame() override;

        /**
         * @brief See base class function for details.
         */
        void GetUserOptions() override;

        /**
         * @brief See base class function for details.
         */
        void UpdateGameInfo() override;

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
         * @brief See base class function for details.
         */
        void RestartGame() override;

        /**
         * @brief See base class function for details.
         */
        void ResetGame() override;

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
         * @param p_command The command in the form of <row, column>.
         * @return true If the command is valid.
         * @return false If the command is not valid.
         */
        bool ValidateCommand(const std::tuple<uint32_t, uint32_t>& p_command);

        /**
         * @brief Executes the command against the game grid.
         *
         * @param p_command The command in the form of <row, column>.
         */
        void ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t>& p_command);
    };
}

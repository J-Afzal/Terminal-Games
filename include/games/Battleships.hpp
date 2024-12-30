#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "Constants.hpp"
#include "games/Game.hpp"
#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    class Battleships : public Game
    {
    public:
        /**
         * @brief Construct a new Battleships object.
         *
         * @param p_onlyUseAscii Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
         */
        explicit Battleships(const bool& p_onlyUseAscii);

    private:
        PageBuilder m_pageBuilder;
        GameInfo m_gameInfo;
        std::default_random_engine m_randomNumberGenerator;
        std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT> m_boardOne;
        std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT> m_boardTwo;
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemainingOne;
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemainingTwo;
        std::unordered_map<std::string, uint32_t> m_shipsRemainingOne;
        std::unordered_map<std::string, uint32_t> m_shipsRemainingTwo;
        std::tuple<uint32_t, uint32_t> m_previousCommand;
        std::string m_computerSpeedName;
        std::string m_currentPlayer;
        std::string m_playerCount;
        uint32_t m_computerSpeed;
        uint32_t m_turnCount;
        bool m_isGameOver;

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
         * @brief Prompts the user to select how the speed of the computer decision making (this does not affect the difficulty
         * of the computer).
         */
        void GetComputerSpeed();

        /**
         * @brief Prompt the user to place all ships on the board.
         */
        void GetUserShipPositions();

        /**
         * @brief
         *
         * @param p_currentShipPositions
         * @param p_selectedShipGridLocation
         * @param p_shipIsHorizontalOrVertical
         * @return true If ship position is valid.
         * @return false If the ship position is invalid.
         */
        bool ValidateUserShipPosition(
            const std::vector<std::tuple<uint32_t, uint32_t>>& p_currentShipPositions,
            const std::tuple<uint32_t, uint32_t>& p_selectedShipGridLocation,
            std::tuple<bool, bool>& p_shipIsHorizontalOrVertical);

        /**
         * @brief Randomly place all ships on the board.
         *
         * @param board The board containing the AI's ship positions.
         */
        void GetComputerShipPositions(std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT>& p_board);

        /**
         * @brief Checks whether at least a single ship is present on a game board.
         *
         * @param p_board The game board to check.
         * @return true If at least a single ship is present on the board.
         * @return false If no ships are present on the board
         */
        static bool IsShipPresent(std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT>& p_board);

        /**
         * @brief Checks whether the command is valid.
         *
         * @param p_commandsRemaining The command that haven't been done.
         * @param p_command The command in the form of <row, column>.
         * @return true If the command is valid.
         * @return false If the command is not valid.
         */
        static bool ValidateCommand(
            const std::vector<std::tuple<uint32_t, uint32_t>>& p_commandsRemaining,
            const std::tuple<uint32_t, uint32_t>& p_command);

        /**
         * @brief Executes the command on the opponent's board and updates their own board and commands remaining.
         *
         * @param p_opponentBoard The board containing the opponent's ship positions.
         * @param p_opponentShipsRemaining The number of squares remaining for each opponent ship.
         * @param p_commandsRemaining List of board spaces that remain un-attacked.
         * @param p_command The board row and column that should be attacked.
         */
        void ExecuteGeneralCommand(
            std::array<std::array<std::string, G_BATTLESHIPS_BOARD_WIDTH>, G_BATTLESHIPS_BOARD_HEIGHT>& p_opponentBoard,
            std::unordered_map<std::string, uint32_t>& p_opponentShipsRemaining,
            std::vector<std::tuple<uint32_t, uint32_t>>& p_commandsRemaining,
            const std::tuple<uint32_t, uint32_t>& p_command);
    };
}

#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "games/Game.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @class Battleships
     * @brief Implementation of the %Battleships board game: https://en.wikipedia.org/wiki/Battleship_(game)
     */
    class Battleships : public Game
    {
    public:
        /**
         * @brief Constructs a new %Battleships object.
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        explicit Battleships(const bool& p_useAnsiEscapeCodes);

    private:
        /**
         * @brief See base class function for details.
         */
        ///@{
        void SetupGame() override;

        void GetUserOptions() override;

        void UpdateGameInfo() override;

        bool IsGameOver() override;

        void ToggleCurrentPlayer() override;

        bool IsCurrentTurnUsers() override;

        /**
         * @brief See base class function for details.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserCommandFromGameGrid()`.
         * @bug If the user presses the `Globals::G_TERMINAL_BACKSPACE_KEY` the thrown exception
         * `Globals::Exceptions::BackspaceKeyPressed` will never be caught and the program will crash.
         */
        void ExecuteUserCommand() override;

        void ExecuteComputerCommand() override;

        /**
         * @brief See base class function for details.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameOverMenu()`.
         */
        void GameOver() override;

        void RestartGame() override;

        void ResetGame() override;
        ///@}

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select how the speed of the computer decision making (this does not affect the difficulty
         * of the computer).
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetComputerSpeed();

        /**
         * @brief Prompt the user to place all ships on the board.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserCommandFromGameGrid()` except for
         * `Globals::Exceptions::BackspaceKeyPressed`.
         */
        void GetUserShipPositions();

        /**
         * @brief Validates whether (true) or not (false) `p_selectedShipGridLocation` is a valid grid location to place a ship.
         *
         * @param p_currentShipPositions The grid locations selected for the current ship.
         * @param p_selectedShipGridLocation The grid location to validate.
         * @param p_shipIsHorizontal Whether the ship is being placed horizontally (true) or not (false)
         * @param p_shipIsVertical Whether the ship is being placed vertically (true) or not (false)
         * @return `true` If ship position is valid.
         * @return `false` If the ship position is invalid.
         */
        bool ValidateUserShipPosition(
            const std::vector<std::tuple<uint32_t, uint32_t>>& p_currentShipPositions,
            const std::tuple<uint32_t, uint32_t>& p_selectedShipGridLocation,
            bool& p_shipIsHorizontal,
            bool& p_shipIsVertical);

        /**
         * @brief Randomly place all ships on the board and is used to place the computer's ships.
         *
         * @param p_board The board to place the ships.
         */
        void GetRandomShipPositions(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board);

        /**
         * @brief Checks whether at least a single ship is present on a game board.
         *
         * @param p_board The game board to check.
         * @return `true` If at least a single ship is present on the board.
         * @return `false` If no ships are present on the board
         */
        static bool IsShipPresent(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board);

        /**
         * @brief Checks whether the command is valid.
         *
         * @param p_commandsRemaining The command that haven't been done.
         * @param p_command The command in the form of `<row, column>`.
         * @return `true` If the command is valid.
         * @return `false` If the command is not valid.
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
            std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_opponentBoard,
            std::unordered_map<std::string, uint32_t>& p_opponentShipsRemaining,
            std::vector<std::tuple<uint32_t, uint32_t>>& p_commandsRemaining,
            const std::tuple<uint32_t, uint32_t>& p_command);

        /**
         * @brief Used to build pages required by the game.
         */
        PageBuilder m_pageBuilder;

        /**
         * @brief Used to package up the current state of the game so it can be used by `m_pageBuilder`.
         */
        GameInfo m_gameInfo;

        /**
         * @brief Used to randomly select ships positions for the computer and randomly select board <row, column> values for
         * the computer when attacking a ship.
         */
        std::default_random_engine m_randomNumberGenerator;

        /**
         * @brief The current state of the respective player's board.
         */
        ///@{
        std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerOne;
        std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT> m_boardPlayerTwo;
        ///@}

        /**
         * @brief The respective player's board `<row, column>` values they have not chosen yet.
         */
        ///@{
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemainingPlayerOne;
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemainingPlayerTwo;
        ///@}

        /**
         * @brief The respective player's health of each their ships.
         */
        ///@{
        std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerOne;
        std::unordered_map<std::string, uint32_t> m_shipsRemainingPlayerTwo;
        ///@}

        /**
         * @brief The previous board <row, column> value that was chosen by the user. This is used to return the cursor to this
         * position when the user is prompted to select their next command.
         */
        std::tuple<uint32_t, uint32_t> m_previousCommand;

        /**
         * @brief The name of the user selected computer speed.
         */
        std::string m_computerSpeedName;

        /**
         * @brief The name of the player whose turn it is.
         */
        std::string m_currentPlayer;

        /**
         * @brief The count of the user selected number of players.
         */
        std::string m_playerCount;

        /**
         * @brief The computer speed determined by the amount of seconds the computer must wait before executing it's command.
         */
        uint32_t m_computerSpeed;

        /**
         * @brief The number of turns that have occurred.
         */
        uint32_t m_turnCount;

        /**
         * @brief Whether the user has selected all the game options (true) or not/partially (false). This is used to determine
         * whether to re-prompt the user to select the game options when restarting the game.
         */
        bool m_hasSavedGameOptions;

        /**
         * @brief Whether the game is over (true) or not (false).
         */
        bool m_isGameOver;

        /**
         * @brief Whether to save the user's currently selected game options (true) and restart the game or not (false) and
         * reset the game back to the initial state which will re-prompt the user for the game options.
         */
        bool m_saveGameOptions;
    };
}

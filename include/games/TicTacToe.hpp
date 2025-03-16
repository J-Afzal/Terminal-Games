#pragma once

#include <array>
#include <cstdint>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "games/Game.hpp"
#include "helpers/GameInformation.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @class TicTacToe
     * @brief Implementation of the Tic-Tac-Toe game: https://en.wikipedia.org/wiki/Tic-tac-toe
     */
    class TicTacToe : public Game
    {
    public:
        /**
         * @brief Constructs a new %TicTacToe object.
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        explicit TicTacToe(const bool& p_useAnsiEscapeCodes);

    private:
        void SetupGame() override;

        void GetUserOptions() override;

        void UpdateGameInformation() override;

        bool IsGameOver() override;

        void ToggleCurrentPlayer() override;

        bool IsCurrentTurnUsers() override;

        /**
         * @brief Prompt the user to enter their command for the current turn.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserCommandFromGameGrid()`.
         * @bug If the user presses the `Globals::G_TERMINAL_BACKSPACE_KEY` the thrown exception
         * `Globals::Exceptions::BackspaceKeyPressed` will never be caught and the program will crash.
         */
        void ExecuteUserCommand() override;

        void ExecuteComputerCommand() override;

        /**
         * @brief Display the game over message and prompt the user whether they would like to play again or quit the game.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameOverMenu()`.
         */
        void GameOver() override;

        void RestartGame() override;

        void ResetGame() override;

        /**
         * @brief Prompts the user to select how many players will be playing the game.
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetPlayerCount();

        /**
         * @brief Prompts the user to select which player the will be playing the game as (only supported if playing against the
         * computer).
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetUserPlayerChoice();

        /**
         * @brief Prompts the user to select how the speed of computer decision making (this does not affect the difficulty of
         * the computer).
         * @warning This function does not catch any exceptions thrown by `Terminal::GetUserChoiceFromGameMenus()`.
         */
        void GetComputerSpeed();

        /**
         * @brief Checks whether the command is valid.
         *
         * @param p_command The command in the form of <row, column>.
         * @return `true` If the command is valid.
         * @return `false` If the command is not valid.
         */
        bool ValidateCommand(const std::tuple<uint32_t, uint32_t>& p_command);

        /**
         * @brief Executes the command against the game grid.
         *
         * @param p_command The command in the form of `<row, column>`.
         */
        void ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t>& p_command);

        /**
         * @brief Used to build pages required by the game.
         */
        PageBuilder m_pageBuilder;

        /**
         * @brief Used to package up the current state of the game so it can be used by m_pageBuilder.
         */
        GameInformation m_gameInformation;

        /**
         * @brief Used to randomly choose the player to start the game and to randomly decide the computer's next command.
         */
        std::default_random_engine m_randomNumberGenerator;

        /**
         * @brief The Tic Tac Toe grid.
         */
        std::array<std::array<std::string, Globals::G_TICTACTOE_GRID_WIDTH>, Globals::G_TICTACTOE_GRID_HEIGHT> m_gameGrid;

        /**
         * @brief The grid `<row, column>` values that have not been chosen yet.
         */
        std::vector<std::tuple<uint32_t, uint32_t>> m_commandsRemaining;

        /**
         * @brief The previous grid <row, column> value that was chosen by the user. This is used to return the cursor to this
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
         * @brief The choice of which player the user has selected.
         */
        std::string m_userPlayerChoice;

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
         * @brief Whether the game has concluded with a winner (true) or whether it is a draw (false).
         */
        bool m_hasWinner;

        /**
         * @brief Whether to save the user's currently selected game options (true) and restart the game or not (false) and
         * reset the game back to the initial state which will re-prompt the user for the game options.
         */
        bool m_saveGameOptions;
    };
}

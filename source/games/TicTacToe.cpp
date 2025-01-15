#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "games/TicTacToe.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    TicTacToe::TicTacToe(const bool& p_useAnsiEscapeCodes) :
        m_computerSpeed(0),
        m_turnCount(0),
        m_hasSavedGameOptions(false),
        m_hasWinner(false),
        m_saveGameOptions(false)
    {
        m_pageBuilder.SetProperties(Pages::TICTACTOE, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void TicTacToe::SetupGame()
    {
        m_currentPlayer = Globals::G_TICTACTOE_PLAYER_CHOICE_OPTIONS[m_randomNumberGenerator() % 2];
        m_commandsRemaining.clear();
        m_previousCommand = {0, 0};
        m_turnCount = 0;
        m_hasWinner = false;

        for (uint32_t row = 0; row < Globals::G_TICTACTOE_BOARD_HEIGHT; row++)
            for (uint32_t column = 0; column < Globals::G_TICTACTOE_BOARD_WIDTH; column++)
            {
                m_gameGrid.at(row).at(column) = Globals::G_TICTACTOE_EMPTY_GRID_VALUE;
                m_commandsRemaining.emplace_back(row, column);
            }
    }

    void TicTacToe::GetUserOptions()
    {
        if (m_saveGameOptions && m_hasSavedGameOptions)
            return;

        m_computerSpeedName = Globals::G_GAME_UNKNOWN_OPTION;
        m_playerCount = Globals::G_GAME_UNKNOWN_OPTION;
        m_userPlayerChoice = Globals::G_GAME_UNKNOWN_OPTION;

        GetPlayerCount();

        if (m_playerCount == "0" || m_playerCount == "1")
            GetComputerSpeed();

        if (m_playerCount == "1")
            GetUserPlayerChoice();

        m_hasSavedGameOptions = true;
    }

    void TicTacToe::UpdateGameInfo()
    {
        m_gameInfo.m_ticTacToeGameInfo = {
            .m_gameGrid = m_gameGrid,
            .m_computerSpeedName = m_computerSpeedName,
            .m_currentPlayer = m_currentPlayer,
            .m_playerCount = m_playerCount,
            .m_turnCount = m_turnCount,
            .m_hasWinner = m_hasWinner,
        };
    }

    bool TicTacToe::IsGameOver()
    {
        // Check horizontals
        if ((m_gameGrid[0][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[0][0] == m_gameGrid[0][1] && m_gameGrid[0][1] == m_gameGrid[0][2]) ||
            (m_gameGrid[1][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[1][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[1][2]) ||
            (m_gameGrid[2][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[2][0] == m_gameGrid[2][1] && m_gameGrid[2][1] == m_gameGrid[2][2]) ||

            // Check verticals
            (m_gameGrid[0][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[0][0] == m_gameGrid[1][0] && m_gameGrid[1][0] == m_gameGrid[2][0]) ||
            (m_gameGrid[0][1] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[0][1] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][1]) ||
            (m_gameGrid[0][2] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[0][2] == m_gameGrid[1][2] && m_gameGrid[1][2] == m_gameGrid[2][2]) ||

            // Check diagonals
            (m_gameGrid[0][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[0][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][2]) ||
            (m_gameGrid[2][0] != Globals::G_TICTACTOE_EMPTY_GRID_VALUE && m_gameGrid[2][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[0][2]))
        {
            m_hasWinner = true;
            return m_hasWinner;
        }

        return m_turnCount == Globals::G_TICTACTOE_MAXIMUM_ERROR_COUNT;
    }

    void TicTacToe::ToggleCurrentPlayer()
    {
        m_currentPlayer == Globals::G_TICTACTOE_PLAYER_X ? m_currentPlayer = Globals::G_TICTACTOE_PLAYER_O : m_currentPlayer = Globals::G_TICTACTOE_PLAYER_X;
    }

    bool TicTacToe::IsCurrentTurnUsers()
    {
        return m_playerCount == "2" || m_currentPlayer == m_userPlayerChoice;
    }

    void TicTacToe::ExecuteUserCommand()
    {
        while (true)
        {
            const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = Terminal::GetUserCommandFromGameGrid(m_previousCommand, m_pageBuilder, m_gameInfo, true);

            if (ValidateCommand(SELECTED_COMMAND))
            {
                ExecuteGeneralCommand(SELECTED_COMMAND);
                m_previousCommand = SELECTED_COMMAND;
                return;
            }
        }
    }

    void TicTacToe::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));

        const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        if (ValidateCommand(SELECTED_COMMAND))
            ExecuteGeneralCommand(SELECTED_COMMAND);
    }

    void TicTacToe::GameOver()
    {
        Terminal::GetUserChoiceFromGameOverMenu(m_pageBuilder.GetGameOverPage(m_gameInfo), m_pageBuilder.GetQuitOptionSelectionPage());
    }

    void TicTacToe::RestartGame()
    {
        m_saveGameOptions = true;
    }

    void TicTacToe::ResetGame()
    {
        m_saveGameOptions = false;
        m_hasSavedGameOptions = false;
    }

    void TicTacToe::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_playerCount = Globals::G_GAME_MAX_TWO_PLAYERS_OPTIONS[Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)];
    }

    void TicTacToe::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_userPlayerChoice = Globals::G_TICTACTOE_PLAYER_CHOICE_OPTIONS[Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)];
    }

    void TicTacToe::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS);
        m_computerSpeedName = Globals::G_GAME_COMPUTER_SPEED_OPTIONS[m_computerSpeed];
    }

    bool TicTacToe::ValidateCommand(const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_command);

        return COMMAND_FIND_LOCATION != m_commandsRemaining.end();
    }

    void TicTacToe::ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = Globals::ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), p_command);

        m_gameGrid.at(std::get<0>(p_command)).at(std::get<1>(p_command)) = Globals::ImplementStdFormat(Globals::G_TICTACTOE_GRID_OCCUPIED_FORMAT_STRING, m_currentPlayer.back());
        m_commandsRemaining.erase(COMMAND_FIND_LOCATION);
        m_turnCount++;
    }
}

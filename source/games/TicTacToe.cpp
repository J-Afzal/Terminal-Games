#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    TicTacToe::TicTacToe(const bool &onlyUseASCII) // NOLINT(cert-msc32-c,cert-msc51-cpp,cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    {
        m_pageBuilder.SetProperties(Pages::TICTACTOE, onlyUseASCII);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void TicTacToe::SetupGame()
    {
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player X" : m_currentPlayer = "Player O";
        m_commandsRemaining.clear();
        m_previousCommand = {0, 0};
        m_computerSpeedName = "N/A";
        m_playerCount = "N/A";
        m_userPlayerChoice = " ";
        m_turnCount = 0;
        m_hasWinner = false;

        for (uint32_t i = 0; i < g_TICTACTOE_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < g_TICTACTOE_BOARD_WIDTH; j++)
            {
                m_gameGrid[i][j] = "   "; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                m_commandsRemaining.emplace_back(i, j);
            }
        }
    }

    void TicTacToe::UpdateGameInfo()
    {
        m_gameInfo.ticTacToeStruct = {
            .gameGrid = m_gameGrid,
            .computerSpeedName = m_computerSpeedName,
            .currentPlayer = m_currentPlayer,
            .playerCount = m_playerCount,
            .turnCount = m_turnCount,
            .hasWinner = m_hasWinner};
    }

    void TicTacToe::GetUserOptions()
    {
        GetPlayerCount();

        // If only one human user, then ask them which player they want to be (X or O)
        if (m_playerCount == "1  ")
        {
            GetUserPlayerChoice();
        }

        // If computer involved get computer difficulty and speed
        if (m_playerCount != "2  ") // i.e. = 0 or = 1
        {
            GetComputerSpeed();
        }

        UpdateGameInfo();
    }

    bool TicTacToe::IsGameOver()
    {
        // Check horizontals
        if ((m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[0][1] && m_gameGrid[0][1] == m_gameGrid[0][2]) ||
            (m_gameGrid[1][0] != "   " && m_gameGrid[1][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[1][2]) ||
            (m_gameGrid[2][0] != "   " && m_gameGrid[2][0] == m_gameGrid[2][1] && m_gameGrid[2][1] == m_gameGrid[2][2]) ||

            // Check verticals
            (m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[1][0] && m_gameGrid[1][0] == m_gameGrid[2][0]) ||
            (m_gameGrid[0][1] != "   " && m_gameGrid[0][1] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][1]) ||
            (m_gameGrid[0][2] != "   " && m_gameGrid[0][2] == m_gameGrid[1][2] && m_gameGrid[1][2] == m_gameGrid[2][2]) ||

            // Check diagonals
            (m_gameGrid[0][0] != "   " && m_gameGrid[0][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][2]) ||
            (m_gameGrid[2][0] != "   " && m_gameGrid[2][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[0][2]))
        {
            m_hasWinner = true;
            return m_hasWinner;
        }

        return m_turnCount == g_TICTACTOE_MAXIMUM_ERROR_COUNT;
    }

    void TicTacToe::ToggleCurrentPlayer()
    {
        m_currentPlayer == "Player X" ? m_currentPlayer = "Player O" : m_currentPlayer = "Player X";
    }

    bool TicTacToe::IsCurrentTurnUsers()
    {
        // If it is two player game then next turn will always be the user's turn, if not then
        // check if the current player is the same as the user's choice. For a zero player game
        // m_UserPlayerChoice = ' ' and so this will always return false.
        return m_playerCount == "2  " || m_currentPlayer == m_userPlayerChoice;
    }

    void TicTacToe::ExecuteUserCommand()
    {
        const uint32_t startingRow = std::get<0>(m_previousCommand);
        const uint32_t startingColumn = std::get<1>(m_previousCommand);

        while (true)
        {
            const std::tuple<uint32_t, uint32_t> selectedCommand = Terminal::GetUserCommandFromGameGrid(m_pageBuilder, m_gameInfo, startingRow, startingColumn, g_TICTACTOE_BOARD_HEIGHT - 1, g_TICTACTOE_BOARD_WIDTH - 1, g_TICTACTOE_GRID_LEFT_PAD, g_TICTACTOE_GRID_TOP_PAD, g_TICTACTOE_GRID_ELEMENT_WIDTH, g_TICTACTOE_GRID_ELEMENT_HEIGHT, true);

            if (ValidateCommand(selectedCommand))
            {
                ExecuteGeneralCommand(selectedCommand);
                m_previousCommand = selectedCommand;
                return;
            }
        }
    }

    void TicTacToe::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        if (m_computerSpeed != 0)
        {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));
        }

        const std::tuple<uint32_t, uint32_t> selectedCommand = m_commandsRemaining[m_randomNumberGenerator() % m_commandsRemaining.size()];

        if (ValidateCommand(selectedCommand))
        {
            ExecuteGeneralCommand(selectedCommand);
            return;
        }
    }

    void TicTacToe::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == 'q')
        {
            throw Exceptions::QuitGame();
        }
    }

    void TicTacToe::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
    }

    void TicTacToe::GetUserPlayerChoice()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        Terminal::GetUserChoiceFromGameMenus(menus) == 0 ? m_userPlayerChoice = "Player X" : m_userPlayerChoice = "Player O";
    }

    void TicTacToe::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(menus);

        if (m_computerSpeed == 0)
        {
            m_computerSpeedName = "INSTANT";
        }

        else if (m_computerSpeed == 1)
        {
            m_computerSpeedName = "FAST";
        }

        else // == 2
        {
            m_computerSpeedName = "SLOW";
        }
    }

    bool TicTacToe::ValidateCommand(const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandFindLocation = ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), command);

        return commandFindLocation != m_commandsRemaining.end();
    }

    void TicTacToe::ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandFindLocation = ImplementStdRangesFind(m_commandsRemaining.begin(), m_commandsRemaining.end(), command);

        m_gameGrid[std::get<0>(command)][std::get<1>(command)] = std::string(" ") + m_currentPlayer.back() + std::string(" "); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        m_commandsRemaining.erase(commandFindLocation);
        m_turnCount++;
    }
} // namespace TerminalGames

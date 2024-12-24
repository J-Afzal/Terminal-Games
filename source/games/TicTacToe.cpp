#include <algorithm>
#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

#include "games/TicTacToe.hpp"
#include "helpers/Constants.hpp"
#include "helpers/Exceptions.hpp"
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
        m_movesRemaining.clear();
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player X" : m_currentPlayer = "Player O";
        m_playerCount = "N/A";
        m_userPlayerChoice = " ";
        m_AISpeedName = "N/A";
        m_turnCount = 0;
        m_hasWinner = false;

        for (uint32_t i = 0; i < g_TICTACTOE_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < g_TICTACTOE_BOARD_WIDTH; j++)
            {
                m_gameGrid[i][j] = ' '; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                m_movesRemaining.emplace_back(i, j);
            }
        }
    }

    void TicTacToe::UpdateGameInfo()
    {
        m_gameInfo.ticTacToeStruct = {
            .gameGrid = m_gameGrid,
            .currentPlayer = m_currentPlayer,
            .playerCount = m_playerCount,
            .AISpeedName = m_AISpeedName,
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

        // If AI involved get AI difficulty and speed
        if (m_playerCount != "2  ") // i.e. = 0 or = 1
        {
            GetAISpeed();
        }
    }

    void TicTacToe::GetPlayerCount()
    {
        const std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
    }

    void TicTacToe::GetUserPlayerChoice()
    {
        const std::vector<std::string> menus = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
        Terminal::GetUserChoiceFromGameMenus(menus) == 0 ? m_userPlayerChoice = "Player X" : m_userPlayerChoice = "Player O";
    }

    void TicTacToe::GetAISpeed()
    {
        const std::vector<std::string> menus = m_pageBuilder.GetAISpeedOptionSelectionGamePages(m_gameInfo);
        m_AISpeed = Terminal::GetUserChoiceFromGameMenus(menus);

        if (m_AISpeed == 0)
        {
            m_AISpeedName = "INSTANT";
        }

        else if (m_AISpeed == 1)
        {
            m_AISpeedName = "FAST";
        }

        else // == 2
        {
            m_AISpeedName = "SLOW";
        }
    }

    bool TicTacToe::IsGameOver()
    {
        // Check horizontals
        if ((m_gameGrid[0][0] != ' ' && m_gameGrid[0][0] == m_gameGrid[0][1] && m_gameGrid[0][1] == m_gameGrid[0][2]) ||
            (m_gameGrid[1][0] != ' ' && m_gameGrid[1][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[1][2]) ||
            (m_gameGrid[2][0] != ' ' && m_gameGrid[2][0] == m_gameGrid[2][1] && m_gameGrid[2][1] == m_gameGrid[2][2]) ||

            // Check verticals
            (m_gameGrid[0][0] != ' ' && m_gameGrid[0][0] == m_gameGrid[1][0] && m_gameGrid[1][0] == m_gameGrid[2][0]) ||
            (m_gameGrid[0][1] != ' ' && m_gameGrid[0][1] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][1]) ||
            (m_gameGrid[0][2] != ' ' && m_gameGrid[0][2] == m_gameGrid[1][2] && m_gameGrid[1][2] == m_gameGrid[2][2]) ||

            // Check diagonals
            (m_gameGrid[0][0] != ' ' && m_gameGrid[0][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[2][2]) ||
            (m_gameGrid[2][0] != ' ' && m_gameGrid[2][0] == m_gameGrid[1][1] && m_gameGrid[1][1] == m_gameGrid[0][2]))
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
        Terminal::PrintOutput(m_pageBuilder.GetUserCommandPage(m_gameInfo));

        const uint32_t startingRow = std::get<0>(m_movesRemaining.front());
        const uint32_t startingColumn = std::get<1>(m_movesRemaining.front());

        while (true)
        {
            const std::tuple<uint32_t, uint32_t> selectedCommand = Terminal::GetUserCommandFromGameGrid(startingRow, startingColumn, g_TICTACTOE_BOARD_HEIGHT - 1, g_TICTACTOE_BOARD_WIDTH - 1, g_TICTACTOE_GRID_LEFT_PAD, g_TICTACTOE_GRID_TOP_PAD, g_TICTACTOE_GRID_ELEMENT_WIDTH, g_TICTACTOE_GRID_ELEMENT_HEIGHT);

            if (ValidateCommand(selectedCommand))
            {
                ExecuteGeneralCommand(selectedCommand);
                return;
            }
        }
    }

    void TicTacToe::ExecuteAICommand()
    {
        if (m_AISpeed != 0)
        {
            Terminal::PrintOutput(m_pageBuilder.GetAICommandPage(m_gameInfo));
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_AISpeed));
        }

        const std::tuple<uint32_t, uint32_t> selectedCommand = m_movesRemaining[m_randomNumberGenerator() % m_movesRemaining.size()];

        if (ValidateCommand(selectedCommand))
        {
            ExecuteGeneralCommand(selectedCommand);
            return;
        }
    }

    bool TicTacToe::ValidateCommand(const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandPosition = std::ranges::find(m_movesRemaining.begin(), m_movesRemaining.end(), command, {});

        return commandPosition != m_movesRemaining.end();
    }

    void TicTacToe::ExecuteGeneralCommand(const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandPosition = std::ranges::find(m_movesRemaining.begin(), m_movesRemaining.end(), command, {});

        m_gameGrid[std::get<0>(command)][std::get<1>(command)] = m_currentPlayer.back(); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        m_movesRemaining.erase(commandPosition);
        m_turnCount++;
        Terminal::SetCursorVisibility(false);
    }

    void TicTacToe::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == 'q')
        {
            throw Exceptions::QuitGame();
        }
    }
} // namespace TerminalGames

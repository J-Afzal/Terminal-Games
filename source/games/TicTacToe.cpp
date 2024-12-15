#include <chrono>
#include <cstdint>
#include <string>
#include <thread>
#include <vector>

#include "games/TicTacToe.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

TicTacToe::TicTacToe(const bool& outputIsOnlyASCII)
{
    m_pageBuilder.SetProperties(Pages::TICTACTOE, outputIsOnlyASCII);
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

    for (uint32_t i = 0, GridNumber = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++, GridNumber++)
        {
            m_gameGrid[i][j] = ' ';
            m_movesRemaining.push_back(GridNumber); // 0-8
        }
    }
}

void TicTacToe::UpdateGameInfo()
{
    m_gameInfo.ticTacToeStruct = { m_gameGrid, m_currentPlayer, m_playerCount, m_AISpeedName, m_turnCount, m_hasWinner };
}

void TicTacToe::GetUserOptions()
{
    GetPlayerCount();

    // If only one human user, then ask them which player they want to be (X or O)
    if (m_playerCount == "1  ")
        GetUserPlayerChoice();

    // If AI involved get AI difficulty and speed
    if (m_playerCount != "2  ") // i.e. = 0 or = 1
        GetAISpeed();
}

void TicTacToe::GetPlayerCount()
{
    std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
    m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
}

void TicTacToe::GetUserPlayerChoice()
{
    std::vector<std::string> menus = m_pageBuilder.GetUserPlayerChoiceOptionSelectionGamePages(m_gameInfo);
    Terminal::GetUserChoiceFromGameMenus(menus) == 0 ? m_userPlayerChoice = "Player X" : m_userPlayerChoice = "Player O";
}

void TicTacToe::GetAISpeed()
{
    std::vector<std::string> menus = m_pageBuilder.GetAISpeedOptionSelectionGamePages(m_gameInfo);
    m_AISpeed = Terminal::GetUserChoiceFromGameMenus(menus);

    if (m_AISpeed == 0)
        m_AISpeedName = "INSTANT";
    else if (m_AISpeed == 1)
        m_AISpeedName = "FAST";
    else // == 2
        m_AISpeedName = "SLOW";
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

    else
        return m_turnCount == 9;
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

    Terminal::SetCursorVisibility(true);

    uint32_t KeyPress, Row = m_movesRemaining[0] / 3, Column = m_movesRemaining[0] % 3;

    while (true)
    {
        while (true)
        {
            Terminal::SetCursorPosition(3 + Column * 4, 4 + Row * 2);

            KeyPress = Terminal::GetNextKeyPress();

            if (KeyPress == '\r') // enter key
                break;
            else if (KeyPress == 72) // up arrow key
                Row == 0 ? Row = 2 : --Row;
            else if (KeyPress == 80) // down arrow key
                Row == 2 ? Row = 0 : ++Row;
            else if (KeyPress == 75) // left arrow key
                Column == 0 ? Column = 2 : --Column;
            else if (KeyPress == 77) // right arrow key
                Column == 2 ? Column = 0 : ++Column;
            else if (KeyPress == 'q')
            {
                Terminal::SetCursorVisibility(false);
                throw Exceptions::QuitGame();
            }
        }

        auto CommandPosition = std::find(m_movesRemaining.begin(), m_movesRemaining.end(), Row * 3 + Column);

        if (CommandPosition != m_movesRemaining.end())
        {
            m_gameGrid[Row][Column] = m_currentPlayer.back();
            m_movesRemaining.erase(CommandPosition);
            m_turnCount++;
            Terminal::SetCursorVisibility(false);
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

    m_AICommand = m_movesRemaining[m_randomNumberGenerator() % m_movesRemaining.size()];

    m_gameGrid[m_AICommand / 3][m_AICommand % 3] = m_currentPlayer.back();
    m_movesRemaining.erase(std::find(m_movesRemaining.begin(), m_movesRemaining.end(), m_AICommand));
    m_turnCount++;
}

void TicTacToe::GameOver()
{
    Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

    if (Terminal::GetNextKeyPress() == 'q')
        throw Exceptions::QuitGame();
}

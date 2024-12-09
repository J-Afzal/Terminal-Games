/**
 * @file TicTacToe.cpp
 * @author Junaid Afzal
 * @brief Implementation of TicTacToe.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "games/TicTacToe.hpp"

TicTacToe::TicTacToe(const bool& outputIsOnlyASCII)
{
    m_stringBuilder.SetProperties("Tic Tac Toe", "q = quit to main menu", 53, outputIsOnlyASCII);
    m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void TicTacToe::SetupGame()
{
    m_movesRemaining.clear();
    m_playerCount = "N/A";
    m_speedNameAI = "N/A";
    m_turnCount = 0;
    m_playerChoiceUser = ' ';
    m_hasWinner = false;
    m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = 'X' : m_currentPlayer = 'O';

    for (uint32_t i = 0, GridNumber = 0; i < 3; i++)
    {
        for (uint32_t j = 0; j < 3; j++, GridNumber++)
        {
            m_gameGrid[i][j] = ' ';
            m_movesRemaining.push_back(GridNumber); // 0-8
        }
    }

    GetPlayerCount();

    // If only one human user, then ask them which player they want to be (X or O)
    if (m_playerCount == "1  ")
        GetPlayerChoiceFromUser();

    // If AI involved get AI difficulty and speed
    if (m_playerCount != "2  ") // i.e. = 0 or = 1
        GetAISpeed();
}

void TicTacToe::GetPlayerCount()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select the number of players:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > 0", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   1");
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   2");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   0");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > 1", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   2");
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[2] = GameDisplay;
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   0");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   1");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified(" > 2", Colours::BLUE);
    Menus[2] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(Menus)) + "  ";
}

void TicTacToe::GetPlayerChoiceFromUser()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select the player you would like to be:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > PLAYER X", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   PLAYER O");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   PLAYER X");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > PLAYER O", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Terminal::GetUserChoiceFromGameMenus(Menus) == 0 ? m_playerChoiceUser = 'X' : m_playerChoiceUser = 'O';
}

void TicTacToe::GetAISpeed()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = GetGameDisplay() + m_stringBuilder.AddNewLineLeftJustified(" Please select the AI speed:");

    Menus[0] = GameDisplay;
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified(" > INSTANT", Colours::BLUE);
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   FAST");
    Menus[0] += m_stringBuilder.AddNewLineLeftJustified("   SLOW");
    Menus[0] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[1] = GameDisplay;
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   INSTANT");
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified(" > FAST", Colours::BLUE);
    Menus[1] += m_stringBuilder.AddNewLineLeftJustified("   SLOW");
    Menus[1] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    Menus[2] = GameDisplay;
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   INSTANT");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified("   FAST");
    Menus[2] += m_stringBuilder.AddNewLineLeftJustified(" > SLOW", Colours::BLUE);
    Menus[2] += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    m_speedAI = Terminal::GetUserChoiceFromGameMenus(Menus);

    if (m_speedAI == 0)
        m_speedNameAI = "INSTANT";
    else if (m_speedAI == 1)
        m_speedNameAI = "FAST";
    else // == 2
        m_speedNameAI = "SLOW";
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
    m_currentPlayer == 'X' ? m_currentPlayer = 'O' : m_currentPlayer = 'X';
}

bool TicTacToe::IsNextTurnUser() const
{
    // If it is two player game then next turn will always be the user's turn, if not then
    // check if the current player is the same as the user's choice. For a zero player game
    // m_UserPlayerChoice = ' ' and so this will always return false.
    return m_playerCount == "2  " || m_currentPlayer == m_playerChoiceUser;
}

void TicTacToe::ExecuteCommandUser()
{
    std::string Output = GetGameDisplay();
    Output += m_stringBuilder.AddNewLineLeftJustified(std::string(" Player ") + m_currentPlayer + ", please enter your next command!");
    Output += m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();
    Terminal::PrintOutput(Output);

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
            m_gameGrid[Row][Column] = m_currentPlayer;
            m_movesRemaining.erase(CommandPosition);
            m_turnCount++;
            Terminal::SetCursorVisibility(false);
            return;
        }
    }
}

void TicTacToe::ExecuteCommandAI()
{
    if (m_speedAI != 0)
    {
        std::string Output = GetGameDisplay();
        Output += m_stringBuilder.AddNewLineLeftJustified(" The AI is executing their next move!") + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddEmptyLine() + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();
        Terminal::PrintOutput(Output);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_speedAI));
    }

    m_commandAI = m_movesRemaining[m_randomNumberGenerator() % m_movesRemaining.size()];

    m_gameGrid[m_commandAI / 3][m_commandAI % 3] = m_currentPlayer;
    m_movesRemaining.erase(std::find(m_movesRemaining.begin(), m_movesRemaining.end(), m_commandAI));
    m_turnCount++;
}

std::string TicTacToe::GetGameOverMessage() const
{
    std::string Output = GetGameDisplay() + m_stringBuilder.AddNewLineCentred("GAME OVER") + m_stringBuilder.AddEmptyLine();

    if (m_hasWinner)
        Output += m_stringBuilder.AddNewLineCentred(
                std::string("Player ") + m_currentPlayer + " has won! The game lasted " +
                std::to_string(m_turnCount) + " turns.");
    else
        Output += m_stringBuilder.AddNewLineCentred(
                "It is a draw! The game lasted " + std::to_string(m_turnCount) + " turns.");

    Output += m_stringBuilder.AddEmptyLine() +
            m_stringBuilder.AddNewLineCentred("Press 'Q' to quit OR Enter to play again...") + m_stringBuilder.AddBottomLine() + m_stringBuilder.AddBottomBox();

    return Output;
}

std::string TicTacToe::GetGameDisplay() const
{
    std::string Output = m_stringBuilder.AddTopBox();

    Output += m_stringBuilder.AddTopLine();

    Output += m_stringBuilder.AddNewLineLeftJustified(std::string("  ") + m_gameGrid[0][0] + " " + char(179) + " " + m_gameGrid[0][1] + " " + char(179) + " " + m_gameGrid[0][2]);

    Output += m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "    # of Players = " + m_playerCount);

    Output += m_stringBuilder.AddNewLineLeftJustified(std::string("  ") + m_gameGrid[1][0] + " " + char(179) + " " + m_gameGrid[1][1] + " " + char(179) + " " + m_gameGrid[1][2]);

    Output += m_stringBuilder.AddNewLineLeftJustified(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "    AI Speed = " + m_speedNameAI);

    Output += m_stringBuilder.AddNewLineLeftJustified(std::string("  ") + m_gameGrid[2][0] + " " + char(179) + " " + m_gameGrid[2][1] + " " + char(179) + " " + m_gameGrid[2][2]);

    return Output += m_stringBuilder.AddEmptyLine();
}

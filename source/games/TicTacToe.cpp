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

TicTacToe::TicTacToe()
{
    m_StringBuilder.Set(53, "Tic Tac Toe", "q = quit to main menu");
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void TicTacToe::Setup_Game()
{
    m_MovesRemaining.clear();
    m_AIDifficulty = "EASY";
    m_NumberOfPlayers = "N/A";
    m_NumberOfTurns = 0;
    m_UserPlayerChoice = ' ';
    m_WinningConditionsMet = false;
    m_RandomNumberGenerator() % 2 == 0 ? m_CurrentPlayer = 'X' : m_CurrentPlayer = 'O';

    for (int i = 0, GridNumber = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++, GridNumber++)
        {
            m_GameGrid[i][j] = ' ';
            m_MovesRemaining.push_back(GridNumber); // 0-8
        }
    }

    Get_Number_Of_Players();

    // If only one human user, then ask them which player they want to be (X or O)
    if (m_NumberOfPlayers == "1  ")
        Get_User_Player_Choice();

    // If AI involved get AI difficulty and speed
    if (m_NumberOfPlayers != "2  ") // i.e. = 0 or = 1
    {
        Get_AI_Difficulty();
        Get_AI_Speed();
    }
}

void TicTacToe::Get_Number_Of_Players()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the number of players:");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > 0", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   1");
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   2");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   0");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > 1", Colours::BLUE);
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   2");
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[2] = GameDisplay;
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   0");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   1");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified(" > 2", Colours::BLUE);
    Menus[2] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    m_NumberOfPlayers = std::to_string(m_Terminal.Get_User_Menu_Choice(Menus)) + "  ";
}

void TicTacToe::Get_User_Player_Choice()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the player you would like to be:");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > PLAYER X", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   PLAYER O");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   PLAYER X");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > PLAYER O", Colours::BLUE);
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    m_Terminal.Get_User_Menu_Choice(Menus) == 0 ? m_UserPlayerChoice = 'X' : m_UserPlayerChoice = 'O';
}

void TicTacToe::Get_AI_Difficulty()
{
    std::vector<std::string> Menus(2);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the AI difficulty:");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > EASY", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   HARD");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   EASY");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > HARD", Colours::BLUE);
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    m_Terminal.Get_User_Menu_Choice(Menus) == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
}

void TicTacToe::Get_AI_Speed()
{
    std::vector<std::string> Menus(3);
    std::string GameDisplay = Get_Game_Display() + m_StringBuilder.New_Line_Left_Justified(" Please select the AI speed:");

    Menus[0] = GameDisplay;
    Menus[0] += m_StringBuilder.New_Line_Left_Justified(" > INSTANT", Colours::BLUE);
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   FAST");
    Menus[0] += m_StringBuilder.New_Line_Left_Justified("   SLOW");
    Menus[0] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[1] = GameDisplay;
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   INSTANT");
    Menus[1] += m_StringBuilder.New_Line_Left_Justified(" > FAST", Colours::BLUE);
    Menus[1] += m_StringBuilder.New_Line_Left_Justified("   SLOW");
    Menus[1] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    Menus[2] = GameDisplay;
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   INSTANT");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified("   FAST");
    Menus[2] += m_StringBuilder.New_Line_Left_Justified(" > SLOW", Colours::BLUE);
    Menus[2] += m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    m_AISpeed = m_Terminal.Get_User_Menu_Choice(Menus);
}

bool TicTacToe::Game_Over()
{
    // Check horizontals
    if ((m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[0][1] && m_GameGrid[0][1] == m_GameGrid[0][2]) ||
        (m_GameGrid[1][0] != ' ' && m_GameGrid[1][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[1][2]) ||
        (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[2][1] && m_GameGrid[2][1] == m_GameGrid[2][2]) ||

        // Check verticals
        (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][0] && m_GameGrid[1][0] == m_GameGrid[2][0]) ||
        (m_GameGrid[0][1] != ' ' && m_GameGrid[0][1] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][1]) ||
        (m_GameGrid[0][2] != ' ' && m_GameGrid[0][2] == m_GameGrid[1][2] && m_GameGrid[1][2] == m_GameGrid[2][2]) ||

        // Check diagonals
        (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][2]) ||
        (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[0][2]))
    {
        m_WinningConditionsMet = true;
        return m_WinningConditionsMet;
    }

    else
        return m_NumberOfTurns == 9;
}

void TicTacToe::Toggle_Current_Player()
{
    m_CurrentPlayer == 'X' ? m_CurrentPlayer = 'O' : m_CurrentPlayer = 'X';
}

bool TicTacToe::Next_Turn_Is_User()
{
    /**
     * If it is two player game then next turn will always be the user's turn, if not then
     * check if the current player is the same as the user's choice. For a zero player game
     * m_UserPlayerChoice = ' ' and so this will always return false.
     */
    return m_NumberOfPlayers == "2  " || m_CurrentPlayer == m_UserPlayerChoice;
}

void TicTacToe::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display();
    Output += m_StringBuilder.New_Line_Left_Justified(std::string(" Player ") + m_CurrentPlayer + ", please enter your next command!");
    Output += m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();
    m_Terminal.Output_To_Terminal(Output);

    m_Terminal.Set_Cursor_Visibility(true);

    int KeyPress, Row = m_MovesRemaining[0] / 3, Column = m_MovesRemaining[0] % 3;

    while (true)
    {
        while (true)
        {
            m_Terminal.Set_Cursor_Position(3 + Column * 4, 4 + Row * 2);

            KeyPress = m_Terminal.Get_Key_Pressed();

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
                m_Terminal.Set_Cursor_Visibility(false);
                throw Exceptions::Quit();
            }
        }

        auto CommandPosition = std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), Row * 3 + Column);

        if (CommandPosition != m_MovesRemaining.end())
        {
            m_GameGrid[Row][Column] = m_CurrentPlayer;
            m_MovesRemaining.erase(CommandPosition);
            m_NumberOfTurns++;
            m_Terminal.Set_Cursor_Visibility(false);
            return;
        }
    }
}

void TicTacToe::Execute_Next_AI_Command()
{
    if (m_AISpeed != 0)
    {
        std::string Output = Get_Game_Display();
        Output += m_StringBuilder.New_Line_Left_Justified(" The AI is executing their next move!") + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Empty_Line() + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();
        m_Terminal.Output_To_Terminal(Output);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_AISpeed));
    }

    if (m_AIDifficulty == "EASY")
        m_AICommand = m_MovesRemaining[m_RandomNumberGenerator() % m_MovesRemaining.size()];
    else
        m_AICommand = m_MovesRemaining[m_RandomNumberGenerator() % m_MovesRemaining.size()];

    m_GameGrid[m_AICommand / 3][m_AICommand % 3] = m_CurrentPlayer;
    m_MovesRemaining.erase(std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), m_AICommand));
    m_NumberOfTurns++;
}

std::string TicTacToe::Get_Game_Over_Message()
{
    std::string Output = Get_Game_Display() + m_StringBuilder.New_Line_Centered("GAME OVER") + m_StringBuilder.Empty_Line();

    if (m_WinningConditionsMet)
        Output += m_StringBuilder.New_Line_Centered(std::string("Player ") + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.");
    else
        Output += m_StringBuilder.New_Line_Centered("It is a draw! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.");

    Output += m_StringBuilder.Empty_Line() + m_StringBuilder.New_Line_Centered("Press 'Q' to quit OR Enter to play again...") + m_StringBuilder.Bottom_Line() + m_StringBuilder.Bottom_Box();

    return Output;
}

std::string TicTacToe::Get_Game_Display()
{
    std::string Output = m_StringBuilder.Top_Box();

    Output += m_StringBuilder.Top_Line();

    Output += m_StringBuilder.New_Line(std::string("  ") + m_GameGrid[0][0] + " " + char(179) + " " + m_GameGrid[0][1] + " " + char(179) + " " + m_GameGrid[0][2] + "                                          ");

    Output += m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "      # of Players = " + m_NumberOfPlayers + "                 ");

    Output += m_StringBuilder.New_Line(std::string("  ") + m_GameGrid[1][0] + " " + char(179) + " " + m_GameGrid[1][1] + " " + char(179) + " " + m_GameGrid[1][2] + "                                          ");

    Output += m_StringBuilder.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "     AI Difficulty = " + m_AIDifficulty + "                ");

    Output += m_StringBuilder.New_Line(std::string("  ") + m_GameGrid[2][0] + " " + char(179) + " " + m_GameGrid[2][1] + " " + char(179) + " " + m_GameGrid[2][2] + "                                          ");

    return Output += m_StringBuilder.Empty_Line();
}

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

#include "TicTacToe.hpp"

TicTacToe::TicTacToe()
{
    m_Terminal.Set(53, "Tic Tac Toe", "q = quit to main menu");
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void TicTacToe::Setup_Game()
{
    m_MovesRemaining.clear();
    m_AIDifficulty = "N/A ";
    m_NumberOfPlayers = "N/A";
    m_NumberOfTurns = 0;
    m_UserPlayerChoice = ' ';
    m_WinningConditionsMet = false;

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

    // If AI involved get AI difficulty
    if (m_NumberOfPlayers != "2  ") // i.e. = 0 or = 1
        Get_AI_Difficulty();

    m_RandomNumberGenerator() % 2 == 0 ? m_CurrentPlayer = 'X' : m_CurrentPlayer = 'O';
}

bool TicTacToe::Game_Over()
{
    // Check Horizontals
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
        return m_WinningConditionsMet = true;

    else
        return m_NumberOfTurns == 9;
}

void TicTacToe::Toggle_Current_Player()
{
    m_CurrentPlayer == 'X' ? m_CurrentPlayer = 'O' : m_CurrentPlayer = 'X';
}

bool TicTacToe::Next_Turn_Is_User()
{
    return m_NumberOfPlayers == "2  " || m_CurrentPlayer == m_UserPlayerChoice;
}

void TicTacToe::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display();
    Output += m_Terminal.New_Line(std::string(" Player ") + m_CurrentPlayer + ", please enter your next command!           ");
    Output += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    Terminal::Output_To_Terminal(Output);

    m_Terminal.Set_Cursor_Visibility(true);

    int KeyPress, Row = m_MovesRemaining[0] / 3, Column = m_MovesRemaining[0] % 3;

    while (true)
    {
        while (true)
        {
            m_Terminal.Set_Cursor_Position(3 + Column * 4, 4 + Row * 2);

            KeyPress = Terminal::Get_Key_Pressed();

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
                throw Quit();
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
    int AICommand = m_MovesRemaining[m_RandomNumberGenerator() % m_MovesRemaining.size()];
    m_GameGrid[AICommand / 3][AICommand % 3] = m_CurrentPlayer;
    m_MovesRemaining.erase(std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), AICommand));
    m_NumberOfTurns++;
}

void TicTacToe::Display_Game_Over_Message()
{
    std::string Output = Get_Game_Display() + m_Terminal.New_Line_Centered("GAME OVER") + m_Terminal.Empty_Line();

    if (m_WinningConditionsMet)
        Output += m_Terminal.New_Line_Centered(std::string("Player ") + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.");
    else
        Output += m_Terminal.New_Line_Centered("It is a draw! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.");

    Output += m_Terminal.Empty_Line() + m_Terminal.New_Line_Centered("Press 'Q' to quit OR any other key to play again...") + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    Terminal::Output_To_Terminal(Output);

    if (Terminal::Get_Key_Pressed() == 'q')
        throw Quit();
}

void TicTacToe::Get_Number_Of_Players()
{
    std::vector<std::string> OptionMenus(3);
    std::string GameDisplay = Get_Game_Display() + m_Terminal.New_Line(" Please select the number of human players:          ");

    OptionMenus[0] = GameDisplay;
    OptionMenus[0] += m_Terminal.New_Line(" > 0                                                 ", "BLUE");
    OptionMenus[0] += m_Terminal.New_Line("   1                                                 ");
    OptionMenus[0] += m_Terminal.New_Line("   2                                                 ");
    OptionMenus[0] += m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    OptionMenus[1] = GameDisplay;
    OptionMenus[1] += m_Terminal.New_Line("   0                                                 ");
    OptionMenus[1] += m_Terminal.New_Line(" > 1                                                 ", "BLUE");
    OptionMenus[1] += m_Terminal.New_Line("   2                                                 ");
    OptionMenus[1] += m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    OptionMenus[2] = GameDisplay;
    OptionMenus[2] += m_Terminal.New_Line("   0                                                 ");
    OptionMenus[2] += m_Terminal.New_Line("   1                                                 ");
    OptionMenus[2] += m_Terminal.New_Line(" > 2                                                 ", "BLUE");
    OptionMenus[2] += m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    std::vector<std::string> Options(3);
    Options[0] = "0  ";
    Options[1] = "1  ";
    Options[2] = "2  ";

    m_NumberOfPlayers = Get_User_Option_Choice(OptionMenus, Options);
}

void TicTacToe::Get_User_Player_Choice()
{
    std::vector<std::string> OptionMenus(2);
    std::string GameDisplay = Get_Game_Display() + m_Terminal.New_Line(" Please select the number of human players:          ");

    OptionMenus[0] = GameDisplay;
    OptionMenus[0] += m_Terminal.New_Line(" > PLAYER X                                          ", "BLUE");
    OptionMenus[0] += m_Terminal.New_Line("   PLAYER O                                          ");
    OptionMenus[0] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    OptionMenus[1] = GameDisplay;
    OptionMenus[1] += m_Terminal.New_Line("   PLAYER X                                          ");
    OptionMenus[1] += m_Terminal.New_Line(" > PLAYER O                                          ", "BLUE");
    OptionMenus[1] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    std::vector<char> Options(2);
    Options[0] = 'X';
    Options[1] = 'O';

    m_UserPlayerChoice = Get_User_Option_Choice(OptionMenus, Options);
}

void TicTacToe::Get_AI_Difficulty()
{
    std::vector<std::string> OptionMenus(2);
    std::string GameDisplay = Get_Game_Display() + m_Terminal.New_Line(" Please select the AI difficulty:                    ");

    OptionMenus[0] = GameDisplay;
    OptionMenus[0] += m_Terminal.New_Line(" > EASY                                              ", "BLUE");
    OptionMenus[0] += m_Terminal.New_Line("   HARD (Coming Soon!)                               ");
    OptionMenus[0] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    OptionMenus[1] = GameDisplay;
    OptionMenus[1] += m_Terminal.New_Line("   EASY                                              ");
    OptionMenus[1] += m_Terminal.New_Line(" > HARD (Coming Soon!)                               ", "BLUE");
    OptionMenus[1] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    std::vector<std::string> Options(2);
    Options[0] = "EASY";
    Options[1] = "HARD";

    while (m_AIDifficulty != "EASY") // As HARD is not implemented
        m_AIDifficulty = Get_User_Option_Choice(OptionMenus, Options);
}

std::string TicTacToe::Get_Game_Display()
{
    std::string Output = m_Terminal.Top_Box();

    Output += m_Terminal.Top_Line();

    Output += m_Terminal.New_Line(std::string("  ") + m_GameGrid[0][0] + " " + char(179) + " " + m_GameGrid[0][1] + " " + char(179) + " " + m_GameGrid[0][2] + "                                          ");

    Output += m_Terminal.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "      # of Players = " + m_NumberOfPlayers + "                 ");

    Output += m_Terminal.New_Line(std::string("  ") + m_GameGrid[1][0] + " " + char(179) + " " + m_GameGrid[1][1] + " " + char(179) + " " + m_GameGrid[1][2] + "                                          ");

    Output += m_Terminal.New_Line(std::string(" ") + (char)196 + (char)196 + (char)196 + (char)197 + (char)196 + (char)196 + (char)196 + char(197) + (char)196 + (char)196 + (char)196 + "     AI Difficulty = " + m_AIDifficulty + "                ");

    Output += m_Terminal.New_Line(std::string("  ") + m_GameGrid[2][0] + " " + char(179) + " " + m_GameGrid[2][1] + " " + char(179) + " " + m_GameGrid[2][2] + "                                          ");

    return Output += m_Terminal.Empty_Line();
}

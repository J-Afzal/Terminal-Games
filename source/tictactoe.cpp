/**
 * @file tictactoe.cpp
 * @author Junaid Afzal
 * @brief Implementation of tictactoe.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "terminal.hpp"
#include "tictactoe.hpp"

TicTacToe::TicTacToe(const HANDLE &ConsoleHandle) : m_ConsoleHandle(ConsoleHandle) {}

TicTacToe::~TicTacToe() = default;

bool TicTacToe::Setup_Game()
{
    m_MovesRemaining.clear();
    m_AIDifficulty = "N/A";
    m_NumberOfTurns = 0;
    m_NumberOfPlayers = -1;
    m_UserPlayerChoice = -1;
    m_WinningConditionsMet = false;
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());

    for (int i = 0, GridNumber = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++, GridNumber++)
        {
            m_GameGrid[i][j] = ' ';
            m_MovesRemaining.push_back(GridNumber); // 0-8
        }
    }

    if (Get_Number_Of_Players()) // if true, quit to main menu
        return true;

    // If only one human user, then ask them which player they want to be (X or O)
    if (m_NumberOfPlayers == 1)
        if (Get_User_Player_Choice()) // if true, quit to main menu
            return true;

    // If AI involved get AI difficulty
    if (m_NumberOfPlayers < 2)
        if (Get_AI_Difficulty()) // if true, quit to main menu
            return true;

    m_RandomNumberGenerator() % 2 == 0 ? m_CurrentPlayer = 'X' : m_CurrentPlayer = 'O';

    return false;
}

bool TicTacToe::Game_Over()
{
    // Check Horizontals
    if ((m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[0][1] && m_GameGrid[0][1] == m_GameGrid[0][2]) || (m_GameGrid[1][0] != ' ' && m_GameGrid[1][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[1][2]) || (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[2][1] && m_GameGrid[2][1] == m_GameGrid[2][2])

        // Check verticals
        || (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][0] && m_GameGrid[1][0] == m_GameGrid[2][0]) || (m_GameGrid[0][1] != ' ' && m_GameGrid[0][1] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][1]) || (m_GameGrid[0][2] != ' ' && m_GameGrid[0][2] == m_GameGrid[1][2] && m_GameGrid[1][2] == m_GameGrid[2][2])

        // Check diagonals
        || (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][2]) || (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[0][2]))
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
    return m_NumberOfPlayers == 2 || m_CurrentPlayer == m_UserPlayerChoice;
}

bool TicTacToe::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display();
    Output += New_Line(std::string(" Player ") + m_CurrentPlayer + ", please enter your next command!           ");
    Output += Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Output_To_Terminal(Output);

    Set_Cursor_Visibility(m_ConsoleHandle, true);

    int KeyPress, Row = m_MovesRemaining[0] / 3, Column = m_MovesRemaining[0] % 3;

    while (true)
    {
        while (true)
        {
            COORD CursorPosition;
            CursorPosition.X = 3 + Column * 4;
            CursorPosition.Y = 4 + Row * 2;
            SetConsoleCursorPosition(m_ConsoleHandle, CursorPosition);

            KeyPress = _getch();

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
                Set_Cursor_Visibility(m_ConsoleHandle, false);
                return true;
            }
        }

        auto CommandPosition = std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), Row * 3 + Column);

        if (CommandPosition != m_MovesRemaining.end())
        {
            m_GameGrid[Row][Column] = m_CurrentPlayer;
            m_MovesRemaining.erase(CommandPosition);
            m_NumberOfTurns++;
            Set_Cursor_Visibility(m_ConsoleHandle, false);
            return false;
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

bool TicTacToe::Display_Game_Over_Message()
{
    std::string Output = Get_Game_Display();
    Output += New_Line("                      GAME OVER                      ") + Empty_Line(m_Width);

    if (m_WinningConditionsMet)
        Output += New_Line(std::string("     Player ") + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.      ");
    else
        Output += New_Line("       It is a draw! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.        ");

    Output += Empty_Line(m_Width) + New_Line(" Press 'Q' to quit OR any other key to play again... ") + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Output_To_Terminal(Output);

    return _getch() == 'q';
}

bool TicTacToe::Get_Number_Of_Players()
{
    std::array<std::string, 3> Options;
    std::string GameDisplay = Get_Game_Display() + New_Line(" Please select the number of human players:          ");

    Options[0] = GameDisplay;
    Options[0] += New_Line(BLUE + " > 0                                                 " + WHITE);
    Options[0] += New_Line("   1                                                 ");
    Options[0] += New_Line("   2                                                 ");
    Options[0] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Options[1] = GameDisplay;
    Options[1] += New_Line("   0                                                 ");
    Options[1] += New_Line(BLUE + " > 1                                                 " + WHITE);
    Options[1] += New_Line("   2                                                 ");
    Options[1] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Options[2] = GameDisplay;
    Options[2] += New_Line("   0                                                 ");
    Options[2] += New_Line("   1                                                 ");
    Options[2] += New_Line(BLUE + " > 2                                                 " + WHITE);
    Options[2] += Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
        {
            m_NumberOfPlayers = CurrentSelection;
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool TicTacToe::Get_User_Player_Choice()
{
    std::array<std::string, 3> Options;
    std::string GameDisplay = Get_Game_Display() + New_Line(" Please select the number of human players:          ");

    Options[0] = GameDisplay;
    Options[0] += New_Line(BLUE + " > PLAYER X                                          " + WHITE);
    Options[0] += New_Line("   PLAYER O                                          ");
    Options[0] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Options[1] = GameDisplay;
    Options[1] += New_Line("   PLAYER X                                          ");
    Options[1] += New_Line(BLUE + " > PLAYER O                                          " + WHITE);
    Options[1] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
        {
            CurrentSelection == 0 ? m_UserPlayerChoice = 'X' : m_UserPlayerChoice = 'O';
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool TicTacToe::Get_AI_Difficulty()
{
    std::array<std::string, 2> Options;
    std::string GameDisplay = Get_Game_Display() + New_Line(" Please select the AI difficulty:                    ");

    Options[0] = GameDisplay;
    Options[0] += New_Line(BLUE + " > EASY                                              " + WHITE);
    Options[0] += New_Line("   HARD (Coming Soon!)                               ");
    Options[0] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    Options[1] = GameDisplay;
    Options[1] += New_Line("   EASY                                              ");
    Options[1] += New_Line(BLUE + " > HARD (Coming Soon!)                               " + WHITE);
    Options[1] += Empty_Line(m_Width) + Empty_Line(m_Width) + Bottom_Line(m_Width) + Box(m_Width, "                q = quit to main menu                ");

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
        {
            // CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
            m_AIDifficulty = "EASY";
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

std::string TicTacToe::Get_Game_Display()
{
    // Top bar
    std::string Output = WHITE + Box(m_Width, "                     Tic Tac Toe                     ");

    // Centre information
    Output += Top_Line(m_Width);

    // Line 1
    Output += New_Line(std::string("  ") + m_GameGrid[0][0] + " " + char(179) + " " + m_GameGrid[0][1] + " " + char(179) + " " + m_GameGrid[0][2] + "                                          ");

    // Line 2
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (m_NumberOfPlayers == -1)
        Output += std::string("     # of Players = N/A                  ") + (char)186 + "\n";
    else
        Output += "      # of Players = " + std::to_string(m_NumberOfPlayers) + "                   " + (char)186 + "\n";

    // Line 3
    Output += New_Line(std::string("  ") + m_GameGrid[1][0] + " " + char(179) + " " + m_GameGrid[1][1] + " " + char(179) + " " + m_GameGrid[1][2] + "                                          ");

    // Line 4
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (m_AIDifficulty == "N/A")
        Output += std::string("     AI Difficulty = N/A                 ") + (char)186 + "\n";
    else
        Output += "    AI Difficulty = " + m_AIDifficulty + "                 " + (char)186 + "\n";

    // Line 5
    Output += New_Line(std::string("  ") + m_GameGrid[2][0] + " " + char(179) + " " + m_GameGrid[2][1] + " " + char(179) + " " + m_GameGrid[2][2] + "                                          ");

    return Output += Empty_Line(m_Width);
}

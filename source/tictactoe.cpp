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

#include <algorithm>
#include <iomanip>
#include <conio.h>
#include "terminal.hpp"
#include "tictactoe.hpp"

void TicTacToe::Play(const HANDLE &ConsoleHandle)
{
    TicTacToe::Game GameObject(ConsoleHandle);

    while (true)
    {
        if (GameObject.Setup_Game()) // if true, quit to main menu
            return;

        while (!GameObject.Game_Over())
        {
            GameObject.Toggle_Current_Player();

            if (GameObject.Next_Turn_Is_User())
            {
                if (GameObject.Execute_Next_User_Command()) // if true, quit to main menu
                    return;
            }
            else
                GameObject.Execute_Next_AI_Command();
        }

        if (GameObject.Display_Game_Over_Message()) // if true, quit to main menu
            return;
    }
}

TicTacToe::Game::Game(const HANDLE &ConsoleHandle) : m_ConsoleHandle(ConsoleHandle) {}

TicTacToe::Game::~Game() {}

bool TicTacToe::Game::Setup_Game(void)
{
    m_MovesRemaining.clear();
    m_AIDifficulty = "N/A";
    m_NumberOfTurns = 0;
    m_NumberOfPlayers = -1;
    m_UserPlayerChoice = -1;
    m_WinningConditionsMet = false;
    std::srand(std::time(0));

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

    std::rand() % 2 == 0 ? m_CurrentPlayer = 'X' : m_CurrentPlayer = 'O';

    return false;
}

bool TicTacToe::Game::Get_Number_Of_Players()
{
    std::string CommonString = Get_Game_Display() + New_Line(" Please select the number of human players:          ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > 0                                                 " + WHITE);
    CaseZero += New_Line("   1                                                 ");
    CaseZero += New_Line("   2                                                 ");
    CaseZero += Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   0                                                 ");
    CaseOne += New_Line(BLUE + " > 1                                                 " + WHITE);
    CaseOne += New_Line("   2                                                 ");
    CaseOne += Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += New_Line("   0                                                 ");
    CaseTwo += New_Line("   1                                                 ");
    CaseTwo += New_Line(BLUE + " > 2                                                 " + WHITE);
    CaseTwo += Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);
        else if (CurrentSelection == 2)
            Output_To_Terminal(CaseTwo);

        KeyPress = _getch();

        if (KeyPress == '\r')
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

bool TicTacToe::Game::Get_User_Player_Choice()
{
    std::string CommonString = Get_Game_Display() + New_Line(" Please select what player you would like to be:     ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > PLAYER X                                          " + WHITE);
    CaseZero += New_Line("   PLAYER O                                          ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   PLAYER X                                          ");
    CaseOne += New_Line(BLUE + " > PLAYER O                                          " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r')
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

bool TicTacToe::Game::Get_AI_Difficulty()
{
    std::string CommonString = Get_Game_Display() + New_Line(" Please select the AI difficulty:                    ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > EASY                                              " + WHITE);
    CaseZero += New_Line("   HARD (Coming Soon!)                               ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   EASY                                              ");
    CaseOne += New_Line(BLUE + " > HARD (Coming Soon!)                               " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
        {
            CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
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

bool TicTacToe::Game::Game_Over()
{
    return Winning_Conditions_Met() || No_Moves_Available() ? true : false;
}

bool TicTacToe::Game::Winning_Conditions_Met()
{
    // Check Horizontals
    if (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[0][1] && m_GameGrid[0][1] == m_GameGrid[0][2])
        m_WinningConditionsMet = true;

    else if (m_GameGrid[1][0] != ' ' && m_GameGrid[1][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[1][2])
        m_WinningConditionsMet = true;

    else if (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[2][1] && m_GameGrid[2][1] == m_GameGrid[2][2])
        m_WinningConditionsMet = true;

    // Check verticals
    else if (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][0] && m_GameGrid[1][0] == m_GameGrid[2][0])
        m_WinningConditionsMet = true;

    else if (m_GameGrid[0][1] != ' ' && m_GameGrid[0][1] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][1])
        m_WinningConditionsMet = true;

    else if (m_GameGrid[0][2] != ' ' && m_GameGrid[0][2] == m_GameGrid[1][2] && m_GameGrid[1][2] == m_GameGrid[2][2])
        m_WinningConditionsMet = true;

    // Check diagonals
    else if (m_GameGrid[0][0] != ' ' && m_GameGrid[0][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[2][2])
        m_WinningConditionsMet = true;

    else if (m_GameGrid[2][0] != ' ' && m_GameGrid[2][0] == m_GameGrid[1][1] && m_GameGrid[1][1] == m_GameGrid[0][2])
        m_WinningConditionsMet = true;

    return m_WinningConditionsMet;
}

bool TicTacToe::Game::No_Moves_Available()
{
    return m_NumberOfTurns == 9 ? true : false;
}

void TicTacToe::Game::Toggle_Current_Player(void)
{
    m_CurrentPlayer == 'X' ? m_CurrentPlayer = 'O' : m_CurrentPlayer = 'X';
}

bool TicTacToe::Game::Next_Turn_Is_User(void)
{
    return (m_NumberOfPlayers == 2 || m_CurrentPlayer == m_UserPlayerChoice) ? true : false;
}

bool TicTacToe::Game::Execute_Next_User_Command(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line(std::string(" Player ") + m_CurrentPlayer + ", please enter your next command!           ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    Set_Cursor_Visibility(m_ConsoleHandle, true);

    int KeyPress = 0, Row = m_MovesRemaining[0] / 3, Column = m_MovesRemaining[0] % 3;
    while (true)
    {
        while (true)
        {
            COORD CursorPosition;
            CursorPosition.X = 3 + Column * 4;
            CursorPosition.Y = 4 + Row * 2;
            SetConsoleCursorPosition(m_ConsoleHandle, CursorPosition);

            KeyPress = _getch();

            if (KeyPress == '\r')
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
        else
            KeyPress = 0;
    }
}

void TicTacToe::Game::Execute_Next_AI_Command(void)
{
    int AICommand = m_MovesRemaining[std::rand() % m_MovesRemaining.size()];
    m_MovesRemaining.erase(std::find(m_MovesRemaining.begin(), m_MovesRemaining.end(), AICommand));
    m_GameGrid[AICommand / 3][AICommand % 3] = m_CurrentPlayer;
    m_NumberOfTurns++;
}

bool TicTacToe::Game::Display_Game_Over_Message(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line("                      GAME OVER                      ") + Empty_Line();

    if (m_WinningConditionsMet)
        Output += New_Line(std::string("     Player ") + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.      ");
    else
        Output += New_Line("       It is a draw! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.        ");

    Output += Empty_Line() + New_Line(" Press 'Q' to quit OR any other key to play again... ") + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    return _getch() == 'q' ? true : false;
}

std::string TicTacToe::Game::Get_Game_Display(void)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line() + New_Line(RED + "                     Tic Tac Toe                     " + WHITE) + Bottom_Line();

    // Centre information
    Output += Top_Line();

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

    Output += Empty_Line();

    return Output;
}

std::string TicTacToe::Game::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string TicTacToe::Game::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 53, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string TicTacToe::Game::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 53, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string TicTacToe::Game::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 53, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string TicTacToe::Game::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                q = quit to main menu                " + WHITE) + Bottom_Line();
}

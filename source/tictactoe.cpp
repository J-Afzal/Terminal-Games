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

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include "terminal.hpp"
#include "tictactoe.hpp"

void TicTacToe::Play(const HANDLE &ConsoleHandle,
                     CONSOLE_CURSOR_INFO &CursorInfo)
{
    bool GameIsRunning = true, QuitToMainMenu = false;
    while (GameIsRunning)
    {
        std::vector<std::vector<char>> GameGrid;
        std::vector<int> MovesRemaining;
        char CurrentPlayer = 0, UserPlayerChoice = 0;
        int NumberOfTurns = 0, NumberOfPlayers = 0;
        std::string AIDifficulty = "N/A";

        Setup_Game(GameGrid, MovesRemaining, CurrentPlayer, UserPlayerChoice, NumberOfPlayers, AIDifficulty, QuitToMainMenu);

        if (QuitToMainMenu)
            break;

        while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(GameGrid))
        {
            CurrentPlayer == 'X' ? CurrentPlayer = 'O' : CurrentPlayer = 'X';

            if (NumberOfPlayers == 2 || CurrentPlayer == UserPlayerChoice)
                Get_Next_User_Command(GameGrid, MovesRemaining, CurrentPlayer, NumberOfPlayers, AIDifficulty, ConsoleHandle, CursorInfo, QuitToMainMenu);
            else
                Get_Next_AI_Command(GameGrid, MovesRemaining, CurrentPlayer);

            if (QuitToMainMenu)
                break;

            NumberOfTurns++;
        }

        if (QuitToMainMenu)
            break;

        Display_Game_Over_Message(GameGrid, CurrentPlayer, NumberOfPlayers, NumberOfTurns, AIDifficulty, GameIsRunning);
    }
}

void TicTacToe::Setup_Game(std::vector<std::vector<char>> &GameGrid,
                           std::vector<int> &MovesRemaining,
                           char &CurrentPlayer,
                           char &UserPlayerChoice,
                           int &NumberOfPlayers,
                           std::string &AIDifficulty,
                           bool &QuitToMainMenu)
{
    std::srand(std::time(0));

    for (int i = 0, GridNumber = 0; i < 3; i++)
    {
        std::vector<char> Rows;
        GameGrid.push_back(Rows);

        for (int j = 0; j < 3; j++, GridNumber++)
        {
            GameGrid[i].push_back(' ');
            MovesRemaining.push_back(GridNumber); // 0-8
        }
    }

    NumberOfPlayers = Get_Number_Of_Players(GameGrid, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    // If only one human user, then ask them which player they want to be (X or O)
    if (NumberOfPlayers == 1)
        UserPlayerChoice = Get_User_Player_Choice(GameGrid, NumberOfPlayers, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    // If AI involved get AI difficulty
    if (NumberOfPlayers < 2)
        AIDifficulty = Get_AI_Difficulty(GameGrid, NumberOfPlayers, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    if (std::rand() % 2 == 0)
        CurrentPlayer = 'X';
    else
        CurrentPlayer = 'O';
}

int TicTacToe::Get_Number_Of_Players(const std::vector<std::vector<char>> &GameGrid,
                                     bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(GameGrid, "N/A", "N/A");
    CommonString += New_Line(" Please select the number of human players:          ");

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
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return -1;
        }
    }

    return CurrentSelection;
}

char TicTacToe::Get_User_Player_Choice(const std::vector<std::vector<char>> &GameGrid,
                                       const int &NumberOfPlayers,
                                       bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(GameGrid, std::to_string(NumberOfPlayers), "N/A");
    CommonString += New_Line(" Please select what player you would like to be:     ");

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
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return -1;
        }
    }

    return CurrentSelection == 0 ? 'X' : 'O';
}

std::string TicTacToe::Get_AI_Difficulty(const std::vector<std::vector<char>> &GameGrid,
                                         const int &NumberOfPlayers,
                                         bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(GameGrid, std::to_string(NumberOfPlayers), "N/A");
    CommonString += New_Line(" Please select the AI difficulty:                    ");

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
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return "-1";
        }
    }

    return CurrentSelection == 0 ? "EASY" : "HARD";
}

std::string TicTacToe::Get_Game_Display(const std::vector<std::vector<char>> &GameGrid,
                                        const std::string &NumberOfPlayers,
                                        const std::string &AIDifficulty)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line() + New_Line(RED + "                     Tic Tac Toe                     " + WHITE) + Bottom_Line();

    // Centre information
    Output += Top_Line();

    // Line 1
    Output += New_Line(std::string("  ") + GameGrid[0][0] + " " + char(179) + " " + GameGrid[0][1] + " " + char(179) + " " + GameGrid[0][2] + "                                          ");

    // Line 2
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (NumberOfPlayers == "N/A")
        Output += "     # of Players = " + NumberOfPlayers + "                  " + (char)186 + "\n";
    else
        Output += "      # of Players = " + NumberOfPlayers + "                   " + (char)186 + "\n";

    // Line 3
    Output += New_Line(std::string("  ") + GameGrid[1][0] + " " + char(179) + " " + GameGrid[1][1] + " " + char(179) + " " + GameGrid[1][2] + "                                          ");

    // Line 4
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (AIDifficulty == "N/A")
        Output += "     AI Difficulty = " + AIDifficulty + "                 " + (char)186 + "\n";
    else
        Output += "    AI Difficulty = " + AIDifficulty + "                 " + (char)186 + "\n";

    // Line 5
    Output += New_Line(std::string("  ") + GameGrid[2][0] + " " + char(179) + " " + GameGrid[2][1] + " " + char(179) + " " + GameGrid[2][2] + "                                          ");

    Output += Empty_Line();

    return Output;
}

std::string TicTacToe::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string TicTacToe::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 53, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string TicTacToe::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 53, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string TicTacToe::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 53, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string TicTacToe::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                q = quit to main menu                " + WHITE) + Bottom_Line();
}

void TicTacToe::Get_Next_User_Command(std::vector<std::vector<char>> &GameGrid,
                                      std::vector<int> &MovesRemaining,
                                      const char &CurrentPlayer,
                                      const int &NumberOfPlayers,
                                      const std::string &AIDifficulty,
                                      const HANDLE &ConsoleHandle,
                                      CONSOLE_CURSOR_INFO &CursorInfo,
                                      bool &QuitToMainMenu)
{
    std::string Output = Get_Game_Display(GameGrid, std::to_string(NumberOfPlayers), AIDifficulty);
    Output += New_Line(std::string(" Player ") + CurrentPlayer + ", please enter your next command!           ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    CursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

    int KeyPress = 0, Row = MovesRemaining[0] / 3, Column = MovesRemaining[0] % 3;
    while (true)
    {
        while (true)
        {
            COORD CursorPosition;
            CursorPosition.X = 3 + Column * 4;
            CursorPosition.Y = 4 + Row * 2;
            SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

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
                QuitToMainMenu = true;
                CursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
                return;
            }
        }

        auto CommandPosition = std::find(MovesRemaining.begin(), MovesRemaining.end(), Row * 3 + Column);

        if (CommandPosition != MovesRemaining.end())
        {
            GameGrid[Row][Column] = CurrentPlayer;
            MovesRemaining.erase(CommandPosition);
            break;
        }
        else
            KeyPress = 0;
    }

    CursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}

void TicTacToe::Get_Next_AI_Command(std::vector<std::vector<char>> &GameGrid,
                                    std::vector<int> &MovesRemaining,
                                    const char &CurrentPlayer)
{
    int AICommand = MovesRemaining[std::rand() % MovesRemaining.size()];
    MovesRemaining.erase(std::find(MovesRemaining.begin(), MovesRemaining.end(), AICommand));
    GameGrid[AICommand / 3][AICommand % 3] = CurrentPlayer;
}

bool TicTacToe::Game_Over(const int &NumberOfTurns)
{
    return NumberOfTurns == 9 ? true : false;
}

bool TicTacToe::Winning_Conditions_Met(const std::vector<std::vector<char>> &GameGrid)
{
    // Check Horizontals
    if (GameGrid[0][0] != ' ' && GameGrid[0][0] == GameGrid[0][1] && GameGrid[0][1] == GameGrid[0][2])
        return true;

    else if (GameGrid[1][0] != ' ' && GameGrid[1][0] == GameGrid[1][1] && GameGrid[1][1] == GameGrid[1][2])
        return true;

    else if (GameGrid[2][0] != ' ' && GameGrid[2][0] == GameGrid[2][1] && GameGrid[2][1] == GameGrid[2][2])
        return true;

    // Check verticals
    else if (GameGrid[0][0] != ' ' && GameGrid[0][0] == GameGrid[1][0] && GameGrid[1][0] == GameGrid[2][0])
        return true;

    else if (GameGrid[0][1] != ' ' && GameGrid[0][1] == GameGrid[1][1] && GameGrid[1][1] == GameGrid[2][1])
        return true;

    else if (GameGrid[0][2] != ' ' && GameGrid[0][2] == GameGrid[1][2] && GameGrid[1][2] == GameGrid[2][2])
        return true;

    // Check diagonals
    else if (GameGrid[0][0] != ' ' && GameGrid[0][0] == GameGrid[1][1] && GameGrid[1][1] == GameGrid[2][2])
        return true;

    else if (GameGrid[2][0] != ' ' && GameGrid[2][0] == GameGrid[1][1] && GameGrid[1][1] == GameGrid[0][2])
        return true;

    else
        return false;
}

void TicTacToe::Display_Game_Over_Message(const std::vector<std::vector<char>> &GameGrid,
                                          const char &CurrentPlayer,
                                          const int &NumberOfPlayers,
                                          const int &NumberOfTurns,
                                          const std::string &AIDifficulty,
                                          bool &GameIsRunning)
{
    std::string Output = Get_Game_Display(GameGrid, std::to_string(NumberOfPlayers), AIDifficulty);
    Output += New_Line("                      GAME OVER                      ") + Empty_Line();

    if (Winning_Conditions_Met(GameGrid))
        Output += New_Line(std::string("     Player ") + CurrentPlayer + " has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.      ");
    else
        Output += New_Line("       It is a draw! The game lasted " + std::to_string(NumberOfTurns) + " turns.        ");

    Output += Empty_Line() + New_Line(" Press 'Q' to quit OR any other key to play again... ") + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    if (_getch() == 'q')
        GameIsRunning = false;
}

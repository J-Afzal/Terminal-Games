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
#include "functions.hpp"
#include "tictactoe.hpp"

void Play_Tic_Tac_Toe(const HANDLE &ConsoleHandle,
                      CONSOLE_CURSOR_INFO &CursorInfo)
{
    bool GameIsRunning = true;

    while (GameIsRunning)
    {
        unsigned int NumberOfTurns = 0, NumberOfPlayers = 0;
        std::string CurrentPlayer, UserPlayerChoice, AIDifficulty = "N/A";
        std::vector<unsigned int> ValidMovesRemaining;
        std::vector<std::vector<std::string>> TicTacToeGrid;

        Setup_Game(TicTacToeGrid, ValidMovesRemaining, NumberOfPlayers, UserPlayerChoice, AIDifficulty, CurrentPlayer);

        while (!Game_Over(NumberOfTurns) && !Winning_Conditions_Met(TicTacToeGrid))
        {
            Toggle_Player(CurrentPlayer);

            // Display_Game() called before either user or AI are asked for an input
            if (NumberOfPlayers == 2 || CurrentPlayer == UserPlayerChoice)
            {
                CursorInfo.bVisible = TRUE;
                SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
                Get_Next_User_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining, ConsoleHandle);
                CursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
            }

            else
                Get_Next_AI_Command(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, ValidMovesRemaining);

            NumberOfTurns++;
        }

        Display_Game_Over_Message(TicTacToeGrid, NumberOfPlayers, AIDifficulty, CurrentPlayer, NumberOfTurns, GameIsRunning);
    }
}

void Setup_Game(std::vector<std::vector<std::string>> &TicTacToeGrid,
                std::vector<unsigned int> &ValidMovesRemaining,
                unsigned int &NumberOfPlayers,
                std::string &UserPlayerChoice,
                std::string &AIDifficulty,
                std::string &CurrentPlayer)
{
    for (unsigned int i = 0, GridNumber = 0; i < 3; i++)
    {
        std::vector<std::string> Rows;
        TicTacToeGrid.push_back(Rows);

        for (unsigned int j = 0; j < 3; j++, GridNumber++)
        {
            TicTacToeGrid[i].push_back(" ");
            ValidMovesRemaining.push_back(GridNumber); // 0-8
        }
    }

    NumberOfPlayers = Get_Number_Of_Players(TicTacToeGrid);

    // If only one human user, then ask them which player they want to be (X or O)
    if (NumberOfPlayers == 1)
        UserPlayerChoice = Get_User_Player_Choice(TicTacToeGrid, NumberOfPlayers);

    // If AI involved get AI difficulty
    if (NumberOfPlayers < 2)
        AIDifficulty = Get_AI_Difficulty(TicTacToeGrid, NumberOfPlayers);

    std::srand((unsigned int)std::time(0));
    if (std::rand() % 2 == 0)
        CurrentPlayer = "PLAYER ONE"; // X
    else
        CurrentPlayer = "PLAYER TWO"; // O
}

unsigned int Get_Number_Of_Players(const std::vector<std::vector<std::string>> &TicTacToeGrid)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = TicTacToe_Game_Display(TicTacToeGrid, "N/A", "N/A");
    CommonString += TicTacToe_New_Line(" Please select the number of human players:          ");

    std::string CaseZero = CommonString;
    CaseZero += TicTacToe_New_Line(BLUE + " > 0                                                 " + WHITE);
    CaseZero += TicTacToe_New_Line("   1                                                 ");
    CaseZero += TicTacToe_New_Line("   2                                                 ");
    CaseZero += TicTacToe_Empty_Line();
    CaseZero += TicTacToe_Bottom_Line();
    CaseZero += TicTacToe_Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += TicTacToe_New_Line("   0                                                 ");
    CaseOne += TicTacToe_New_Line(BLUE + " > 1                                                 " + WHITE);
    CaseOne += TicTacToe_New_Line("   2                                                 ");
    CaseOne += TicTacToe_Empty_Line();
    CaseOne += TicTacToe_Bottom_Line();
    CaseOne += TicTacToe_Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += TicTacToe_New_Line("   0                                                 ");
    CaseTwo += TicTacToe_New_Line("   1                                                 ");
    CaseTwo += TicTacToe_New_Line(BLUE + " > 2                                                 " + WHITE);
    CaseTwo += TicTacToe_Empty_Line();
    CaseTwo += TicTacToe_Bottom_Line();
    CaseTwo += TicTacToe_Bottom_Bar();

    while (KeyPress != '\r')
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 2;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 2)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseOne;
            break;

        case 2:
            std::cout << CaseTwo;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection;
}

std::string Get_User_Player_Choice(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                                   const unsigned int &NumberOfPlayers)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = TicTacToe_Game_Display(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");
    CommonString += TicTacToe_New_Line(" Please select what player you would like to be:     ");

    std::string CaseZero = CommonString;
    CaseZero += TicTacToe_New_Line(BLUE + " > PLAYER X                                          " + WHITE);
    CaseZero += TicTacToe_New_Line("   PLAYER O                                          ");
    CaseZero += TicTacToe_Empty_Line();
    CaseZero += TicTacToe_Empty_Line();
    CaseZero += TicTacToe_Bottom_Line();
    CaseZero += TicTacToe_Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += TicTacToe_New_Line("   PLAYER X                                          ");
    CaseOne += TicTacToe_New_Line(BLUE + " > PLAYER O                                          " + WHITE);
    CaseOne += TicTacToe_Empty_Line();
    CaseOne += TicTacToe_Empty_Line();
    CaseOne += TicTacToe_Bottom_Line();
    CaseOne += TicTacToe_Bottom_Bar();

    while (KeyPress != '\r')
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 1;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 1)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseOne;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection == 0 ? "PLAYER ONE" : "PLAYER TWO";
}

std::string Get_AI_Difficulty(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                              const unsigned int &NumberOfPlayers)
{
    unsigned int CurrentSelection = 0;
    unsigned char KeyPress = 0;

    std::string CommonString = TicTacToe_Game_Display(TicTacToeGrid, std::to_string(NumberOfPlayers), "N/A");
    CommonString += TicTacToe_New_Line(" Please select the AI difficulty:                    ");

    std::string CaseZero = CommonString;
    CaseZero += TicTacToe_New_Line(BLUE + " > EASY                                              " + WHITE);
    CaseZero += TicTacToe_New_Line("   HARD (Coming Soon!)                               ");
    CaseZero += TicTacToe_Empty_Line();
    CaseZero += TicTacToe_Empty_Line();
    CaseZero += TicTacToe_Bottom_Line();
    CaseZero += TicTacToe_Bottom_Bar();

    std::string CaseTwo = CommonString;
    CaseTwo += TicTacToe_New_Line("   EASY                                              ");
    CaseTwo += TicTacToe_New_Line(BLUE + " > HARD (Coming Soon!)                               " + WHITE);
    CaseTwo += TicTacToe_Empty_Line();
    CaseTwo += TicTacToe_Empty_Line();
    CaseTwo += TicTacToe_Bottom_Line();
    CaseTwo += TicTacToe_Bottom_Bar();

    while (!(KeyPress == '\r' && CurrentSelection == 0))
    {
        switch (KeyPress)
        {
        case 72: // up arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 1;
            else
                CurrentSelection--;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 1)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        default:
            break;
        }

        Clear_Terminal();

        switch (CurrentSelection)
        {
        case 0:
            std::cout << CaseZero;
            break;

        case 1:
            std::cout << CaseTwo;
            break;
        }

        KeyPress = _getch();
    }

    return CurrentSelection == 0 ? "EASY" : "HARD";
}

std::string TicTacToe_Game_Display(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                                   const std::string &NumberOfPlayers,
                                   const std::string &AIDifficulty)
{
    Clear_Terminal();

    std::string Output;

    // Top bar
    Output.insert(Output.size(), WHITE);
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)187);
    Output.insert(Output.size(), TicTacToe_New_Line(RED + "                   Terminal-Games                    " + WHITE));
    Output.insert(Output.size(), TicTacToe_Bottom_Line());

    // Centre information
    Output.insert(Output.size(), TicTacToe_Top_Line());

    // Line 1
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), "  " + TicTacToeGrid[0][0] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[0][1] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[0][2] + "                                          ");
    Output.insert(Output.size(), 1, (char)186);

    // Line 2
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (NumberOfPlayers == "N/A")
        Output.insert(Output.size(), "     # of Players = " + NumberOfPlayers + "                  ");
    else
        Output.insert(Output.size(), "      # of Players = " + NumberOfPlayers + "                   ");
    Output.insert(Output.size(), 1, (char)186);

    // Line 3
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), "  " + TicTacToeGrid[1][0] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[1][1] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[1][2] + "                                          ");
    Output.insert(Output.size(), 1, (char)186);

    // Line 4
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), " ");
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    Output.insert(Output.size(), 1, (char)197);
    Output.insert(Output.size(), 3, (char)196);
    if (AIDifficulty == "N/A")
        Output.insert(Output.size(), "     AI Difficulty = " + AIDifficulty + "                 ");
    else
        Output.insert(Output.size(), "    AI Difficulty = " + AIDifficulty + "                 ");
    Output.insert(Output.size(), 1, (char)186);

    // Line 5
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), "  " + TicTacToeGrid[2][0] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[2][1] + " ");
    Output.insert(Output.size(), 1, (char)179);
    Output.insert(Output.size(), " " + TicTacToeGrid[2][2] + "                                          ");
    Output.insert(Output.size(), 1, (char)186);

    Output.insert(Output.size(), TicTacToe_Empty_Line());

    return Output;
}

std::string TicTacToe_Empty_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), 53, ' ');
    Output.insert(Output.size(), 1, (char)186);

    return Output;
}

std::string TicTacToe_New_Line(const std::string &Input)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)186);
    Output.insert(Output.size(), Input);
    Output.insert(Output.size(), 1, (char)186);

    return Output;
}

std::string TicTacToe_Top_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)201);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)187);

    return Output;
}

std::string TicTacToe_Bottom_Line(void)
{
    std::string Output;
    Output.insert(Output.size(), "\n");
    Output.insert(Output.size(), 1, (char)200);
    Output.insert(Output.size(), 53, (char)205);
    Output.insert(Output.size(), 1, (char)188);

    return Output;
}

std::string TicTacToe_Bottom_Bar(void)
{
    std::string Output;
    Output += TicTacToe_Top_Line();
    Output += TicTacToe_New_Line(RED + "                     Tic Tac Toe                     " + WHITE);
    Output += TicTacToe_Bottom_Line();

    return Output;
}

void Get_Next_User_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                           const unsigned int &NumberOfPlayers,
                           const std::string &AIDifficulty,
                           const std::string &CurrentPlayer,
                           std::vector<unsigned int> &ValidMovesRemaining,
                           const HANDLE &ConsoleHandle)
{
    bool InputInvalid = true;
    unsigned int UserCommand, Row = ValidMovesRemaining[0] / 3, Column = ValidMovesRemaining[0] % 3;
    unsigned char KeyPress = 0;

    std::string Output = TicTacToe_Game_Display(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);

    if (CurrentPlayer == "PLAYER ONE")
        Output += TicTacToe_New_Line(" Player X, please enter your next command!           ");
    else
        Output += TicTacToe_New_Line(" Player O, please enter your next command!           ");

    Output += TicTacToe_Empty_Line();
    Output += TicTacToe_Empty_Line();
    Output += TicTacToe_Empty_Line();
    Output += TicTacToe_Empty_Line();
    Output += TicTacToe_Bottom_Line();
    Output += TicTacToe_Bottom_Bar();

    while (InputInvalid)
    {
        while (KeyPress != '\r')
        {
            switch (KeyPress)
            {
            case 72: // up arrow key
                if (Row == 0)
                    Row = 2;
                else
                    Row--;
                break;

            case 80: // down arrow key
                if (Row == 2)
                    Row = 0;
                else
                    Row++;
                break;

            case 75: // left arrow key
                if (Column == 0)
                    Column = 2;
                else
                    Column--;
                break;

            case 77: // right arrow key
                if (Column == 2)
                    Column = 0;
                else
                    Column++;
                break;

            default:
                break;
            }

            Clear_Terminal();

            std::cout << Output;

            COORD CursorPosition;
            CursorPosition.X = 3 + Column * 4;
            CursorPosition.Y = 4 + Row * 2;

            SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

            KeyPress = _getch();
        }

        UserCommand = Row * 3 + Column;
        auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), UserCommand);

        if (CommandPosition != ValidMovesRemaining.end())
        {
            InputInvalid = false;

            if (CurrentPlayer == "PLAYER ONE")
                TicTacToeGrid[Row][Column] = "X";
            else
                TicTacToeGrid[Row][Column] = "O";

            ValidMovesRemaining.erase(CommandPosition);
        }
        else
            KeyPress = 0;
    }
}

void Get_Next_AI_Command(std::vector<std::vector<std::string>> &TicTacToeGrid,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         const std::string &CurrentPlayer,
                         std::vector<unsigned int> &ValidMovesRemaining)
{
    unsigned int AICommand, Row, Column;

    AICommand = ValidMovesRemaining[std::rand() % ValidMovesRemaining.size()];
    auto CommandPosition = std::find(ValidMovesRemaining.begin(), ValidMovesRemaining.end(), AICommand);
    ValidMovesRemaining.erase(CommandPosition);

    Column = AICommand % 3;
    Row = AICommand / 3;

    if (CurrentPlayer == "PLAYER ONE")
        TicTacToeGrid[Row][Column] = "X";
    else
        TicTacToeGrid[Row][Column] = "O";
}

bool Game_Over(const unsigned int &NumberOfTurns)
{
    if (NumberOfTurns == 9)
        return true;
    else
        return false;
}

bool Winning_Conditions_Met(const std::vector<std::vector<std::string>> &TicTacToeGrid)
{
    // Check Horizontals
    if (TicTacToeGrid[0][0] != " " && TicTacToeGrid[0][0] == TicTacToeGrid[0][1] && TicTacToeGrid[0][1] == TicTacToeGrid[0][2])
        return true;

    else if (TicTacToeGrid[1][0] != " " && TicTacToeGrid[1][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[1][2])
        return true;

    else if (TicTacToeGrid[2][0] != " " && TicTacToeGrid[2][0] == TicTacToeGrid[2][1] && TicTacToeGrid[2][1] == TicTacToeGrid[2][2])
        return true;

    // Check verticals
    else if (TicTacToeGrid[0][0] != " " && TicTacToeGrid[0][0] == TicTacToeGrid[1][0] && TicTacToeGrid[1][0] == TicTacToeGrid[2][0])
        return true;

    else if (TicTacToeGrid[0][1] != " " && TicTacToeGrid[0][1] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[2][1])
        return true;

    else if (TicTacToeGrid[0][2] != " " && TicTacToeGrid[0][2] == TicTacToeGrid[1][2] && TicTacToeGrid[1][2] == TicTacToeGrid[2][2])
        return true;

    // Check diagonals
    else if (TicTacToeGrid[0][0] != " " && TicTacToeGrid[0][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[2][2])
        return true;

    else if (TicTacToeGrid[2][0] != " " && TicTacToeGrid[2][0] == TicTacToeGrid[1][1] && TicTacToeGrid[1][1] == TicTacToeGrid[0][2])
        return true;

    else
        return false;
}

void Display_Game_Over_Message(const std::vector<std::vector<std::string>> &TicTacToeGrid,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::string &CurrentPlayer,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning)
{
    std::string Output = TicTacToe_Game_Display(TicTacToeGrid, std::to_string(NumberOfPlayers), AIDifficulty);
    Output += TicTacToe_New_Line("                      GAME OVER                      ");
    Output += TicTacToe_Empty_Line();

    if (Winning_Conditions_Met(TicTacToeGrid))
    {
        if (CurrentPlayer == "PLAYER ONE")
            Output += TicTacToe_New_Line("     Player X has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.      ");
        else
            Output += TicTacToe_New_Line("     Player O has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.      ");
    }
    else
        Output += TicTacToe_New_Line("       It is a draw! The game lasted " + std::to_string(NumberOfTurns) + " turns.        ");

    Output += TicTacToe_Empty_Line();
    Output += TicTacToe_New_Line(" Press 'Q' to quit OR any other key to play again... ");
    Output += TicTacToe_Bottom_Line();
    Output += TicTacToe_Bottom_Bar();

    std::cout << Output;

    char temp = _getch();

    if (temp == 'q')
    {
        GameIsRunning = false;
        Clear_Terminal();
    }
}
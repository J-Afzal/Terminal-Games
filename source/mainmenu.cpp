/**
 * @file mainmenu.cpp
 * @author Junaid Afzal
 * @brief Implementation of mainmenu.hpp
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
#include <conio.h>
#include "terminal.hpp"
#include "mainmenu.hpp"
#include "tictactoe.hpp"
#include "hangman.hpp"
#include "battleships.hpp"

void MainMenu::Run()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ConsoleHandle == INVALID_HANDLE_VALUE)
        exit(1);

    CONSOLE_CURSOR_INFO CursorInfo;
    CursorInfo.dwSize = 100;
    CursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

    int KeyPress = 0, CurrentSelection = 0;
    bool ProgramIsRunning = true;
    while (true)
    {
        while (true)
        {
            Output_To_Terminal(MainMenu::Get_Main_Menu(CurrentSelection));

            KeyPress = _getch();

            if (KeyPress == '\r')
                break;
            else if (KeyPress == 72) // up arrow key
                CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
            else if (KeyPress == 80) // down arrow key
                CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
            else if (KeyPress == 'q')
            {
                ProgramIsRunning = false;
                break;
            }
        }

        if (!ProgramIsRunning)
            break;

        if (CurrentSelection == 0)
            TicTacToe::Play(ConsoleHandle, CursorInfo);
        else if (CurrentSelection == 1)
            Hangman::Play(ConsoleHandle);
        else if (CurrentSelection == 2)
            Battleships::Play(ConsoleHandle, CursorInfo);
    }

    Clear_Terminal();
}

std::string MainMenu::Get_Main_Menu(const int &CurrentSelection)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line() + New_Line(RED + "        Terminal-Games        " + WHITE) + Bottom_Line();

    // Centre game list
    if (CurrentSelection == 0)
        Output += Top_Line() + New_Line(BLUE + "       > Tic Tac Toe          " + WHITE) + Empty_Line();
    else
        Output += Top_Line() + New_Line("         Tic Tac Toe          ") + Empty_Line();

    if (CurrentSelection == 1)
        Output += New_Line(BLUE + "         > Hangman            " + WHITE) + Empty_Line();
    else
        Output += New_Line("           Hangman            ") + Empty_Line();

    if (CurrentSelection == 2)
        Output += New_Line(BLUE + "       > Battleships          " + WHITE) + Bottom_Line();
    else
        Output += New_Line("         Battleships          ") + Bottom_Line();

    // Bottom bar
    Output += Top_Line() + New_Line(RED + "           q = quit           " + WHITE) + Bottom_Line() + RESET;

    return Output;
}

std::string MainMenu::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string MainMenu::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 30, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string MainMenu::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 30, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string MainMenu::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 30, (char)205);
    Output += (char)188;
    return Output + "\n";
}

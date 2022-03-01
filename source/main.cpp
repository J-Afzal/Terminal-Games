/**
 * @file main.cpp
 * @author Junaid Afzal
 * @brief Game loop for main UI for
 * all games in Terminal-Games
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <conio.h>
#include "functions.hpp"
#include "tictactoe.hpp"
#include "hangman.hpp"
#include "battleships.hpp"

int main(void)
{
    bool ProgramIsRunning = true;
    unsigned int CurrentSelection = 2;

    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ConsoleHandle == INVALID_HANDLE_VALUE)
        exit(1);

    CONSOLE_CURSOR_INFO CursorInfo;
    CursorInfo.dwSize = 100;
    CursorInfo.bVisible = FALSE;

    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

    while (ProgramIsRunning)
    {
        std::cout << Main_Game_Display(CurrentSelection);

        switch (_getch())
        {
        case 72: // up arrow key
            if (CurrentSelection == 2)
                CurrentSelection = 0;
            else
                CurrentSelection++;
            break;

        case 80: // down arrow key
            if (CurrentSelection == 0)
                CurrentSelection = 2;
            else
                CurrentSelection--;
            break;

        case '\r': // enter key
            switch (CurrentSelection)
            {
            case 0:
                Play_Battleships(ConsoleHandle, CursorInfo);
                break;

            case 1:
                Play_Hangman(ConsoleHandle);
                break;

            case 2:
                Play_Tic_Tac_Toe(ConsoleHandle, CursorInfo);
                break;
            }
            break;

        case 'q':
            ProgramIsRunning = false;
            break;

        default:
            break;
        }
    }

    Clear_Terminal();
}
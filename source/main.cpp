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
            Clear_Terminal();

            std::cout << Main_Menu(CurrentSelection);

            KeyPress = _getch();

            if (KeyPress == '\r')
                break;
            else if (KeyPress == 72) // up arrow key
                (CurrentSelection == 0) ? CurrentSelection = 2 : --CurrentSelection;
            else if (KeyPress == 80) // down arrow key
                (CurrentSelection == 2) ? CurrentSelection = 0 : ++CurrentSelection;
            else if (KeyPress == 'q')
            {
                ProgramIsRunning = false;
                break;
            }
        }

        if (!ProgramIsRunning)
            break;

        if (CurrentSelection == 0)
            Play_Tic_Tac_Toe(ConsoleHandle, CursorInfo);
        else if (CurrentSelection == 1)
            Play_Hangman(ConsoleHandle);
        else if (CurrentSelection == 2)
            Play_Battleships(ConsoleHandle, CursorInfo);
    }

    Clear_Terminal();
}

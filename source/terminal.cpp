/**
 * @file terminal.cpp
 * @author Junaid Afzal
 * @brief Implementation of terminal.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include "terminal.hpp"

void Output_To_Terminal(const std::string &Output)
{
    Clear_Terminal();
    std::cout << Output;
}

void Clear_Terminal(void)
{
    // Windows API method from https://www.cplusplus.com/articles/4z18T05o
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        exit(1);

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &csbi))
        exit(2);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        exit(3);

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count))
        exit(4);

    // Move the cursor home
    SetConsoleCursorPosition(hStdOut, homeCoords);
}

void Set_Cursor_Visibility(const HANDLE &ConsoleHandle, const bool &Visibility)
{
    CONSOLE_CURSOR_INFO CursorInfo;
    CursorInfo.dwSize = 100;
    CursorInfo.bVisible = Visibility;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}
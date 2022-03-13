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

#include "terminal.hpp"

void Output_To_Terminal(const std::string &Output)
{
    Clear_Terminal();
    std::cout << Output;
}

void Clear_Terminal()
{
    // Windows API method from https://www.cplusplus.com/articles/4z18T05o
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hStdOut == INVALID_HANDLE_VALUE)
        exit(1);

    // Get the number of cells in the current buffer
    if (!GetConsoleScreenBufferInfo(hStdOut, &consoleScreenBufferInfo))
        exit(2);
    cellCount = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

    // Fill the entire buffer with spaces
    if (!FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count))
        exit(3);

    // Fill the entire buffer with the current colors and attributes
    if (!FillConsoleOutputAttribute(hStdOut, consoleScreenBufferInfo.wAttributes, cellCount, homeCoords, &count))
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

std::string New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string Empty_Line(const int &Width)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), Width, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Top_Line(const int &Width)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), Width, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Bottom_Line(const int &Width)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), Width, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Box(const int &Width, const std::string &Input)
{
    return Top_Line(Width) + New_Line("\x1B[1;31m" + Input + "\x1B[1;37m") + Bottom_Line(Width); // red + input + white
}

/**
 * @file Terminal.cpp
 * @author Junaid Afzal
 * @brief Implementation of Terminal.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <string>
#include <conio.h>

#include "helpers/Exceptions.hpp"
#include "helpers/Terminal.hpp"

Terminal::Terminal()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE InputBufferHandle = GetStdHandle(STD_INPUT_HANDLE);

    if (ConsoleHandle == INVALID_HANDLE_VALUE || InputBufferHandle == INVALID_HANDLE_VALUE)
        exit(1);

    m_ConsoleHandle = ConsoleHandle;
    m_BufferHandle = InputBufferHandle;
    m_CursorInfo.dwSize = 100;
    Set_Cursor_Visibility(false);
    Set_Cursor_Position(0,0);
}

Terminal::~Terminal()
{
    Terminal::Clear_Terminal();
    Set_Cursor_Visibility(true);
}

uint32_t Terminal::Get_User_Menu_Choice(const std::vector<std::string> &Menus)
{
    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::Output_To_Terminal(Menus[CurrentSelection]);

        KeyPress = Get_Key_Pressed();

        if (KeyPress == '\r')
            return CurrentSelection;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (uint32_t)(Menus.size() - 1) : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == (uint32_t)(Menus.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::Quit();
    }
}

uint32_t Terminal::Get_Key_Pressed()
{
    FlushConsoleInputBuffer(m_BufferHandle);
    return _getch();
}

void Terminal::Clear_Terminal()
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

void Terminal::Output_To_Terminal(const std::string &Output)
{
    Clear_Terminal();
    std::cout << Output;
}

void Terminal::Set_Cursor_Visibility(const bool &CursorVisibility)
{
    m_CursorInfo.bVisible = CursorVisibility;
    SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
}

void Terminal::Set_Cursor_Position(const uint32_t &X, const uint32_t &Y)
{
    m_CursorPosition.X = X;
    m_CursorPosition.Y = Y;
    SetConsoleCursorPosition(m_ConsoleHandle, m_CursorPosition);
}

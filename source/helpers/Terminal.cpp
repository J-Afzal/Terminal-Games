#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

#include "conio.h"
#include "Windows.h"

#include "helpers/Exceptions.hpp"
#include "helpers/Terminal.hpp"

uint32_t Terminal::GetUserChoiceFromMainMenus(const std::vector<std::string>& menus)
{
    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        PrintOutput(menus[CurrentSelection]);

        KeyPress = GetNextKeyPress();

        if (KeyPress == '\r')
            return CurrentSelection;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (menus.size() - 1) : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == (menus.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::QuitMainMenu();
    }
}

uint32_t Terminal::GetUserChoiceFromGameMenus(const std::vector<std::string>& menus)
{
    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        PrintOutput(menus[CurrentSelection]);

        KeyPress = GetNextKeyPress();

        if (KeyPress == '\r')
            return CurrentSelection;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (menus.size() - 1) : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == (menus.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::QuitGame();
    }
}

void Terminal::PrintOutput(const std::string& output)
{
    Clear();
    std::cout << output;
}

void Terminal::Clear()
{
    // Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
    HANDLE hStdOut;
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = { 0, 0 };

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

uint32_t Terminal::GetNextKeyPress()
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    return _getch();
}

void Terminal::SetCursorVisibility(const bool& cursorVisibility)
{
    CONSOLE_CURSOR_INFO cursorInfo(100, cursorVisibility);
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

void Terminal::SetCursorPosition(const uint32_t& x, const uint32_t& y)
{
    COORD cursorPosition(x, y);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
}

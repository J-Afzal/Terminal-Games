#include <conio.h>
#include <iostream>
#include <string>

#include "helpers/Exceptions.hpp"
#include "helpers/Terminal.hpp"

Terminal::Terminal()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE InputBufferHandle = GetStdHandle(STD_INPUT_HANDLE);

    if (ConsoleHandle == INVALID_HANDLE_VALUE || InputBufferHandle == INVALID_HANDLE_VALUE)
        exit(1);

    m_consoleHandle = ConsoleHandle;
    m_bufferHandle = InputBufferHandle;
    m_cursorInfo.dwSize = 100;
    SetCursorVisibility(false);
    SetCursorPosition(0,0);
}

Terminal::~Terminal()
{
    Clear();
    SetCursorVisibility(true);
}

uint32_t Terminal::GetUserChoiceFromMenus(const std::vector<std::string>& menus) const
{
    uint32_t KeyPress, CurrentSelection = 0;
    while (true)
    {
        PrintOutput(menus[CurrentSelection]);

        KeyPress = GetNextKeyPress();

        if (KeyPress == '\r')
            return CurrentSelection;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = (uint32_t)(menus.size() - 1) : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == (uint32_t)(menus.size() - 1) ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw Exceptions::Quit();
    }
}

uint32_t Terminal::GetNextKeyPress() const
{
    FlushConsoleInputBuffer(m_bufferHandle);
    return _getch();
}

void Terminal::Clear() const
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

void Terminal::PrintOutput(const std::string& Output) const
{
    Clear();
    std::cout << Output;
}

void Terminal::SetCursorVisibility(const bool& cursorVisibility)
{
    m_cursorInfo.bVisible = cursorVisibility;
    SetConsoleCursorInfo(m_consoleHandle, &m_cursorInfo);
}

void Terminal::SetCursorPosition(const uint32_t& x, const uint32_t& y)
{
    m_cursorPosition.X = x;
    m_cursorPosition.Y = y;
    SetConsoleCursorPosition(m_consoleHandle, m_cursorPosition);
}

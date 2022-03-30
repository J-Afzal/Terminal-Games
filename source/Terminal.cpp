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

#include "Terminal.hpp"

Terminal::Terminal(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle)
{
    Set(GameWidth, TopTitle, BottomTitle);
}

void Terminal::Set(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle)
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ConsoleHandle == INVALID_HANDLE_VALUE)
        exit(1);

    m_ConsoleHandle = ConsoleHandle;
    m_CursorInfo.dwSize = 100;
    Set_Cursor_Visibility(false);
    Set_Cursor_Position(0,0);
    m_GameWidth = GameWidth;
    m_TopTitle = TopTitle;
    m_BottomTitle = BottomTitle;
}


int Terminal::Get_Key_Pressed()
{
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

void Terminal::Set_Cursor_Position(const int &X, const int &Y)
{
    m_CursorPosition.X = X;
    m_CursorPosition.Y = Y;
    SetConsoleCursorPosition(m_ConsoleHandle, m_CursorPosition);
}

void Terminal::Quit()
{
    Terminal::Clear_Terminal();
    Set_Cursor_Visibility(true);
}

std::string Terminal::New_Line(const std::string &Input, const std::string &Colour) const
{
    std::string Output;
    Output += (char)186;
    if (Colour == "RED")
        Output += m_RED + Input + m_WHITE;
    else if (Colour == "BLUE")
        Output += m_BLUE + Input + m_WHITE;
    else
        Output += Input;
    return Output + (char)186 + "\n";
}

std::string Terminal::New_Line_Centered(const std::string &Input, const std::string &Colour) const
{
    std::string Output;
    Output.insert(Output.size(), floor((m_GameWidth-(double)Input.size())/2), ' ');

    if (Colour == "RED")
        Output += m_RED + Input + m_WHITE;
    else if (Colour == "BLUE")
        Output += m_BLUE + Input + m_WHITE;
    else
        Output += Input;

    Output.insert(Output.size(), ceil((m_GameWidth-(double)Input.size())/2), ' ');
    return New_Line(Output);
}

std::string Terminal::Empty_Line() const
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), m_GameWidth, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Terminal::Top_Line() const
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), m_GameWidth, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Terminal::Bottom_Line() const
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), m_GameWidth, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Terminal::Top_Box() const
{
    return m_WHITE + Top_Line() + New_Line_Centered(m_TopTitle, "RED") + Bottom_Line(); // red + input + white
}

std::string Terminal::Bottom_Box() const
{
    return Top_Line() + New_Line_Centered(m_BottomTitle, "RED") + Bottom_Line() + m_RESET; // red + input + white
}

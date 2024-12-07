/**
 * @file Terminal.hpp
 * @author Junaid Afzal
 * @brief This class handles all terminal related tasks such as getting
 * user input, outputting to the terminal, clearing the terminal, etc
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <vector>
#include <Windows.h>

class Terminal
{
public:
    Terminal();

    ~Terminal();

    /**
     * @brief Gets the user's choice of selection for a particular menu.
     * @param Menus is an array of ASCII strings that are outputted to the console. The only
     * difference between each string is the currently selected menu option.
     * @return The index of Menus that is currently selected.
     */
    uint32_t Get_User_Menu_Choice(const std::vector<std::string>& Menus) const;

    /**
     * @brief Wrapper for Windows.h FlushConsoleInputBuffer() and _getch()
     */
    uint32_t Get_Key_Pressed() const;

    /**
     * @brief Uses Windows.h to clear the contents of the terminal
     * and was taken from: https://www.cplusplus.com/articles/4z18T05o
     */
    void Clear_Terminal() const;

    /**
     * @brief Clear_Terminal() then std::cout << Output
     */
    void Output_To_Terminal(const std::string& Output) const;

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorInfo()
     */
    void Set_Cursor_Visibility(const bool& Visibility);

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorPosition()
     */
    void Set_Cursor_Position(const uint32_t& X, const uint32_t& Y);

private:
    HANDLE m_ConsoleHandle, m_BufferHandle;
    CONSOLE_CURSOR_INFO m_CursorInfo;
    COORD m_CursorPosition;
};

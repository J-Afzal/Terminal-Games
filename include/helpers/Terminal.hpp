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
    explicit Terminal();

    ~Terminal();

    /**
     * @brief Gets the user's choice of selection for a particular menu.
     * @param menus is an array of ASCII strings that are outputted to the console. The only
     * difference between each string is the currently selected menu option.
     * @return The index of menus that is currently selected.
     */
    uint32_t GetUserChoiceFromMenus(const std::vector<std::string>& menus) const;

    /**
     * @brief Wrapper for Windows.h FlushConsoleInputBuffer() and _getch()
     */
    uint32_t GetNextKeyPress() const;

    /**
     * @brief Uses Windows.h to clear the contents of the terminal
     * and was taken from: https://www.cplusplus.com/articles/4z18T05o
     */
    void ClearTerminal() const;

    /**
     * @brief ClearTerminal() then std::cout << Output
     */
    void OutputToTerminal(const std::string& output) const;

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorInfo()
     */
    void SetCursorVisibility(const bool& visibility);

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorPosition()
     */
    void SetCursorPosition(const uint32_t& x, const uint32_t& y);

private:
    COORD m_cursorPosition;
    CONSOLE_CURSOR_INFO m_cursorInfo;
    HANDLE m_consoleHandle, m_bufferHandle;
};

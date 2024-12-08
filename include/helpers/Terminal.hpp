#pragma once

#include <vector>
#include <Windows.h>

/**
 * @brief Handles all terminal related tasks such as getting user input,
 * outputting to the terminal, clearing the terminal, etc
 */
class Terminal
{
public:
    /**
     * @brief Construct a new Terminal object.
     */
    explicit Terminal();

    /**
     * @brief Destroy the Terminal object.
     */
    ~Terminal();

    /**
     * @brief Get the User Choice From Menus object
     *
     * @param menus An array of strings used to print to the terminal. The string chosen
     * depends on user input. The only difference between each string is the selected menu
     * option.
     * @return uint32_t The index of the menu string that the user selected.
     */
    uint32_t GetUserChoiceFromMenus(const std::vector<std::string>& menus) const;

    /**
     * @brief Wrapper for Windows.h FlushConsoleInputBuffer() and _getch()
     *
     * @return uint32_t The key which was pressed represented as an integer.
     */
    uint32_t GetNextKeyPress() const;

    /**
     * @brief Clears the terminal.
     * @see https://www.cplusplus.com/articles/4z18T05o
     */
    void Clear() const;

    /**
     * @brief Clears and then prints to the terminal.
     *
     * @param output The string to output to the terminal.
     */
    void PrintOutput(const std::string& output) const;

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorInfo()
     *
     * @param visibility Whether the cursor should be visible.
     */
    void SetCursorVisibility(const bool& visibility);

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorPosition()
     *
     * @param x The horizontal position to set the cursor to.
     * @param y The vertical position to set the cursor to.
     */
    void SetCursorPosition(const uint32_t& x, const uint32_t& y);

private:
    COORD m_cursorPosition;
    CONSOLE_CURSOR_INFO m_cursorInfo;
    HANDLE m_consoleHandle, m_bufferHandle;
};

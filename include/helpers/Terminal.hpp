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
#include "pch.hpp"

class Terminal
{
public:
    Terminal();

    ~Terminal() = default;

    /**
     * @brief Gets the user's choice of selection for a particular menu
     * @param Menus is an array of ASCII strings that represent
     * different selections being made in the same menu
     * @return The index of Menus that is currently selected
     */
    static int Get_User_Menu_Choice(const std::vector<std::string> &Menus);

    /**
     * @brief A Windows specific method to clear the contents of
     * the terminal from: https://www.cplusplus.com/articles/4z18T05o
     */
    static void Clear_Terminal();

    /**
     * @brief Clear_Terminal() then std::cout << Output
     */
    static void Output_To_Terminal(const std::string &Output);

    /**
     * @brief Wrapper for Windows.h _getch()
     */
    static int Get_Key_Pressed();

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorInfo()
     */
    void Set_Cursor_Visibility(const bool &Visibility);

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorPosition()
     */
    void Set_Cursor_Position(const int &X, const int &Y);

    /**
     * @brief Clear_Terminal() then Set_Cursor_Visibility(true)
     */
    void Quit();

private:
    HANDLE m_ConsoleHandle{};
    CONSOLE_CURSOR_INFO m_CursorInfo{};
    COORD m_CursorPosition{};
};

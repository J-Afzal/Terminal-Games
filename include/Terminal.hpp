/**
 * @file Terminal.hpp
 * @author Junaid Afzal
 * @brief Terminal object
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
    Terminal() = default;

    Terminal(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle);

    ~Terminal() = default;

    void Set(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle);

    static int Get_Key_Pressed();

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
     * @brief Wrapper for Windows.h SetConsoleCursorInfo()
     */
    void Set_Cursor_Visibility(const bool &Visibility);

    /**
     * @brief Wrapper for Windows.h SetConsoleCursorPosition()
     */
    void Set_Cursor_Position(const int &X, const int &Y);

    void Quit();

    /**
     * @return std::string containing a new line text for a generic box
     */
    std::string New_Line(const std::string &Input, const std::string &Colour="WHITE") const;

    /**
     * @return std::string containing a new centered line text for a generic box
     */
    std::string New_Line_Centered(const std::string &Input, const std::string &Colour="WHITE") const;

    /**
     * @return std::string containing empty line of a box
     */
    std::string Empty_Line() const;

    /**
     * @return std::string containing top outline of a box
     */
    std::string Top_Line() const;

    /**
     * @return std::string containing bottom outline of a box
     */
    std::string Bottom_Line() const;

    /**
     * @return std::string containing the top box
     */
    std::string Top_Box() const;

    /**
     * @return std::string containing the bottom box
     */
    std::string Bottom_Box() const;


private:
    HANDLE m_ConsoleHandle{};
    CONSOLE_CURSOR_INFO m_CursorInfo{};
    COORD m_CursorPosition{};
    int m_GameWidth{};
    std::string m_TopTitle, m_BottomTitle;
    const std::string m_WHITE = "\x1B[1;37m", m_RED = "\x1B[1;31m", m_BLUE = "\x1B[1;34m", m_RESET = "\x1B[0m"; // ANSI escape codes for bold text colours
};

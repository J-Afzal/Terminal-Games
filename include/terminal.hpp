/**
 * @file terminal.hpp
 * @author Junaid Afzal
 * @brief Terminal functions and constants
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <string>
#include <Windows.h>

/**
 * @brief ANSI escape codes for bold text colours
 *
 */
const std::string WHITE = "\x1B[1;37m";
const std::string RED = "\x1B[1;31m";
const std::string BLUE = "\x1B[1;34m";
const std::string RESET = "\x1B[0m";

/**
 * @brief Clear_Terminal() then std::cout << Output
 *
 * @param Output
 */
void Output_To_Terminal(const std::string &Output);

/**
 * @brief A Windows specific method to clear the contents of
 * the terminal from: https://www.cplusplus.com/articles/4z18T05o
 *
 */
void Clear_Terminal();

/**
 * @brief A custom wrapper around the Windows.h SetConsoleCursorInfo() function
 *
 * @param ConsoleHandle
 * @param Visibility
 */
void Set_Cursor_Visibility(const HANDLE &ConsoleHandle, const bool &Visibility);

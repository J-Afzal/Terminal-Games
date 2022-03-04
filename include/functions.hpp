/**
 * @file functions.hpp
 * @author Junaid Afzal
 * @brief Shared functions/constants
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <vector>
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
 * @brief A Windows specific method to clear the contents of
 * the terminal from: https://www.cplusplus.com/articles/4z18T05o
 *
 */
void Clear_Terminal(void);

/**
 * @brief A list of the 1,000 most used word in English from:
 * https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> Return_Word_List(void);

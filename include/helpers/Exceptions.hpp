/**
 * @file Quit.hpp
 * @author Junaid Afzal
 * @brief A custom exception that allows for returning to
 * the main menu when many functions deep in a call stack
 * @version 1.0
 * @date 29-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

namespace Exceptions
{
    class Quit : public std::exception {};

    class HangmanWordsFileNotFound : public std::exception {};
}

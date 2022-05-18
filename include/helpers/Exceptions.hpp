/**
 * @file Quit.hpp
 * @author Junaid Afzal
 * @brief Custom exceptions
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

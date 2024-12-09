#pragma once

#include <thread>

namespace Exceptions
{
    /**
     * @brief Used to quit the program.
     */
    class QuitProgram : public std::exception {};

    /**
     * @brief Used to quit a game.
     */
    class QuitGame : public std::exception {};

    /**
     * @brief Used when the words.txt file for the hangman game is not found.
     */
    class HangmanWordsNotFound : public std::exception {};

}

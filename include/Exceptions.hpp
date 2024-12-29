#pragma once

#include <exception>

namespace TerminalGames::Exceptions
{
    /**
     * @brief Used to quit the main menu.
     */
    class QuitMainMenu : public std::exception {};

    /**
     * @brief Used to quit a game.
     */
    class QuitGame : public std::exception {};

    /**
     * @brief Used for functionality that has not been implemented.
     */
    class NotImplementedError : public std::exception {};

    /**
     * @brief Used when the hangman game words.txt file is not found.
     */
    class HangmanWordsNotFound : public std::exception {};

    /**
     * @brief Used when the backspace key is pressed.
     */
    class BackspaceKeyPressed : public std::exception {};

}

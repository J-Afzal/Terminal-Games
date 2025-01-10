#pragma once

#include <exception>

namespace TerminalGames::Exceptions
{
    /**
     * @brief Used to quit the program.
     */
    class QuitProgram : public std::exception
    {};

    /**
     * @brief Used to quit the main menu.
     */
    class QuitMainMenu : public std::exception
    {};

    /**
     * @brief Used to quit a game.
     */
    class QuitGame : public std::exception
    {};

    /**
     * @brief Used to restart a game with the same user options.
     */
    class RestartGame : public std::exception
    {};

    /**
     * @brief Used to reset a game which prompts the user for new options.
     */
    class ResetGame : public std::exception
    {};

    /**
     * @brief Used for functionality that has not been implemented.
     */
    class NotImplementedError : public std::exception
    {};

    /**
     * @brief Used when the hangman game words.txt file is not found.
     */
    class HangmanWordsNotFound : public std::exception
    {};

    /**
     * @brief Used when the backspace key is pressed.
     */
    class BackspaceKeyPressed : public std::exception
    {};

}

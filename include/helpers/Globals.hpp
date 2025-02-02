#pragma once

#include <array>
#include <cstdint>
#include <exception>
#include <sstream>
#include <string>
#include <vector>

/**
 * @namespace TerminalGames::Globals
 * @brief Contains all global and constant objects.
 */
namespace TerminalGames::Globals
{
    /**
     * @namespace TerminalGames::Globals::Exceptions
     * @brief Contains all custom exceptions.
     */
    namespace Exceptions
    {
        /**
         * @brief Used to quit the program.
         */
        class QuitProgram : public std::exception
        {
        };

        /**
         * @brief Used to quit the main menu.
         */
        class QuitMainMenu : public std::exception
        {
        };

        /**
         * @brief Used to quit a game.
         */
        class QuitGame : public std::exception
        {
        };

        /**
         * @brief Used to reset a game which prompts the user for new options.
         */
        class ResetGame : public std::exception
        {
        };

        /**
         * @brief Used to restart a game with the same user options.
         */
        class RestartGame : public std::exception
        {
        };

        /**
         * @brief Used when the backspace key is pressed.
         */
        class BackspaceKeyPressed : public std::exception
        {
        };

        /**
         * @brief Used for functionality that has not been implemented.
         */
        class NotImplementedError : public std::exception
        {
        };
    }

    /**
     * @brief Implements `std::ranges::find` which *should* work for all standard template library containers.
     *
     *
     * @tparam T Any standard template library container.
     * @tparam U The type being stored by the standard template library container.
     * @param p_begin The iterator returned from `begin()` function.
     * @param p_end The iterator returned from `end()` function.
     * @param p_value The value to find in the standard template library container.
     * @return `T` An iterator to the found value. If the value is not found then `p_end` is returned.
     * @warning Don't use this. Just use the built-in `std::ranges::find`. This has been crudely implemented as
     * `std::ranges::find` was not supported by the ubuntu-latest compilers in the CI workflow.
     */
    template<typename T, typename U>
    static constexpr T ImplementStdRangesFind(const T& p_begin, const T& p_end, const U& p_value)
    {
        for (T i = p_begin; i < p_end; i++)
        {
            if (*i == p_value)
            {
                return i;
            }
        }

        return p_end;
    }

    /**
     * @brief Implements `std::count` which it *should* work for all standard template library containers.
     *
     * @tparam T Any standard template library container.
     * @tparam U The type being stored by the standard template library container.
     * @param p_begin The iterator returned from `begin()` function.
     * @param p_end The iterator returned from `end()` function.
     * @param p_value The value to count in the standard template library container.
     * @return `int32_t` The number of occurrences of `p_value` in the input container.
     * @warning Don't use this. Just use the built-in `std::count`. This has been crudely implemented as `std::count` was not
     * supported by the ubuntu-latest compilers in the CI workflow.
     */
    template<typename T, typename U>
    static constexpr int32_t ImplementStdCount(const T& p_begin, const T& p_end, const U& p_value)
    {
        int32_t count = 0;

        for (T i = p_begin; i < p_end; i++)
        {
            if (*i == p_value)
            {
                ++count;
            }
        }

        return count;
    }

    /**
     * @brief Repeats `p_stringToRepeat` for a total of `p_numberOfRepetitions` number of times.
     *
     * @param p_numberOfRepetitions The number of times to repeat `p_stringToRepeat`.
     * @param p_stringToRepeat The string to repeat.
     * @return `std::string` The input `p_stringToRepeat` repeated `p_numberOfRepetitions` number of times.
     */
    static std::string RepeatString(const uint32_t& p_numberOfRepetitions, const std::string& p_stringToRepeat)
    {
        std::ostringstream buffer;
        for (uint32_t currentRepetition = 0; currentRepetition < p_numberOfRepetitions; currentRepetition++)
        {
            buffer << p_stringToRepeat;
        }
        return buffer.str();
    }

    /**
     * @brief Removes in-place all instances of a `p_subString` from `p_string` .
     *
     * @param p_string The string to be checked and edited.
     * @param p_subString The substring to be removed.
     */
    static constexpr void RemoveSubString(std::string& p_string, const std::string& p_subString)
    {
        const uint32_t SUB_STRING_LENGTH = p_subString.size();
        for (std::string::size_type currentSubStringLocation = p_string.find(p_subString); currentSubStringLocation != std::string::npos; currentSubStringLocation = p_string.find(p_subString))
        {
            p_string.erase(currentSubStringLocation, SUB_STRING_LENGTH);
        }
    }

    /**
     * @brief Used by PageBuilder to display the current platform being used and used by Terminal to decided whether to use
     * `<Windows.h>` for enhanced user input.
     */
#ifdef _WIN32
    static const inline bool G_PLATFORM_IS_WINDOWS = true;
#else
    static const inline bool G_PLATFORM_IS_WINDOWS = false;
#endif

    /**
     * @brief Extended ASCII characters for edges and corners of the page.
     */
    ///@{
    static inline const char G_PAGE_HORIZONTAL_LINE = static_cast<char>(205);
    static inline const char G_PAGE_VERTICAL_LINE = static_cast<char>(186);
    static inline const char G_PAGE_TOP_RIGHT_CORNER = static_cast<char>(187);
    static inline const char G_PAGE_BOTTOM_RIGHT_CORNER = static_cast<char>(188);
    static inline const char G_PAGE_BOTTOM_LEFT_CORNER = static_cast<char>(200);
    static inline const char G_PAGE_TOP_LEFT_CORNER = static_cast<char>(201);
    ///@}

    /**
     * @brief Extended ASCII characters for grids.
     */
    ///@{
    static inline const char G_PAGE_GRID_HORIZONTAL_LINE = static_cast<char>(196);
    static inline const char G_PAGE_GRID_VERTICAL_LINE = static_cast<char>(179);
    static inline const char G_PAGE_GRID_INTERSECTION = static_cast<char>(197);
    static inline const char G_PAGE_GRID_UPSIDE_DOWN_T = static_cast<char>(193);
    static inline const char G_PAGE_GRID_T = static_cast<char>(194);
    static inline const char G_PAGE_GRID_LEFT_SIDEWAYS_T = static_cast<char>(195);
    static inline const char G_PAGE_GRID_RIGHT_SIDEWAYS_T = static_cast<char>(180);
    static inline const char G_PAGE_GRID_TOP_LEFT = static_cast<char>(218);
    static inline const char G_PAGE_GRID_TOP_RIGHT = static_cast<char>(191);
    static inline const char G_PAGE_GRID_BOTTOM_LEFT = static_cast<char>(192);
    static inline const char G_PAGE_GRID_BOTTOM_RIGHT = static_cast<char>(217);
    ///@}

    /**
     * @brief Misc extended ASCII characters.
     */
    ///@{
    static inline const char G_PAGE_CENTRAL_DOT = static_cast<char>(250);
    static inline const char G_PAGE_LIGHT_HASH = static_cast<char>(176);
    static inline const char G_PAGE_DARK_HASH = static_cast<char>(178);
    ///@}

    /**
     * @brief Minimum padding amounts.
     */

    ///@{
    static inline const uint32_t G_PAGE_MINIMUM_LEFT_VERTICAL_LINE_SIZE = 1;
    static inline const uint32_t G_PAGE_MINIMUM_LEFT_PADDING_SIZE = 1;
    static inline const uint32_t G_PAGE_MINIMUM_RIGHT_PADDING_SIZE = 1;
    static inline const uint32_t G_PAGE_MINIMUM_RIGHT_VERTICAL_LINE_SIZE = 1;
    ///@}

    /**
     * @brief For when highlighting what is currently selected in an option menu.
     */
    ///@{
    static inline const std::string G_PAGE_OPTION_SELECTOR = ">";
    static inline const std::string G_PAGE_OPTION_SELECTOR_ABSENT_PADDING = std::string(Globals::G_PAGE_OPTION_SELECTOR.size() + 1, ' ');
    ///@}

    /**
     * @brief ANSI colour escape codes to add colour to output.
     */
    ///@{
    static inline const uint32_t G_PAGE_ANSI_COLOUR_ESCAPE_CODE_COUNT = 6;
    static inline const uint32_t G_PAGE_ANSI_COLOUR_ESCAPE_CODE_SIZE = 7;
    static inline const char G_PAGE_ANSI_COLOUR_ESCAPE_CODE_START = '\x1B';
    static inline const std::string G_PAGE_ANSI_WHITE_COLOUR_ESCAPE_CODE = "\x1B[1;37m";
    static inline const std::string G_PAGE_ANSI_RED_COLOUR_ESCAPE_CODE = "\x1B[1;31m";
    static inline const std::string G_PAGE_ANSI_BLUE_COLOUR_ESCAPE_CODE = "\x1B[1;34m";
    static inline const std::string G_PAGE_ANSI_GREEN_COLOUR_ESCAPE_CODE = "\x1B[1;32m";
    static inline const std::string G_PAGE_ANSI_YELLOW_COLOUR_ESCAPE_CODE = "\x1B[1;33m";
    static inline const std::string G_PAGE_ANSI_RESET_COLOUR_ESCAPE_CODE = "\x1B[0m";
    /**
     * @warning The order should match the order `Colours` enum.
     */
    static inline const std::array<std::string, G_PAGE_ANSI_COLOUR_ESCAPE_CODE_COUNT> G_PAGE_ANSI_ALL_COLOUR_ESCAPE_CODES = {
        G_PAGE_ANSI_WHITE_COLOUR_ESCAPE_CODE,
        G_PAGE_ANSI_RED_COLOUR_ESCAPE_CODE,
        G_PAGE_ANSI_BLUE_COLOUR_ESCAPE_CODE,
        G_PAGE_ANSI_GREEN_COLOUR_ESCAPE_CODE,
        G_PAGE_ANSI_YELLOW_COLOUR_ESCAPE_CODE,
        G_PAGE_ANSI_RESET_COLOUR_ESCAPE_CODE,
    };
    ///@}

    /**
     * @brief Colours representing ANSI escape codes.
     */
    enum class Colours : std::uint8_t
    {
        WHITE = 0,
        RED,
        BLUE,
        GREEN,
        YELLOW,
        RESET
    };

    /**
     * @brief Page attributes for the homepage.
     */
    ///@{
    static inline const std::string G_HOMEPAGE_TOP_TITLE = "Terminal Games";
    static inline const std::string G_HOMEPAGE_BOTTOM_TITLE = "q = quit program";
    static inline const uint32_t G_HOMEPAGE_DISPLAY_WIDTH = 40;
    static inline const uint32_t G_HOMEPAGE_DISPLAY_HEIGHT = 20;
    ///@}

    /**
     * @brief Page attributes for the MainMenu page.
     */
    ///@{
    static inline const std::string G_MAIN_MENU_TOP_TITLE = "Main Menu";
    static inline const std::string G_MAIN_MENU_BOTTOM_TITLE = "q = quit to homepage";
    static inline const uint32_t G_MAIN_MENU_DISPLAY_WIDTH = 32;
    static inline const uint32_t G_MAIN_MENU_DISPLAY_HEIGHT = 13;
    ///@}

    /**
     * @brief Page attributes for all TicTacToe pages.
     */
    ///@{
    static inline const std::string G_TICTACTOE_TOP_TITLE = "Tic Tac Toe";
    static inline const std::string G_TICTACTOE_BOTTOM_TITLE = "q = show quit menu";
    static inline const uint32_t G_TICTACTOE_DISPLAY_WIDTH = 57;
    static inline const uint32_t G_TICTACTOE_DISPLAY_HEIGHT = 19;
    ///@}

    /**
     * @brief Page attributes for all Hangman pages.
     */
    ///@{
    static inline const std::string G_HANGMAN_TOP_TITLE = "Hangman";
    static inline const std::string G_HANGMAN_BOTTOM_TITLE = "q = show quit menu";
    static inline const uint32_t G_HANGMAN_DISPLAY_WIDTH = 62;
    static inline const uint32_t G_HANGMAN_DISPLAY_HEIGHT = 22;
    ///@}

    /**
     * @brief Page attributes for all Battleships pages.
     */
    ///@{
    static inline const std::string G_BATTLESHIPS_TOP_TITLE = "Battleships";
    static inline const std::string G_BATTLESHIPS_BOTTOM_TITLE = "q = show quit menu";
    static inline const uint32_t G_BATTLESHIPS_DISPLAY_WIDTH = 142;
    static inline const uint32_t G_BATTLESHIPS_DISPLAY_HEIGHT = 38;
    ///@}

    /**
     * @brief Quit menu options.
     */
    ///@{
    static inline const uint32_t G_QUIT_MENU_RESTART_GAME_INDEX = 0;
    static inline const uint32_t G_QUIT_MENU_RESET_GAME_INDEX = 1;
    static inline const uint32_t G_QUIT_MENU_QUIT_GAME_INDEX = 2;
    static inline const uint32_t G_QUIT_MENU_QUIT_MAIN_MENU_INDEX = 3;
    static inline const uint32_t G_QUIT_MENU_QUIT_PROGRAM_INDEX = 4;
    static inline const uint32_t G_QUIT_MENU_CANCEL_INDEX = 5;
    static inline const std::vector<std::string> G_QUIT_MENU_OPTIONS = {
        "Restart Game",
        "Reset Game",
        "Quit to Main Menu",
        "Quit to Homepage",
        "Quit Program",
        "Cancel",
    };
    ///@}

    /**
     * @brief Keyboard values when getting user input on Windows.
     */
    ///@{
    static inline const uint32_t G_TERMINAL_ENTER_KEY = '\r';
    static inline const uint32_t G_TERMINAL_BACKSPACE_KEY = 8;
    static inline const uint32_t G_TERMINAL_UP_ARROW_KEY = 72;
    static inline const uint32_t G_TERMINAL_DOWN_ARROW_KEY = 80;
    static inline const uint32_t G_TERMINAL_LEFT_ARROW_KEY = 75;
    static inline const uint32_t G_TERMINAL_RIGHT_ARROW_KEY = 77;
    static inline const uint32_t G_TERMINAL_QUIT_KEY = 'q';
    static inline const uint32_t G_TERMINAL_RESTART_KEY = 'r';
    ///@}

    /**
     * @brief Keyboard values when getting user input other platforms.
     */
    ///@{
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_ENTER_KEY = 'e';
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_BACKSPACE_KEY = 'z';
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_UP_ARROW_KEY = 'w';
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_DOWN_ARROW_KEY = 's';
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_LEFT_ARROW_KEY = 'a';
    static inline const uint32_t G_TERMINAL_ALTERNATIVE_RIGHT_ARROW_KEY = 'd';
    ///@}

    /**
     * @brief The cursor width while running on windows.
     */
    static inline const uint32_t G_TERMINAL_CURSOR_WIDTH_PERCENTAGE = 100;

    /**
     * @brief CLI help message.
     */

    static inline const std::string G_MAIN_MENU_CLI_HELP_MESSAGE = "\nUsage: terminal-games [options]\n\nOPTIONS:\n\nGeneric Options:\n\n  --h --help        Display available options.\n\nterminal-games options:\n\n  --a --ascii-only  Only use extended ASCII characters (this removes all colour).\n\n";

    /**
     * @brief Used by multiple games or an attribute not specific to one game.
     */
    ///@{
    static inline const uint32_t G_GAME_TWO_OPTIONS = 2;
    static inline const uint32_t G_GAME_THREE_OPTIONS = 3;
    static inline const std::string G_GAME_UNKNOWN_OPTION = "N/A";
    static inline const std::string G_GAME_NUMBER_OF_PLAYERS = "# of Players = ";
    static inline const std::string G_GAME_COMPUTER_SPEED = "Computer Speed = ";
    static inline const std::vector<std::string> G_GAME_COMPUTER_SPEED_OPTIONS = {"INSTANT", "FAST", "SLOW"};
    static inline const std::vector<std::string> G_GAME_MAX_TWO_PLAYERS_OPTIONS = {"0", "1", "2"};
    static inline const std::vector<std::string> G_GAME_MAX_ONE_PLAYER_OPTIONS = {"0", "1"};
    ///@}

    /**
     * @brief TicTacToe grid attributes.
     */
    ///@{
    static inline const uint32_t G_TICTACTOE_GRID_WIDTH = 3;
    static inline const uint32_t G_TICTACTOE_GRID_HEIGHT = 3;
    static inline const uint32_t G_TICTACTOE_GRID_ELEMENT_WIDTH = 3;
    static inline const uint32_t G_TICTACTOE_GRID_ELEMENT_HEIGHT = 1;
    static inline const uint32_t G_TICTACTOE_GRID_LEFT_PAD = 3;
    static inline const uint32_t G_TICTACTOE_GRID_TOP_PAD = 4;
    ///@}

    /**
     * @brief TicTacToe grid values.
     */
    ///@{
    static inline const std::string G_TICTACTOE_GRID_ROW_VALUE_DIVIDER = std::string(G_TICTACTOE_GRID_ELEMENT_WIDTH, G_PAGE_GRID_HORIZONTAL_LINE);
    static inline const std::string G_TICTACTOE_EMPTY_GRID_VALUE = std::string(G_TICTACTOE_GRID_ELEMENT_WIDTH, ' ');
    static inline const std::string G_TICTACTOE_GRID_PLAYER_X_OCCUPIED = " X ";
    static inline const std::string G_TICTACTOE_GRID_PLAYER_O_OCCUPIED = " O ";
    ///@}

    /**
     * @brief TicTacToe maximum errors count to determine whether the game is over.
     */
    static inline const uint32_t G_TICTACTOE_MAXIMUM_ERROR_COUNT = G_TICTACTOE_GRID_WIDTH * G_TICTACTOE_GRID_HEIGHT;

    /**
     * @brief TicTacToe player choice options.
     */
    ///@{
    static inline const std::string G_TICTACTOE_PLAYER_X = "Player X";
    static inline const std::string G_TICTACTOE_PLAYER_O = "Player O";
    static inline const std::vector<std::string> G_TICTACTOE_PLAYER_CHOICE_OPTIONS = {G_TICTACTOE_PLAYER_X, G_TICTACTOE_PLAYER_O};
    ///@}

    /**
     * @brief Hangman word to be guessed constraints.
     */
    ///@{
    static inline const uint32_t G_HANGMAN_MINIMUM_WORD_SIZE = 3;
    static inline const uint32_t G_HANGMAN_MAXIMUM_WORD_SIZE = 16;
    ///@}
#
    /**
     * @brief Hangman cursor position when getting user input on Windows.
     */
    ///@{
    static inline const uint32_t G_HANGMAN_USER_INPUT_ROW = 13;
    static inline const uint32_t G_HANGMAN_GET_WORD_FROM_USER_COLUMN = 39;
    static inline const uint32_t G_HANGMAN_GET_USER_COMMAND_COLUMN = 41;
    ///@}

    /**
     * @brief Hangman value to minus from key press to get char representation.
     */
    static inline const uint32_t G_HANGMAN_KEY_PRESS_CHAR_OFFSET = 32;

    /**
     * @brief Hangman maximum errors count to determine whether the game is over.
     */
    static inline const uint32_t G_HANGMAN_MAXIMUM_ERROR_COUNT = 10;

    /**
     * @brief Hangman constants used to construct the hangman.
     */
    ///@{
    static inline const uint32_t G_HANGMAN_GALLOWS_BASE_WIDTH = 7;
    static inline const uint32_t G_HANGMAN_GALLOWS_BASE_WIDTH_HALF = 3;
    static inline const std::string G_HANGMAN_GALLOWS_BASE_INITIAL = std::string(G_HANGMAN_GALLOWS_BASE_WIDTH, G_PAGE_GRID_HORIZONTAL_LINE) + "      ";
    static inline const std::string G_HANGMAN_GALLOWS_BASE_HALF = std::string(G_HANGMAN_GALLOWS_BASE_WIDTH_HALF, G_PAGE_GRID_HORIZONTAL_LINE);
    static inline const std::string G_HANGMAN_GALLOWS_BASE = G_HANGMAN_GALLOWS_BASE_HALF + std::string(1, G_PAGE_GRID_UPSIDE_DOWN_T) + G_HANGMAN_GALLOWS_BASE_HALF + "      ";
    static inline const std::string G_HANGMAN_GALLOWS_VERTICAL_BEAM = "   " + std::string(1, Globals::G_PAGE_GRID_VERTICAL_LINE);
    static inline const std::string G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING = G_HANGMAN_GALLOWS_VERTICAL_BEAM + "         ";
    static inline const std::string G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE = Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       " + Globals::G_PAGE_GRID_VERTICAL_LINE + ' ';
    static inline const std::string G_HANGMAN_GALLOWS_TOP_BEAM_INITIAL = "   " + std::string(1, Globals::G_PAGE_GRID_TOP_LEFT) + std::string(G_HANGMAN_GALLOWS_BASE_WIDTH, G_PAGE_GRID_HORIZONTAL_LINE) + "  ";
    static inline const std::string G_HANGMAN_GALLOWS_TOP_BEAM = "   " + std::string(1, Globals::G_PAGE_GRID_TOP_LEFT) + std::string(G_HANGMAN_GALLOWS_BASE_WIDTH, G_PAGE_GRID_HORIZONTAL_LINE) + Globals::G_PAGE_GRID_TOP_RIGHT + ' ';
    static inline const char G_HANGMAN_HIDDEN_LETTER = '_';

    /**
     * @brief Hangman constants used to display the current state of the Hangman game.
     */
    ///@{
    static inline const std::vector<std::vector<std::string>> G_HANGMAN_STATES = {
        {
         "",
         "",
         "",
         "",
         "",
         "",
         "",
         },
        {
         "",
         "",
         "",
         "",
         "",
         "",
         Globals::G_HANGMAN_GALLOWS_BASE_INITIAL,
         },
        {
         "",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM_INITIAL,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       | ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       | ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      /  ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       | ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      / \\",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      /|  ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      / \\",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         },
        {
         Globals::G_HANGMAN_GALLOWS_TOP_BEAM,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_ROPE,
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "       O ",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      /|\\",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM + "      / \\",
         Globals::G_HANGMAN_GALLOWS_VERTICAL_BEAM_WITH_PADDING,
         Globals::G_HANGMAN_GALLOWS_BASE,
         }
    };

    static inline const std::string G_HANGMAN_INCORRECT_GUESSES_TITLE = "Incorrect Guesses";
    static inline const std::string G_HANGMAN_INCORRECT_GUESSES_PADDING = "   ";
    static inline const uint32_t G_HANGMAN_INCORRECT_GUESSES_FIRST_LINE_LAST_INDEX = 4;
    static inline const uint32_t G_HANGMAN_INCORRECT_GUESSES_SECOND_LINE_LAST_INDEX = 9;

    static inline const std::string G_HANGMAN_WORD_TO_BE_GUESSED_START = "(The word was ";
    static inline const std::string G_HANGMAN_WORD_TO_BE_GUESSED_END = ")";
    ///@}

    /**
     * @brief Hangman player choice options.
     */
    ///@{
    static inline const std::string G_HANGMAN_GUESSER = "GUESSER";
    static inline const std::string G_HANGMAN_WORD_SETTER = "WORD SETTER";
    static inline const std::vector<std::string> G_HANGMAN_PLAYER_CHOICE_OPTIONS = {G_HANGMAN_GUESSER, G_HANGMAN_WORD_SETTER};
    ///@}

    /**
     * @brief Hangman computer word list for when the computer is asked to chose a word to be guessed.
     */
    ///@{
    static inline const uint32_t G_HANGMAN_NUMBER_OF_COMPUTER_WORDS = 972;
    static inline const std::array<std::string, G_HANGMAN_NUMBER_OF_COMPUTER_WORDS> G_HANGMAN_COMPUTER_WORDS = {
        "ABILITY",
        "ABLE",
        "ABOUT",
        "ABOVE",
        "ACCEPT",
        "ACCORDING",
        "ACCOUNT",
        "ACROSS",
        "ACT",
        "ACTION",
        "ACTIVITY",
        "ACTUALLY",
        "ADD",
        "ADDRESS",
        "ADMINISTRATION",
        "ADMIT",
        "ADULT",
        "AFFECT",
        "AFTER",
        "AGAIN",
        "AGAINST",
        "AGE",
        "AGENCY",
        "AGENT",
        "AGO",
        "AGREE",
        "AGREEMENT",
        "AHEAD",
        "AIR",
        "ALL",
        "ALLOW",
        "ALMOST",
        "ALONE",
        "ALONG",
        "ALREADY",
        "ALSO",
        "ALTHOUGH",
        "ALWAYS",
        "AMERICAN",
        "AMONG",
        "AMOUNT",
        "ANALYSIS",
        "AND",
        "ANIMAL",
        "ANOTHER",
        "ANSWER",
        "ANY",
        "ANYONE",
        "ANYTHING",
        "APPEAR",
        "APPLY",
        "APPROACH",
        "AREA",
        "ARGUE",
        "ARM",
        "AROUND",
        "ARRIVE",
        "ART",
        "ARTICLE",
        "ARTIST",
        "ASK",
        "ASSUME",
        "ATTACK",
        "ATTENTION",
        "ATTORNEY",
        "AUDIENCE",
        "AUTHOR",
        "AUTHORITY",
        "AVAILABLE",
        "AVOID",
        "AWAY",
        "BABY",
        "BACK",
        "BAD",
        "BAG",
        "BALL",
        "BANK",
        "BAR",
        "BASE",
        "BEAT",
        "BEAUTIFUL",
        "BECAUSE",
        "BECOME",
        "BED",
        "BEFORE",
        "BEGIN",
        "BEHAVIOUR",
        "BEHIND",
        "BELIEVE",
        "BENEFIT",
        "BEST",
        "BETTER",
        "BETWEEN",
        "BEYOND",
        "BIG",
        "BILL",
        "BILLION",
        "BIT",
        "BLACK",
        "BLOOD",
        "BLUE",
        "BOARD",
        "BODY",
        "BOOK",
        "BORN",
        "BOTH",
        "BOX",
        "BOY",
        "BREAK",
        "BRING",
        "BROTHER",
        "BUDGET",
        "BUILD",
        "BUILDING",
        "BUSINESS",
        "BUT",
        "BUY",
        "CALL",
        "CAMERA",
        "CAMPAIGN",
        "CAN",
        "CANCER",
        "CANDIDATE",
        "CAPITAL",
        "CAR",
        "CARD",
        "CARE",
        "CAREER",
        "CARRY",
        "CASE",
        "CATCH",
        "CAUSE",
        "CELL",
        "CENTER",
        "CENTRAL",
        "CENTURY",
        "CERTAIN",
        "CERTAINLY",
        "CHAIR",
        "CHALLENGE",
        "CHANCE",
        "CHANGE",
        "CHARACTER",
        "CHARGE",
        "CHECK",
        "CHILD",
        "CHOICE",
        "CHOOSE",
        "CHURCH",
        "CITIZEN",
        "CITY",
        "CIVIL",
        "CLAIM",
        "CLASS",
        "CLEAR",
        "CLEARLY",
        "CLOSE",
        "COACH",
        "COLD",
        "COLLECTION",
        "COLLEGE",
        "COLOUR",
        "COME",
        "COMMERCIAL",
        "COMMON",
        "COMMUNITY",
        "COMPANY",
        "COMPARE",
        "COMPUTER",
        "CONCERN",
        "CONDITION",
        "CONFERENCE",
        "CONGRESS",
        "CONSIDER",
        "CONSUMER",
        "CONTAIN",
        "CONTINUE",
        "CONTROL",
        "COST",
        "COULD",
        "COUNTRY",
        "COUPLE",
        "COURSE",
        "COURT",
        "COVER",
        "CREATE",
        "CRIME",
        "CULTURAL",
        "CULTURE",
        "CUP",
        "CURRENT",
        "CUSTOMER",
        "CUT",
        "DARK",
        "DATA",
        "DAUGHTER",
        "DAY",
        "DEAD",
        "DEAL",
        "DEATH",
        "DEBATE",
        "DECADE",
        "DECIDE",
        "DECISION",
        "DEEP",
        "DEFENCE",
        "DEGREE",
        "DEMOCRAT",
        "DEMOCRATIC",
        "DESCRIBE",
        "DESIGN",
        "DESPITE",
        "DETAIL",
        "DETERMINE",
        "DEVELOP",
        "DEVELOPMENT",
        "DIE",
        "DIFFERENCE",
        "DIFFERENT",
        "DIFFICULT",
        "DINNER",
        "DIRECTION",
        "DIRECTOR",
        "DISCOVER",
        "DISCUSS",
        "DISCUSSION",
        "DISEASE",
        "DOCTOR",
        "DOG",
        "DOOR",
        "DOWN",
        "DRAW",
        "DREAM",
        "DRIVE",
        "DROP",
        "DRUG",
        "DURING",
        "EACH",
        "EARLY",
        "EAST",
        "EASY",
        "EAT",
        "ECONOMIC",
        "ECONOMY",
        "EDGE",
        "EDUCATION",
        "EFFECT",
        "EFFORT",
        "EIGHT",
        "EITHER",
        "ELECTION",
        "ELSE",
        "EMPLOYEE",
        "END",
        "ENERGY",
        "ENJOY",
        "ENOUGH",
        "ENTER",
        "ENTIRE",
        "ENVIRONMENT",
        "ENVIRONMENTAL",
        "ESPECIALLY",
        "ESTABLISH",
        "EVEN",
        "EVENING",
        "EVENT",
        "EVER",
        "EVERY",
        "EVERYBODY",
        "EVERYONE",
        "EVERYTHING",
        "EVIDENCE",
        "EXACTLY",
        "EXAMPLE",
        "EXECUTIVE",
        "EXIST",
        "EXPECT",
        "EXPERIENCE",
        "EXPERT",
        "EXPLAIN",
        "EYE",
        "FACE",
        "FACT",
        "FACTOR",
        "FAIL",
        "FALL",
        "FAMILY",
        "FAR",
        "FAST",
        "FATHER",
        "FEAR",
        "FEDERAL",
        "FEEL",
        "FEELING",
        "FEW",
        "FIELD",
        "FIGHT",
        "FIGURE",
        "FILL",
        "FILM",
        "FINAL",
        "FINALLY",
        "FINANCIAL",
        "FIND",
        "FINE",
        "FINGER",
        "FINISH",
        "FIRE",
        "FIRM",
        "FIRST",
        "FISH",
        "FIVE",
        "FLOOR",
        "FLY",
        "FOCUS",
        "FOLLOW",
        "FOOD",
        "FOOT",
        "FOR",
        "FORCE",
        "FOREIGN",
        "FORGET",
        "FORM",
        "FORMER",
        "FORWARD",
        "FOUR",
        "FREE",
        "FRIEND",
        "FROM",
        "FRONT",
        "FULL",
        "FUND",
        "FUTURE",
        "GAME",
        "GARDEN",
        "GAS",
        "GENERAL",
        "GENERATION",
        "GET",
        "GIRL",
        "GIVE",
        "GLASS",
        "GOAL",
        "GOOD",
        "GOVERNMENT",
        "GREAT",
        "GREEN",
        "GROUND",
        "GROUP",
        "GROW",
        "GROWTH",
        "GUESS",
        "GUN",
        "GUY",
        "HAIR",
        "HALF",
        "HAND",
        "HANG",
        "HAPPEN",
        "HAPPY",
        "HARD",
        "HAVE",
        "HEAD",
        "HEALTH",
        "HEAR",
        "HEART",
        "HEAT",
        "HEAVY",
        "HELP",
        "HER",
        "HERE",
        "HERSELF",
        "HIGH",
        "HIM",
        "HIMSELF",
        "HIS",
        "HISTORY",
        "HIT",
        "HOLD",
        "HOME",
        "HOPE",
        "HOSPITAL",
        "HOT",
        "HOTEL",
        "HOUR",
        "HOUSE",
        "HOW",
        "HOWEVER",
        "HUGE",
        "HUMAN",
        "HUNDRED",
        "HUSBAND",
        "IDEA",
        "IDENTIFY",
        "IMAGE",
        "IMAGINE",
        "IMPACT",
        "IMPORTANT",
        "IMPROVE",
        "INCLUDE",
        "INCLUDING",
        "INCREASE",
        "INDEED",
        "INDICATE",
        "INDIVIDUAL",
        "INDUSTRY",
        "INFORMATION",
        "INSIDE",
        "INSTEAD",
        "INSTITUTION",
        "INTEREST",
        "INTERESTING",
        "INTERNATIONAL",
        "INTERVIEW",
        "INTO",
        "INVESTMENT",
        "INVOLVE",
        "ISSUE",
        "ITEM",
        "ITS",
        "ITSELF",
        "JOB",
        "JOIN",
        "JUST",
        "KEEP",
        "KEY",
        "KID",
        "KILL",
        "KIND",
        "KITCHEN",
        "KNOW",
        "KNOWLEDGE",
        "LAND",
        "LANGUAGE",
        "LARGE",
        "LAST",
        "LATE",
        "LATER",
        "LAUGH",
        "LAW",
        "LAWYER",
        "LAY",
        "LEAD",
        "LEADER",
        "LEARN",
        "LEAST",
        "LEAVE",
        "LEFT",
        "LEG",
        "LEGAL",
        "LESS",
        "LET",
        "LETTER",
        "LEVEL",
        "LIE",
        "LIFE",
        "LIGHT",
        "LIKE",
        "LIKELY",
        "LINE",
        "LIST",
        "LISTEN",
        "LITTLE",
        "LIVE",
        "LOCAL",
        "LONG",
        "LOOK",
        "LOSE",
        "LOSS",
        "LOT",
        "LOVE",
        "LOW",
        "MACHINE",
        "MAGAZINE",
        "MAIN",
        "MAINTAIN",
        "MAJOR",
        "MAJORITY",
        "MAKE",
        "MAN",
        "MANAGE",
        "MANAGEMENT",
        "MANAGER",
        "MANY",
        "MARKET",
        "MARRIAGE",
        "MATERIAL",
        "MATTER",
        "MAY",
        "MAYBE",
        "MEAN",
        "MEASURE",
        "MEDIA",
        "MEDICAL",
        "MEET",
        "MEETING",
        "MEMBER",
        "MEMORY",
        "MENTION",
        "MESSAGE",
        "METHOD",
        "MIDDLE",
        "MIGHT",
        "MILITARY",
        "MILLION",
        "MIND",
        "MINUTE",
        "MISS",
        "MISSION",
        "MODEL",
        "MODERN",
        "MOMENT",
        "MONEY",
        "MONTH",
        "MORE",
        "MORNING",
        "MOST",
        "MOTHER",
        "MOUTH",
        "MOVE",
        "MOVEMENT",
        "MOVIE",
        "MRS",
        "MUCH",
        "MUSIC",
        "MUST",
        "MYSELF",
        "NAME",
        "NATION",
        "NATIONAL",
        "NATURAL",
        "NATURE",
        "NEAR",
        "NEARLY",
        "NECESSARY",
        "NEED",
        "NETWORK",
        "NEVER",
        "NEW",
        "NEWS",
        "NEWSPAPER",
        "NEXT",
        "NICE",
        "NIGHT",
        "NONE",
        "NOR",
        "NORTH",
        "NOT",
        "NOTE",
        "NOTHING",
        "NOTICE",
        "NOW",
        "N'T",
        "NUMBER",
        "OCCUR",
        "OFF",
        "OFFER",
        "OFFICE",
        "OFFICER",
        "OFFICIAL",
        "OFTEN",
        "OIL",
        "OLD",
        "ONCE",
        "ONE",
        "ONLY",
        "ONTO",
        "OPEN",
        "OPERATION",
        "OPPORTUNITY",
        "OPTION",
        "ORDER",
        "ORGANIZATION",
        "OTHER",
        "OTHERS",
        "OUR",
        "OUT",
        "OUTSIDE",
        "OVER",
        "OWN",
        "OWNER",
        "PAGE",
        "PAIN",
        "PAINTING",
        "PAPER",
        "PARENT",
        "PART",
        "PARTICIPANT",
        "PARTICULAR",
        "PARTICULARLY",
        "PARTNER",
        "PARTY",
        "PASS",
        "PAST",
        "PATIENT",
        "PATTERN",
        "PAY",
        "PEACE",
        "PEOPLE",
        "PER",
        "PERFORM",
        "PERFORMANCE",
        "PERHAPS",
        "PERIOD",
        "PERSON",
        "PERSONAL",
        "PHONE",
        "PHYSICAL",
        "PICK",
        "PICTURE",
        "PIECE",
        "PLACE",
        "PLAN",
        "PLANT",
        "PLAY",
        "PLAYER",
        "POINT",
        "POLICE",
        "POLICY",
        "POLITICAL",
        "POLITICS",
        "POOR",
        "POPULAR",
        "POPULATION",
        "POSITION",
        "POSITIVE",
        "POSSIBLE",
        "POWER",
        "PRACTICE",
        "PREPARE",
        "PRESENT",
        "PRESIDENT",
        "PRESSURE",
        "PRETTY",
        "PREVENT",
        "PRICE",
        "PRIVATE",
        "PROBABLY",
        "PROBLEM",
        "PROCESS",
        "PRODUCE",
        "PRODUCT",
        "PRODUCTION",
        "PROFESSIONAL",
        "PROFESSOR",
        "PROGRAM",
        "PROJECT",
        "PROPERTY",
        "PROTECT",
        "PROVE",
        "PROVIDE",
        "PUBLIC",
        "PULL",
        "PURPOSE",
        "PUSH",
        "PUT",
        "QUALITY",
        "QUESTION",
        "QUICKLY",
        "QUITE",
        "RACE",
        "RADIO",
        "RAISE",
        "RANGE",
        "RATE",
        "RATHER",
        "REACH",
        "READ",
        "READY",
        "REAL",
        "REALITY",
        "REALIZE",
        "REALLY",
        "REASON",
        "RECEIVE",
        "RECENT",
        "RECENTLY",
        "RECOGNIZE",
        "RECORD",
        "RED",
        "REDUCE",
        "REFLECT",
        "REGION",
        "RELATE",
        "RELATIONSHIP",
        "RELIGIOUS",
        "REMAIN",
        "REMEMBER",
        "REMOVE",
        "REPORT",
        "REPRESENT",
        "REPUBLICAN",
        "REQUIRE",
        "RESEARCH",
        "RESOURCE",
        "RESPOND",
        "RESPONSE",
        "RESPONSIBILITY",
        "REST",
        "RESULT",
        "RETURN",
        "REVEAL",
        "RICH",
        "RIGHT",
        "RISE",
        "RISK",
        "ROAD",
        "ROCK",
        "ROLE",
        "ROOM",
        "RULE",
        "RUN",
        "SAFE",
        "SAME",
        "SAVE",
        "SAY",
        "SCENE",
        "SCHOOL",
        "SCIENCE",
        "SCIENTIST",
        "SCORE",
        "SEA",
        "SEASON",
        "SEAT",
        "SECOND",
        "SECTION",
        "SECURITY",
        "SEE",
        "SEEK",
        "SEEM",
        "SELL",
        "SEND",
        "SENIOR",
        "SENSE",
        "SERIES",
        "SERIOUS",
        "SERVE",
        "SERVICE",
        "SET",
        "SEVEN",
        "SEVERAL",
        "SHAKE",
        "SHARE",
        "SHE",
        "SHOOT",
        "SHORT",
        "SHOT",
        "SHOULD",
        "SHOULDER",
        "SHOW",
        "SIDE",
        "SIGN",
        "SIGNIFICANT",
        "SIMILAR",
        "SIMPLE",
        "SIMPLY",
        "SINCE",
        "SING",
        "SINGLE",
        "SISTER",
        "SIT",
        "SITE",
        "SITUATION",
        "SIX",
        "SIZE",
        "SKILL",
        "SKIN",
        "SMALL",
        "SMILE",
        "SOCIAL",
        "SOCIETY",
        "SOLDIER",
        "SOME",
        "SOMEBODY",
        "SOMEONE",
        "SOMETHING",
        "SOMETIMES",
        "SON",
        "SONG",
        "SOON",
        "SORT",
        "SOUND",
        "SOURCE",
        "SOUTH",
        "SOUTHERN",
        "SPACE",
        "SPEAK",
        "SPECIAL",
        "SPECIFIC",
        "SPEECH",
        "SPEND",
        "SPORT",
        "SPRING",
        "STAFF",
        "STAGE",
        "STAND",
        "STANDARD",
        "STAR",
        "START",
        "STATE",
        "STATEMENT",
        "STATION",
        "STAY",
        "STEP",
        "STILL",
        "STOCK",
        "STOP",
        "STORE",
        "STORY",
        "STRATEGY",
        "STREET",
        "STRONG",
        "STRUCTURE",
        "STUDENT",
        "STUDY",
        "STUFF",
        "STYLE",
        "SUBJECT",
        "SUCCESS",
        "SUCCESSFUL",
        "SUCH",
        "SUDDENLY",
        "SUFFER",
        "SUGGEST",
        "SUMMER",
        "SUPPORT",
        "SURE",
        "SURFACE",
        "SYSTEM",
        "TABLE",
        "TAKE",
        "TALK",
        "TASK",
        "TAX",
        "TEACH",
        "TEACHER",
        "TEAM",
        "TECHNOLOGY",
        "TELEVISION",
        "TELL",
        "TEN",
        "TEND",
        "TERM",
        "TEST",
        "THAN",
        "THANK",
        "THAT",
        "THE",
        "THEIR",
        "THEM",
        "THEMSELVES",
        "THEN",
        "THEORY",
        "THERE",
        "THESE",
        "THEY",
        "THING",
        "THINK",
        "THIRD",
        "THIS",
        "THOSE",
        "THOUGH",
        "THOUGHT",
        "THOUSAND",
        "THREAT",
        "THREE",
        "THROUGH",
        "THROUGHOUT",
        "THROW",
        "THUS",
        "TIME",
        "TODAY",
        "TOGETHER",
        "TONIGHT",
        "TOO",
        "TOP",
        "TOTAL",
        "TOUGH",
        "TOWARD",
        "TOWN",
        "TRADE",
        "TRADITIONAL",
        "TRAINING",
        "TRAVEL",
        "TREAT",
        "TREATMENT",
        "TREE",
        "TRIAL",
        "TRIP",
        "TROUBLE",
        "TRUE",
        "TRUTH",
        "TRY",
        "TURN",
        "TWO",
        "TYPE",
        "UNDER",
        "UNDERSTAND",
        "UNIT",
        "UNTIL",
        "UPON",
        "USE",
        "USUALLY",
        "VALUE",
        "VARIOUS",
        "VERY",
        "VICTIM",
        "VIEW",
        "VIOLENCE",
        "VISIT",
        "VOICE",
        "VOTE",
        "WAIT",
        "WALK",
        "WALL",
        "WANT",
        "WAR",
        "WATCH",
        "WATER",
        "WAY",
        "WEAPON",
        "WEAR",
        "WEEK",
        "WEIGHT",
        "WELL",
        "WEST",
        "WESTERN",
        "WHAT",
        "WHATEVER",
        "WHEN",
        "WHERE",
        "WHETHER",
        "WHICH",
        "WHILE",
        "WHITE",
        "WHO",
        "WHOLE",
        "WHOM",
        "WHOSE",
        "WHY",
        "WIDE",
        "WIFE",
        "WILL",
        "WIN",
        "WIND",
        "WINDOW",
        "WISH",
        "WITH",
        "WITHIN",
        "WITHOUT",
        "WOMAN",
        "WONDER",
        "WORD",
        "WORK",
        "WORKER",
        "WORLD",
        "WORRY",
        "WOULD",
        "WRITE",
        "WRITER",
        "WRONG",
        "YARD",
        "YEAH",
        "YEAR",
        "YES",
        "YET",
        "YOU",
        "YOUNG",
        "YOUR",
        "YOURSELF",
    };
    ///@}

    /**
     * @brief Battleships board attributes.
     */
    ///@{
    static inline const uint32_t G_BATTLESHIPS_BOARD_WIDTH = 10;
    static inline const uint32_t G_BATTLESHIPS_BOARD_HEIGHT = 10;
    static inline const uint32_t G_BATTLESHIPS_GRID_ELEMENT_WIDTH = 3;
    static inline const uint32_t G_BATTLESHIPS_GRID_ELEMENT_HEIGHT = 1;
    static inline const uint32_t G_BATTLESHIPS_GRID_PLAYER_ONE_BOARD_LEFT_PAD = 8;
    static inline const uint32_t G_BATTLESHIPS_GRID_PLAYER_TWO_BOARD_LEFT_PAD = 101;
    static inline const uint32_t G_BATTLESHIPS_GRID_TOP_PAD = 8;
    ///@}

    /**
     * @brief Battleships board constants used to construct the board.
     */
    ///@{
    static inline const std::string G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE = std::string(G_BATTLESHIPS_GRID_ELEMENT_WIDTH, G_PAGE_GRID_HORIZONTAL_LINE);

    static inline const std::string G_BATTLESHIPS_GRID_TOP_LINE_TOP_LEFT = std::string(1, G_PAGE_GRID_TOP_LEFT) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;
    static inline const std::string G_BATTLESHIPS_GRID_TOP_LINE_MIDDLE = std::string(1, G_PAGE_GRID_T) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;

    static inline const std::string G_BATTLESHIPS_GRID_MIDDLE_LINE_LEFT = std::string(1, G_PAGE_GRID_LEFT_SIDEWAYS_T) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;
    static inline const std::string G_BATTLESHIPS_GRID_MIDDLE_LINE_MIDDLE = std::string(1, G_PAGE_GRID_INTERSECTION) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;

    static inline const std::string G_BATTLESHIPS_GRID_BOTTOM_LINE_BOTTOM_LEFT = std::string(1, G_PAGE_GRID_BOTTOM_LEFT) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;
    static inline const std::string G_BATTLESHIPS_GRID_BOTTOM_LINE_MIDDLE = std::string(1, G_PAGE_GRID_UPSIDE_DOWN_T) + G_BATTLESHIPS_GRID_ITEM_HORIZONTAL_LINE;

    static inline const std::string G_BATTLESHIPS_GRID_TOP_LINE = G_BATTLESHIPS_GRID_TOP_LINE_TOP_LEFT + RepeatString(G_BATTLESHIPS_BOARD_WIDTH, G_BATTLESHIPS_GRID_TOP_LINE_MIDDLE) + std::string(1, G_PAGE_GRID_TOP_RIGHT);
    static inline const std::string G_BATTLESHIPS_GRID_MIDDLE_LINE = G_BATTLESHIPS_GRID_MIDDLE_LINE_LEFT + RepeatString(G_BATTLESHIPS_BOARD_WIDTH, G_BATTLESHIPS_GRID_MIDDLE_LINE_MIDDLE) + std::string(1, G_PAGE_GRID_RIGHT_SIDEWAYS_T);
    static inline const std::string G_BATTLESHIPS_GRID_BOTTOM_LINE = G_BATTLESHIPS_GRID_BOTTOM_LINE_BOTTOM_LEFT + RepeatString(G_BATTLESHIPS_BOARD_WIDTH, G_BATTLESHIPS_GRID_BOTTOM_LINE_MIDDLE) + std::string(1, G_PAGE_GRID_BOTTOM_RIGHT);

    static inline const uint32_t G_BATTLESHIPS_LETTER_OFFSET = 65;
    ///@}

    /**
     * @brief Battleships board values.
     */
    ///@{
    static inline const std::string G_BATTLESHIPS_EMPTY_GRID_VALUE = std::string(G_BATTLESHIPS_GRID_ELEMENT_WIDTH, ' ');
    static inline const std::string G_BATTLESHIPS_MISSED_ATTACK = std::string(1, ' ') + G_PAGE_CENTRAL_DOT + ' ';
    static inline const std::string G_BATTLESHIPS_SHIP_PRESENT = std::string(G_BATTLESHIPS_GRID_ELEMENT_WIDTH, G_PAGE_DARK_HASH);
    static inline const std::string G_BATTLESHIPS_SUCCESSFUL_ATTACK = std::string(G_BATTLESHIPS_GRID_ELEMENT_WIDTH, G_PAGE_LIGHT_HASH);
    ///@}

    /**
     * @brief Battleships player choice options.
     */
    ///@{
    static inline const std::string G_BATTLESHIPS_PLAYER_ONE = "Player One";
    static inline const std::string G_BATTLESHIPS_PLAYER_TWO = "Player Two";
    static inline const std::array<std::string, G_GAME_TWO_OPTIONS> G_BATTLESHIPS_PLAYER_CHOICE_OPTIONS = {G_BATTLESHIPS_PLAYER_ONE, G_BATTLESHIPS_PLAYER_TWO};
    ///@}

    /**
     * @brief Battleships number of ships for each board/player.
     */
    static inline const uint32_t G_BATTLESHIPS_SHIP_COUNT = 5;

    /**
     * @brief Battleships ship-related constants used in later arrays.
     */
    ///@{
    static inline const uint32_t G_BATTLESHIPS_CARRIER_SIZE = 5;
    static inline const uint32_t G_BATTLESHIPS_BATTLESHIP_SIZE = 4;
    static inline const uint32_t G_BATTLESHIPS_DESTROYER_SIZE = 3;
    static inline const uint32_t G_BATTLESHIPS_SUBMARINE_SIZE = 3;
    static inline const uint32_t G_BATTLESHIPS_PATROL_BOAT_SIZE = 2;

    static inline const std::string G_BATTLESHIPS_CARRIER_NAME = "Carrier";
    static inline const std::string G_BATTLESHIPS_BATTLESHIP_NAME = "Battleship";
    static inline const std::string G_BATTLESHIPS_DESTROYER_NAME = "Destroyer";
    static inline const std::string G_BATTLESHIPS_SUBMARINE_NAME = "Submarine";
    static inline const std::string G_BATTLESHIPS_PATROL_BOAT_NAME = "Patrol Boat";

    static inline const std::string G_BATTLESHIPS_CARRIER_PLACED_NAME = G_BATTLESHIPS_SHIP_PRESENT + G_BATTLESHIPS_CARRIER_NAME;
    static inline const std::string G_BATTLESHIPS_BATTLESHIP_PLACED_NAME = G_BATTLESHIPS_SHIP_PRESENT + G_BATTLESHIPS_BATTLESHIP_NAME;
    static inline const std::string G_BATTLESHIPS_DESTROYER_PLACED_NAME = G_BATTLESHIPS_SHIP_PRESENT + G_BATTLESHIPS_DESTROYER_NAME;
    static inline const std::string G_BATTLESHIPS_SUBMARINE_PLACED_NAME = G_BATTLESHIPS_SHIP_PRESENT + G_BATTLESHIPS_SUBMARINE_NAME;
    static inline const std::string G_BATTLESHIPS_PATROL_BOAT_PLACED_NAME = G_BATTLESHIPS_SHIP_PRESENT + G_BATTLESHIPS_PATROL_BOAT_NAME;
    ///@}

    /**
     * @brief Battleships list of instructions use when asking the user for the grid locations for their ships.
     */
    static inline const std::array<std::string, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_INSTRUCTIONS = {
        "Please enter the " + std::to_string(G_BATTLESHIPS_CARRIER_SIZE) + " grid locations for the Carrier",
        "Please enter the " + std::to_string(G_BATTLESHIPS_BATTLESHIP_SIZE) + " grid locations for the Battleship",
        "Please enter the " + std::to_string(G_BATTLESHIPS_DESTROYER_SIZE) + " grid locations for the Destroyer",
        "Please enter the " + std::to_string(G_BATTLESHIPS_SUBMARINE_SIZE) + " grid locations for the Submarine",
        "Please enter the " + std::to_string(G_BATTLESHIPS_PATROL_BOAT_SIZE) + " grid locations for the Patrol Boat",
    };

    /**
     * @brief Battleships list of ship names.
     */
    static inline const std::array<std::string, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_NAMES = {
        G_BATTLESHIPS_CARRIER_NAME,
        G_BATTLESHIPS_BATTLESHIP_NAME,
        G_BATTLESHIPS_DESTROYER_NAME,
        G_BATTLESHIPS_SUBMARINE_NAME,
        G_BATTLESHIPS_PATROL_BOAT_NAME,
    };

    /**
     * @brief Battleships list of ship names when placed on a board.
     */
    static inline const std::array<std::string, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_PLACED_NAMES = {
        G_BATTLESHIPS_CARRIER_PLACED_NAME,
        G_BATTLESHIPS_BATTLESHIP_PLACED_NAME,
        G_BATTLESHIPS_DESTROYER_PLACED_NAME,
        G_BATTLESHIPS_SUBMARINE_PLACED_NAME,
        G_BATTLESHIPS_PATROL_BOAT_PLACED_NAME,
    };

    /**
     * @brief Battleships list of ship sizes.
     */
    static inline const std::array<uint32_t, G_BATTLESHIPS_SHIP_COUNT> G_BATTLESHIPS_SHIP_SIZES = {
        G_BATTLESHIPS_CARRIER_SIZE,
        G_BATTLESHIPS_BATTLESHIP_SIZE,
        G_BATTLESHIPS_DESTROYER_SIZE,
        G_BATTLESHIPS_SUBMARINE_SIZE,
        G_BATTLESHIPS_PATROL_BOAT_SIZE,
    };
}

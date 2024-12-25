// NOLINTBEGIN(fuchsia-statically-constructed-objects, cert-err58-cpp)

#pragma once

#include <cstdint>
#include <string>

namespace TerminalGames
{
    /**
     * @brief Terminal
     */
    // Keyboard values when getting user input.
    static constexpr uint32_t g_ENTER_KEY = '\r';
    static constexpr uint32_t g_UP_ARROW_KEY = 72;
    static constexpr uint32_t g_DOWN_ARROW_KEY = 80;
    static constexpr uint32_t g_LEFT_ARROW_KEY = 75;
    static constexpr uint32_t g_RIGHT_ARROW_KEY = 77;
    static constexpr uint32_t g_QUIT_KEY = 'q';

    // Cursor width while running.
    static constexpr uint32_t g_CURSOR_WIDTH_PERCENTAGE = 100;

    /**
     * @brief PageBuilder
     */
    // Page dimensions.
    static constexpr uint32_t g_MAIN_MENU_DISPLAY_WIDTH = 30;
    static constexpr uint32_t g_MAIN_MENU_DISPLAY_HEIGHT = 13;
    static constexpr uint32_t g_TICTACTOE_DISPLAY_WIDTH = 53;
    static constexpr uint32_t g_TICTACTOE_DISPLAY_HEIGHT = 19;
    static constexpr uint32_t g_HANGMAN_DISPLAY_WIDTH = 62;
    static constexpr uint32_t g_HANGMAN_DISPLAY_HEIGHT = 22;
    static constexpr uint32_t g_BATTLESHIPS_DISPLAY_WIDTH = 147;
    static constexpr uint32_t g_BATTLESHIPS_DISPLAY_HEIGHT = 38;

    // Selector when selecting options.
    static const std::string g_SELECTOR = ">";

    // Bottom box titles.
    static const std::string g_MENU_BOTTOM_TITLE = "q = quit";
    static const std::string g_GAME_BOTTOM_TITLE = "q = quit to main menu";

    // Extended ASCII characters for edges and corners of the page.
    static constexpr char g_HORIZONTAL_LINE = static_cast<char>(205);
    static constexpr char g_VERTICAL_LINE = static_cast<char>(186);
    static constexpr char g_TOP_RIGHT_CORNER = static_cast<char>(187);
    static constexpr char g_BOTTOM_RIGHT_CORNER = static_cast<char>(188);
    static constexpr char g_BOTTOM_LEFT_CORNER = static_cast<char>(200);
    static constexpr char g_TOP_LEFT_CORNER = static_cast<char>(201);

    // ANSI colour escape codes.
    static const std::string g_WHITE_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;37m";
    static const std::string g_RED_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;31m";
    static const std::string g_BLUE_ANSI_COLOUR_ESCAPE_CODE = "\x1B[1;34m";
    static const std::string g_RESET_ANSI_COLOUR_ESCAPE_CODE = "\x1B[0m";

    /**
     * @brief Tic Tac Toe
     */
    static constexpr uint32_t g_TICTACTOE_BOARD_WIDTH = 3;
    static constexpr uint32_t g_TICTACTOE_BOARD_HEIGHT = 3;
    static constexpr uint32_t g_TICTACTOE_MAXIMUM_ERROR_COUNT = g_TICTACTOE_BOARD_WIDTH * g_TICTACTOE_BOARD_HEIGHT;
    static constexpr uint32_t g_TICTACTOE_GRID_LEFT_PAD = 4;
    static constexpr uint32_t g_TICTACTOE_GRID_TOP_PAD = 4;
    static constexpr uint32_t g_TICTACTOE_GRID_ELEMENT_WIDTH = 4;
    static constexpr uint32_t g_TICTACTOE_GRID_ELEMENT_HEIGHT = 2;

    /**
     * @brief Hangman
     */
    static constexpr uint32_t g_HANGMAN_NUMBER_OF_LETTERS_IN_THE_ALPHABET = 26;
    static constexpr uint32_t g_HANGMAN_MINIMUM_WORD_LENGTH = 3;
    static constexpr uint32_t g_HANGMAN_MAXIMUM_WORD_LENGTH = 14;
    static constexpr uint32_t g_HANGMAN_MAXIMUM_ERROR_COUNT = 10;

    /**
     * @brief Battleships
     */
    static constexpr uint32_t g_BATTLESHIPS_BOARD_WIDTH = 10;
    static constexpr uint32_t g_BATTLESHIPS_BOARD_HEIGHT = 10;
    static constexpr uint32_t g_BATTLESHIPS_SHIP_COUNT = 5;
    static const std::string g_BATTLESHIPS_CARRIER_NAME = "Carrier";
    static const std::string g_BATTLESHIPS_BATTLESHIP_NAME = "Battleship";
    static const std::string g_BATTLESHIPS_DESTROYER_NAME = "Destroyer";
    static const std::string g_BATTLESHIPS_SUBMARINE_NAME = "Submarine";
    static const std::string g_BATTLESHIPS_PATROL_BOAT_NAME = "Patrol Boat";
    static constexpr uint32_t g_BATTLESHIPS_CARRIER_SIZE = 5;
    static constexpr uint32_t g_BATTLESHIPS_BATTLESHIP_SIZE = 4;
    static constexpr uint32_t g_BATTLESHIPS_DESTROYER_SIZE = 3;
    static constexpr uint32_t g_BATTLESHIPS_SUBMARINE_SIZE = 3;
    static constexpr uint32_t g_BATTLESHIPS_PATROL_BOAT_SIZE = 2;

    /**
     * @brief Functions which are not supported by some compilers so are crudely implemented here for the project specific use
     * case. Usually because the function call fails with GNU 12.2.0.
     */

    // Only works for strings
    static int32_t ImplementStdCount(const std::string::const_iterator &begin, const std::string::const_iterator &end, const char &character)
    {
        int32_t count = 0;

        for (auto i = begin; i < end; i++)
        {
            if (*i == character)
            {
                ++count;
            }
        }

        return count;
    }

    // Only works for single instance of {} in string
    static std::string ImplementStdFormat(const std::string &stringToFormat, const uint32_t &varToInsert)
    {
        const std::string beforeString = stringToFormat.substr(0, stringToFormat.find("{}")); // NOLINT(fuchsia-default-arguments-calls)
        const std::string afterString = stringToFormat.substr(stringToFormat.find("{}") + 2, stringToFormat.size() - stringToFormat.find("{}")); // NOLINT(fuchsia-default-arguments-calls)

        return beforeString + std::to_string(varToInsert) + afterString;
    }

    // Should work for all containers
    template <typename T, typename U>
    static T ImplementStdRangesFind(const T &begin, const T &end, const U &value)
    {
        return std::find(begin, end, value);
    }
} // namespace TerminalGames
// NOLINTEND(fuchsia-statically-constructed-objects, cert-err58-cpp)
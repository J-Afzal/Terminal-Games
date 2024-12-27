// NOLINTBEGIN(fuchsia-statically-constructed-objects, cert-err58-cpp)

#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace TerminalGames
{
    /**
     * @brief Some C++ functions are not supported by some compilers (usually because the function call fails with GNU 12.2.0
     * within the CI pipeline.) These functions are crudely implemented below for the project's specific use case.
     */
    // Should work for all std containers
    template <typename T, typename U>
    static T ImplementStdRangesFind(const T &begin, const T &end, const U &value)
    {
        for (T i = begin; i < end; i++)
        {
            if (*i == value)
            {
                return i;
            }
        }

        return end;
    }

    // Should work for all std containers
    template <typename T, typename U>
    static int32_t ImplementStdCount(const T &begin, const T &end, const U &value)
    {
        int32_t count = 0;

        for (T i = begin; i < end; i++)
        {
            if (*i == value)
            {
                ++count;
            }
        }

        return count;
    }

    // Only works for single instance of {} in stringToFormat
    static std::string ImplementStdFormat(const std::string &stringToFormat, const uint32_t &varToInsert)
    {
        const std::string formatIdentifier = "{}";
        const std::string beforeString = stringToFormat.substr(0, stringToFormat.find(formatIdentifier));
        const std::string afterString = stringToFormat.substr(stringToFormat.find(formatIdentifier) + formatIdentifier.size(), stringToFormat.size() - stringToFormat.find("{}"));

        return beforeString + std::to_string(varToInsert) + afterString;
    }

    /**
     * @brief Terminal
     */
    // Keyboard values when getting user input on Windows.
    static constexpr uint32_t g_ENTER_KEY = '\r';
    static constexpr uint32_t g_BACKSPACE_KEY = 8;
    static constexpr uint32_t g_UP_ARROW_KEY = 72;
    static constexpr uint32_t g_DOWN_ARROW_KEY = 80;
    static constexpr uint32_t g_LEFT_ARROW_KEY = 75;
    static constexpr uint32_t g_RIGHT_ARROW_KEY = 77;
    static constexpr uint32_t g_QUIT_KEY = 'q';

    // Keyboard values when getting user input on other platforms.
    static constexpr uint32_t g_ALTERNATIVE_ENTER_KEY = 'e';
    static constexpr uint32_t g_ALTERNATIVE_BACKSPACE_KEY = 'z';
    static constexpr uint32_t g_ALTERNATIVE_UP_ARROW_KEY = 'w';
    static constexpr uint32_t g_ALTERNATIVE_DOWN_ARROW_KEY = 's';
    static constexpr uint32_t g_ALTERNATIVE_LEFT_ARROW_KEY = 'a';
    static constexpr uint32_t g_ALTERNATIVE_RIGHT_ARROW_KEY = 'd';
    static constexpr uint32_t g_ALTERNATIVE_QUIT_KEY = 'q';

    // Cursor width while running on windows.
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

    static constexpr uint32_t g_TICTACTOE_GRID_LEFT_PAD = 3;
    static constexpr uint32_t g_TICTACTOE_GRID_TOP_PAD = 4;
    static constexpr uint32_t g_TICTACTOE_GRID_ELEMENT_WIDTH = 4;
    static constexpr uint32_t g_TICTACTOE_GRID_ELEMENT_HEIGHT = 2;

    static constexpr uint32_t g_TICTACTOE_MAXIMUM_ERROR_COUNT = g_TICTACTOE_BOARD_WIDTH * g_TICTACTOE_BOARD_HEIGHT;
    
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

    static constexpr uint32_t g_BATTLESHIPS_GRID_LEFT_PAD = 10;
    static constexpr uint32_t g_BATTLESHIPS_GRID_TOP_PAD = 8;
    static constexpr uint32_t g_BATTLESHIPS_GRID_ELEMENT_WIDTH = 4;
    static constexpr uint32_t g_BATTLESHIPS_GRID_ELEMENT_HEIGHT = 2;

    static const std::string g_BATTLESHIPS_PLACED_SHIP{static_cast<char>(178)};
    static const std::string g_BATTLESHIPS_SUCCESSFUL_ATTACK{static_cast<char>(176)};
    static const std::string g_BATTLESHIPS_MISSED_ATTACK{static_cast<char>(250)};

    static constexpr uint32_t g_BATTLESHIPS_SHIP_COUNT = 5;

    static const std::string g_BATTLESHIPS_CARRIER_NAME = g_BATTLESHIPS_PLACED_SHIP + "C" + g_BATTLESHIPS_PLACED_SHIP;
    static const std::string g_BATTLESHIPS_BATTLESHIP_NAME = g_BATTLESHIPS_PLACED_SHIP + "B" + g_BATTLESHIPS_PLACED_SHIP;
    static const std::string g_BATTLESHIPS_DESTROYER_NAME = g_BATTLESHIPS_PLACED_SHIP + "D" + g_BATTLESHIPS_PLACED_SHIP;
    static const std::string g_BATTLESHIPS_SUBMARINE_NAME = g_BATTLESHIPS_PLACED_SHIP + "S" + g_BATTLESHIPS_PLACED_SHIP;
    static const std::string g_BATTLESHIPS_PATROL_BOAT_NAME = g_BATTLESHIPS_PLACED_SHIP + "P" + g_BATTLESHIPS_PLACED_SHIP;
    static const std::array<std::string, g_BATTLESHIPS_SHIP_COUNT> g_BATTLESHIPS_SHIP_NAMES = {
        g_BATTLESHIPS_CARRIER_NAME,
        g_BATTLESHIPS_BATTLESHIP_NAME,
        g_BATTLESHIPS_DESTROYER_NAME,
        g_BATTLESHIPS_SUBMARINE_NAME,
        g_BATTLESHIPS_PATROL_BOAT_NAME};

    static constexpr uint32_t g_BATTLESHIPS_CARRIER_SIZE = 5;
    static constexpr uint32_t g_BATTLESHIPS_BATTLESHIP_SIZE = 4;
    static constexpr uint32_t g_BATTLESHIPS_DESTROYER_SIZE = 3;
    static constexpr uint32_t g_BATTLESHIPS_SUBMARINE_SIZE = 3;
    static constexpr uint32_t g_BATTLESHIPS_PATROL_BOAT_SIZE = 2;
    static const std::array<uint32_t, g_BATTLESHIPS_SHIP_COUNT> g_BATTLESHIPS_SHIP_SIZES = {
        g_BATTLESHIPS_CARRIER_SIZE,
        g_BATTLESHIPS_BATTLESHIP_SIZE,
        g_BATTLESHIPS_DESTROYER_SIZE,
        g_BATTLESHIPS_SUBMARINE_SIZE,
        g_BATTLESHIPS_PATROL_BOAT_SIZE};

    static const std::array<std::string, g_BATTLESHIPS_SHIP_COUNT> g_BATTLESHIPS_SHIP_INSTRUCTIONS = {
        TerminalGames::ImplementStdFormat("Please enter the {} grid locations for the Carrier", g_BATTLESHIPS_CARRIER_SIZE),
        TerminalGames::ImplementStdFormat("Please enter the {} grid locations for the Battleship", g_BATTLESHIPS_BATTLESHIP_SIZE),
        TerminalGames::ImplementStdFormat("Please enter the {} grid locations for the Destroyer", g_BATTLESHIPS_DESTROYER_SIZE),
        TerminalGames::ImplementStdFormat("Please enter the {} grid locations for the Submarine", g_BATTLESHIPS_SUBMARINE_SIZE),
        TerminalGames::ImplementStdFormat("Please enter the {} grid locations for the Patrol Boat", g_BATTLESHIPS_PATROL_BOAT_SIZE)
    };
} // namespace TerminalGames
// NOLINTEND(fuchsia-statically-constructed-objects, cert-err58-cpp)

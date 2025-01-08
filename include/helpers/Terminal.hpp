#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "helpers/PageBuilder.hpp"

namespace TerminalGames
{
    /**
     * @brief Handles all terminal related tasks such as getting user input, outputting to the terminal, clearing the terminal,
     * etc.
     */
    class Terminal
    {
    public:
        Terminal() = delete;

        /**
         * @brief Get the user choice from a list of homepage strings that are printed to the terminal.
         *
         * @param p_menus An array of strings used to print to the terminal. The string chosen depends on user input. The only
         * difference between each string is the selected menu option.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only ASCII characters (false).
         * @return true If to use ANSI escape codes
         * @return false If to not use ANSI escape code (only use ASCII characters)
         */
        static bool GetUserChoiceFromHomepage(const std::vector<std::string>& p_menus, const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Get the user choice from a list of main menus strings that are printed to the terminal.
         *
         * @param p_menus An array of strings used to print to the terminal. The string chosen depends on user input. The only
         * difference between each string is the selected menu option.
         * @return uint32_t The index of the menu string that the user selected.
         */
        static uint32_t GetUserChoiceFromMainMenus(const std::vector<std::string>& p_menus);

        /**
         * @brief Get the user choice from a list of game menus strings that are printed to the terminal.
         *
         * @param p_menus An array of strings used to print to the terminal. The string chosen depends on user input. The only
         * difference between each string is the selected menu option.
         * @return uint32_t The index of the menu string that the user selected.
         */
        static uint32_t GetUserChoiceFromGameMenus(const std::vector<std::string>& p_menus);

        /**
         * @brief Gets a user command based on the currently displayed game grid. Most of the parameters are to enable the
         * correct alignment of the cursor for different game grid sizes.
         *
         * @param p_startingGridLocation The initial row and column to place the cursor.
         * @param p_pageBuilder The page builder object to allow for refreshing the screen.
         * @param p_gameInfo The game info object to pass to the page builder object.
         * @param p_displayGetUserCommandPage Whether to display the get user command page.
         * @return std::tuple<uint32_t, uint32_t> The user command from the user in the for <row, column>.
         */
        static std::tuple<uint32_t, uint32_t> GetUserCommandFromGameGrid(
            const std::tuple<uint32_t, uint32_t>& p_startingGridLocation,
            const PageBuilder& p_pageBuilder,
            const GameInfo& p_gameInfo,
            const bool& p_displayGetUserCommandPage);

        /**
         * @brief Clears and then prints to the terminal.
         *
         * @param output The string to output to the terminal.
         */
        static void PrintOutput(const std::string& p_output);

        /**
         * @brief Clears the terminal.
         * @see https://www.cplusplus.com/articles/4z18T05o
         */
        static void Clear();

        /**
         * @brief Wrapper for Windows.h FlushConsoleInputBuffer() and _getch()
         *
         * @return uint32_t The key which was pressed represented as an integer.
         */
        static uint32_t GetNextKeyPress();

        /**
         * @brief Wrapper for Windows.h SetConsoleCursorInfo()
         *
         * @param p_cursorVisibility Whether the cursor should be visible.
         */
        static void SetCursorVisibility(const bool& p_cursorVisibility);

        /**
         * @brief Wrapper for Windows.h SetConsoleCursorPosition()
         *
         * @param p_coords The horizontal and vertical position to set the cursor to.
         */
        static void SetCursorPosition(const std::tuple<int16_t, int16_t>& p_coords);

        /**
         * @brief Initialises terminal for the program.
         */
        static void InitialiseTerminal();

        /**
         * @brief Reset terminal to its original state before the program was run.
         */
        static void ResetTerminal();
    };
}

#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

namespace TerminalGames
{
    /**
     * @brief Handles all terminal related tasks such as getting user input,
     * outputting to the terminal, clearing the terminal, etc
     */
    class Terminal
    {
    public:
        Terminal() = delete;

        /**
         * @brief Get the user choice from a list of main menus strings that are printed to
         * the terminal.
         *
         * @param menus An array of strings used to print to the terminal. The string chosen
         * depends on user input. The only difference between each string is the selected menu
         * option.
         * @return uint32_t The index of the menu string that the user selected.
         */
        static uint32_t GetUserChoiceFromMainMenus(const std::vector<std::string> &menus);

        /**
         * @brief Get the user choice from a list of game menus strings that are printed to
         * the terminal.
         *
         * @param menus An array of strings used to print to the terminal. The string chosen
         * depends on user input. The only difference between each string is the selected menu
         * option.
         * @return uint32_t The index of the menu string that the user selected.
         */
        static uint32_t GetUserChoiceFromGameMenus(const std::vector<std::string> &menus);

        /**
         * @brief Get the User Command From Game Grid object
         *
         * @param startingRow
         * @param startingColumn
         * @param maxRow
         * @param maxColumn
         * @param gridLeftPad
         * @param gridTopPad
         * @param gridElementWidth
         * @param gridElementHeight
         * @return std::tuple<uint32_t, uint32_t>
         */
        static std::tuple<uint32_t, uint32_t> GetUserCommandFromGameGrid(
            const uint32_t &startingRow,
            const uint32_t &startingColumn,
            const uint32_t &maxRow,
            const uint32_t &maxColumn,
            const uint32_t &gridLeftPad,
            const uint32_t &gridTopPad,
            const uint32_t &gridElementWidth,
            const uint32_t &gridElementHeight);

        /**
         * @brief Clears and then prints to the terminal.
         *
         * @param output The string to output to the terminal.
         */
        static void PrintOutput(const std::string &output);

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
         * @param visibility Whether the cursor should be visible.
         */
        static void SetCursorVisibility(const bool &visibility);

        /**
         * @brief Wrapper for Windows.h SetConsoleCursorPosition()
         *
         * @param xCoord The horizontal position to set the cursor to.
         * @param yCoord The vertical position to set the cursor to.
         */
        static void SetCursorPosition(const int16_t &xCoord, const int16_t &yCoord);
    };
} // namespace TerminalGames

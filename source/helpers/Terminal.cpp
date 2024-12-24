// NOLINTBEGIN(misc-include-cleaner)
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "conio.h"
#include "Windows.h"

#include "helpers/Constants.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    uint32_t Terminal::GetUserChoiceFromMainMenus(const std::vector<std::string> &menus)
    {
        uint32_t keyPress = 0;
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(menus[currentSelection]);

            keyPress = GetNextKeyPress();

            if (keyPress == g_QUIT_KEY)
            {
                throw Exceptions::QuitMainMenu();
            }

            if (keyPress == g_ENTER_KEY)
            {
                return currentSelection;
            }

            if (keyPress == g_UP_ARROW_KEY)
            {
                currentSelection == 0 ? currentSelection = (menus.size() - 1) : --currentSelection;
            }

            else if (keyPress == g_DOWN_ARROW_KEY)
            {
                currentSelection == (menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
            }
        }
    }

    uint32_t Terminal::GetUserChoiceFromGameMenus(const std::vector<std::string> &menus)
    {
        uint32_t keyPress = 0;
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(menus[currentSelection]);

            keyPress = GetNextKeyPress();

            if (keyPress == g_QUIT_KEY)
            {
                throw Exceptions::QuitGame();
            }

            if (keyPress == g_ENTER_KEY)
            {
                return currentSelection;
            }

            if (keyPress == g_UP_ARROW_KEY)
            {
                currentSelection == 0 ? currentSelection = (menus.size() - 1) : --currentSelection;
            }

            else if (keyPress == g_DOWN_ARROW_KEY)
            {
                currentSelection == (menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
            }
        }
    }

    // NOLINTBEGIN (bugprone-easily-swappable-parameters)
    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGrid(
        const uint32_t &startingRow,
        const uint32_t &startingColumn,
        const uint32_t &maxRow,
        const uint32_t &maxColumn,
        const uint32_t &gridLeftPad,
        const uint32_t &gridTopPad,
        const uint32_t &gridElementWidth,
        const uint32_t &gridElementHeight)
    // NOLINTEND (bugprone-easily-swappable-parameters)
    {
        Terminal::SetCursorVisibility(true);

        uint32_t keyPress = 0;
        uint32_t row = startingRow;
        uint32_t column = startingColumn;

        while (true)
        {
            Terminal::SetCursorPosition(static_cast<int16_t>(gridLeftPad + (column * gridElementWidth)), static_cast<int16_t>(gridTopPad + (row * gridElementHeight)));

            keyPress = Terminal::GetNextKeyPress();

            if (keyPress == g_QUIT_KEY)
            {
                Terminal::SetCursorVisibility(false);
                throw Exceptions::QuitGame();
            }

            if (keyPress == g_ENTER_KEY)
            {
                Terminal::SetCursorVisibility(false);
                return {row, column};
            }

            if (keyPress == g_UP_ARROW_KEY)
            {
                row == 0 ? row = maxRow : --row;
            }

            else if (keyPress == g_DOWN_ARROW_KEY)
            {
                row == maxRow ? row = 0 : ++row;
            }

            else if (keyPress == g_LEFT_ARROW_KEY)
            {
                column == 0 ? column = maxColumn : --column;
            }

            else if (keyPress == g_RIGHT_ARROW_KEY)
            {
                column == maxColumn ? column = 0 : ++column;
            }
        }
    }

    void Terminal::PrintOutput(const std::string &output)
    {
        Clear();
        std::cout << output;
    }

    void Terminal::Clear()
    {
        // Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
        const COORD homeCoords = {0, 0};
        CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
        DWORD count = 0;
        DWORD cellCount = 0;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE)
        {
            std::exit(1); // NOLINT(concurrency-mt-unsafe)
        }

        // Get the number of cells in the current buffer
        if (!static_cast<bool>(GetConsoleScreenBufferInfo(hStdOut, &consoleScreenBufferInfo)))
        {
            std::exit(2); // NOLINT(concurrency-mt-unsafe)
        }
        cellCount = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

        // Fill the entire buffer with spaces
        if (!FillConsoleOutputCharacter(hStdOut, ' ', cellCount, homeCoords, &count))
        {
            std::exit(3); // NOLINT(concurrency-mt-unsafe)
        }

        // Fill the entire buffer with the current colors and attributes
        if (!static_cast<bool>(FillConsoleOutputAttribute(hStdOut, consoleScreenBufferInfo.wAttributes, cellCount, homeCoords, &count)))
        {
            std::exit(4); // NOLINT(concurrency-mt-unsafe)
        }

        // Move the cursor home
        SetConsoleCursorPosition(hStdOut, homeCoords);
    }

    uint32_t Terminal::GetNextKeyPress()
    {
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return _getch();
    }

    void Terminal::SetCursorVisibility(const bool &cursorVisibility)
    {
        const CONSOLE_CURSOR_INFO cursorInfo(g_CURSOR_WIDTH_PERCENTAGE, static_cast<int>(cursorVisibility));
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
    }

    void Terminal::SetCursorPosition(const int16_t &xCoord, const int16_t &yCoord)
    {
        const COORD cursorPosition(xCoord, yCoord);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
    }
} // namespace TerminalGames
// NOLINTEND(misc-include-cleaner)

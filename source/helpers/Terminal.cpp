// NOLINTBEGIN(misc-include-cleaner)
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#ifdef _WIN32
#include "conio.h"
#include "Windows.h"
#endif

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    uint32_t Terminal::GetUserChoiceFromMainMenus(const std::vector<std::string> &menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case g_QUIT_KEY:
                throw Exceptions::QuitMainMenu();

            case g_ENTER_KEY:
                return currentSelection;

            case g_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (menus.size() - 1) : --currentSelection;
                break;

            case g_DOWN_ARROW_KEY:
                currentSelection == (menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    uint32_t Terminal::GetUserChoiceFromGameMenus(const std::vector<std::string> &menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case g_QUIT_KEY:
                throw Exceptions::QuitGame();

            case g_ENTER_KEY:
                return currentSelection;

            case g_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (menus.size() - 1) : --currentSelection;
                break;

            case g_DOWN_ARROW_KEY:
                currentSelection == (menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    // NOLINTBEGIN (bugprone-easily-swappable-parameters)
    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGrid(
        const PageBuilder &pageBuilder,
        const GameInfo &gameInfo,
        const uint32_t &startingRow,
        const uint32_t &startingColumn,
        const uint32_t &maxRow,
        const uint32_t &maxColumn,
        const uint32_t &gridLeftPad,
        const uint32_t &gridTopPad,
        const uint32_t &gridElementWidth,
        const uint32_t &gridElementHeight,
        const bool & displayGetUserCommandPage)
    // NOLINTEND (bugprone-easily-swappable-parameters)
    {
        if (displayGetUserCommandPage)
        {
            PrintOutput(pageBuilder.GetUserCommandPage(gameInfo));
        }

        uint32_t row = startingRow;
        uint32_t column = startingColumn;

        while (true)
        {
#ifdef _WIN32
            SetCursorVisibility(true);
            SetCursorPosition(static_cast<int16_t>(gridLeftPad + (column * gridElementWidth)), static_cast<int16_t>(gridTopPad + (row * gridElementHeight)));
#else
            GameInfo currentGameInfo = gameInfo;

            switch (pageBuilder.GetCurrentPage())
            {
            case Pages::TICTACTOE:
                currentGameInfo.ticTacToeStruct.gameGrid[row][column][0] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                currentGameInfo.ticTacToeStruct.gameGrid[row][column][2] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                break;

            case Pages::BATTLESHIPS:
                if (displayGetUserCommandPage)
                {
                    currentGameInfo.battleshipsStruct.boardTwo[row][column][0] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                    currentGameInfo.battleshipsStruct.boardTwo[row][column][2] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                }

                else
                {
                    currentGameInfo.battleshipsStruct.boardOne[row][column][0] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                    currentGameInfo.battleshipsStruct.boardOne[row][column][2] = '#'; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                }
                break;

            default:
                break;
            }

            PrintOutput(pageBuilder.GetUserCommandPage(currentGameInfo));
#endif
            switch (GetNextKeyPress())
            {
            case g_QUIT_KEY:
                SetCursorVisibility(false);
                throw Exceptions::QuitGame();

            case g_BACKSPACE_KEY:
                SetCursorVisibility(false);
                throw Exceptions::BackspaceKeyPressed();

            case g_ENTER_KEY:
                SetCursorVisibility(false);
                return {row, column};

            case g_UP_ARROW_KEY:
                row == 0 ? row = maxRow : --row;
                break;

            case g_DOWN_ARROW_KEY:
                row == maxRow ? row = 0 : ++row;
                break;

            case g_LEFT_ARROW_KEY:
                column == 0 ? column = maxColumn : --column;
                break;

            case g_RIGHT_ARROW_KEY:
                column == maxColumn ? column = 0 : ++column;
                break;

            default:
                break;
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
#ifdef _WIN32
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
#else
        std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
#endif
    }

    uint32_t Terminal::GetNextKeyPress()
    {
#ifdef _WIN32
        FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
        return _getch();
#else
        std::string inputString;

        while (true)
        {
            std::getline(std::cin, inputString);

            if (inputString.size() != 1)
            {
                continue;
            }

            switch (inputString[0])
            {
            case g_ALTERNATIVE_BACKSPACE_KEY:
                return g_BACKSPACE_KEY;

            case g_ALTERNATIVE_ENTER_KEY:
                return g_ENTER_KEY;

            case g_ALTERNATIVE_UP_ARROW_KEY:
                return g_UP_ARROW_KEY;

            case g_ALTERNATIVE_DOWN_ARROW_KEY:
                return g_DOWN_ARROW_KEY;

            case g_ALTERNATIVE_LEFT_ARROW_KEY:
                return g_LEFT_ARROW_KEY;

            case g_ALTERNATIVE_RIGHT_ARROW_KEY:
                return g_RIGHT_ARROW_KEY;


            default:
                return inputString[0];
            }
        }
#endif
    }

    void Terminal::SetCursorVisibility(const bool &cursorVisibility)
    {
#ifdef _WIN32
        const CONSOLE_CURSOR_INFO cursorInfo(g_CURSOR_WIDTH_PERCENTAGE, static_cast<int>(cursorVisibility));
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
#endif
    }

    void Terminal::SetCursorPosition(const int16_t &xCoord, const int16_t &yCoord)
    {
#ifdef _WIN32
        const COORD cursorPosition(xCoord, yCoord);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPosition);
#endif
    }
} // namespace TerminalGames
// NOLINTEND(misc-include-cleaner)

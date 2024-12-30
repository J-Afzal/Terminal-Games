// NOLINTBEGIN(misc-include-cleaner)
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>
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
    uint32_t Terminal::GetUserChoiceFromMainMenus(const std::vector<std::string>& p_menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case G_QUIT_KEY:
                throw Exceptions::QuitMainMenu();

            case G_ENTER_KEY:
                return currentSelection;

            case G_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case G_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    uint32_t Terminal::GetUserChoiceFromGameMenus(const std::vector<std::string>& p_menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case G_QUIT_KEY:
                throw Exceptions::QuitGame();

            case G_ENTER_KEY:
                return currentSelection;

            case G_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case G_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGrid(
        const std::tuple<uint32_t, uint32_t>& p_startingGridLocation,
        const PageBuilder& p_pageBuilder,
        const GameInfo& p_gameInfo,
        const bool& p_displayGetUserCommandPage)
    {
        if (p_displayGetUserCommandPage)
        {
            PrintOutput(p_pageBuilder.GetUserCommandPage(p_gameInfo));
        }

        uint32_t currentRow = std::get<0>(p_startingGridLocation);
        uint32_t currentColumn = std::get<1>(p_startingGridLocation);
        uint32_t maxRow = 0;
        uint32_t maxColumn = 0;

        switch (p_pageBuilder.GetCurrentPage())
        {
        case Pages::TICTACTOE:
            maxColumn = G_TICTACTOE_BOARD_WIDTH - 1;
            maxRow = G_TICTACTOE_BOARD_HEIGHT - 1;
            break;

        case Pages::BATTLESHIPS:
            maxColumn = G_BATTLESHIPS_BOARD_WIDTH - 1;
            maxRow = G_BATTLESHIPS_BOARD_HEIGHT - 1;
            break;

        default:
            break;
        }

        while (true)
        {
#ifdef _WIN32

            uint32_t gridLeftPad = 0;
            uint32_t gridTopPad = 0;
            uint32_t gridElementWidth = 0;
            uint32_t gridElementHeight = 0;

            switch (p_pageBuilder.GetCurrentPage())
            {
            case Pages::TICTACTOE:
                maxColumn = G_TICTACTOE_BOARD_WIDTH - 1;
                maxRow = G_TICTACTOE_BOARD_HEIGHT - 1;
                gridLeftPad = G_TICTACTOE_GRID_LEFT_PAD;
                gridTopPad = G_TICTACTOE_GRID_TOP_PAD;
                gridElementWidth = G_TICTACTOE_GRID_ELEMENT_WIDTH;
                gridElementHeight = G_TICTACTOE_GRID_ELEMENT_HEIGHT;
                break;

            case Pages::BATTLESHIPS:
                maxColumn = G_BATTLESHIPS_BOARD_WIDTH - 1;
                maxRow = G_BATTLESHIPS_BOARD_HEIGHT - 1;
                gridLeftPad = G_BATTLESHIPS_GRID_LEFT_PAD;
                gridTopPad = G_BATTLESHIPS_GRID_TOP_PAD;
                gridElementWidth = G_BATTLESHIPS_GRID_ELEMENT_WIDTH;
                gridElementHeight = G_BATTLESHIPS_GRID_ELEMENT_HEIGHT;
                break;

            default:
                break;
            }
            SetCursorVisibility(true);
            SetCursorPosition({static_cast<int16_t>(gridLeftPad + (currentColumn * gridElementWidth)), static_cast<int16_t>(gridTopPad + (currentRow * gridElementHeight))});
#else
            GameInfo currentGameInfo = p_gameInfo;

            switch (p_pageBuilder.GetCurrentPage())
            {
            case Pages::TICTACTOE:
                currentGameInfo.m_ticTacToeStruct.m_gameGrid.at(currentRow).at(currentColumn).at(0) = '#';
                currentGameInfo.m_ticTacToeStruct.m_gameGrid.at(currentRow).at(currentColumn).at(2) = '#';
                break;

            case Pages::BATTLESHIPS:
                if (p_displayGetUserCommandPage)
                {
                    currentGameInfo.m_battleshipsStruct.m_boardTwo.at(currentRow).at(currentColumn).at(0) = '#';
                    currentGameInfo.m_battleshipsStruct.m_boardTwo.at(currentRow).at(currentColumn).at(2) = '#';
                }

                else
                {
                    currentGameInfo.m_battleshipsStruct.m_boardOne.at(currentRow).at(currentColumn).at(0) = '#';
                    currentGameInfo.m_battleshipsStruct.m_boardOne.at(currentRow).at(currentColumn).at(2) = '#';
                }
                break;

            default:
                break;
            }

            PrintOutput(p_pageBuilder.GetUserCommandPage(currentGameInfo));
#endif
            switch (GetNextKeyPress())
            {
            case G_QUIT_KEY:
                SetCursorVisibility(false);
                throw Exceptions::QuitGame();

            case G_BACKSPACE_KEY:
                SetCursorVisibility(false);
                throw Exceptions::BackspaceKeyPressed();

            case G_ENTER_KEY:
                SetCursorVisibility(false);
                return {currentRow, currentColumn};

            case G_UP_ARROW_KEY:
                currentRow == 0 ? currentRow = maxRow : --currentRow;
                break;

            case G_DOWN_ARROW_KEY:
                currentRow == maxRow ? currentRow = 0 : ++currentRow;
                break;

            case G_LEFT_ARROW_KEY:
                currentColumn == 0 ? currentColumn = maxColumn : --currentColumn;
                break;

            case G_RIGHT_ARROW_KEY:
                currentColumn == maxColumn ? currentColumn = 0 : ++currentColumn;
                break;

            default:
                break;
            }
        }
    }

    void Terminal::PrintOutput(const std::string& p_output)
    {
        Clear();
        std::cout << p_output;
    }

    void Terminal::Clear()
    {
#ifdef _WIN32
        // Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
        const COORD HOME_COORDS = {0, 0};
        CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
        DWORD count = 0;
        DWORD cellCount = 0;

        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hStdOut == INVALID_HANDLE_VALUE)
        {
            std::exit(1);
        }

        // Get the number of cells in the current buffer
        if (!static_cast<bool>(GetConsoleScreenBufferInfo(hStdOut, &consoleScreenBufferInfo)))
        {
            std::exit(2);
        }
        cellCount = consoleScreenBufferInfo.dwSize.X * consoleScreenBufferInfo.dwSize.Y;

        // Fill the entire buffer with spaces
        if (!FillConsoleOutputCharacter(hStdOut, ' ', cellCount, HOME_COORDS, &count))
        {
            std::exit(3);
        }

        // Fill the entire buffer with the current colors and attributes
        if (!static_cast<bool>(FillConsoleOutputAttribute(hStdOut, consoleScreenBufferInfo.wAttributes, cellCount, HOME_COORDS, &count)))
        {
            std::exit(4);
        }

        // Move the cursor home
        SetConsoleCursorPosition(hStdOut, HOME_COORDS);
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
            case G_ALTERNATIVE_BACKSPACE_KEY:
                return G_BACKSPACE_KEY;

            case G_ALTERNATIVE_ENTER_KEY:
                return G_ENTER_KEY;

            case G_ALTERNATIVE_UP_ARROW_KEY:
                return G_UP_ARROW_KEY;

            case G_ALTERNATIVE_DOWN_ARROW_KEY:
                return G_DOWN_ARROW_KEY;

            case G_ALTERNATIVE_LEFT_ARROW_KEY:
                return G_LEFT_ARROW_KEY;

            case G_ALTERNATIVE_RIGHT_ARROW_KEY:
                return G_RIGHT_ARROW_KEY;

            default:
                return inputString[0];
            }
        }
#endif
    }

    void Terminal::SetCursorVisibility(const bool& p_cursorVisibility)
    {
#ifdef _WIN32
        const CONSOLE_CURSOR_INFO CURSOR_INFO(G_CURSOR_WIDTH_PERCENTAGE, static_cast<int>(p_cursorVisibility));
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURSOR_INFO);
#endif
    }

    void Terminal::SetCursorPosition(const std::tuple<int16_t, int16_t>& p_coords)
    {
#ifdef _WIN32
        const COORD CURSOR_POSITION(std::get<0>(p_coords), std::get<1>(p_coords));
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CURSOR_POSITION);
#endif
    }
}

// NOLINTEND(misc-include-cleaner)

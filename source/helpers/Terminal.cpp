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

#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    bool Terminal::GetUserChoiceFromHomepage(const std::vector<std::string> &p_menus, const bool &p_useAnsiEscapeCodes)
    {
        // Yes option selected is at index 0 and No option selected is at index 1. Therefore, can convert the current selected
        // index to a bool and invert it to get whether to use ANSI escape codes.
        uint32_t currentSelection = static_cast<uint32_t>(!p_useAnsiEscapeCodes);

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                throw Globals::Exceptions::QuitProgram();

            case Globals::G_TERMINAL_ENTER_KEY:
                return !static_cast<bool>(currentSelection);

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    uint32_t Terminal::GetUserChoiceFromMainMenus(const std::vector<std::string> &p_menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                throw Globals::Exceptions::QuitMainMenu();

            case Globals::G_TERMINAL_ENTER_KEY:
                return currentSelection;

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    uint32_t Terminal::GetUserChoiceFromGameMenus(const std::vector<std::string> &p_menus, const std::vector<std::string> &p_quitOptionMenus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                Terminal::GetUserChoiceFromQuitMenus(p_quitOptionMenus);
                break;

            case Globals::G_TERMINAL_ENTER_KEY:
                return currentSelection;

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGrid(
        const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
        const PageBuilder &p_pageBuilder,
        const GameInfo &p_gameInfo,
        const bool &p_displayGetUserCommandPage)
    {
        if (Globals::G_PLATFORM_IS_WINDOWS)
        {
            return GetUserCommandFromGameGridWindows(p_startingGridLocation, p_pageBuilder, p_gameInfo, p_displayGetUserCommandPage);
        }

        return GetUserCommandFromGameGridNonWindows(p_startingGridLocation, p_pageBuilder, p_gameInfo, p_displayGetUserCommandPage);
    }

    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGridWindows(
        const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
        const PageBuilder &p_pageBuilder,
        const GameInfo &p_gameInfo,
        const bool &p_displayGetUserCommandPage)
    {
        PageBuilder pageBuilder = p_pageBuilder;
        uint32_t currentRow = std::get<0>(p_startingGridLocation);
        uint32_t currentColumn = std::get<1>(p_startingGridLocation);
        uint32_t maxRow = 0;
        uint32_t maxColumn = 0;
        uint32_t gridLeftPad = 0;
        uint32_t gridTopPad = 0;
        uint32_t gridElementWidth = 0;
        uint32_t gridElementHeight = 0;

        switch (p_pageBuilder.GetCurrentPageType())
        {
        case Pages::TICTACTOE:
        {
            maxColumn = Globals::G_TICTACTOE_GRID_WIDTH - 1; // -1 to account for zero-indexing
            maxRow = Globals::G_TICTACTOE_GRID_HEIGHT - 1;   // -1 to account for zero-indexing
            gridLeftPad = Globals::G_TICTACTOE_GRID_LEFT_PAD;
            gridTopPad = Globals::G_TICTACTOE_GRID_TOP_PAD;
            gridElementWidth = Globals::G_TICTACTOE_GRID_ELEMENT_WIDTH + 1;   // +1 to account for the grid divider '|'
            gridElementHeight = Globals::G_TICTACTOE_GRID_ELEMENT_HEIGHT + 1; // +1 to account for the grid divider '───'
            break;
        }

        case Pages::BATTLESHIPS:
        {
            maxColumn = Globals::G_BATTLESHIPS_BOARD_WIDTH - 1; // -1 to account for zero-indexing
            maxRow = Globals::G_BATTLESHIPS_BOARD_HEIGHT - 1;   // -1 to account for zero-indexing
            gridLeftPad = p_displayGetUserCommandPage ? Globals::G_BATTLESHIPS_GRID_PLAYER_TWO_BOARD_LEFT_PAD : Globals::G_BATTLESHIPS_GRID_PLAYER_ONE_BOARD_LEFT_PAD;
            gridTopPad = Globals::G_BATTLESHIPS_GRID_TOP_PAD;
            gridElementWidth = Globals::G_BATTLESHIPS_GRID_ELEMENT_WIDTH + 1;   // +1 to account for the grid divider '|'
            gridElementHeight = Globals::G_BATTLESHIPS_GRID_ELEMENT_HEIGHT + 1; // +1 to account for the grid divider '───'
            break;
        }

        default:
            throw Globals::Exceptions::NotImplementedError();
        }

        if (p_displayGetUserCommandPage)
        {
            PrintOutput(pageBuilder.GetUserCommandPage(p_gameInfo));
        }

        while (true)
        {
            SetCursorVisibility(true);
            SetCursorPosition(static_cast<int16_t>(gridLeftPad + (currentColumn * gridElementWidth)), static_cast<int16_t>(gridTopPad + (currentRow * gridElementHeight)));

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                SetCursorVisibility(false);
                Terminal::GetUserChoiceFromQuitMenus(pageBuilder.GetQuitOptionSelectionPage());
                SetCursorVisibility(true);
                break;

            case Globals::G_TERMINAL_BACKSPACE_KEY:
                SetCursorVisibility(false);
                throw Globals::Exceptions::BackspaceKeyPressed();

            case Globals::G_TERMINAL_ENTER_KEY:
                SetCursorVisibility(false);
                return {currentRow, currentColumn};

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentRow == 0 ? currentRow = maxRow : --currentRow;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentRow == maxRow ? currentRow = 0 : ++currentRow;
                break;

            case Globals::G_TERMINAL_LEFT_ARROW_KEY:
                currentColumn == 0 ? currentColumn = maxColumn : --currentColumn;
                break;

            case Globals::G_TERMINAL_RIGHT_ARROW_KEY:
                currentColumn == maxColumn ? currentColumn = 0 : ++currentColumn;
                break;

            default:
                break;
            }
        }
    }

    std::tuple<uint32_t, uint32_t> Terminal::GetUserCommandFromGameGridNonWindows(
        const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
        const PageBuilder &p_pageBuilder,
        const GameInfo &p_gameInfo,
        const bool &p_displayGetUserCommandPage)
    {
        const Pages CURRENT_PAGE_TYPE = p_pageBuilder.GetCurrentPageType();
        PageBuilder pageBuilder = p_pageBuilder;
        uint32_t currentRow = std::get<0>(p_startingGridLocation);
        uint32_t currentColumn = std::get<1>(p_startingGridLocation);
        uint32_t maxRow = 0;
        uint32_t maxColumn = 0;

        switch (CURRENT_PAGE_TYPE)
        {
        case Pages::TICTACTOE:
            maxColumn = Globals::G_TICTACTOE_GRID_WIDTH - 1; // -1 to account for zero-indexing
            maxRow = Globals::G_TICTACTOE_GRID_HEIGHT - 1;   // -1 to account for zero-indexing
            break;

        case Pages::BATTLESHIPS:
            maxColumn = Globals::G_BATTLESHIPS_BOARD_WIDTH - 1; // -1 to account for zero-indexing
            maxRow = Globals::G_BATTLESHIPS_BOARD_HEIGHT - 1;   // -1 to account for zero-indexing
            break;

        default:
            throw Globals::Exceptions::NotImplementedError();
        }

        while (true)
        {
            GameInfo currentGameInfo = p_gameInfo;

            if (CURRENT_PAGE_TYPE == Pages::TICTACTOE)
            {
                currentGameInfo.m_ticTacToeGameInfo.m_gameGrid.at(currentRow).at(currentColumn) = "#" + std::string(1, currentGameInfo.m_ticTacToeGameInfo.m_gameGrid.at(currentRow).at(currentColumn).at(1)) + "#";
            }

            else if (CURRENT_PAGE_TYPE == Pages::BATTLESHIPS && p_displayGetUserCommandPage)
            {
                currentGameInfo.m_battleshipsGameInfo.m_boardPlayerTwo.at(currentRow).at(currentColumn) = "#" + std::string(1, currentGameInfo.m_battleshipsGameInfo.m_boardPlayerTwo.at(currentRow).at(currentColumn).at(0)) + "#";
            }

            else if (CURRENT_PAGE_TYPE == Pages::BATTLESHIPS)
            {
                currentGameInfo.m_battleshipsGameInfo.m_boardPlayerOne.at(currentRow).at(currentColumn) = "#" + std::string(1, currentGameInfo.m_battleshipsGameInfo.m_boardPlayerOne.at(currentRow).at(currentColumn).at(0)) + "#";
            }

            if (p_displayGetUserCommandPage)
            {
                PrintOutput(pageBuilder.GetUserCommandPage(currentGameInfo));
            }

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                SetCursorVisibility(false);
                Terminal::GetUserChoiceFromQuitMenus(pageBuilder.GetQuitOptionSelectionPage());
                SetCursorVisibility(true);
                break;

            case Globals::G_TERMINAL_BACKSPACE_KEY:
                SetCursorVisibility(false);
                throw Globals::Exceptions::BackspaceKeyPressed();

            case Globals::G_TERMINAL_ENTER_KEY:
                SetCursorVisibility(false);
                return {currentRow, currentColumn};

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentRow == 0 ? currentRow = maxRow : --currentRow;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentRow == maxRow ? currentRow = 0 : ++currentRow;
                break;

            case Globals::G_TERMINAL_LEFT_ARROW_KEY:
                currentColumn == 0 ? currentColumn = maxColumn : --currentColumn;
                break;

            case Globals::G_TERMINAL_RIGHT_ARROW_KEY:
                currentColumn == maxColumn ? currentColumn = 0 : ++currentColumn;
                break;

            default:
                break;
            }
        }
    }

    void Terminal::GetUserChoiceFromGameOverMenu(const std::string &p_gameOverPage, const std::vector<std::string> &p_quitOptionMenus)
    {
        while (true)
        {
            PrintOutput(p_gameOverPage);

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_QUIT_KEY:
                GetUserChoiceFromQuitMenus(p_quitOptionMenus);
                break;

            case Globals::G_TERMINAL_RESTART_KEY:
                throw Globals::Exceptions::RestartGame();

            default:
                throw Globals::Exceptions::ResetGame();
            }
        }
    }

    void Terminal::GetUserChoiceFromQuitMenus(const std::vector<std::string> &p_menus)
    {
        uint32_t currentSelection = 0;

        while (true)
        {
            PrintOutput(p_menus[currentSelection]);

            switch (GetNextKeyPress())
            {
            case Globals::G_TERMINAL_ENTER_KEY:
                switch (currentSelection)
                {
                case Globals::G_QUIT_MENU_RESTART_GAME_INDEX:
                    throw Globals::Exceptions::RestartGame();

                case Globals::G_QUIT_MENU_RESET_GAME_INDEX:
                    throw Globals::Exceptions::ResetGame();

                case Globals::G_QUIT_MENU_QUIT_GAME_INDEX:
                    throw Globals::Exceptions::QuitGame();

                case Globals::G_QUIT_MENU_QUIT_MAIN_MENU_INDEX:
                    throw Globals::Exceptions::QuitMainMenu();

                case Globals::G_QUIT_MENU_QUIT_PROGRAM_INDEX:
                    throw Globals::Exceptions::QuitProgram();

                case Globals::G_QUIT_MENU_CANCEL_INDEX:
                    return;

                default:
                    break;
                }

            case Globals::G_TERMINAL_UP_ARROW_KEY:
                currentSelection == 0 ? currentSelection = (p_menus.size() - 1) : --currentSelection;
                break;

            case Globals::G_TERMINAL_DOWN_ARROW_KEY:
                currentSelection == (p_menus.size() - 1) ? currentSelection = 0 : ++currentSelection;
                break;

            default:
                break;
            }
        }
    }

    void Terminal::PrintOutput(const std::string &p_output)
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
            case Globals::G_TERMINAL_ALTERNATIVE_ENTER_KEY:
                return Globals::G_TERMINAL_ENTER_KEY;

            case Globals::G_TERMINAL_ALTERNATIVE_BACKSPACE_KEY:
                return Globals::G_TERMINAL_BACKSPACE_KEY;

            case Globals::G_TERMINAL_ALTERNATIVE_UP_ARROW_KEY:
                return Globals::G_TERMINAL_UP_ARROW_KEY;

            case Globals::G_TERMINAL_ALTERNATIVE_DOWN_ARROW_KEY:
                return Globals::G_TERMINAL_DOWN_ARROW_KEY;

            case Globals::G_TERMINAL_ALTERNATIVE_LEFT_ARROW_KEY:
                return Globals::G_TERMINAL_LEFT_ARROW_KEY;

            case Globals::G_TERMINAL_ALTERNATIVE_RIGHT_ARROW_KEY:
                return Globals::G_TERMINAL_RIGHT_ARROW_KEY;

            default:
                return inputString[0];
            }
        }
#endif
    }

    void Terminal::SetCursorVisibility(const bool &p_cursorVisibility)
    {
#ifdef _WIN32
        const CONSOLE_CURSOR_INFO CURSOR_INFO(Globals::G_TERMINAL_CURSOR_WIDTH_PERCENTAGE, static_cast<int>(p_cursorVisibility));
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CURSOR_INFO);
#endif
    }

    void Terminal::SetCursorPosition(const int16_t &p_xCoord, const int16_t &p_yCoord)
    {
#ifdef _WIN32
        const COORD CURSOR_POSITION(p_xCoord, p_yCoord);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CURSOR_POSITION);
#endif
    }

    void Terminal::InitialiseTerminal()
    {
        Clear();
        SetCursorVisibility(false);
    }

    void Terminal::ResetTerminal()
    {
        Clear();
        SetCursorVisibility(true);
    }
}

// NOLINTEND(misc-include-cleaner)

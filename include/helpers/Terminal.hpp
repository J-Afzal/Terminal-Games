#pragma once

#include <cstdint>
#include <string>
#include <tuple>
#include <vector>

#include "helpers/PageBuilder.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @brief The Terminal class handles all terminal related tasks such as getting user input, outputting to the terminal,
     * clearing the terminal, etc.
     */
    class Terminal
    {
    public:
        /**
         * @brief Disable constructing a Terminal object.
         */
        Terminal() = delete;

        /**
         * @brief Get the user choice from a list of homepage screens that are printed to the terminal.
         *
         * @param p_menus An array of screens used to print the current option selected to the terminal. The screen chosen
         * depends on user input. The only difference between each screen is the selected option.
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         * @return `true` If to use ANSI escape codes.
         * @return `false` If to not use ANSI escape code (only use extended ASCII characters).
         * @exception Globals::Exceptions::QuitProgram When the user presses the Globals::G_TERMINAL_QUIT_KEY.
         */
        static bool GetUserChoiceFromHomepage(const std::vector<std::string> &p_menus, const bool &p_useAnsiEscapeCodes);

        /**
         * @brief Get the user choice from a list of main menus screens that are printed to the terminal.
         *
         * @param p_menus An array of screens used to print the current option selected to the terminal. The screen chosen
         * depends on user input. The only difference between each screen is the selected option.
         * @return `uint32_t` The index of the menu string that the user selected.
         * @exception Globals::Exceptions::QuitMainMenu When the user presses the Globals::G_TERMINAL_QUIT_KEY.
         */
        static uint32_t GetUserChoiceFromMainMenus(const std::vector<std::string> &p_menus);

        /**
         * @brief Get the user choice from a list of game menus screens that are printed to the terminal.
         *
         * @param p_menus An array of screens used to print the current option selected to the terminal. The screen chosen
         * depends on user input. The only difference between each screen is the selected option.
         * @param p_quitOptionMenus The quit option selection screens returned from `PageBuilder::GetQuitOptionSelectionPage()`.
         * @return `uint32_t` The index of the menu string that the user selected.
         * @exception Globals::Exceptions::RestartGame When the user selects the restart game option from the quit menu.
         * @exception Globals::Exceptions::ResetGame When the user selects the reset game option from the quit menu.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option from the quit menu.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option from the quit menu.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option from the quit menu.
         */
        static uint32_t GetUserChoiceFromGameMenus(const std::vector<std::string> &p_menus, const std::vector<std::string> &p_quitOptionMenus);

        /**
         * @brief Gets a user command based on the currently displayed game grid (wrapper function around the platform-specific
         * `GetUserCommandFromGameGrid()` functions as the Windows variant uses `Windows.h`).
         *
         * @param p_startingGridLocation The initial row and column to place the cursor.
         * @param p_pageBuilder The PageBuilder object to allow for refreshing the terminal based on user input.
         * @param p_gameInfo The GameInfo object to pass to the PageBuilder object.
         * @param p_displayGetUserCommandPage Whether to display the get user command page.
         * @return `std::tuple<uint32_t, uint32_t>` The user command from the user in the form `<row, column>`.
         * @exception Globals::Exceptions::NotImplementedError When the user passes a PageBuilder with a page type not supported
         * by this function.
         * @exception Globals::Exceptions::BackspaceKeyPressed When the user presses the Globals::G_TERMINAL_BACKSPACE_KEY.
         * @exception Globals::Exceptions::RestartGame When the user selects the restart game option from the quit menu.
         * @exception Globals::Exceptions::ResetGame When the user selects the reset game option from the quit menu.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option from the quit menu.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option from the quit menu.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option from the quit menu.
         */
        static std::tuple<uint32_t, uint32_t> GetUserCommandFromGameGrid(
            const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
            const PageBuilder &p_pageBuilder,
            const GameInfo &p_gameInfo,
            const bool &p_displayGetUserCommandPage);

        /**
         * @brief (Windows) Gets a user command based on the currently displayed game grid.
         *
         * @param p_startingGridLocation The initial row and column to place the cursor.
         * @param p_pageBuilder The PageBuilder object to allow for refreshing the terminal based on user input.
         * @param p_gameInfo The GameInfo object to pass to the PageBuilder object.
         * @param p_displayGetUserCommandPage Whether to display the get user command page.
         * @return `std::tuple<uint32_t, uint32_t>` The user command from the user in the form `<row, column>`.
         * @exception Globals::Exceptions::NotImplementedError When the user passes a PageBuilder with a page type not supported
         * by this function.
         * @exception Globals::Exceptions::BackspaceKeyPressed When the user presses the Globals::G_TERMINAL_BACKSPACE_KEY.
         * @exception Globals::Exceptions::RestartGame When the user selects the restart game option from the quit menu.
         * @exception Globals::Exceptions::ResetGame When the user selects the reset game option from the quit menu.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option from the quit menu.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option from the quit menu.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option from the quit menu.
         */
        static std::tuple<uint32_t, uint32_t> GetUserCommandFromGameGridWindows(
            const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
            const PageBuilder &p_pageBuilder,
            const GameInfo &p_gameInfo,
            const bool &p_displayGetUserCommandPage);

        /**
         * @brief (Non-window) Gets a user command based on the currently displayed game grid.
         *
         * @param p_startingGridLocation The initial row and column to place the cursor.
         * @param p_pageBuilder The PageBuilder object to allow for refreshing the terminal based on user input.
         * @param p_gameInfo The GameInfo object to pass to the PageBuilder object.
         * @param p_displayGetUserCommandPage Whether to display the get user command page.
         * @return `std::tuple<uint32_t, uint32_t>` The user command from the user in the form `<row, column>`.
         * @exception Globals::Exceptions::NotImplementedError When the user passes a PageBuilder with a page type not supported
         * by this function.
         * @exception Globals::Exceptions::BackspaceKeyPressed When the user presses the Globals::G_TERMINAL_BACKSPACE_KEY.
         * @exception Globals::Exceptions::RestartGame When the user selects the restart game option from the quit menu.
         * @exception Globals::Exceptions::ResetGame When the user selects the reset game option from the quit menu.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option from the quit menu.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option from the quit menu.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option from the quit menu.
         */
        static std::tuple<uint32_t, uint32_t> GetUserCommandFromGameGridNonWindows(
            const std::tuple<uint32_t, uint32_t> &p_startingGridLocation,
            const PageBuilder &p_pageBuilder,
            const GameInfo &p_gameInfo,
            const bool &p_displayGetUserCommandPage);

        /**
         * @brief Get the user choice whether to restart the game, reset the game or a choice from the
         * GetUserChoiceFromQuitMenus() function.
         *
         * @param p_gameOverPage The game over page to display returned from `PageBuilder::GetGameOverPage()`.
         * @param p_quitOptionMenus The quit option selection pages returned from `PageBuilder::GetQuitOptionSelectionPage()`.
         * @exception Globals::Exceptions::RestartGame When the user presses the Globals::G_TERMINAL_RESTART_KEY or when the
         * user selects the restart game option for the quit menu.
         * @exception Globals::Exceptions::ResetGame When the user presses any key other than the
         * Globals::G_TERMINAL_RESTART_KEY or when the user selects the reset game option from the quit menu.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option from the quit menu.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option from the quit menu.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option from the quit menu.
         */
        static void GetUserChoiceFromGameOverMenu(const std::string &p_gameOverPage, const std::vector<std::string> &p_quitOptionMenus);

        /**
         * @brief Gets the user choice from the quit menu. All user choices result in a different custom exception being thrown
         * except for the "Cancel" option which results in the function returning normally.
         *
         * @param p_menus The quit option selection pages returned from `PageBuilder::GetQuitOptionSelectionPage()`.
         * @exception Globals::Exceptions::RestartGame When the user selects the restart game option.
         * @exception Globals::Exceptions::ResetGame When the user selects the reset game option.
         * @exception Globals::Exceptions::QuitGame When the user selects the quit game option.
         * @exception Globals::Exceptions::QuitMainMenu When the user selects the quit to main menu option.
         * @exception Globals::Exceptions::QuitProgram When the user selects the quit program option.
         */
        static void GetUserChoiceFromQuitMenus(const std::vector<std::string> &p_menus);

        /**
         * @brief Clears and then prints to the terminal.
         *
         * @param p_output The string to output to the terminal.
         */
        static void PrintOutput(const std::string &p_output);

        /**
         * @brief Clears the terminal based on this article: https://www.cplusplus.com/articles/4z18T05o
         */
        static void Clear();

        /**
         * @brief Wrapper for `<Windows.h>` API for the `FlushConsoleInputBuffer()` and `_getch()` functions.
         *
         * @return `uint32_t` The key which was pressed represented as an integer.
         */
        static uint32_t GetNextKeyPress();

        /**
         * @brief Wrapper around the `<Windows.h>` API for the `SetConsoleCursorInfo()` function.
         *
         * @param p_cursorVisibility Whether the cursor should be visible (true) or not (false).
         */
        static void SetCursorVisibility(const bool &p_cursorVisibility);

        /**
         * @brief Wrapper around the `<Windows.h>` API for the `SetConsoleCursorPosition()` function.
         *
         * @param p_xCoord The horizontal position to set the cursor to.
         * @param p_yCoord The vertical position to set the cursor to.
         */
        static void SetCursorPosition(const int16_t &p_xCoord, const int16_t &p_yCoord);

        /**
         * @brief Initialises the terminal for the program.
         */
        static void InitialiseTerminal();

        /**
         * @brief Resets the terminal to its original state before the program was run.
         */
        static void ResetTerminal();
    };
}

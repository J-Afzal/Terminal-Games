#pragma once

#include <memory>
#include <string>
#include <vector>

#include "games/Game.hpp"

/**
 * @namespace TerminalGames
 * @brief Contains all Terminal-Games objects.
 */
namespace TerminalGames
{
    /**
     * @class MainMenu
     * @brief Orchestration class which runs the homepage and the main menu pages which allow for games to be ran.
     */
    class MainMenu
    {
    public:
        /**
         * @brief Constructs a new MainMenu object (for API use).
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        explicit MainMenu(const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Constructs a new MainMenu object (for CLI use).
         *
         * @param p_commandLineArguments List of all command line arguments.
         */
        explicit MainMenu(const std::vector<std::string>& p_commandLineArguments);

        /**
         * @brief Destructs a MainMenu object.
         */
        ~MainMenu();

        /**
         * @brief Orchestration function which contains the main program loop.
         */
        void Run();

        /**
         * @brief Disable constructing a new Main Menu object with no arguments.
         */
        MainMenu() = delete;

        /**
         * @brief Disable constructing a new MainMenu object using copy constructor.
         *
         * @param p_mainMenu The MainMenu to copy.
         */
        MainMenu(const MainMenu& p_mainMenu) = delete;

        /**
         * @brief Disable constructing a new MainMenu object using move constructor.
         *
         * @param p_mainMenu The MainMenu to copy.
         */
        MainMenu(const MainMenu&& p_mainMenu) = delete;

        /**
         * @brief Disable constructing a new MainMenu object using copy assignment operator.
         *
         * @param p_mainMenu The MainMenu to copy.
         */
        MainMenu& operator=(const MainMenu& p_mainMenu) = delete;

        /**
         * @brief Disable constructing a new MainMenu object using move assignment operator.
         *
         * @param p_mainMenu The MainMenu to copy.
         */
        MainMenu& operator=(const MainMenu&& p_mainMenu) = delete;

    private:
        /**
         * @brief Create the option selection home pages.
         */
        void SetupHomepages();

        /**
         * @brief Create the main menu game selection pages and the game array.
         */
        void SetupMainMenuPagesAndGames();

        /**
         * @brief Parses the command line arguments. Below is the help message:
         *
         * Usage: terminal-games [options]
         *
         * OPTIONS:
         *
         * Generic Options:
         *
         *   --h --help        Display available options.
         *
         * terminal-games options:
         *
         *   --a --ascii-only  Only use extended ASCII characters (this removes all colour).
         *
         * @param p_commandLineArguments The command line arguments.
         * @return true If to use use ANSI escapes codes
         * @return false If to only use extended ASCII characters
         */
        static bool ParseCommandLineArguments(const std::vector<std::string>& p_commandLineArguments);

        /**
         * @brief Games that can be selected and played.
         */
        std::vector<std::unique_ptr<Game>> m_games;

        /**
         * @brief Contains the different options available on the homepage.
         */
        std::vector<std::string> m_homepages;

        /**
         * @brief Contains the different options available on the main menu page.
         */
        std::vector<std::string> m_mainMenus;

        /**
         * @brief Whether to use use ANSI escapes codes (true) or only extended ASCII characters (false).
         */
        bool m_useAnsiEscapeCodes;
    };
}

#pragma once

#include <memory>
#include <string>
#include <vector>

#include "games/Game.hpp"

namespace TerminalGames
{
    /**
     * @brief Orchestration class for Terminal-Games.
     */
    class MainMenu
    {
    public:
        /**
         * @brief Constructs a new MainMenu object (for CLI use).
         *
         * @param p_commandLineArguments List of all command line arguments
         */
        explicit MainMenu(const std::vector<std::string>& p_commandLineArguments);

        /**
         * @brief Constructs a new MainMenu object.
         *
         * @param p_useAnsiEscapeCodes Whether to use use ANSI escapes codes (true) or only ASCII characters (false).
         */
        explicit MainMenu(const bool& p_useAnsiEscapeCodes);

        /**
         * @brief Destruct a MainMenu object.
         */
        ~MainMenu();

        /**
         * @brief Orchestration function for Terminal-Games.
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
         * @brief Create option selection home pages.
         */
        void SetupHomepages();

        /**
         * @brief Create main menu game selection pages and game array.
         */
        void SetupMainMenuPagesAndGames();

        /**
         * @brief Parses the passed in command line arguments.
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
         *   --a --ascii-only  Only use ASCII characters (this removes all colour).
         *
         * @param p_commandLineArguments List of all command line arguments
         */
        static bool ParseCommandLineArguments(const std::vector<std::string>& p_commandLineArguments);

        std::vector<std::unique_ptr<Game>> m_games;
        std::vector<std::string> m_homepages;
        std::vector<std::string> m_mainMenus;
        bool m_useAnsiEscapeCodes;
    };
}

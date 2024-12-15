#pragma once

#include <memory>
#include <string>
#include <vector>

#include "games/Game.hpp"

/**
 * @brief Orchestration class for Terminal-Games.
 */
class MainMenu
{
public:
    /**
     * @brief Construct a new MainMenu object (CLI). Below are the expected arguments.
     * 
     * Usage: Terminal-Games [--a --ascii-only]
     *
     * Options:
     *         --a --ascii-only        Only use ASCII characters.
     * 
     * @param argc Number of command line arguments.
     * @param argv Command line arguments.
     */
    explicit MainMenu(int argc, char* argv[]);

    /**
    * @brief Construct a new MainMenu object.
    * 
    * @param outputIsOnlyASCII Whether to use only ASCII characters (true) or to also use ANSI escapes codes (false).
    */
    explicit MainMenu(const bool& outputIsOnlyASCII = false);

    /**
     * @brief Destruct a MainMenu object.
     */
    ~MainMenu();

    /**
     * @brief Orchestration function for Terminal-Games.
     */
    void Run();

private:
    /**
     * @brief Parses the passed in command line arguments. Below are the expected arguments.
     *
     * Usage: Terminal-Games [--a --ascii-only]
     *
     * Options:
     *         --a --ascii-only        Only use ASCII characters.
     *
     * @param commandLineArguments List of all command line arguments
     */
    bool ParseCommandLineArguments(const std::vector<std::string>& commandLineArguments) const;

    std::vector<std::unique_ptr<Game>> m_games;
    std::vector<std::string> m_mainMenus;
    bool m_outputIsOnlyASCII;
};

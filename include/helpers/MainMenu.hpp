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
     * @brief Construct a new MainMenu object which accepts command line arguements to specify whether to use only 
     * ASCII characters:
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
     * @brief Destruct a MainMenu object.
     */
    ~MainMenu();

    /**
     * @brief Orchestration function for Terminal-Games.
     */
    void Run();

private:

    bool ParseCommandLineArguments(const std::vector<std::string>& cliArgs) const;

    std::vector<std::unique_ptr<Game>> m_games;
    std::vector<std::string> m_mainMenus;
};

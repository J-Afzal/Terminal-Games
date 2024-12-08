#pragma once

#include <array>
#include <vector>

#include "games/Game.hpp"

/**
 * @brief Orchestration class for Terminal-Games.
 */
class MainMenu
{
public:
    /**
     * @brief Construct a new Main Menu object
     * @param outputIsOnlyASCII Whether to use only ASCII characters (true) 
     * or also use ANSI escapes codes (false).
     */
    explicit MainMenu(const bool& outputIsOnlyASCII = false);

    /**
     * @brief Orchestration function for Terminal-Games.
     */
    void Run();

private:
    Terminal m_terminal;
    std::array<std::unique_ptr<Game>, 3> m_games;
    std::vector<std::string> m_menus;
    uint32_t m_currentSelection;
};

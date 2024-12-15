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
     * @brief Construct a new MainMenu object.
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
    std::vector<std::unique_ptr<Game>> m_games;
    std::vector<std::string> m_mainMenus;
};

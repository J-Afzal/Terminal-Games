#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "games/Battleships.hpp"
#include "games/Hangman.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/MainMenu.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

MainMenu::MainMenu(int argc, char* argv[])
{
    const bool outputIsOnlyASCII = ParseCommandLineArguments(std::vector<std::string>(argv, argv + argc));

    PageBuilder PageBuilder(Pages::MAINMENU, outputIsOnlyASCII);
    m_mainMenus = PageBuilder.GetGameSelectionMainMenuPages({"Tic Tac Toe", "Hangman", "Battleships"});

    // The index of games in m_Games should match the index of the string in m_mainMenus which has the game selected,
    // which is defined by the order of the input array to the previous line.
    m_games.push_back(std::make_unique<TicTacToe>(outputIsOnlyASCII));
    m_games.push_back(std::make_unique<Hangman>(outputIsOnlyASCII));
    m_games.push_back(std::make_unique<Battleships>(outputIsOnlyASCII));

    Terminal::SetCursorVisibility(false);
    Terminal::SetCursorPosition(0, 0);
}

MainMenu::~MainMenu()
{
    Terminal::Clear();
    Terminal::SetCursorVisibility(true);
    Terminal::SetCursorPosition(0, 0);
}

void MainMenu::Run()
{
    // Custom exceptions are used to return exit the games and the main menu.
    while (true)
    {
        try { m_games[Terminal::GetUserChoiceFromMainMenus(m_mainMenus)]->Play(); }

        catch (Exceptions::QuitMainMenu& e) { return; }

        catch (Exceptions::QuitGame& e) { continue; }
    }
}

bool MainMenu::ParseCommandLineArguments(const std::vector<std::string>& cliArgs) const
{
    if (cliArgs.size() == 1) // Default if no CLI args given.
        return false;
    
    if (cliArgs.size() == 2 && (cliArgs[0] == "--a" || cliArgs[0] == "--ascii-only"))
        return true;

    std::cout << "\nUsage: Terminal-Games [--a --ascii-only]\n\nOptions:\n\t--a --ascii-only\tOnly use ASCII characters." << std::endl;
    exit(1);
}
 
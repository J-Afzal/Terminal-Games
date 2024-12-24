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

namespace TerminalGames
{
    MainMenu::MainMenu(const std::vector<std::string> &commandLineArguments) : m_onlyUseASCII(ParseCommandLineArguments(commandLineArguments)) {}

    MainMenu::MainMenu(const bool &onlyUseASCII) : m_onlyUseASCII(onlyUseASCII) {}

    bool MainMenu::ParseCommandLineArguments(const std::vector<std::string> &commandLineArguments)
    {
        if (commandLineArguments.size() == 1) // Default if no CLI args given.
        {
            return false;
        }

        if (commandLineArguments.size() == 2 && (commandLineArguments[0] == "--a" || commandLineArguments[0] == "--ascii-only"))
        {
            return true;
        }

        std::cout << "\nUsage: Terminal-Games [--a --ascii-only]\n\nOptions:\n\t--a --ascii-only\tOnly use ASCII characters.\n";
        exit(1); // NOLINT(concurrency-mt-unsafe)
    }

    MainMenu::~MainMenu()
    {
        Terminal::Clear();
        Terminal::SetCursorVisibility(true);
        Terminal::SetCursorPosition(0, 0);
    }

    void MainMenu::Run()
    {
        const PageBuilder PageBuilder(Pages::MAINMENU, m_onlyUseASCII);
        const std::vector<std::string> menus({"Tic Tac Toe", "Hangman", "Battleships"}); // NOLINT(fuchsia-default-arguments-calls)
        m_mainMenus = PageBuilder.GetGameSelectionMainMenuPages(menus);

        // The index of games in m_Games should match the index of the string in m_mainMenus which has the game selected.
        // This is defined by the order of the input array to the previous line.
        m_games.push_back(std::make_unique<TicTacToe>(m_onlyUseASCII));
        m_games.push_back(std::make_unique<Hangman>(m_onlyUseASCII));
        m_games.push_back(std::make_unique<Battleships>(m_onlyUseASCII));

        Terminal::SetCursorVisibility(false);
        Terminal::SetCursorPosition(0, 0);

        // Custom exceptions are used to return exit the games and the main menu.
        while (true)
        {
            try
            {
                m_games[Terminal::GetUserChoiceFromMainMenus(m_mainMenus)]->Play();
            }

            catch (Exceptions::QuitMainMenu &e)
            {
                return;
            }

            catch (Exceptions::QuitGame &e)
            {
                continue;
            }
        }

        Terminal::Clear();
        Terminal::SetCursorVisibility(true);
        Terminal::SetCursorPosition(0, 0);
    }
} // namespace TerminalGames

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "Exceptions.hpp"
#include "games/Battleships.hpp"
#include "games/Hangman.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/MainMenu.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    MainMenu::MainMenu(const std::vector<std::string> &commandLineArguments) : m_onlyUseASCII(ParseCommandLineArguments(commandLineArguments)) {}

    MainMenu::MainMenu(const bool &onlyUseASCII) : m_onlyUseASCII(onlyUseASCII) {}

    MainMenu::~MainMenu()
    {
        Terminal::SetCursorPosition(0, 0);
        Terminal::SetCursorVisibility(true);
        Terminal::Clear();
    }

    void MainMenu::Run()
    {
        const PageBuilder pageBuilder(Pages::MAINMENU, m_onlyUseASCII);
        const std::vector<std::string> menus({"Tic Tac Toe", "Hangman", "Battleships"});
        m_mainMenus = pageBuilder.GetGameSelectionMainMenuPages(menus);

        // The index of games in m_Games should match the index of the string in m_mainMenus which has the game selected. This
        // is defined by the order of the input array to the previous line.
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

    bool MainMenu::ParseCommandLineArguments(const std::vector<std::string> &commandLineArguments)
    {
        for (const std::string &argument : commandLineArguments)
        {
            if (argument == "--a" || argument == "--ascii-only")
            {
                return true;
            }

            if (argument == "--help")
            {
                std::string helpMessage = "\nUsage: terminal-games [options]";
                helpMessage += "\n\nOPTIONS:";
                helpMessage += "\n\nGeneric Options:";
                helpMessage += "\n\n  --help            Display available options.";
                helpMessage += "\n\nterminal-games options:";
                helpMessage += "\n\n  --a --ascii-only  Only use ASCII characters (this removes all colour).\n\n";
                std::cout << helpMessage;
                exit(1); // NOLINT(concurrency-mt-unsafe)
            }
        }

        return false;
    }
} // namespace TerminalGames

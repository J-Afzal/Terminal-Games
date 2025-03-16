#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "games/Battleships.hpp"
#include "games/Hangman.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/Globals.hpp"
#include "helpers/MainMenu.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    MainMenu::MainMenu(const bool& p_useAnsiEscapeCodes) :
        m_useAnsiEscapeCodes(p_useAnsiEscapeCodes)
    {
        SetupHomepages();
    }

    MainMenu::MainMenu(const std::vector<std::string>& p_commandLineArguments) :
        m_useAnsiEscapeCodes(true)
    {
        for (const std::string& argument : p_commandLineArguments)
        {
            if (argument == "--a" || argument == "--ascii-only")
            {
                m_useAnsiEscapeCodes = false;
                break;
            }

            if (argument == "-h" || argument == "--help")
            {
                std::cout << Globals::G_MAIN_MENU_CLI_HELP_MESSAGE;
                exit(1);
            }
        }

        SetupHomepages();
    }

    MainMenu::~MainMenu()
    {
        Terminal::ResetTerminal();
    }

    void MainMenu::Run()
    {
        Terminal::InitialiseTerminal();

        uint32_t gameChoice = 0;
        bool goToHomePage = true;

        while (true)
        {
            try
            {
                if (goToHomePage)
                {
                    m_useAnsiEscapeCodes = Terminal::GetUserChoiceFromHomepage(m_homepages, m_useAnsiEscapeCodes);
                    SetupMainMenuPagesAndGames();
                }

                gameChoice = Terminal::GetUserChoiceFromMainMenus(m_mainMenus);

                m_games[gameChoice]->Play();
            }

            catch (Globals::Exceptions::QuitGame& e)
            {
                goToHomePage = false;
            }

            catch (Globals::Exceptions::QuitMainMenu& e)
            {
                goToHomePage = true;
            }

            catch (Globals::Exceptions::QuitProgram& e)
            {
                Terminal::ResetTerminal();
                return;
            }
        }
    }

    void MainMenu::SetupHomepages()
    {
        PageBuilder homePageBuilder(Pages::HOMEPAGE, m_useAnsiEscapeCodes);
        m_homepages = homePageBuilder.GetOptionSelectionHomepages();
    }

    void MainMenu::SetupMainMenuPagesAndGames()
    {
        const PageBuilder MENUS_PAGE_BUILDER(Pages::MAINMENU, m_useAnsiEscapeCodes);
        m_mainMenus = MENUS_PAGE_BUILDER.GetGameSelectionMainMenuPages({"Tic Tac Toe", "Hangman", "Battleships"});

        // The order of games in m_Games should match the order of games in GetGameSelectionMainMenuPages function call.
        m_games.clear();
        m_games.emplace_back(std::make_unique<TicTacToe>(m_useAnsiEscapeCodes));
        m_games.emplace_back(std::make_unique<Hangman>(m_useAnsiEscapeCodes));
        m_games.emplace_back(std::make_unique<Battleships>(m_useAnsiEscapeCodes));
    }
}

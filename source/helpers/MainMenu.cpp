#include "games/Battleships.hpp"
#include "games/Hangman.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/MainMenu.hpp"

MainMenu::MainMenu(const bool& outputIsOnlyASCII)
{
    Terminal::SetCursorVisibility(false);
    Terminal::SetCursorPosition(0, 0);

    // The only difference between the three std::strings in m_mainMenus is the game that is selected using '>' which is also coloured blue.
    StringBuilder StringBuilder("Terminal-Games", "q = quit", 30, outputIsOnlyASCII);
    
    m_mainMenus.push_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_mainMenus[0] += StringBuilder.AddNewLine("       > Tic Tac Toe          ", Colours::BLUE) + StringBuilder.AddEmptyLine();
    m_mainMenus[0] += StringBuilder.AddNewLine("           Hangman            ") + StringBuilder.AddEmptyLine();
    m_mainMenus[0] += StringBuilder.AddNewLine("         Battleships          ");
    m_mainMenus[0] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    m_mainMenus.push_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_mainMenus[1] += StringBuilder.AddNewLine("         Tic Tac Toe          ") + StringBuilder.AddEmptyLine();
    m_mainMenus[1] += StringBuilder.AddNewLine("         > Hangman            ", Colours::BLUE) + StringBuilder.AddEmptyLine();
    m_mainMenus[1] += StringBuilder.AddNewLine("         Battleships          ");
    m_mainMenus[1] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    m_mainMenus.push_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_mainMenus[2] += StringBuilder.AddNewLine("         Tic Tac Toe          ") + StringBuilder.AddEmptyLine();
    m_mainMenus[2] += StringBuilder.AddNewLine("           Hangman            ") + StringBuilder.AddEmptyLine();
    m_mainMenus[2] += StringBuilder.AddNewLine("       > Battleships          ", Colours::BLUE);
    m_mainMenus[2] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    // The index of games in m_Games should match the index of the corresponding string in m_mainMenus.
    m_games.push_back(std::make_unique<TicTacToe>(outputIsOnlyASCII));
    m_games.push_back(std::make_unique<Hangman>(outputIsOnlyASCII));
    m_games.push_back(std::make_unique<Battleships>(outputIsOnlyASCII));
}

MainMenu::~MainMenu()
{
    Terminal::Clear();
    Terminal::SetCursorVisibility(true);
    Terminal::SetCursorPosition(0, 0);
}

void MainMenu::Run()
{
    // Custom Quit exceptions are used to return to the while loop.
    while (true)
    {
        try { m_games[Terminal::GetUserChoiceFromMainMenus(m_mainMenus)]->Play(); }
        
        catch (Exceptions::QuitProgram& e) { return; }

        catch (Exceptions::QuitGame& e) { continue; }
    }
}

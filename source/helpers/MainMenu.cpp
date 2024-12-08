#include "games/Battleships.hpp"
#include "games/Hangman.hpp"
#include "games/TicTacToe.hpp"
#include "helpers/MainMenu.hpp"

MainMenu::MainMenu(const bool& outputIsOnlyASCII)
{
    StringBuilder StringBuilder("Terminal-Games", "q = quit", 30, outputIsOnlyASCII);

    // The only difference between the three std::strings in m_menus is the game that is selected using '>' which is also coloured blue.
    m_menus.emplace_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_menus[0] += StringBuilder.AddNewLine("       > Tic Tac Toe          ", Colours::BLUE) + StringBuilder.AddEmptyLine();
    m_menus[0] += StringBuilder.AddNewLine("           Hangman            ") + StringBuilder.AddEmptyLine();
    m_menus[0] += StringBuilder.AddNewLine("         Battleships          ");
    m_menus[0] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    m_menus.emplace_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_menus[1] += StringBuilder.AddNewLine("         Tic Tac Toe          ") + StringBuilder.AddEmptyLine();
    m_menus[1] += StringBuilder.AddNewLine("         > Hangman            ", Colours::BLUE) + StringBuilder.AddEmptyLine();
    m_menus[1] += StringBuilder.AddNewLine("         Battleships          ");
    m_menus[1] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    m_menus.emplace_back(StringBuilder.AddTopBox() + StringBuilder.AddTopLine());
    m_menus[2] += StringBuilder.AddNewLine("         Tic Tac Toe          ") + StringBuilder.AddEmptyLine();
    m_menus[2] += StringBuilder.AddNewLine("           Hangman            ") + StringBuilder.AddEmptyLine();
    m_menus[2] += StringBuilder.AddNewLine("       > Battleships          ", Colours::BLUE);
    m_menus[2] += StringBuilder.AddBottomLine() + StringBuilder.AddBottomBox();

    // The index of games in m_Games should match the index of the corresponding string in m_menus.
    m_games[0] = std::make_unique<TicTacToe>(outputIsOnlyASCII);
    m_games[1] = std::make_unique<Hangman>(outputIsOnlyASCII);
    m_games[2] = std::make_unique<Battleships>(outputIsOnlyASCII);
}

void MainMenu::Run()
{
    // Quit exceptions are used to return to the MainMenu while loop.
    while (true)
    {
        try { m_currentSelection = m_terminal.GetUserChoiceFromMenus(m_menus); }
        catch (Exceptions::Quit& e) { return; }

        try { m_games[m_currentSelection]->Play(); }
        catch (Exceptions::Quit& e) { continue; }
    }
}

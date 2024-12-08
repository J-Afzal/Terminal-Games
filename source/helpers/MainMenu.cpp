/**
 * @file MainMenu.cpp
 * @author Junaid Afzal
 * @brief Implementation of MainMenu.hpp
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "helpers/MainMenu.hpp"
#include "games/TicTacToe.hpp"
#include "games/Hangman.hpp"
#include "games/Battleships.hpp"

MainMenu::MainMenu(const bool& outputIsOnlyASCII)
{
    StringBuilder StringBuilder("Terminal-Games", "q = quit", 30, outputIsOnlyASCII);

    /**
     * The only difference between the three std::strings in m_menus is the game that is selected using '>' and coloured blue.
     */

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

    /**
     * All game objects derive from the Game class and inherit a final Play() function, which contains
     * pure virtual functions for all sub classes to implement.
     *
     * This allows for all games to be stored in a single m_Games array, using polymorphism, and for a single
     * m_Games[m_CurrentSelection]->Play() to be used regardless of the game selected.
     *
     * Note that the index of a game in m_Games and the index of the corresponding m_menus string are the same.
     */
    m_games[0] = std::make_unique<TicTacToe>(outputIsOnlyASCII);
    m_games[1] = std::make_unique<Hangman>(outputIsOnlyASCII);
    m_games[2] = std::make_unique<Battleships>(outputIsOnlyASCII);
}

void MainMenu::Run()
{
    /**
     * Exceptions are only thrown in functions that accept user input and are allowed to propagate up the call stack
     * until it returns to this while loop and exist as a way for the user to quit a game at any point.
     */
    while (true)
    {
        try { m_currentSelection = m_terminal.GetUserChoiceFromMenus(m_menus); }
        catch (Exceptions::Quit& e) { return; }

        try { m_games[m_currentSelection]->Play(); }
        catch (Exceptions::Quit& e) { continue; }
    }
}

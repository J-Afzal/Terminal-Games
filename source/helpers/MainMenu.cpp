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

MainMenu::MainMenu(const bool& ASCIIOnly)
{
    StringBuilder StringBuilder(ASCIIOnly, 30, "Terminal-Games", "q = quit");

    /**
     * The only difference between the three std::strings in m_Menus is the game that is selected using '>' and coloured blue.
     */
    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[0] += StringBuilder.New_Line("       > Tic Tac Toe          ", Colours::BLUE) + StringBuilder.Empty_Line();
    m_Menus[0] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    m_Menus[0] += StringBuilder.New_Line("         Battleships          ");
    m_Menus[0] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[1] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    m_Menus[1] += StringBuilder.New_Line("         > Hangman            ", Colours::BLUE) + StringBuilder.Empty_Line();
    m_Menus[1] += StringBuilder.New_Line("         Battleships          ");
    m_Menus[1] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[2] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    m_Menus[2] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    m_Menus[2] += StringBuilder.New_Line("       > Battleships          ", Colours::BLUE);
    m_Menus[2] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    /**
     * All game objects derive from the Game class and inherit a final Play() function, which contains
     * pure virtual functions for all sub classes to implement.
     *
     * This allows for all games to be stored in a single m_Games array, using polymorphism, and for a single
     * m_Games[m_CurrentSelection]->Play() to be used regardless of the game selected.
     *
     * Note that the index of a game in m_Games and the index of the corresponding m_Menus string are the same.
     */
    m_Games[0] = std::make_unique<TicTacToe>(ASCIIOnly);
    m_Games[1] = std::make_unique<Hangman>(ASCIIOnly);
    m_Games[2] = std::make_unique<Battleships>(ASCIIOnly);
}

void MainMenu::Run()
{
    /**
     * Exceptions are only thrown in functions that accept user input and are allowed to propagate up the call stack
     * until it returns to this while loop and exist as a way for the user to quit a game at any point.
     */
    while (true)
    {
        try { m_CurrentSelection = m_Terminal.Get_User_Menu_Choice(m_Menus); }
        catch (Exceptions::Quit &e) { return; }

        try { m_Games[m_CurrentSelection]->Play(); }
        catch (Exceptions::Quit &ignored) { }
    }
}

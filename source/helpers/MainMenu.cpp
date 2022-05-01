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

void MainMenu::Run()
{
    Setup();

    /**
     * A note on exceptions use:
     *   A custom exception is used as it can be allowed to propagate up the call stack until control
     *   is returned to this function. The alternative would have been to continually return booleans
     *   until the code returns to the while loop. A simplified call stack shows why this would get messy.
     *
     *   Exceptions are only thrown in functions that accept user input.
     *
     *   - MainMenu::Run()
     *      - Games[CurrentSelection]->Play()
     *          - TicTacToe::Setup_Game()
     *               - TicTacToe::Get_Number_Of_Players()
     *                  - Terminal::Get_User_Menu_Choice() -> User requests a return to the main menu at this function
     */
    while (true)
    {
        try { m_CurrentSelection = Terminal::Get_User_Menu_Choice(m_Menus); }
        catch (Exceptions::Quit &e) { return; }

        try { m_Games[m_CurrentSelection]->Play(); }
        catch (Exceptions::Quit &ignored) { }
    }
}

void MainMenu::Setup()
{
    StringBuilder StringBuilder;
    StringBuilder.Set(30, "Terminal-Games", "q = quit");

    /**
     * The only difference between the three std::strings in Menus is which game is selected using '>' and coloured blue.
     */
    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[0] += StringBuilder.New_Line("       > Tic Tac Toe          ", "BLUE") + StringBuilder.Empty_Line();
    m_Menus[0] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    m_Menus[0] += StringBuilder.New_Line("         Battleships          ");
    m_Menus[0] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[1] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    m_Menus[1] += StringBuilder.New_Line("         > Hangman            ", "BLUE") + StringBuilder.Empty_Line();
    m_Menus[1] += StringBuilder.New_Line("         Battleships          ");
    m_Menus[1] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    m_Menus.emplace_back(StringBuilder.Top_Box() + StringBuilder.Top_Line());
    m_Menus[2] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    m_Menus[2] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    m_Menus[2] += StringBuilder.New_Line("       > Battleships          ", "BLUE");
    m_Menus[2] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    /**
     * All game objects derive from Game and inherit a pure virtual Play() function. This allows for runtime
     * polymorphism to be utilised by storing all games in single Game array and invoking the Play() function
     * on any of the games depending on what game currently selected.
     *
     * Note that the index of a game in the Games array and the index of a menu string that the game
     * is selected in the Menus array are the same.
     */
    m_Games[0] = std::make_unique<TicTacToe>(TicTacToe());
    m_Games[1] = std::make_unique<Hangman>(Hangman());
    m_Games[2] = std::make_unique<Battleships>(Battleships());
}

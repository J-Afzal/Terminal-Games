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

#include "MainMenu.hpp"
#include "TicTacToe.hpp"
#include "Hangman.hpp"
#include "Battleships.hpp"

void MainMenu::Run()
{
    Terminal Terminal;
    std::vector<std::string> Menus(3);
    std::array<std::unique_ptr<Game>, 3> Games;
    int CurrentSelection;

    MainMenu::Setup(Menus, Games);

    /**
     * A custom exception is used as it can be allowed to propagate up the call stack until it
     * returns back to this while loop, thus simplifying the code. Exceptions are only thrown in
     * functions that accept user input.
     *
     * The alternative to exceptions would have been to continually return booleans until the code
     * returns to the while loop. A simplified call stack shows why this would get messy.
     *
     * - Games[CurrentSelection]->Play()()
     *     - Setup_Game()
     *         - Get_Number_Of_Players()
     *             - Terminal::Get_User_Menu_Choice() -> User requests a return to the main menu at this function
     */
    while (true)
    {
        try { CurrentSelection = Terminal::Get_User_Menu_Choice(Menus); }
        catch (Exceptions::Quit &e) { Terminal.Quit(); return; }

        try { Games[CurrentSelection]->Play(); }
        catch (Exceptions::Quit &ignored) { }
    }
}

void MainMenu::Setup(std::vector<std::string> &Menus, std::array<std::unique_ptr<Game>, 3> &Games)
{
    StringBuilder StringBuilder;
    StringBuilder.Set(30, "Terminal-Games", "q = quit");

    /**
     * The only difference between the three std::strings in Menus is which game is selected using '>' and coloured blue.
     */
    Menus[0] = StringBuilder.Top_Box() + StringBuilder.Top_Line();
    Menus[0] += StringBuilder.New_Line("       > Tic Tac Toe          ", "BLUE") + StringBuilder.Empty_Line();
    Menus[0] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    Menus[0] += StringBuilder.New_Line("         Battleships          ");
    Menus[0] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    Menus[1] = StringBuilder.Top_Box() + StringBuilder.Top_Line();
    Menus[1] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    Menus[1] += StringBuilder.New_Line("         > Hangman            ", "BLUE") + StringBuilder.Empty_Line();
    Menus[1] += StringBuilder.New_Line("         Battleships          ");
    Menus[1] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    Menus[2] = StringBuilder.Top_Box() + StringBuilder.Top_Line();
    Menus[2] += StringBuilder.New_Line("         Tic Tac Toe          ") + StringBuilder.Empty_Line();
    Menus[2] += StringBuilder.New_Line("           Hangman            ") + StringBuilder.Empty_Line();
    Menus[2] += StringBuilder.New_Line("       > Battleships          ", "BLUE");
    Menus[2] += StringBuilder.Bottom_Line() + StringBuilder.Bottom_Box();

    /**
     * All game objects derive from Game and inherit a pure virtual Play() function. This allows for runtime
     * polymorphism to be utilised by storing all games in single Game array and invoking the Play() function
     * on any of the games depending on what game currently selected.
     *
     * Note that the index of a game in the Games array and the index of a menu string that the game
     * is selected in the Menus array are the same.
     */
    Games[0] = std::make_unique<TicTacToe>(TicTacToe());
    Games[1] = std::make_unique<Hangman>(Hangman());
    Games[2] = std::make_unique<Battleships>(Battleships());
}

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
    Terminal Terminal(30, "Terminal-Games", "q = quit");
    std::vector<std::string> OptionMenus(3);
    std::vector<int> Options(3);
    std::array<std::unique_ptr<Game>, 3> Games;

    MainMenu::Setup(Terminal, OptionMenus, Options, Games);

    int CurrentSelection;
    while (true)
    {
        try { CurrentSelection = Game::Get_User_Option_Choice(OptionMenus, Options); }
        catch (Quit& e) { Terminal.Quit(); return; }

        try { Games[CurrentSelection]->Play(); }
        catch (Quit& ignored) { }
    }
}

void MainMenu::Setup(Terminal &Terminal, std::vector<std::string> &OptionMenus, std::vector<int> &Options, std::array<std::unique_ptr<Game>, 3> &Games)
{
    OptionMenus[0] = Terminal.Top_Box() + Terminal.Top_Line();
    OptionMenus[0] += Terminal.New_Line("       > Tic Tac Toe          ", "BLUE") + Terminal.Empty_Line();
    OptionMenus[0] += Terminal.New_Line("           Hangman            ") + Terminal.Empty_Line();
    OptionMenus[0] += Terminal.New_Line("         Battleships          ");
    OptionMenus[0] += Terminal.Bottom_Line() + Terminal.Bottom_Box();

    OptionMenus[1] = Terminal.Top_Box() + Terminal.Top_Line();
    OptionMenus[1] += Terminal.New_Line("         Tic Tac Toe          ") + Terminal.Empty_Line();
    OptionMenus[1] += Terminal.New_Line("         > Hangman            ", "BLUE") + Terminal.Empty_Line();
    OptionMenus[1] += Terminal.New_Line("         Battleships          ");
    OptionMenus[1] += Terminal.Bottom_Line() + Terminal.Bottom_Box();

    OptionMenus[2] = Terminal.Top_Box() + Terminal.Top_Line();
    OptionMenus[2] += Terminal.New_Line("         Tic Tac Toe          ") + Terminal.Empty_Line();
    OptionMenus[2] += Terminal.New_Line("           Hangman            ") + Terminal.Empty_Line();
    OptionMenus[2] += Terminal.New_Line("       > Battleships          ", "BLUE");
    OptionMenus[2] += Terminal.Bottom_Line() + Terminal.Bottom_Box();

    Options[0] = 0;
    Options[1] = 1;
    Options[2] = 2;

    Games[0] = std::make_unique<TicTacToe>(TicTacToe());
    Games[1] = std::make_unique<Hangman>(Hangman());
    Games[2] = std::make_unique<Battleships>(Battleships());
}

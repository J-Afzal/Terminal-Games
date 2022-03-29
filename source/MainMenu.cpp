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

#include "Terminal.hpp"
#include "MainMenu.hpp"
#include "Game.hpp"
#include "QuitToMainMenu.hpp"
#include "TicTacToe.hpp"
#include "Hangman.hpp"
#include "Battleships.hpp"

void MainMenu::Run()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ConsoleHandle == INVALID_HANDLE_VALUE)
        exit(1);

    Terminal terminal(ConsoleHandle, 30, "Terminal-Games", "q = quit");

    // ANSI escape codes for bold text colours
    std::array<std::string, 3> Options;
    Options[0] = terminal.Top_Box() + terminal.Top_Line();
    Options[0] += terminal.New_Line("       > Tic Tac Toe          ", "BLUE") + terminal.Empty_Line();
    Options[0] += terminal.New_Line("           Hangman            ") + terminal.Empty_Line();
    Options[0] += terminal.New_Line("         Battleships          ");
    Options[0] += terminal.Bottom_Line() + terminal.Bottom_Box();

    Options[1] = terminal.Top_Box() + terminal.Top_Line();
    Options[1] += terminal.New_Line("         Tic Tac Toe          ") + terminal.Empty_Line();
    Options[1] += terminal.New_Line("         > Hangman            ", "BLUE") + terminal.Empty_Line();
    Options[1] += terminal.New_Line("         Battleships          ");
    Options[1] += terminal.Bottom_Line() + terminal.Bottom_Box();

    Options[2] = terminal.Top_Box() + terminal.Top_Line();
    Options[2] += terminal.New_Line("         Tic Tac Toe          ") + terminal.Empty_Line();
    Options[2] += terminal.New_Line("           Hangman            ") + terminal.Empty_Line();
    Options[2] += terminal.New_Line("       > Battleships          ", "BLUE");
    Options[2] += terminal.Bottom_Line() + terminal.Bottom_Box();

    std::array<std::unique_ptr<Game>, 3> Games;
    Games[0] = std::make_unique<TicTacToe>(TicTacToe(ConsoleHandle));
    Games[1] = std::make_unique<Hangman>(Hangman(ConsoleHandle));
    Games[2] = std::make_unique<Battleships>(Battleships(ConsoleHandle));

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
            try { Games[CurrentSelection]->Play(); } catch (QuitToMainMenu& ignored) { }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            Terminal::Clear_Terminal();
            terminal.Set_Cursor_Visibility(true);
            return;
        }
    }
}

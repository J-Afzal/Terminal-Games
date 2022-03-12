/**
 * @file mainmenu.cpp
 * @author Junaid Afzal
 * @brief Implementation of mainmenu.hpp
 * @version 1.0
 * @date 04-03-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <conio.h>
#include <memory>
#include "terminal.hpp"
#include "mainmenu.hpp"
#include "game.hpp"
#include "tictactoe.hpp"
#include "hangman.hpp"
#include "battleships.hpp"

void MainMenu::Run()
{
    HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    if (ConsoleHandle == INVALID_HANDLE_VALUE)
        exit(1);

    Set_Cursor_Visibility(ConsoleHandle, false);

    // ANSI escape codes for bold text colours
    const std::string WHITE = "\x1B[1;37m", BLUE = "\x1B[1;34m", RESET = "\x1B[0m";

    std::array<std::string, 3> Options;
    Options[0] = WHITE + Box(30, "        Terminal-Games        ") + Top_Line(30);
    Options[0] += New_Line(BLUE + "       > Tic Tac Toe          " + WHITE) + Empty_Line(30);
    Options[0] += New_Line("           Hangman            ") + Empty_Line(30);
    Options[0] += New_Line("         Battleships          ") + Bottom_Line(30);
    Options[0] += Box(30, "           q = quit           ") + RESET;

    Options[1] = WHITE + Box(30, "        Terminal-Games        ") + Top_Line(30);
    Options[1] += New_Line("         Tic Tac Toe          ") + Empty_Line(30);
    Options[1] += New_Line(BLUE + "         > Hangman            " + WHITE) + Empty_Line(30);
    Options[1] += New_Line("         Battleships          ") + Bottom_Line(30);
    Options[1] += Box(30, "           q = quit           ") + RESET;

    Options[2] = WHITE + Box(30, "        Terminal-Games        ") + Top_Line(30);
    Options[2] += New_Line("         Tic Tac Toe          ") + Empty_Line(30);
    Options[2] += New_Line("           Hangman            ") + Empty_Line(30);
    Options[2] += New_Line(BLUE + "       > Battleships          " + WHITE) + Bottom_Line(30);
    Options[2] += Box(30, "           q = quit           ") + RESET;

    std::array<std::unique_ptr<Game>, 3> Games;
    Games[0] = std::make_unique<TicTacToe>(TicTacToe(ConsoleHandle));
    Games[1] = std::make_unique<Hangman>(Hangman(ConsoleHandle));
    Games[2] = std::make_unique<Battleships>(Battleships(ConsoleHandle));

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
            Games[CurrentSelection]->Play();
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 2 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 2 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            Clear_Terminal();
            Set_Cursor_Visibility(ConsoleHandle, true);
            return;
        }
    }
}

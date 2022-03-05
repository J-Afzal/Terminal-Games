/**
 * @file battleships.cpp
 * @author Junaid Afzal
 * @brief Implementation of battlships.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <conio.h>
#include "terminal.hpp"
#include "battleships.hpp"

void Battleships::Play(const HANDLE &ConsoleHandle,
                       CONSOLE_CURSOR_INFO &CursorInfo)
{
    bool GameIsRunning = true;
    bool QuitToMainMenu = false;
    while (GameIsRunning)
    {
        std::vector<std::vector<char>> BoardOne, BoardTwo;
        std::vector<int> MovesRemainingOne, MovesRemainingTwo;
        std::map<char, int> ShipsRemainingOne, ShipsRemainingTwo;
        std::string CurrentPlayer, AIDifficulty;
        int NumberOfPlayers, NumberOfTurns = 0, previousCommand = 0;

        Setup_Game(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, MovesRemainingOne, MovesRemainingTwo, CurrentPlayer, AIDifficulty, NumberOfPlayers, ConsoleHandle, CursorInfo, QuitToMainMenu);

        if (QuitToMainMenu)
            break;

        while (!Winning_Conditions_Met(BoardOne, BoardTwo))
        {
            CurrentPlayer == "Player One" ? CurrentPlayer = "Player Two" : CurrentPlayer = "Player One";

            if (NumberOfPlayers == 1 && CurrentPlayer == "Player One")
                Get_Next_User_Command(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, MovesRemainingOne, CurrentPlayer, AIDifficulty, NumberOfPlayers, previousCommand, ConsoleHandle, CursorInfo, QuitToMainMenu);
            else
                Get_Next_AI_Command(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, MovesRemainingOne, MovesRemainingTwo, CurrentPlayer);

            if (QuitToMainMenu)
                break;

            NumberOfTurns++;
        }

        if (QuitToMainMenu)
            break;

        Display_Game_Over_Message(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, CurrentPlayer, AIDifficulty, NumberOfPlayers, NumberOfTurns, GameIsRunning);
    }
}

void Battleships::Setup_Game(std::vector<std::vector<char>> &BoardOne,
                             std::vector<std::vector<char>> &BoardTwo,
                             std::map<char, int> &ShipsRemainingOne,
                             std::map<char, int> &ShipsRemainingTwo,
                             std::vector<int> &MovesRemainingOne,
                             std::vector<int> &MovesRemainingTwo,
                             std::string &CurrentPlayer,
                             std::string &AIDifficulty,
                             int &NumberOfPlayers,
                             const HANDLE &ConsoleHandle,
                             CONSOLE_CURSOR_INFO &CursorInfo,
                             bool &QuitToMainMenu)
{
    std::srand(std::time(0));

    for (int i = 0, GridNumber = 0; i < 10; i++)
    {
        std::vector<char> Row;
        BoardOne.push_back(Row);
        BoardTwo.push_back(Row);

        for (int j = 0; j < 10; j++, GridNumber++)
        {
            BoardOne[i].push_back(' ');
            BoardTwo[i].push_back(' ');
            MovesRemainingOne.push_back(GridNumber);
            MovesRemainingTwo.push_back(GridNumber);
        }
    }

    ShipsRemainingOne['C'] = 5;
    ShipsRemainingOne['B'] = 4;
    ShipsRemainingOne['D'] = 3;
    ShipsRemainingOne['S'] = 3;
    ShipsRemainingOne['P'] = 2;

    ShipsRemainingTwo['C'] = 5;
    ShipsRemainingTwo['B'] = 4;
    ShipsRemainingTwo['D'] = 3;
    ShipsRemainingTwo['S'] = 3;
    ShipsRemainingTwo['P'] = 2;

    NumberOfPlayers = Get_Number_Of_Players(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    AIDifficulty = Get_AI_Difficulty(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, NumberOfPlayers, QuitToMainMenu);
    if (QuitToMainMenu)
        return;

    if (NumberOfPlayers == 1)
        Get_User_Ship_Positions(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, AIDifficulty, NumberOfPlayers, ConsoleHandle, CursorInfo, QuitToMainMenu);
    else
        Get_AI_Ship_Positions(BoardOne);

    if (QuitToMainMenu)
        return;

    // Player two will always be AI controlled
    Get_AI_Ship_Positions(BoardTwo);

    if ((std::rand() % 2) == 0)
        CurrentPlayer = "Player One";
    else
        CurrentPlayer = "Player Two";
}

int Battleships::Get_Number_Of_Players(const std::vector<std::vector<char>> &BoardOne,
                                       const std::vector<std::vector<char>> &BoardTwo,
                                       const std::map<char, int> &ShipsRemainingOne,
                                       const std::map<char, int> &ShipsRemainingTwo,
                                       bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, "N/A", "N/A", false);
    CommonString += New_Line(" Please select the number of human players:                                                                                                        ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > 0                                                                                                                                               " + WHITE);
    CaseZero += New_Line("   1                                                                                                                                               ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   0                                                                                                                                               ");
    CaseOne += New_Line(BLUE + " > 1                                                                                                                                               " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r')
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return -1;
        }
    }

    return CurrentSelection;
}

std::string Battleships::Get_AI_Difficulty(const std::vector<std::vector<char>> &BoardOne,
                                           const std::vector<std::vector<char>> &BoardTwo,
                                           const std::map<char, int> &ShipsRemainingOne,
                                           const std::map<char, int> &ShipsRemainingTwo,
                                           const int &NumberOfPlayers,
                                           bool &QuitToMainMenu)
{
    std::string CommonString = Get_Game_Display(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, "N/A", std::to_string(NumberOfPlayers), false);
    CommonString += New_Line(" Please select the AI difficulty:                                                                                                                  ");

    std::string CaseZero = CommonString;
    CaseZero += New_Line(BLUE + " > EASY                                                                                                                                            " + WHITE);
    CaseZero += New_Line("   HARD (Coming Soon!)                                                                                                                             ");
    CaseZero += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    std::string CaseOne = CommonString;
    CaseOne += New_Line("   EASY                                                                                                                                            ");
    CaseOne += New_Line(BLUE + " > HARD (Coming Soon!)                                                                                                                             " + WHITE);
    CaseOne += Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    int KeyPress = 0, CurrentSelection = 0;
    while (true)
    {
        if (CurrentSelection == 0)
            Output_To_Terminal(CaseZero);
        else if (CurrentSelection == 1)
            Output_To_Terminal(CaseOne);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
            break;
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
        {
            QuitToMainMenu = true;
            return "-1";
        }
    }

    return CurrentSelection == 0 ? "EASY" : "HARD";
}

void Battleships::Get_User_Ship_Positions(std::vector<std::vector<char>> &BoardOne,
                                          const std::vector<std::vector<char>> &BoardTwo,
                                          const std::map<char, int> &ShipsRemainingOne,
                                          const std::map<char, int> &ShipsRemainingTwo,
                                          const std::string &AIDifficulty,
                                          const int &NumberOfPlayers,
                                          const HANDLE &ConsoleHandle,
                                          CONSOLE_CURSOR_INFO &CursorInfo,
                                          bool &QuitToMainMenu)
{
    std::vector<std::string> ShipInstructions = {
        "                                                 Please enter the 5 grid locations for the Carrier                                                 ",
        "                                               Please enter the 4 grid locations for the Battleship                                                ",
        "                                                Please enter the 3 grid locations for the Destroyer                                                ",
        "                                                Please enter the 3 grid locations for the Submarine                                                ",
        "                                               Please enter the 2 grid locations for the Patrol Boat                                               "};
    std::vector<char> ShipLetters = {'C', 'B', 'D', 'S', 'P'};
    std::vector<int> ShipSizes = {5, 4, 3, 3, 2};
    int lastShipRow = 0, lastShipColumn = 0;

    CursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

    for (int i = 0; i < 5; i++) // for each ship
    {
        std::vector<std::vector<char>> TempBoardOne = BoardOne;
        std::vector<int> ShipRows, ShipColumns;
        std::string shipOrientation = "N/A";

        for (int j = 0; j < ShipSizes[i]; j++) // for each ship grid locations
        {
            std::string Output = Get_Game_Display(TempBoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, AIDifficulty, std::to_string(NumberOfPlayers), false);
            Output += New_Line(ShipInstructions[i]) + Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

            Output_To_Terminal(Output);

            int KeyPress, Row = 0, Column = 0;

            if (j == 0)
            {
                Row = lastShipRow;
                Column = lastShipColumn;
            }
            else
            {
                Row = ShipRows.back();
                Column = ShipColumns.back();
            }

            while (true) // while ship grid location incorrect
            {

                while (true)
                {
                    COORD CursorPosition;
                    CursorPosition.X = 10 + Column * 4;
                    CursorPosition.Y = 8 + Row * 2;
                    SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

                    KeyPress = _getch();

                    if (KeyPress == '\r')
                        break;
                    else if (KeyPress == 72) // up arrow key
                        Row == 0 ? Row = 9 : --Row;
                    else if (KeyPress == 80) // down arrow key
                        Row == 9 ? Row = 0 : ++Row;
                    else if (KeyPress == 75) // left arrow key
                        Column == 0 ? Column = 9 : --Column;
                    else if (KeyPress == 77) // right arrow key
                        Column == 9 ? Column = 0 : ++Column;
                    else if (KeyPress == 8 && j > 0) // backspace key
                    {
                        TempBoardOne[ShipRows.back()][ShipColumns.back()] = ' ';

                        std::string Output = Get_Game_Display(TempBoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, AIDifficulty, std::to_string(NumberOfPlayers), false);
                        Output += New_Line(ShipInstructions[i]) + Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

                        Output_To_Terminal(Output);

                        ShipRows.pop_back();
                        ShipColumns.pop_back();

                        j--;

                        if (j == 0)
                        {
                            Row = lastShipRow;
                            Column = lastShipColumn;
                        }
                        else
                        {
                            Row = ShipRows.back();
                            Column = ShipColumns.back();
                        }
                    }
                    else if (KeyPress == 'q')
                    {
                        QuitToMainMenu = true;
                        CursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
                        return;
                    }
                }

                // Check if grid location is already occupied by another ship
                if (BoardOne[Row][Column] == ' ')
                {
                    if (ShipRows.size() == 0)
                    {
                        ShipRows.push_back(Row);
                        ShipColumns.push_back(Column);
                        break;
                    }

                    else
                    {
                        bool ColumnsSame = false, RowsSame = false;
                        if (ShipRows.back() == Row)
                            RowsSame = true;
                        if (ShipColumns.back() == Column)
                            ColumnsSame = true;

                        // check if row or column same/different but both cannot be different or same
                        if ((RowsSame && ColumnsSame) || (!RowsSame && !ColumnsSame))
                        {
                            KeyPress = 0;
                            continue;
                        }

                        if (ShipRows.size() == 1)
                        {
                            if (RowsSame)
                                shipOrientation = "HORIZONTAL";
                            else
                                shipOrientation = "VERTICAL";

                            ShipRows.push_back(Row);
                            ShipColumns.push_back(Column);
                            break;
                        }

                        else if (RowsSame && (shipOrientation == "HORIZONTAL") && (std::abs(Column - ShipColumns.back()) == 1))
                        {
                            // If row same then column must an increment or decrement of previous position if there is one
                            ShipRows.push_back(Row);
                            ShipColumns.push_back(Column);
                            break;
                        }

                        else if (ColumnsSame && (shipOrientation == "VERTICAL") && (std::abs(Row - ShipRows.back()) == 1))
                        {
                            // If column same then row must an increment or decrement of previous position if there is one
                            ShipRows.push_back(Row);
                            ShipColumns.push_back(Column);
                            break;
                        }

                        else
                            KeyPress = 0;
                    }
                }

                else
                {
                    KeyPress = 0;
                    continue;
                }
            }

            TempBoardOne[Row][Column] = 'X';

            if (j == (ShipSizes[i] - 1))
            {
                lastShipRow = Row;
                lastShipColumn = Column;
            }
        }

        // Place ship
        for (unsigned int j = 0; j < ShipRows.size(); j++)
            BoardOne[ShipRows[j]][ShipColumns[j]] = ShipLetters[i];
    }

    CursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}

void Battleships::Get_AI_Ship_Positions(std::vector<std::vector<char>> &AIBoard)
{
    std::vector<int> ShipSizes = {5, 4, 3, 3, 2};
    std::vector<char> ShipLetters = {'C', 'B', 'D', 'S', 'P'};

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            std::vector<int> ShipRows, ShipColumns;
            int Column, Row;

            // Get a random ship position
            if ((std::rand() % 2) == 0) // Horizontal
            {
                // A max column number exists, as ship is horizontal, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Column = std::rand() % (11 - ShipSizes[i]);

                Row = std::rand() % 10; // Any row number allowed as ship is horizontal

                // Horizontal positions have a difference in columns of 1
                for (int j = 0; j < ShipSizes[i]; j++)
                {
                    ShipRows.push_back(Row);
                    ShipColumns.push_back(Column + j);
                }
            }

            else // Vertical
            {
                Column = std::rand() % 10; // Any column number allowed as ship is vertical

                // A max row number exists, as ship is vertical, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Row = std::rand() % (11 - ShipSizes[i]);

                // Vertical positions have a difference in rows of 1
                for (int j = 0; j < ShipSizes[i]; j++)
                {
                    ShipRows.push_back(Row + j);
                    ShipColumns.push_back(Column);
                }
            }

            // Check if ship is already located on requested ship position
            bool NoErrors = true;
            for (unsigned int j = 0; j < ShipRows.size(); j++)
                if (AIBoard[ShipRows[j]][ShipColumns[j]] == 'C' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'B' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'D' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'S' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'P')
                    NoErrors = false;

            if (NoErrors) // Place ship
            {
                for (unsigned int j = 0; j < ShipRows.size(); j++)
                    AIBoard[ShipRows[j]][ShipColumns[j]] = ShipLetters[i];
                break;
            }
        }
    }
}

std::string Battleships::Get_Game_Display(const std::vector<std::vector<char>> &BoardOne,
                                          const std::vector<std::vector<char>> &BoardTwo,
                                          const std::map<char, int> &ShipsRemainingOne,
                                          const std::map<char, int> &ShipsRemainingTwo,
                                          const std::string &AIDifficulty,
                                          const std::string &NumberOfPlayers,
                                          const bool &GameOver)
{
    std::string Output;

    // Top bar
    Output += WHITE + Top_Line();
    Output += New_Line(RED + "                                                                    Battleships                                                                    " + WHITE);
    Output += Bottom_Line();

    // Main game box
    Output += Top_Line();

    // Top row and letter co-ordinates of both boards
    Output += New_Line("                    Player One                                                                                       Player Two                    ");

    Output += (char)186 + std::string("   ");
    for (int i = 0; i < 2; i++)
    {
        Output += (char)218;
        Output.insert(Output.size(), 3, (char)196);
        for (int j = 0; j < 10; j++)
        {
            Output += (char)194;
            Output.insert(Output.size(), 3, (char)196);
        }
        Output += (char)191;

        if (i == 0)
            Output.insert(Output.size(), "                                                   ");
    }
    Output += std::string("   ") + (char)186 + "\n";

    Output += (char)186 + std::string("   ");
    for (int i = 0; i < 2; i++)
    {
        Output += (char)179 + std::string("   ") + (char)179 + " A " + (char)179 + " B " + (char)179 + " C " + (char)179 + " D " + (char)179 + " E " + (char)179 + " F " + (char)179 + " G " + (char)179 + " H " + (char)179 + " I " + (char)179 + " J " + (char)179;

        if (i == 0)
            Output += "                                                   ";
    }
    Output += std::string("   ") + (char)186 + "\n";

    // Main parts of both boards and centre information
    for (int i = 0; i < 10; i++)
    {
        // First Line
        // Left outer box edge
        Output += (char)186 + std::string("   ");

        // Player One Board horizontal dividers
        Output += (char)195;
        Output.insert(Output.size(), 3, (char)196);
        for (int j = 0; j < 10; j++)
        {
            Output += (char)197;
            Output.insert(Output.size(), 3, (char)196);
        }
        Output += (char)180;

        // Centre information
        if (i == 3)
            Output += "   Carrier                               Carrier   ";
        else if (i == 5) // Battleship
        {
            Output += "   ";
            for (int j = 0; j < 4; j++, Output += " ")
            {
                if (j < ShipsRemainingOne.at('B'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "              ";
            for (int j = 0; j < 4; j++, Output += " ")
            {
                if (j < (4 - ShipsRemainingTwo.at('B')))
                    Output.insert(Output.size(), 3, (char)176);
                else
                    Output.insert(Output.size(), 3, (char)178);
            }
            Output += "  ";
        }
        else if (i == 6)
            Output += "   Destroyer                           Destroyer   ";
        else if (i == 8) // Submarine
        {
            Output += "   ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < ShipsRemainingOne.at('S'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                      ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < (3 - ShipsRemainingTwo.at('S')))
                    Output.insert(Output.size(), 3, (char)176);
                else
                    Output.insert(Output.size(), 3, (char)178);
            }
            Output += "  ";
        }
        else if (i == 9)
            Output += "   Patrol Boat                       Patrol Boat   ";
        else
            Output += "                                                   ";

        // Player Two Board horizontal dividers
        Output += (char)195;
        Output.insert(Output.size(), 3, (char)196);
        for (int j = 0; j < 10; j++)
        {
            Output += (char)197;
            Output.insert(Output.size(), 3, (char)196);
        }
        Output += (char)180 + std::string("   ") + (char)186 + "\n";

        // Second Line
        // Player one left outer box edge and number co-ord
        Output += (char)186 + std::string("   ") + (char)179 + " " + std::to_string(i) + " " + (char)179;

        // Player One board ships
        for (int j = 0; j < 10; j++)
        {
            if (BoardOne[i][j] == 'C' || BoardOne[i][j] == 'B' || BoardOne[i][j] == 'D' || BoardOne[i][j] == 'S' || BoardOne[i][j] == 'P')
                Output.insert(Output.size(), 3, (char)178);
            else if (BoardOne[i][j] == 'X')
                Output.insert(Output.size(), 3, (char)176);
            else if (BoardOne[i][j] == '.')
                Output += std::string(" ") + (char)250 + " ";
            else
                Output += "   ";
            Output += (char)179;
        }

        // Centre Information
        if (i == 0)
        {
            if (NumberOfPlayers == "N/A")
                Output += "                # of Players = " + NumberOfPlayers + "                 ";
            else
                Output += "                 # of Players = " + NumberOfPlayers + "                  ";
        }
        else if (i == 1)
        {
            if (AIDifficulty == "N/A")
                Output += "                AI Difficulty = " + AIDifficulty + "                ";
            else
                Output += "               AI Difficulty = " + AIDifficulty + "                ";
        }
        else if (i == 3) // Carrier
        {
            Output += "   ";
            for (int j = 0; j < 5; j++, Output += " ")
            {
                if (j < ShipsRemainingOne.at('C'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "      ";
            for (int j = 0; j < 5; j++, Output += " ")
            {
                if (j < (5 - ShipsRemainingTwo.at('C')))
                    Output.insert(Output.size(), 3, (char)176);
                else
                    Output.insert(Output.size(), 3, (char)178);
            }
            Output += "  ";
        }
        else if (i == 4)
            Output += "   Battleship                         Battleship   ";
        else if (i == 6) // Destroyer
        {
            Output += "   ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < ShipsRemainingOne.at('D'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                      ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < (3 - ShipsRemainingTwo.at('D')))
                    Output.insert(Output.size(), 3, (char)176);
                else
                    Output.insert(Output.size(), 3, (char)178);
            }
            Output += "  ";
        }
        else if (i == 7)
            Output += "   Submarine                           Submarine   ";
        else if (i == 9) // Patrol Boat
        {
            Output += "   ";
            for (int j = 0; j < 2; j++, Output += " ")
            {
                if (j < ShipsRemainingOne.at('P'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                              ";
            for (int j = 0; j < 2; j++, Output += " ")
            {
                if (j < (2 - ShipsRemainingTwo.at('P')))
                    Output.insert(Output.size(), 3, (char)176);
                else
                    Output.insert(Output.size(), 3, (char)178);
            }
            Output += "  ";
        }
        else
            Output += "                                                   ";

        // Player Two left outer box edge and number co-ord
        Output += (char)179 + std::string(" ") + std::to_string(i) + " " + (char)179;

        // Player Two board ships
        for (int j = 0; j < 10; j++)
        {
            if ((GameOver || NumberOfPlayers == "0") && (BoardTwo[i][j] == 'C' || BoardTwo[i][j] == 'B' || BoardTwo[i][j] == 'D' || BoardTwo[i][j] == 'S' || BoardTwo[i][j] == 'P'))
                Output.insert(Output.size(), 3, (char)178);
            else if (BoardTwo[i][j] == 'X')
                Output.insert(Output.size(), 3, (char)176);
            else if (BoardTwo[i][j] == '.')
                Output += std::string(" ") + (char)250 + " ";
            else
                Output += "   ";
            Output += (char)179;
        }
        Output += std::string("   ") + (char)186 + "\n";
    }

    // Bottom row of both boards
    Output += (char)186 + std::string("   ");
    for (int i = 0; i < 2; i++)
    {
        Output += (char)192;
        Output.insert(Output.size(), 3, (char)196);
        for (int j = 0; j < 10; j++)
        {
            Output += (char)193;
            Output.insert(Output.size(), 3, (char)196);
        }
        Output += (char)217;

        if (i == 0)
            Output += "                                                   ";
    }
    Output += std::string("   ") + (char)186 + "\n" + Empty_Line();

    return Output;
}

std::string Battleships::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string Battleships::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 147, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Battleships::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 147, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Battleships::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 147, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Battleships::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                                                               q = quit to main menu                                                               " + WHITE) + Bottom_Line();
}

bool Battleships::Winning_Conditions_Met(const std::vector<std::vector<char>> &BoardOne,
                                         const std::vector<std::vector<char>> &BoardTwo)
{
    bool PlayerOneShipsPresent = false;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (BoardOne[i][j] == 'C' || BoardOne[i][j] == 'B' || BoardOne[i][j] == 'D' || BoardOne[i][j] == 'S' || BoardOne[i][j] == 'P')
                PlayerOneShipsPresent = true;

    bool PlayerTwoShipsPresent = false;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (BoardTwo[i][j] == 'C' || BoardTwo[i][j] == 'B' || BoardTwo[i][j] == 'D' || BoardTwo[i][j] == 'S' || BoardTwo[i][j] == 'P')
                PlayerTwoShipsPresent = true;

    return (!PlayerOneShipsPresent || !PlayerTwoShipsPresent) ? true : false;
}

void Battleships::Get_Next_User_Command(std::vector<std::vector<char>> &BoardOne,
                                        std::vector<std::vector<char>> &BoardTwo,
                                        std::map<char, int> &ShipsRemainingOne,
                                        std::map<char, int> &ShipsRemainingTwo,
                                        std::vector<int> &MovesRemainingOne,
                                        const std::string &CurrentPlayer,
                                        const std::string &AIDifficulty,
                                        const int &NumberOfPlayers,
                                        int &previousCommand,
                                        const HANDLE &ConsoleHandle,
                                        CONSOLE_CURSOR_INFO &CursorInfo,
                                        bool &QuitToMainMenu)
{
    std::string Output = Get_Game_Display(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, AIDifficulty, std::to_string(NumberOfPlayers), false);
    Output += New_Line(" Player One, please enter your next command!                                                                                                       ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    int KeyPress, Command, Row = previousCommand / 10, Column = previousCommand % 10;

    CursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);

    while (true)
    {
        while (true)
        {
            COORD CursorPosition;
            CursorPosition.X = 106 + Column * 4;
            CursorPosition.Y = 8 + Row * 2;
            SetConsoleCursorPosition(ConsoleHandle, CursorPosition);

            KeyPress = _getch();

            if (KeyPress == '\r')
                break;
            else if (KeyPress == 72) // up arrow key
                Row == 0 ? Row = 9 : --Row;
            else if (KeyPress == 80) // down arrow key
                Row == 9 ? Row = 0 : ++Row;
            else if (KeyPress == 75) // left arrow key
                Column == 0 ? Column = 9 : --Column;
            else if (KeyPress == 77) // right arrow key
                Column == 9 ? Column = 0 : ++Column;
            else if (KeyPress == 'q')
            {
                QuitToMainMenu = true;
                CursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
                return;
            }
        }

        Command = Row * 10 + Column;
        auto CommandPosition = std::find(MovesRemainingOne.begin(), MovesRemainingOne.end(), Command);

        if (CommandPosition != MovesRemainingOne.end())
        {
            MovesRemainingOne.erase(CommandPosition);
            break;
        }
        else
            KeyPress = 0;
    }

    previousCommand = Command;

    Execute_Next_Turn(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, CurrentPlayer, Command);

    CursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(ConsoleHandle, &CursorInfo);
}

void Battleships::Get_Next_AI_Command(std::vector<std::vector<char>> &BoardOne,
                                      std::vector<std::vector<char>> &BoardTwo,
                                      std::map<char, int> &ShipsRemainingOne,
                                      std::map<char, int> &ShipsRemainingTwo,
                                      std::vector<int> &MovesRemainingOne,
                                      std::vector<int> &MovesRemainingTwo,
                                      const std::string &CurrentPlayer)
{
    if (CurrentPlayer == "Player One")
    {
        int Command = MovesRemainingOne[std::rand() % MovesRemainingOne.size()];
        MovesRemainingOne.erase(std::find(MovesRemainingOne.begin(), MovesRemainingOne.end(), Command));
        Execute_Next_Turn(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, CurrentPlayer, Command);
    }

    else
    {
        int Command = MovesRemainingTwo[std::rand() % MovesRemainingTwo.size()];
        MovesRemainingTwo.erase(std::find(MovesRemainingTwo.begin(), MovesRemainingTwo.end(), Command));
        Execute_Next_Turn(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, CurrentPlayer, Command);
    }
}

void Battleships::Execute_Next_Turn(std::vector<std::vector<char>> &BoardOne,
                                    std::vector<std::vector<char>> &BoardTwo,
                                    std::map<char, int> &ShipsRemainingOne,
                                    std::map<char, int> &ShipsRemainingTwo,
                                    const std::string &CurrentPlayer,
                                    const int &Command)
{
    int Row = Command / 10;
    int Column = Command % 10;

    if (CurrentPlayer == "Player One")
    {
        if (BoardTwo[Row][Column] == 'C' || BoardTwo[Row][Column] == 'B' || BoardTwo[Row][Column] == 'D' || BoardTwo[Row][Column] == 'S' || BoardTwo[Row][Column] == 'P')
        {
            ShipsRemainingTwo[BoardTwo[Row][Column]]--;
            BoardTwo[Row][Column] = 'X';
        }
        else
            BoardTwo[Row][Column] = '.';
    }

    else
    {
        if (BoardOne[Row][Column] == 'C' || BoardOne[Row][Column] == 'B' || BoardOne[Row][Column] == 'D' || BoardOne[Row][Column] == 'S' || BoardOne[Row][Column] == 'P')
        {
            ShipsRemainingOne[BoardOne[Row][Column]]--;
            BoardOne[Row][Column] = 'X';
        }
        else
            BoardOne[Row][Column] = '.';
    }
}

void Battleships::Display_Game_Over_Message(const std::vector<std::vector<char>> &BoardOne,
                                            const std::vector<std::vector<char>> &BoardTwo,
                                            const std::map<char, int> &ShipsRemainingOne,
                                            const std::map<char, int> &ShipsRemainingTwo,
                                            const std::string &CurrentPlayer,
                                            const std::string &AIDifficulty,
                                            const int &NumberOfPlayers,
                                            const int &NumberOfTurns,
                                            bool &GameIsRunning)
{
    std::string Output = Get_Game_Display(BoardOne, BoardTwo, ShipsRemainingOne, ShipsRemainingTwo, AIDifficulty, std::to_string(NumberOfPlayers), true);
    Output += New_Line("                                                                     GAME OVER                                                                     ") + Empty_Line();
    Output += New_Line("                                                  " + CurrentPlayer + " has won! The game lasted " + std::to_string(NumberOfTurns) + " turns.                                                   ");
    Output += Empty_Line() + New_Line("                                                Press 'Q' to quit OR any other key to play again...                                                ");
    Output += Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    if (_getch() == 'q')
        GameIsRunning = false;
}

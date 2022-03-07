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

void Battleships::Play(const HANDLE &ConsoleHandle, CONSOLE_CURSOR_INFO &CursorInfo)
{
    Battleships::Game GameObject(ConsoleHandle, CursorInfo);

    while (true)
    {
        if (GameObject.Setup_Game()) // if true, quit to main menu
            return;

        while (!GameObject.Game_Over())
        {
            GameObject.Toggle_Current_Player();

            if (GameObject.Next_Turn_Is_User())
            {
                if (GameObject.Execute_Next_User_Command()) // if true, quit to main menu
                    return;
            }
            else
                GameObject.Execute_Next_AI_Command();
        }

        if (GameObject.Display_Game_Over_Message()) // if true, quit to main menu
            return;
    }
}

Battleships::Game::Game(const HANDLE &ConsoleHandle, CONSOLE_CURSOR_INFO &CursorInfo) : m_ConsoleHandle(ConsoleHandle), m_CursorInfo(CursorInfo) {}

Battleships::Game::~Game() {}

bool Battleships::Game::Setup_Game(void)
{
    m_MovesRemainingOne.clear();
    m_MovesRemainingTwo.clear();

    for (int i = 0, GridNumber = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++, GridNumber++)
        {
            m_BoardOne[i][j] = ' ';
            m_BoardTwo[i][j] = ' ';
            m_MovesRemainingOne.push_back(GridNumber);
            m_MovesRemainingTwo.push_back(GridNumber);
        }
    }

    m_ShipsRemainingOne.clear();
    m_ShipsRemainingOne['C'] = 5;
    m_ShipsRemainingOne['B'] = 4;
    m_ShipsRemainingOne['D'] = 3;
    m_ShipsRemainingOne['S'] = 3;
    m_ShipsRemainingOne['P'] = 2;

    m_ShipsRemainingTwo.clear();
    m_ShipsRemainingTwo['C'] = 5;
    m_ShipsRemainingTwo['B'] = 4;
    m_ShipsRemainingTwo['D'] = 3;
    m_ShipsRemainingTwo['S'] = 3;
    m_ShipsRemainingTwo['P'] = 2;

    m_AIDifficulty = "N/A";
    m_NumberOfPlayers = -1;
    m_NumberOfTurns = 0;
    m_PreviousCommand = 0;
    m_GameOver = false;
    std::srand(std::time(0));

    if (Get_Number_Of_Players())
        return true;

    if (Get_AI_Difficulty())
        return true;

    if (m_NumberOfPlayers == 1)
    {
        if (Get_User_Ship_Positions())
            return true;
    }
    else
        Get_AI_Ship_Positions(m_BoardOne);

    Get_AI_Ship_Positions(m_BoardTwo);

    std::rand() % 2 == 0 ? m_CurrentPlayer = "PLAYER ONE" : m_CurrentPlayer = "PLAYER TWO";

    return false;
}

bool Battleships::Game::Get_Number_Of_Players(void)
{
    std::string CommonString = Get_Game_Display();
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
        {
            m_NumberOfPlayers = CurrentSelection;
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool Battleships::Game::Get_AI_Difficulty(void)
{
    std::string CommonString = Get_Game_Display();
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
        {
            CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
            return false;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            return true;
    }
}

bool Battleships::Game::Get_User_Ship_Positions(void)
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

    m_CursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);

    for (int i = 0; i < 5; i++) // for each ship
    {
        std::vector<int> ShipRows, ShipColumns;
        std::string shipOrientation = "N/A";

        for (int j = 0; j < ShipSizes[i]; j++) // for each ship grid locations
        {
            std::string Output = Get_Game_Display();
            Output += New_Line(ShipInstructions[i]) + Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

            Output_To_Terminal(Output);

            int KeyPress = 0, Row = 0, Column = 0;

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
                    SetConsoleCursorPosition(m_ConsoleHandle, CursorPosition);

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
                        m_BoardOne[ShipRows.back()][ShipColumns.back()] = ' ';

                        Output = Get_Game_Display();
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
                        m_CursorInfo.bVisible = FALSE;
                        SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
                        return true;
                    }
                }

                // Check if grid location is already occupied by another ship
                if (m_BoardOne[Row][Column] == ' ')
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
                    KeyPress = 0;
            }

            m_BoardOne[Row][Column] = 'X';

            if (j == (ShipSizes[i] - 1))
            {
                lastShipRow = Row;
                lastShipColumn = Column;
            }
        }

        // Place ship
        for (unsigned int j = 0; j < ShipRows.size(); j++)
            m_BoardOne[ShipRows[j]][ShipColumns[j]] = ShipLetters[i];
    }

    m_CursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);

    return false;
}

void Battleships::Game::Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard)
{
    std::vector<int> ShipSizes = {5, 4, 3, 3, 2};
    std::vector<char> ShipLetters = {'C', 'B', 'D', 'S', 'P'};

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            std::vector<int> ShipRows, ShipColumns;
            int Row, Column;

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
            bool Errors = false;
            for (unsigned int j = 0; j < ShipRows.size(); j++)
                if (AIBoard[ShipRows[j]][ShipColumns[j]] == 'C' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'B' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'D' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'S' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'P')
                    Errors = true;

            if (!Errors) // Place ship
            {
                for (unsigned int j = 0; j < ShipRows.size(); j++)
                    AIBoard[ShipRows[j]][ShipColumns[j]] = ShipLetters[i];
                break;
            }
        }
    }
}

bool Battleships::Game::Game_Over(void)
{
    bool PlayerOneShipsPresent = false;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (m_BoardOne[i][j] == 'C' || m_BoardOne[i][j] == 'B' || m_BoardOne[i][j] == 'D' || m_BoardOne[i][j] == 'S' || m_BoardOne[i][j] == 'P')
                PlayerOneShipsPresent = true;

    bool PlayerTwoShipsPresent = false;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            if (m_BoardTwo[i][j] == 'C' || m_BoardTwo[i][j] == 'B' || m_BoardTwo[i][j] == 'D' || m_BoardTwo[i][j] == 'S' || m_BoardTwo[i][j] == 'P')
                PlayerTwoShipsPresent = true;

    !PlayerOneShipsPresent || !PlayerTwoShipsPresent ? m_GameOver = true : m_GameOver = false;
    return m_GameOver;
}

void Battleships::Game::Toggle_Current_Player(void)
{
    m_CurrentPlayer == "PLAYER ONE" ? m_CurrentPlayer = "PLAYER TWO" : m_CurrentPlayer = "PLAYER ONE";
}

bool Battleships::Game::Next_Turn_Is_User(void)
{
    return m_NumberOfPlayers == 1 && m_CurrentPlayer == "PLAYER ONE" ? true : false;
}

bool Battleships::Game::Execute_Next_User_Command(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line(" Player One, please enter your next command!                                                                                                       ");
    Output += Empty_Line() + Empty_Line() + Empty_Line() + Empty_Line() + Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    int KeyPress, Command, Row = m_PreviousCommand / 10, Column = m_PreviousCommand % 10;

    m_CursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);

    while (true)
    {
        while (true)
        {
            COORD CursorPosition;
            CursorPosition.X = 106 + Column * 4;
            CursorPosition.Y = 8 + Row * 2;
            SetConsoleCursorPosition(m_ConsoleHandle, CursorPosition);

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
                m_CursorInfo.bVisible = FALSE;
                SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
                return true;
            }
        }

        Command = Row * 10 + Column;
        auto CommandPosition = std::find(m_MovesRemainingOne.begin(), m_MovesRemainingOne.end(), Command);

        if (CommandPosition != m_MovesRemainingOne.end())
        {
            if (m_BoardTwo[Row][Column] == 'C' || m_BoardTwo[Row][Column] == 'B' || m_BoardTwo[Row][Column] == 'D' || m_BoardTwo[Row][Column] == 'S' || m_BoardTwo[Row][Column] == 'P')
            {
                m_ShipsRemainingTwo[m_BoardTwo[Row][Column]]--;
                m_BoardTwo[Row][Column] = 'X';
            }
            else
                m_BoardTwo[Row][Column] = '.';

            m_PreviousCommand = Command;

            m_NumberOfTurns++;

            m_MovesRemainingOne.erase(CommandPosition);

            m_CursorInfo.bVisible = FALSE;
            SetConsoleCursorInfo(m_ConsoleHandle, &m_CursorInfo);
            return false;
        }
        else
            KeyPress = 0;
    }
}

void Battleships::Game::Execute_Next_AI_Command(void)
{
    if (m_CurrentPlayer == "PLAYER ONE")
    {
        int Command = m_MovesRemainingOne[std::rand() % m_MovesRemainingOne.size()];
        int Row = Command / 10, Column = Command % 10;

        if (m_BoardTwo[Row][Column] == 'C' || m_BoardTwo[Row][Column] == 'B' || m_BoardTwo[Row][Column] == 'D' || m_BoardTwo[Row][Column] == 'S' || m_BoardTwo[Row][Column] == 'P')
        {
            m_ShipsRemainingTwo[m_BoardTwo[Row][Column]]--;
            m_BoardTwo[Row][Column] = 'X';
        }
        else
            m_BoardTwo[Row][Column] = '.';

        m_MovesRemainingOne.erase(std::find(m_MovesRemainingOne.begin(), m_MovesRemainingOne.end(), Command));
    }

    else
    {
        int Command = m_MovesRemainingTwo[std::rand() % m_MovesRemainingTwo.size()];
        int Row = Command / 10, Column = Command % 10;

        if (m_BoardOne[Row][Column] == 'C' || m_BoardOne[Row][Column] == 'B' || m_BoardOne[Row][Column] == 'D' || m_BoardOne[Row][Column] == 'S' || m_BoardOne[Row][Column] == 'P')
        {
            m_ShipsRemainingOne[m_BoardOne[Row][Column]]--;
            m_BoardOne[Row][Column] = 'X';
        }
        else
            m_BoardOne[Row][Column] = '.';

        m_MovesRemainingTwo.erase(std::find(m_MovesRemainingTwo.begin(), m_MovesRemainingTwo.end(), Command));
    }

    m_NumberOfTurns++;
}

bool Battleships::Game::Display_Game_Over_Message(void)
{
    std::string Output = Get_Game_Display();
    Output += New_Line("                                                                     GAME OVER                                                                     ") + Empty_Line();
    Output += New_Line("                                                  " + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.                                                   ");
    Output += Empty_Line() + New_Line("                                                Press 'Q' to quit OR any other key to play again...                                                ");
    Output += Bottom_Line() + Bottom_Bar();

    Output_To_Terminal(Output);

    return _getch() == 'q' ? true : false;
}

std::string Battleships::Game::Get_Game_Display(void)
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
                if (j < m_ShipsRemainingOne.at('B'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "              ";
            for (int j = 0; j < 4; j++, Output += " ")
            {
                if (j < (4 - m_ShipsRemainingTwo.at('B')))
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
                if (j < m_ShipsRemainingOne.at('S'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                      ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < (3 - m_ShipsRemainingTwo.at('S')))
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
            if (m_BoardOne[i][j] == 'C' || m_BoardOne[i][j] == 'B' || m_BoardOne[i][j] == 'D' || m_BoardOne[i][j] == 'S' || m_BoardOne[i][j] == 'P')
                Output.insert(Output.size(), 3, (char)178);
            else if (m_BoardOne[i][j] == 'X')
                Output.insert(Output.size(), 3, (char)176);
            else if (m_BoardOne[i][j] == '.')
                Output += std::string(" ") + (char)250 + " ";
            else
                Output += "   ";
            Output += (char)179;
        }

        // Centre Information
        if (i == 0)
        {
            if (m_NumberOfPlayers == -1)
                Output += "                # of Players = N/A                 ";
            else
                Output += "                 # of Players = " + std::to_string(m_NumberOfPlayers) + "                  ";
        }
        else if (i == 1)
        {
            if (m_AIDifficulty == "N/A")
                Output += "                AI Difficulty = N/A                ";
            else
                Output += "               AI Difficulty = " + m_AIDifficulty + "                ";
        }
        else if (i == 3) // Carrier
        {
            Output += "   ";
            for (int j = 0; j < 5; j++, Output += " ")
            {
                if (j < m_ShipsRemainingOne.at('C'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "      ";
            for (int j = 0; j < 5; j++, Output += " ")
            {
                if (j < (5 - m_ShipsRemainingTwo.at('C')))
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
                if (j < m_ShipsRemainingOne.at('D'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                      ";
            for (int j = 0; j < 3; j++, Output += " ")
            {
                if (j < (3 - m_ShipsRemainingTwo.at('D')))
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
                if (j < m_ShipsRemainingOne.at('P'))
                    Output.insert(Output.size(), 3, (char)178);
                else
                    Output.insert(Output.size(), 3, (char)176);
            }
            Output += "                              ";
            for (int j = 0; j < 2; j++, Output += " ")
            {
                if (j < (2 - m_ShipsRemainingTwo.at('P')))
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
            if ((m_GameOver || m_NumberOfPlayers == 0) && (m_BoardTwo[i][j] == 'C' || m_BoardTwo[i][j] == 'B' || m_BoardTwo[i][j] == 'D' || m_BoardTwo[i][j] == 'S' || m_BoardTwo[i][j] == 'P'))
                Output.insert(Output.size(), 3, (char)178);
            else if (m_BoardTwo[i][j] == 'X')
                Output.insert(Output.size(), 3, (char)176);
            else if (m_BoardTwo[i][j] == '.')
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

std::string Battleships::Game::New_Line(const std::string &Input)
{
    return (char)186 + Input + (char)186 + "\n";
}

std::string Battleships::Game::Empty_Line(void)
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), 147, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string Battleships::Game::Top_Line(void)
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), 147, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string Battleships::Game::Bottom_Line(void)
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), 147, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string Battleships::Game::Bottom_Bar(void)
{
    return Top_Line() + New_Line(RED + "                                                               q = quit to main menu                                                               " + WHITE) + Bottom_Line();
}

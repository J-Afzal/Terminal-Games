/**
 * @file Battleships.cpp
 * @author Junaid Afzal
 * @brief Implementation of Battleships.hpp
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "Terminal.hpp"
#include "QuitToMainMenu.hpp"
#include "Battleships.hpp"

Battleships::Battleships(const HANDLE &ConsoleHandle)
{
    m_Terminal.Set(ConsoleHandle, 147, "Battleships", "q = quit to main menu");
    m_RandomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Battleships::Setup_Game()
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

    Get_Number_Of_Players();

    Get_AI_Difficulty();

    if (m_NumberOfPlayers == 1)
        Get_User_Ship_Positions();
    else
        Get_AI_Ship_Positions(m_BoardOne);

    Get_AI_Ship_Positions(m_BoardTwo);

    m_RandomNumberGenerator() % 2 == 0 ? m_CurrentPlayer = "Player One" : m_CurrentPlayer = "Player Two";
}

bool Battleships::Game_Over()
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

    return !(PlayerOneShipsPresent && PlayerTwoShipsPresent) ? (m_GameOver = true) : (m_GameOver = false);
}

void Battleships::Toggle_Current_Player()
{
    m_CurrentPlayer == "Player One" ? m_CurrentPlayer = "Player Two" : m_CurrentPlayer = "Player One";
}

bool Battleships::Next_Turn_Is_User()
{
    return m_NumberOfPlayers == 1 && m_CurrentPlayer == "Player One";
}

void Battleships::Execute_Next_User_Command()
{
    std::string Output = Get_Game_Display();
    Output += m_Terminal.New_Line(" Player One, please enter your next command!                                                                                                       ");
    Output += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line();
    Output += m_Terminal.Bottom_Box();

    Terminal::Output_To_Terminal(Output);

    int KeyPress, Command, Row = m_PreviousCommand / 10, Column = m_PreviousCommand % 10;

    m_Terminal.Set_Cursor_Visibility(true);

    while (true)
    {
        while (true)
        {
            m_Terminal.Set_Cursor_Position(106 + Column * 4, 8 + Row * 2);

            KeyPress = _getch();

            if (KeyPress == '\r') // enter key
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
                m_Terminal.Set_Cursor_Visibility(false);
                throw QuitToMainMenu();
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

            m_Terminal.Set_Cursor_Visibility(false);

            return;
        }
    }
}

void Battleships::Execute_Next_AI_Command()
{
    if (m_CurrentPlayer == "Player One")
    {
        int Command = m_MovesRemainingOne[m_RandomNumberGenerator() % m_MovesRemainingOne.size()];
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
        int Command = m_MovesRemainingTwo[m_RandomNumberGenerator() % m_MovesRemainingTwo.size()];
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

void Battleships::Display_Game_Over_Message()
{
    std::string Output = Get_Game_Display();
    Output += m_Terminal.New_Line("                                                                     GAME OVER                                                                     ") + m_Terminal.Empty_Line();
    Output += m_Terminal.New_Line("                                                  " + m_CurrentPlayer + " has won! The game lasted " + std::to_string(m_NumberOfTurns) + " turns.                                                   ");
    Output += m_Terminal.Empty_Line() + m_Terminal.New_Line("                                                Press 'Q' to quit OR any other key to play again...                                                ") + m_Terminal.Bottom_Line();
    Output += m_Terminal.Bottom_Box();

    Terminal::Output_To_Terminal(Output);

    if (_getch() == 'q')
        throw QuitToMainMenu();
}

void Battleships::Get_Number_Of_Players()
{
    std::array<std::string, 2> Options;
    std::string GameDisplay = Get_Game_Display() + m_Terminal.New_Line(" Please select the number of human players:                                                                                                        ");

    Options[0] = GameDisplay;
    Options[0] += m_Terminal.New_Line(" > 0                                                                                                                                               ", "BLUE");
    Options[0] += m_Terminal.New_Line("   1                                                                                                                                               ");
    Options[0] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    Options[1] = GameDisplay;
    Options[1] += m_Terminal.New_Line("   0                                                                                                                                               ");
    Options[1] += m_Terminal.New_Line(" > 1                                                                                                                                               ", "BLUE");
    Options[1] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r') // enter key
        {
            m_NumberOfPlayers = CurrentSelection;
            return;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw QuitToMainMenu();
    }
}

void Battleships::Get_AI_Difficulty()
{
    std::array<std::string, 2> Options;
    std::string GameDisplay = Get_Game_Display() + m_Terminal.New_Line(" Please select the AI difficulty:                                                                                                                  ");

    Options[0] = GameDisplay;
    Options[0] += m_Terminal.New_Line(" > EASY                                                                                                                                            ", "BLUE");
    Options[0] += m_Terminal.New_Line("   HARD (Coming Soon!)                                                                                                                             ");
    Options[0] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    Options[1] = GameDisplay;
    Options[1] += m_Terminal.New_Line("   EASY                                                                                                                                            ");
    Options[1] += m_Terminal.New_Line(" > HARD (Coming Soon!)                                                                                                                             ", "BLUE");
    Options[1] += m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line() + m_Terminal.Bottom_Box();

    int KeyPress, CurrentSelection = 0;
    while (true)
    {
        Terminal::Output_To_Terminal(Options[CurrentSelection]);

        KeyPress = _getch();

        if (KeyPress == '\r' && CurrentSelection == 0)
        {
            // CurrentSelection == 0 ? m_AIDifficulty = "EASY" : m_AIDifficulty = "HARD";
            m_AIDifficulty = "EASY";
            return;
        }
        else if (KeyPress == 72) // up arrow key
            CurrentSelection == 0 ? CurrentSelection = 1 : --CurrentSelection;
        else if (KeyPress == 80) // down arrow key
            CurrentSelection == 1 ? CurrentSelection = 0 : ++CurrentSelection;
        else if (KeyPress == 'q')
            throw QuitToMainMenu();
    }
}

void Battleships::Get_User_Ship_Positions()
{
    std::array<std::string, 5> ShipInstructions = {
        "                                                 Please enter the 5 grid locations for the Carrier                                                 ",
        "                                               Please enter the 4 grid locations for the Battleship                                                ",
        "                                                Please enter the 3 grid locations for the Destroyer                                                ",
        "                                                Please enter the 3 grid locations for the Submarine                                                ",
        "                                               Please enter the 2 grid locations for the Patrol Boat                                               "};
    std::array<char, 5> ShipLetters = {'C', 'B', 'D', 'S', 'P'};
    std::array<int, 5> ShipSizes = {5, 4, 3, 3, 2};
    int lastShipRow = 0, lastShipColumn = 0;

    m_Terminal.Set_Cursor_Visibility(true);

    for (int i = 0; i < 5; i++) // for each ship
    {
        std::vector<int> ShipRows, ShipColumns;
        std::string ShipOrientation = "N/A";

        for (int j = 0; j < ShipSizes[i]; j++) // for each ship grid locations
        {
            std::string Output = Get_Game_Display();
            Output += m_Terminal.New_Line(ShipInstructions[i]) + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line();
            Output += m_Terminal.Bottom_Box();

            Terminal::Output_To_Terminal(Output);

            int KeyPress, Row, Column;

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
                    m_Terminal.Set_Cursor_Position(10 + Column * 4, 8 + Row * 2);

                    KeyPress = _getch();

                    if (KeyPress == '\r') // enter key
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
                        Output += m_Terminal.New_Line(ShipInstructions[i]) + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Empty_Line() + m_Terminal.Bottom_Line();
                        Output += m_Terminal.Bottom_Box();

                        Terminal::Output_To_Terminal(Output);

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
                        m_Terminal.Set_Cursor_Visibility(false);
                        throw QuitToMainMenu();
                    }
                }

                // Check if grid location is already occupied by another ship
                if (m_BoardOne[Row][Column] == ' ')
                {
                    if (ShipRows.empty())
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
                            continue;

                        if (ShipRows.size() == 1)
                        {
                            if (RowsSame)
                                ShipOrientation = "HORIZONTAL";
                            else
                                ShipOrientation = "VERTICAL";

                            ShipRows.push_back(Row);
                            ShipColumns.push_back(Column);
                            break;
                        }

                        else if (((RowsSame && (ShipOrientation == "HORIZONTAL") && (std::abs(Column - ShipColumns.back()) == 1)) || (ColumnsSame && (ShipOrientation == "VERTICAL") && (std::abs(Row - ShipRows.back()) == 1))))
                        {
                            // If row or column same then column must an increment or decrement of previous position if there is one
                            ShipRows.push_back(Row);
                            ShipColumns.push_back(Column);
                            break;
                        }
                    }
                }
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

    m_Terminal.Set_Cursor_Visibility(false);
}

void Battleships::Get_AI_Ship_Positions(std::array<std::array<char, 10>, 10> &AIBoard)
{
    std::array<int, 5> ShipSizes = {5, 4, 3, 3, 2};
    std::array<char, 5> ShipLetters = {'C', 'B', 'D', 'S', 'P'};

    for (int i = 0; i < 5; i++)
    {
        while (true)
        {
            std::vector<unsigned int> ShipRows, ShipColumns;
            unsigned int Row, Column;

            // Get a random ship position
            if ((m_RandomNumberGenerator() % 2) == 0) // Horizontal
            {
                // A max column number exists, as ship is horizontal, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Column = m_RandomNumberGenerator() % (11 - ShipSizes[i]);

                Row = m_RandomNumberGenerator() % 10; // Any row number allowed as ship is horizontal

                // Horizontal positions have a difference in columns of 1
                for (int j = 0; j < ShipSizes[i]; j++)
                {
                    ShipRows.push_back(Row);
                    ShipColumns.push_back(Column + j);
                }
            }

            else // Vertical
            {
                Column = m_RandomNumberGenerator() % 10; // Any column number allowed as ship is vertical

                // A max row number exists, as ship is vertical, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Row = m_RandomNumberGenerator() % (11 - ShipSizes[i]);

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

std::string Battleships::Get_Game_Display()
{
    // Top bar
    std::string Output = m_Terminal.Top_Box();

    // Main game box
    Output += m_Terminal.Top_Line();

    // Top row and letter co-ordinates of both boards
    Output += m_Terminal.New_Line("                    Player One                                                                                       Player Two                    ");

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
    Output += std::string("   ") + (char)186 + "\n" + m_Terminal.Empty_Line();

    return Output;
}

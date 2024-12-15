#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "games/Battleships.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

Battleships::Battleships(const bool& outputIsOnlyASCII)
{
    m_pageBuilder.SetProperties(Pages::BATTLESHIPS, outputIsOnlyASCII);
    m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

void Battleships::SetupGame()
{
    m_movesRemainingOne.clear();
    m_movesRemainingTwo.clear();

    for (uint32_t i = 0, GridNumber = 0; i < 10; i++)
    {
        for (uint32_t j = 0; j < 10; j++, GridNumber++)
        {
            m_boardOne[i][j] = ' ';
            m_boardTwo[i][j] = ' ';
            m_movesRemainingOne.push_back(GridNumber);
            m_movesRemainingTwo.push_back(GridNumber);
        }
    }

    m_shipsRemainingOne.clear();
    m_shipsRemainingOne['C'] = 5;
    m_shipsRemainingOne['B'] = 4;
    m_shipsRemainingOne['D'] = 3;
    m_shipsRemainingOne['S'] = 3;
    m_shipsRemainingOne['P'] = 2;

    m_shipsRemainingTwo.clear();
    m_shipsRemainingTwo['C'] = 5;
    m_shipsRemainingTwo['B'] = 4;
    m_shipsRemainingTwo['D'] = 3;
    m_shipsRemainingTwo['S'] = 3;
    m_shipsRemainingTwo['P'] = 2;

    m_AISpeedName = "N/A    ";
    m_playerCount = "N/A";
    m_turnCount = 0;
    m_previousCommand = 0;
    m_isGameOver = false;
    m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player One" : m_currentPlayer = "Player Two";
}

void Battleships::UpdateGameInfo()
{
    m_gameInfo.battleshipsStruct = { m_boardOne, m_boardTwo, m_shipsRemainingOne, m_shipsRemainingTwo, m_playerCount, m_AISpeedName, m_currentPlayer, m_turnCount, m_isGameOver };
}

void Battleships::GetUserOptions()
{
    GetPlayerCount();

    GetAISpeed();

    if (m_playerCount == "1  ")
        GetUserShipPositions();
    else
        GetAIShipPositions(m_boardOne);

    GetAIShipPositions(m_boardTwo);
}

void Battleships::GetPlayerCount()
{
    std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
    m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
}

void Battleships::GetAISpeed()
{
    std::vector<std::string> menus = m_pageBuilder.GetAISpeedOptionSelectionGamePages(m_gameInfo);
    m_AISpeed = Terminal::GetUserChoiceFromGameMenus(menus);

    if (m_AISpeed == 0)
        m_AISpeedName = "INSTANT";
    else if (m_AISpeed == 1)
    {
        m_AISpeed = 100;
        m_AISpeedName = "FAST   ";
    }
    else // == 2
    {
        m_AISpeed = 1000;
        m_AISpeedName = "SLOW   ";
    }
}

void Battleships::GetUserShipPositions()
{
    // The user is prompted to enter sequentially increasing or decreasing co-ordinates
    // for each ship, and repeatedly if needed, until a valid set of co-ordinates are given.
    // After passing the error checks, each set of co-ordinates is used to place a ship
    // on player one's board (as user is always player one).

    std::array<std::string, 5> shipInstructions = {
            "Please enter the 5 grid locations for the Carrier",
            "Please enter the 4 grid locations for the Battleship",
            "Please enter the 3 grid locations for the Destroyer",
            "Please enter the 3 grid locations for the Submarine",
            "Please enter the 2 grid locations for the Patrol Boat"
    };
    std::array<char, 5> shipLetters = {'C', 'B', 'D', 'S', 'P'};
    std::array<uint32_t, 5> shipSizes = {5, 4, 3, 3, 2};
    uint32_t lastShipRow = 0, lastShipColumn = 0;

    Terminal::SetCursorVisibility(true);

    for (uint32_t i = 0; i < 5; i++) // for each ship
    {
        std::vector<uint32_t> shipRows, shipColumns;
        bool shipOrientationHorizontal = false;
        bool shipOrientationVertical = false;

        for (uint32_t j = 0; j < shipSizes[i]; j++) // for each ship grid locations
        {
            Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, shipInstructions[i]));

            uint32_t keyPress, row, column;

            if (j == 0)
            {
                row = lastShipRow;
                column = lastShipColumn;
            }
            else
            {
                row = shipRows.back();
                column = shipColumns.back();
            }

            while (true) // while ship grid location incorrect
            {
                while (true) // enter not pressed
                {
                    Terminal::SetCursorPosition(10 + column * 4, 8 + row * 2);

                    keyPress = Terminal::GetNextKeyPress();

                    if (keyPress == '\r') // enter key
                        break;
                    else if (keyPress == 72) // up arrow key
                        row == 0 ? row = 9 : --row;
                    else if (keyPress == 80) // down arrow key
                        row == 9 ? row = 0 : ++row;
                    else if (keyPress == 75) // left arrow key
                        column == 0 ? column = 9 : --column;
                    else if (keyPress == 77) // right arrow key
                        column == 9 ? column = 0 : ++column;
                    else if (keyPress == 8 && j > 0) // backspace key (undo ship placement)
                    {
                        m_boardOne[shipRows.back()][shipColumns.back()] = ' ';

                        Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, shipInstructions[i]));

                        shipRows.pop_back();
                        shipColumns.pop_back();

                        j--;

                        // Reset ship orientation
                        if (j == 1)
                        {
                            shipOrientationHorizontal = false;
                            shipOrientationVertical = false;
                        }

                        // If all ship locations cleared cursor will be placed at previous ship last location as ShipRows/ShipColumns is now empty
                        if (j == 0)
                        {
                            row = lastShipRow;
                            column = lastShipColumn;
                        }
                        else // Put cursor at last entered ship placement for this ship
                        {
                            row = shipRows.back();
                            column = shipColumns.back();
                        }
                    }
                    else if (keyPress == 'q')
                    {
                        Terminal::SetCursorVisibility(false);
                        throw Exceptions::QuitGame();
                    }
                }

                // Only check if grid location is not occupied by another ship
                if (m_boardOne[row][column] == ' ')
                {
                    if (shipRows.empty()) // To avoid comparing Row/Column with themselves below
                    {
                        shipRows.push_back(row);
                        shipColumns.push_back(column);
                        break;
                    }

                    else
                    {
                        bool ColumnsSame = false, RowsSame = false;
                        if (shipRows.back() == row)
                            RowsSame = true;
                        if (shipColumns.back() == column)
                            ColumnsSame = true;

                        // check if row or column same/different but both cannot be different or same
                        if ((RowsSame && ColumnsSame) || (!RowsSame && !ColumnsSame))
                            continue;

                        if (RowsSame && (std::abs((int)column - (int)shipColumns.back()) == 1))
                        {
                            if (shipRows.size() == 1)
                            {
                                shipOrientationHorizontal = true;
                                shipRows.push_back(row);
                                shipColumns.push_back(column);
                                break; // And go to "Place ship" code below and then go to next j iteration
                            }
                            else if (shipOrientationHorizontal)
                            {
                                shipRows.push_back(row);
                                shipColumns.push_back(column);
                                break; // And go to "Place ship" code below and then go to next j iteration
                            }
                        }

                        else if (ColumnsSame && (std::abs((int)row - (int)shipRows.back()) == 1))
                        {
                            if (shipRows.size() == 1)
                            {
                                shipOrientationVertical = true;
                                shipRows.push_back(row);
                                shipColumns.push_back(column);
                                break; // And go to "Place ship" code below and then go to next j iteration
                            }
                            else if (shipOrientationVertical)
                            {
                                shipRows.push_back(row);
                                shipColumns.push_back(column);
                                break; // And go to "Place ship" code below and then go to next j iteration
                            }
                        }
                    }
                }
            }

            // Place ship
            m_boardOne[row][column] = 'X';
            if (j == (shipSizes[i] - 1)) // only on last j iteration
            {
                lastShipRow = row;
                lastShipColumn = column;
            }

            UpdateGameInfo();
        }

        // All grid location received and are valid, so place ship
        for (uint32_t j = 0; j < shipRows.size(); j++)
            m_boardOne[shipRows[j]][shipColumns[j]] = shipLetters[i];

        UpdateGameInfo();
    }

    Terminal::SetCursorVisibility(false);
}

void Battleships::GetAIShipPositions(std::array<std::array<char, 10>, 10>& AIBoard)
{
    std::array<uint32_t, 5> ShipSizes = {5, 4, 3, 3, 2};
    std::array<char, 5> ShipLetters = {'C', 'B', 'D', 'S', 'P'};

    for (uint32_t i = 0; i < 5; i++)
    {
        while (true)
        {
            std::vector<uint32_t> ShipRows, ShipColumns;
            uint32_t Row, Column;

            // Get a random ship position
            if ((m_randomNumberGenerator() % 2) == 0) // Horizontal
            {
                // A max column number exists, as ship is horizontal, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Column = m_randomNumberGenerator() % (11 - ShipSizes[i]);

                Row = m_randomNumberGenerator() % 10; // Any row number allowed as ship is horizontal

                // Horizontal positions have a difference in columns of 1
                for (uint32_t j = 0; j < ShipSizes[i]; j++)
                {
                    ShipRows.push_back(Row);
                    ShipColumns.push_back(Column + j);
                }
            }

            else // Vertical
            {
                Column = m_randomNumberGenerator() % 10; // Any column number allowed as ship is vertical

                // A max row number exists, as ship is vertical, which is linked with the size of the ship
                // with the assumption being this value will be the first and smallest of the positions
                Row = m_randomNumberGenerator() % (11 - ShipSizes[i]);

                // Vertical positions have a difference in rows of 1
                for (uint32_t j = 0; j < ShipSizes[i]; j++)
                {
                    ShipRows.push_back(Row + j);
                    ShipColumns.push_back(Column);
                }
            }

            // Check if ship is already located on requested ship position
            bool Errors = false;
            for (uint32_t j = 0; j < ShipRows.size(); j++)
                if (AIBoard[ShipRows[j]][ShipColumns[j]] == 'C' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'B' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'D' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'S' ||
                    AIBoard[ShipRows[j]][ShipColumns[j]] == 'P')
                    Errors = true;

            if (!Errors) // Place ship
            {
                for (uint32_t j = 0; j < ShipRows.size(); j++)
                    AIBoard[ShipRows[j]][ShipColumns[j]] = ShipLetters[i];
                break;
            }
        }
    }
}

bool Battleships::IsGameOver()
{
    bool PlayerOneShipsPresent = false;
    for (uint32_t i = 0; i < 10; i++)
        for (uint32_t j = 0; j < 10; j++)
            if (m_boardOne[i][j] == 'C' || m_boardOne[i][j] == 'B' || m_boardOne[i][j] == 'D' || m_boardOne[i][j] == 'S' || m_boardOne[i][j] == 'P')
                PlayerOneShipsPresent = true;

    bool PlayerTwoShipsPresent = false;
    for (uint32_t i = 0; i < 10; i++)
        for (uint32_t j = 0; j < 10; j++)
            if (m_boardTwo[i][j] == 'C' || m_boardTwo[i][j] == 'B' || m_boardTwo[i][j] == 'D' || m_boardTwo[i][j] == 'S' || m_boardTwo[i][j] == 'P')
                PlayerTwoShipsPresent = true;

    !(PlayerOneShipsPresent && PlayerTwoShipsPresent) ? m_isGameOver = true : m_isGameOver = false;

    return m_isGameOver;
}

void Battleships::ToggleCurrentPlayer()
{
    m_currentPlayer == "Player One" ? m_currentPlayer = "Player Two" : m_currentPlayer = "Player One";
}

bool Battleships::IsCurrentTurnUsers()
{
    return m_playerCount == "1  " && m_currentPlayer == "Player One";
}

void Battleships::ExecuteUserCommand()
{
    Terminal::PrintOutput(m_pageBuilder.GetUserCommandPage(m_gameInfo));

    Terminal::SetCursorVisibility(true);

    uint32_t KeyPress, Command, Row = m_previousCommand / 10, Column = m_previousCommand % 10;

    while (true)
    {
        while (true)
        {
            Terminal::SetCursorPosition(106 + Column * 4, 8 + Row * 2);

            KeyPress = Terminal::GetNextKeyPress();

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
                Terminal::SetCursorVisibility(false);
                throw Exceptions::QuitGame();
            }
        }

        Command = Row * 10 + Column;
        auto CommandPosition = std::find(m_movesRemainingOne.begin(), m_movesRemainingOne.end(), Command);

        if (CommandPosition != m_movesRemainingOne.end())
        {
            ExecuteCommand(m_boardTwo, m_shipsRemainingTwo, m_movesRemainingOne, Command);

            m_previousCommand = Command;

            Terminal::SetCursorVisibility(false);

            return;
        }
    }
}

void Battleships::ExecuteAICommand()
{
    if (m_AISpeed != 0)
    {
        Terminal::PrintOutput(m_pageBuilder.GetAICommandPage(m_gameInfo));
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::milliseconds(m_AISpeed));
    }

    if (m_currentPlayer == "Player One")
    {
        m_AICommand = m_movesRemainingOne[m_randomNumberGenerator() % m_movesRemainingOne.size()];
        ExecuteCommand(m_boardTwo, m_shipsRemainingTwo, m_movesRemainingOne, m_AICommand);
    }
    else
    {
        m_AICommand = m_movesRemainingTwo[m_randomNumberGenerator() % m_movesRemainingTwo.size()];
        ExecuteCommand(m_boardOne, m_shipsRemainingOne, m_movesRemainingTwo, m_AICommand);
    }
}

void Battleships::ExecuteCommand(
    std::array<std::array<char, 10>, 10>& opponentBoard,
    std::unordered_map<char, uint32_t>& opponentShipsRemaining,
    std::vector<uint32_t>& commandsRemaining,
    const uint32_t& command)
{
    uint32_t Row = command / 10, Column = command % 10;

    if (opponentBoard[Row][Column] == 'C' || opponentBoard[Row][Column] == 'B' || opponentBoard[Row][Column] == 'D' || opponentBoard[Row][Column] == 'S' || opponentBoard[Row][Column] == 'P')
    {
        opponentShipsRemaining[opponentBoard[Row][Column]]--;
        opponentBoard[Row][Column] = 'X';
    }
    else
        opponentBoard[Row][Column] = '.';

    commandsRemaining.erase(std::find(commandsRemaining.begin(), commandsRemaining.end(), command));

    m_turnCount++;
}

void Battleships::GameOver()
{
    Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

    if (Terminal::GetNextKeyPress() == 'q')
        throw Exceptions::QuitGame();
}

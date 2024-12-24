// NOLINTBEGIN

#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <format>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#include "games/Battleships.hpp"
#include "helpers/Constants.hpp"
#include "helpers/Exceptions.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Battleships::Battleships(const bool &onlyUseASCII)
    {
        m_pageBuilder.SetProperties(Pages::BATTLESHIPS, onlyUseASCII);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Battleships::SetupGame()
    {
        m_movesRemainingOne.clear();
        m_movesRemainingTwo.clear();
        for (uint32_t i = 0, GridNumber = 0; i < g_BATTLESHIPS_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < g_BATTLESHIPS_BOARD_WIDTH; j++, GridNumber++)
            {
                m_boardOne[i][j] = ' ';
                m_boardTwo[i][j] = ' ';
                m_movesRemainingOne.push_back(GridNumber);
                m_movesRemainingTwo.push_back(GridNumber);
            }
        }

        m_shipsRemainingOne = m_shipsRemainingTwo = {
            {g_BATTLESHIPS_CARRIER_NAME, g_BATTLESHIPS_CARRIER_SIZE},
            {g_BATTLESHIPS_BATTLESHIP_NAME, g_BATTLESHIPS_BATTLESHIP_SIZE},
            {g_BATTLESHIPS_DESTROYER_NAME, g_BATTLESHIPS_DESTROYER_SIZE},
            {g_BATTLESHIPS_SUBMARINE_NAME, g_BATTLESHIPS_SUBMARINE_SIZE},
            {g_BATTLESHIPS_PATROL_BOAT_NAME, g_BATTLESHIPS_PATROL_BOAT_SIZE}};

        m_AISpeedName = "N/A    ";
        m_playerCount = "N/A";
        m_turnCount = 0;
        m_previousCommand = 0;
        m_isGameOver = false;
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player One" : m_currentPlayer = "Player Two";
    }

    void Battleships::UpdateGameInfo()
    {
        m_gameInfo.battleshipsStruct = {
            .boardOne = m_boardOne,
            .boardTwo = m_boardTwo,
            .shipsRemainingOne = m_shipsRemainingOne,
            .shipsRemainingTwo = m_shipsRemainingTwo,
            .playerCount = m_playerCount,
            .AISpeedName = m_AISpeedName,
            .currentPlayer = m_currentPlayer,
            .turnCount = m_turnCount,
            .isGameOver = m_isGameOver};
    }

    void Battleships::GetUserOptions()
    {
        GetPlayerCount();

        GetAISpeed();

        if (m_playerCount == "1  ")
        {
            GetUserShipPositions();
        }

        else
        {
            GetAIShipPositions(m_boardOne);
        }

        GetAIShipPositions(m_boardTwo);
    }

    void Battleships::GetPlayerCount()
    {
        const std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
    }

    void Battleships::GetAISpeed()
    {
        const std::vector<std::string> menus = m_pageBuilder.GetAISpeedOptionSelectionGamePages(m_gameInfo);
        m_AISpeed = Terminal::GetUserChoiceFromGameMenus(menus);

        if (m_AISpeed == 0)
        {
            m_AISpeedName = "INSTANT";
        }

        else if (m_AISpeed == 1)
        {
            m_AISpeedName = "FAST   ";
        }

        else // == 2
        {
            m_AISpeedName = "SLOW   ";
        }
    }

    void Battleships::GetUserShipPositions()
    {
        // The user is prompted to enter sequentially increasing or decreasing co-ordinates
        // for each ship, and repeatedly if needed, until a valid set of co-ordinates are given.
        // After passing the error checks, each set of co-ordinates is used to place a ship
        // on player one's board (as user is always player one).

        std::array<std::string, g_BATTLESHIPS_SHIP_COUNT> shipInstructions = {
            std::format("Please enter the {} grid locations for the Carrier", g_BATTLESHIPS_CARRIER_SIZE),
            std::format("Please enter the {} grid locations for the Battleship", g_BATTLESHIPS_BATTLESHIP_SIZE),
            std::format("Please enter the {} grid locations for the Destroyer", g_BATTLESHIPS_DESTROYER_SIZE),
            std::format("Please enter the {} grid locations for the Submarine", g_BATTLESHIPS_SUBMARINE_SIZE),
            std::format("Please enter the {} grid locations for the Patrol Boat", g_BATTLESHIPS_PATROL_BOAT_SIZE)};
        std::array<std::string, g_BATTLESHIPS_SHIP_COUNT> shipLetters = {g_BATTLESHIPS_CARRIER_NAME, g_BATTLESHIPS_BATTLESHIP_NAME, g_BATTLESHIPS_DESTROYER_NAME, g_BATTLESHIPS_SUBMARINE_NAME, g_BATTLESHIPS_PATROL_BOAT_NAME};
        std::array<uint32_t, g_BATTLESHIPS_SHIP_COUNT> shipSizes = {g_BATTLESHIPS_CARRIER_SIZE, g_BATTLESHIPS_BATTLESHIP_SIZE, g_BATTLESHIPS_DESTROYER_SIZE, g_BATTLESHIPS_SUBMARINE_SIZE, g_BATTLESHIPS_PATROL_BOAT_SIZE};
        uint32_t lastShipRow = 0;
        uint32_t lastShipColumn = 0;

        Terminal::SetCursorVisibility(true);

        for (uint32_t i = 0; i < g_BATTLESHIPS_SHIP_COUNT; i++)
        {
            std::vector<uint32_t> shipRows;
            std::vector<uint32_t> shipColumns;
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
                    if (m_boardOne[row][column] == " ")
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

    void Battleships::GetAIShipPositions(std::array<std::array<std::string, g_BATTLESHIPS_BOARD_WIDTH>, g_BATTLESHIPS_BOARD_HEIGHT> &AIBoard)
    {
        std::array<std::string, g_BATTLESHIPS_SHIP_COUNT> shipLetters = {g_BATTLESHIPS_CARRIER_NAME, g_BATTLESHIPS_BATTLESHIP_NAME, g_BATTLESHIPS_DESTROYER_NAME, g_BATTLESHIPS_SUBMARINE_NAME, g_BATTLESHIPS_PATROL_BOAT_NAME};
        std::array<uint32_t, g_BATTLESHIPS_SHIP_COUNT> shipSizes = {g_BATTLESHIPS_CARRIER_SIZE, g_BATTLESHIPS_BATTLESHIP_SIZE, g_BATTLESHIPS_DESTROYER_SIZE, g_BATTLESHIPS_SUBMARINE_SIZE, g_BATTLESHIPS_PATROL_BOAT_SIZE};

        for (uint32_t i = 0; i < g_BATTLESHIPS_SHIP_COUNT; i++)
        {
            while (true)
            {
                std::vector<uint32_t> shipRows, shipColumns;
                uint32_t row, column;

                // Get a random ship position
                if ((m_randomNumberGenerator() % 2) == 0) // Horizontal
                {
                    // A max column number exists, as ship is horizontal, which is linked with the size of the ship
                    // with the assumption being this value will be the first and smallest of the positions
                    column = m_randomNumberGenerator() % (11 - shipSizes[i]);

                    row = m_randomNumberGenerator() % 10; // Any row number allowed as ship is horizontal

                    // Horizontal positions have a difference in columns of 1
                    for (uint32_t j = 0; j < shipSizes[i]; j++)
                    {
                        shipRows.push_back(row);
                        shipColumns.push_back(column + j);
                    }
                }

                else // Vertical
                {
                    column = m_randomNumberGenerator() % 10; // Any column number allowed as ship is vertical

                    // A max row number exists, as ship is vertical, which is linked with the size of the ship
                    // with the assumption being this value will be the first and smallest of the positions
                    row = m_randomNumberGenerator() % (11 - shipSizes[i]);

                    // Vertical positions have a difference in rows of 1
                    for (uint32_t j = 0; j < shipSizes[i]; j++)
                    {
                        shipRows.push_back(row + j);
                        shipColumns.push_back(column);
                    }
                }

                // Check if ship is already located on requested ship position
                bool errors = false;
                for (uint32_t j = 0; j < shipRows.size(); j++)
                    if (AIBoard[shipRows[j]][shipColumns[j]] == g_BATTLESHIPS_CARRIER_NAME ||
                        AIBoard[shipRows[j]][shipColumns[j]] == g_BATTLESHIPS_BATTLESHIP_NAME ||
                        AIBoard[shipRows[j]][shipColumns[j]] == g_BATTLESHIPS_DESTROYER_NAME ||
                        AIBoard[shipRows[j]][shipColumns[j]] == g_BATTLESHIPS_SUBMARINE_NAME ||
                        AIBoard[shipRows[j]][shipColumns[j]] == g_BATTLESHIPS_PATROL_BOAT_NAME)
                        errors = true;

                if (!errors) // Place ship
                {
                    for (uint32_t j = 0; j < shipRows.size(); j++)
                        AIBoard[shipRows[j]][shipColumns[j]] = shipLetters[i];
                    break;
                }
            }
        }
    }

    bool Battleships::IsGameOver()
    {
        bool playerOneShipsPresent = false;
        for (uint32_t i = 0; i < 10; i++)
            for (uint32_t j = 0; j < 10; j++)
                if (m_boardOne[i][j] == g_BATTLESHIPS_CARRIER_NAME || m_boardOne[i][j] == g_BATTLESHIPS_BATTLESHIP_NAME || m_boardOne[i][j] == g_BATTLESHIPS_DESTROYER_NAME || m_boardOne[i][j] == g_BATTLESHIPS_SUBMARINE_NAME || m_boardOne[i][j] == g_BATTLESHIPS_PATROL_BOAT_NAME)
                    playerOneShipsPresent = true;

        bool playerTwoShipsPresent = false;
        for (uint32_t i = 0; i < 10; i++)
            for (uint32_t j = 0; j < 10; j++)
                if (m_boardTwo[i][j] == g_BATTLESHIPS_CARRIER_NAME || m_boardTwo[i][j] == g_BATTLESHIPS_BATTLESHIP_NAME || m_boardTwo[i][j] == g_BATTLESHIPS_DESTROYER_NAME || m_boardTwo[i][j] == g_BATTLESHIPS_SUBMARINE_NAME || m_boardTwo[i][j] == g_BATTLESHIPS_PATROL_BOAT_NAME)
                    playerTwoShipsPresent = true;

        !(playerOneShipsPresent && playerTwoShipsPresent) ? m_isGameOver = true : m_isGameOver = false;

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

        uint32_t keyPress, command, row = m_previousCommand / 10, Column = m_previousCommand % 10;

        while (true)
        {
            while (true)
            {
                Terminal::SetCursorPosition(106 + Column * 4, 8 + row * 2);

                keyPress = Terminal::GetNextKeyPress();

                if (keyPress == '\r') // enter key
                    break;
                else if (keyPress == 72) // up arrow key
                    row == 0 ? row = 9 : --row;
                else if (keyPress == 80) // down arrow key
                    row == 9 ? row = 0 : ++row;
                else if (keyPress == 75) // left arrow key
                    Column == 0 ? Column = 9 : --Column;
                else if (keyPress == 77) // right arrow key
                    Column == 9 ? Column = 0 : ++Column;
                else if (keyPress == 'q')
                {
                    Terminal::SetCursorVisibility(false);
                    throw Exceptions::QuitGame();
                }
            }

            command = row * 10 + Column;
            auto CommandPosition = std::ranges::find(m_movesRemainingOne.begin(), m_movesRemainingOne.end(), command);

            if (CommandPosition != m_movesRemainingOne.end())
            {
                ExecuteCommand(m_boardTwo, m_shipsRemainingTwo, m_movesRemainingOne, command);

                m_previousCommand = command;

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
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_AISpeed));
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
        std::array<std::array<std::string, 10>, 10> &opponentBoard,
        std::unordered_map<std::string, uint32_t> &opponentShipsRemaining,
        std::vector<uint32_t> &commandsRemaining,
        const uint32_t &command)
    {
        uint32_t row = command / 10, column = command % 10;

        if (opponentBoard[row][column] == g_BATTLESHIPS_CARRIER_NAME || opponentBoard[row][column] == g_BATTLESHIPS_BATTLESHIP_NAME || opponentBoard[row][column] == g_BATTLESHIPS_DESTROYER_NAME || opponentBoard[row][column] == g_BATTLESHIPS_SUBMARINE_NAME || opponentBoard[row][column] == g_BATTLESHIPS_PATROL_BOAT_NAME)
        {
            opponentShipsRemaining[opponentBoard[row][column]]--;
            opponentBoard[row][column] = 'X';
        }
        else
            opponentBoard[row][column] = '.';

        commandsRemaining.erase(std::ranges::find(commandsRemaining.begin(), commandsRemaining.end(), command));

        m_turnCount++;
    }

    void Battleships::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == 'q')
            throw Exceptions::QuitGame();
    }
} // namespace TerminalGames

// NOLINTEND

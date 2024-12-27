#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "Constants.hpp"
#include "Exceptions.hpp"
#include "games/Battleships.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Battleships::Battleships(const bool &onlyUseASCII) // NOLINT(cert-msc32-c,cert-msc51-cpp,cppcoreguidelines-pro-type-member-init,hicpp-member-init)
    {
        m_pageBuilder.SetProperties(Pages::BATTLESHIPS, onlyUseASCII);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Battleships::SetupGame()
    {
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player One" : m_currentPlayer = "Player Two";
        m_commandsRemainingOne.clear();
        m_commandsRemainingTwo.clear();
        m_shipsRemainingOne = m_shipsRemainingTwo = {
            {g_BATTLESHIPS_CARRIER_NAME, g_BATTLESHIPS_CARRIER_SIZE},
            {g_BATTLESHIPS_BATTLESHIP_NAME, g_BATTLESHIPS_BATTLESHIP_SIZE},
            {g_BATTLESHIPS_DESTROYER_NAME, g_BATTLESHIPS_DESTROYER_SIZE},
            {g_BATTLESHIPS_SUBMARINE_NAME, g_BATTLESHIPS_SUBMARINE_SIZE},
            {g_BATTLESHIPS_PATROL_BOAT_NAME, g_BATTLESHIPS_PATROL_BOAT_SIZE}};
        m_previousCommand = {0, 0};
        m_computerSpeedName = "N/A    ";
        m_playerCount = "N/A";
        m_turnCount = 0;
        m_isGameOver = false;

        for (uint32_t i = 0; i < g_BATTLESHIPS_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < g_BATTLESHIPS_BOARD_WIDTH; j++)
            {
                m_boardOne[i][j] = "   "; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index) // TODO: this should use constants and probably same in tictactoe
                m_boardTwo[i][j] = "   "; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                m_commandsRemainingOne.emplace_back(i, j);
                m_commandsRemainingTwo.emplace_back(i, j);
            }
        }
    }

    void Battleships::UpdateGameInfo()
    {
        m_gameInfo.battleshipsStruct = {
            .boardOne = m_boardOne,
            .boardTwo = m_boardTwo,
            .shipsRemainingOne = m_shipsRemainingOne,
            .shipsRemainingTwo = m_shipsRemainingTwo,
            .computerSpeedName = m_computerSpeedName,
            .currentPlayer = m_currentPlayer,
            .playerCount = m_playerCount,
            .turnCount = m_turnCount,
            .isGameOver = m_isGameOver};
    }

    void Battleships::GetUserOptions()
    {
        GetPlayerCount();

        GetComputerSpeed();

        if (m_playerCount == "1  ")
        {
            GetUserShipPositions();
        }

        else
        {
            GetComputerShipPositions(m_boardOne);
        }

        GetComputerShipPositions(m_boardTwo);

        UpdateGameInfo();
    }

    bool Battleships::IsGameOver()
    {
        (IsShipPresent(m_boardOne) || IsShipPresent(m_boardTwo)) ? m_isGameOver = false : m_isGameOver = true;

        return m_isGameOver;
    }

    bool Battleships::IsShipPresent(std::array<std::array<std::string, g_BATTLESHIPS_BOARD_WIDTH>, g_BATTLESHIPS_BOARD_HEIGHT> &board)
    {
        for (const std::array<std::string, g_BATTLESHIPS_BOARD_WIDTH> &currentRow : board)
        {
            for (const std::string &currentValue : currentRow)
            {
                const auto currentValueFindLocation = ImplementStdRangesFind(g_BATTLESHIPS_SHIP_NAMES.begin(), g_BATTLESHIPS_SHIP_NAMES.end(), currentValue);

                if (currentValueFindLocation != g_BATTLESHIPS_SHIP_NAMES.end())
                {
                    return true;
                }
            }
        }

        return false;
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
        // This function is assumed to be only called during one player games where player one is the user and player two is the computer.

        const uint32_t startingRow = std::get<0>(m_previousCommand);
        const uint32_t startingColumn = std::get<1>(m_previousCommand);

        while (true)
        {
            const std::tuple<uint32_t, uint32_t> selectedCommand = Terminal::GetUserCommandFromGameGrid(m_pageBuilder, m_gameInfo, startingRow, startingColumn, g_BATTLESHIPS_BOARD_HEIGHT - 1, g_BATTLESHIPS_BOARD_WIDTH - 1, g_BATTLESHIPS_GRID_LEFT_PAD, g_BATTLESHIPS_GRID_TOP_PAD, g_BATTLESHIPS_GRID_ELEMENT_WIDTH, g_BATTLESHIPS_GRID_ELEMENT_HEIGHT, true);

            if (ValidateCommand(m_commandsRemainingOne, selectedCommand))
            {
                ExecuteGeneralCommand(m_boardTwo, m_shipsRemainingTwo, m_commandsRemainingOne, selectedCommand);
                m_previousCommand = selectedCommand;
                return;
            }
        }
    }

    void Battleships::ExecuteComputerCommand()
    {
        Terminal::PrintOutput(m_pageBuilder.GetComputerCommandPage(m_gameInfo));

        if (m_computerSpeed != 0)
        {
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));
        }

        if (m_currentPlayer == "Player One")
        {
            const std::tuple<uint32_t, uint32_t> selectedCommand = m_commandsRemainingOne[m_randomNumberGenerator() % m_commandsRemainingOne.size()];
            ExecuteGeneralCommand(m_boardTwo, m_shipsRemainingTwo, m_commandsRemainingOne, selectedCommand);
        }

        else
        {
            const std::tuple<uint32_t, uint32_t> selectedCommand = m_commandsRemainingTwo[m_randomNumberGenerator() % m_commandsRemainingTwo.size()];
            ExecuteGeneralCommand(m_boardOne, m_shipsRemainingOne, m_commandsRemainingTwo, selectedCommand);
        }
    }

    void Battleships::GameOver()
    {
        Terminal::PrintOutput(m_pageBuilder.GetGameOverPage(m_gameInfo));

        if (Terminal::GetNextKeyPress() == 'q')
        {
            throw Exceptions::QuitGame();
        }
    }

    void Battleships::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(menus)) + "  ";
    }

    void Battleships::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> menus = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(menus);

        if (m_computerSpeed == 0)
        {
            m_computerSpeedName = "INSTANT";
        }

        else if (m_computerSpeed == 1)
        {
            m_computerSpeedName = "FAST   ";
        }

        else // == 2
        {
            m_computerSpeedName = "SLOW   ";
        }
    }

    void Battleships::GetUserShipPositions()
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the computer.

        UpdateGameInfo();

        uint32_t startingRow = 0;
        uint32_t startingColumn = 0;
        uint32_t lastShipStartingRow = 0;
        uint32_t lastShipStartingColumn = 0;
        bool shipIsVertical = false;
        bool shipIsHorizontal = false;

        // For each ship
        for (uint32_t currentShip = 0; currentShip < g_BATTLESHIPS_SHIP_COUNT; currentShip++)
        {
            std::vector<std::tuple<uint32_t, uint32_t>> currentShipPositions;

            // For each ship grid location (intentionally a signed int)
            for (int32_t currentShipSize = 0; currentShipSize < g_BATTLESHIPS_SHIP_SIZES[currentShip]; currentShipSize++) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
            {
                // Set cursor position to the last known valid ship grid location selection
                if (!currentShipPositions.empty())
                {
                    startingRow = std::get<0>(currentShipPositions.back());
                    startingColumn = std::get<1>(currentShipPositions.back());
                }

                else // No valid ship grid locations selected for current ship so use previous ship's last known valid grid location
                {
                    startingRow = lastShipStartingRow;
                    startingColumn = lastShipStartingColumn;
                    // Reset these values
                    shipIsVertical = false;
                    shipIsHorizontal = false;
                }

                while (true) // While ship grid location is incorrect
                {
                    try
                    {
                        Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, g_BATTLESHIPS_SHIP_INSTRUCTIONS[currentShip])); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

                        const std::tuple<uint32_t, uint32_t> selectedShipGridLocation = Terminal::GetUserCommandFromGameGrid(m_pageBuilder, m_gameInfo, startingRow, startingColumn, g_BATTLESHIPS_BOARD_HEIGHT - 1, g_BATTLESHIPS_BOARD_WIDTH - 1, g_BATTLESHIPS_GRID_LEFT_PAD, g_BATTLESHIPS_GRID_TOP_PAD, g_BATTLESHIPS_GRID_ELEMENT_WIDTH, g_BATTLESHIPS_GRID_ELEMENT_HEIGHT, false);

                        if (ValidateUserShipPosition(currentShipPositions, selectedShipGridLocation, shipIsVertical, shipIsHorizontal))
                        {
                            currentShipPositions.push_back(selectedShipGridLocation);

                            // Place ship on selected grid location
                            m_boardOne[std::get<0>(selectedShipGridLocation)][std::get<1>(selectedShipGridLocation)] = g_BATTLESHIPS_SHIP_NAMES[currentShip]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index, performance-inefficient-string-concatenation)

                            UpdateGameInfo();

                            break;
                        }
                    }

                    catch (Exceptions::BackspaceKeyPressed &e)
                    {
                        if (currentShipSize != 0)
                        {
                            // Undo previous ship placement and refresh display
                            m_boardOne[std::get<0>(currentShipPositions.back())][std::get<1>(currentShipPositions.back())] = "   "; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index) // TODO: hardcoded value
                            UpdateGameInfo();
                            currentShipPositions.pop_back();
                            Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, g_BATTLESHIPS_SHIP_INSTRUCTIONS[currentShip])); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

                            // Go back one in for loop (and another -1 to account for increment)
                            currentShipSize -= 2;

                            break;
                        }
                    }
                }
            }

            // Update the last known ship grid location selection for when no ship grid locations selected
            lastShipStartingRow = std::get<0>(currentShipPositions.back());
            lastShipStartingColumn = std::get<1>(currentShipPositions.back());
        }
    }

    bool Battleships::ValidateUserShipPosition(
        const std::vector<std::tuple<uint32_t, uint32_t>> &currentShipPositions,
        const std::tuple<uint32_t, uint32_t> &selectedShipGridLocation,
        bool &shipIsVertical, // NOLINT(bugprone-easily-swappable-parameters)
        bool &shipIsHorizontal)
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the computer.

        const uint32_t selectedShipGridRow = std::get<0>(selectedShipGridLocation);
        const uint32_t selectedShipGridColumn = std::get<1>(selectedShipGridLocation);

        if (m_boardOne[selectedShipGridRow][selectedShipGridColumn] != "   ") // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index) // TODO: hardcoded value
        {
            return false;
        }

        if (currentShipPositions.empty())
        {
            return true;
        }

        const uint32_t previousSelectedShipGridRow = std::get<0>(currentShipPositions.back());
        const uint32_t previousSelectedShipGridColumn = std::get<1>(currentShipPositions.back());

        // As selected grid locations are added incrementally only the previous selection needs to be checked.
        const bool rowsAreTheSame = previousSelectedShipGridRow == selectedShipGridRow;
        const bool columnsAreTheSame = previousSelectedShipGridColumn == selectedShipGridColumn;

        // Prevents selection of a diagonal grid location relative to the previous selection.
        if (!rowsAreTheSame && !columnsAreTheSame)
        {
            return false;
        }

        const uint32_t rowDifferenceToPreviousSelection = std::abs(static_cast<int>(selectedShipGridRow) - static_cast<int>(previousSelectedShipGridRow));
        const uint32_t columnDifferenceToPreviousSelection = std::abs(static_cast<int>(selectedShipGridColumn) - static_cast<int>(previousSelectedShipGridColumn));

        // Only adjacents grid locations are allowed
        if ((rowDifferenceToPreviousSelection > 1) && (columnDifferenceToPreviousSelection > 1))
        {
            return false;
        }

        if (currentShipPositions.size() == 1)
        {
            shipIsHorizontal = rowsAreTheSame;
            shipIsVertical = columnsAreTheSame;
            return true;
        }

        if (shipIsHorizontal && !rowsAreTheSame)
        {
            return false;
        }

        if (shipIsVertical && !columnsAreTheSame)
        {
            return false;
        }

        return true;
    }

    void Battleships::GetComputerShipPositions(std::array<std::array<std::string, g_BATTLESHIPS_BOARD_WIDTH>, g_BATTLESHIPS_BOARD_HEIGHT> &board) // NOLINT(readability-function-cognitive-complexity)
    {
        // For each ship
        for (uint32_t currentShip = 0; currentShip < g_BATTLESHIPS_SHIP_COUNT; currentShip++)
        {
            while (true)
            {
                std::vector<std::tuple<uint32_t, uint32_t>> shipPositions;
                uint32_t startingRow = 0;
                uint32_t startingColumn = 0;

                // Get a random ship orientation
                if (static_cast<bool>(m_randomNumberGenerator() % 2)) // Horizontal
                {
                    // As the ship will be placed horizontally and assuming the first column value will be the smallest and all
                    // other column values will increment, then a max starting column value exists which is linked with the size
                    // of the ship. Therefore get a random value from 0 to the max starting column value.

                    startingRow = m_randomNumberGenerator() % g_BATTLESHIPS_BOARD_HEIGHT; // Any row value allowed as ship is horizontal

                    startingColumn = m_randomNumberGenerator() % (g_BATTLESHIPS_BOARD_WIDTH - g_BATTLESHIPS_SHIP_SIZES[currentShip]); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

                    // Column values increment by one
                    for (uint32_t i = 0; i < g_BATTLESHIPS_SHIP_SIZES[currentShip]; i++) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                    {
                        shipPositions.emplace_back(startingRow, startingColumn + i);
                    }
                }

                else // Vertical
                {
                    // As the ship will be placed vertically and assuming the first row value will be the smallest and all other
                    // row values will increment, then a max starting row value exists which is linked with the size of the
                    // ship. Therefore get a random value from 0 to the max starting row value.

                    startingRow = m_randomNumberGenerator() % (g_BATTLESHIPS_BOARD_HEIGHT - g_BATTLESHIPS_SHIP_SIZES[currentShip]); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

                    startingColumn = m_randomNumberGenerator() % g_BATTLESHIPS_BOARD_WIDTH; // Any column value allowed as ship is vertical

                    // Row values increment by one
                    for (uint32_t j = 0; j < g_BATTLESHIPS_SHIP_SIZES[currentShip]; j++) // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                    {
                        shipPositions.emplace_back(startingRow + j, startingColumn);
                    }
                }

                // Check if a ship has already been placed at the requested ship positions for the current ship
                bool locationIsAlreadyOccupied = false;
                for (std::tuple<uint32_t, uint32_t> currentPosition : shipPositions)
                {

                    const auto currentPositionFindLocation = ImplementStdRangesFind(
                        g_BATTLESHIPS_SHIP_NAMES.begin(),
                        g_BATTLESHIPS_SHIP_NAMES.end(),
                        board[std::get<0>(currentPosition)][std::get<1>(currentPosition)]); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

                    if (currentPositionFindLocation != g_BATTLESHIPS_SHIP_NAMES.end())
                    {
                        locationIsAlreadyOccupied = true;
                        break;
                    }
                }

                // Place ship
                if (!locationIsAlreadyOccupied)
                {
                    for (std::tuple<uint32_t, uint32_t> currentPosition : shipPositions)
                    {
                        board[std::get<0>(currentPosition)][std::get<1>(currentPosition)] = g_BATTLESHIPS_SHIP_NAMES[currentShip]; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
                    }

                    break; // Go to next ship to place
                }
            }
        }
    }

    bool Battleships::ValidateCommand(const std::vector<std::tuple<uint32_t, uint32_t>> &commandsRemaining, const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandFindLocation = ImplementStdRangesFind(commandsRemaining.begin(), commandsRemaining.end(), command);

        return commandFindLocation != commandsRemaining.end();
    }

    void Battleships::ExecuteGeneralCommand(
        std::array<std::array<std::string, g_BATTLESHIPS_BOARD_WIDTH>, g_BATTLESHIPS_BOARD_HEIGHT> &opponentBoard,
        std::unordered_map<std::string, uint32_t> &opponentShipsRemaining,
        std::vector<std::tuple<uint32_t, uint32_t>> &commandsRemaining,
        const std::tuple<uint32_t, uint32_t> &command)
    {
        const auto commandFindLocation = ImplementStdRangesFind(commandsRemaining.begin(), commandsRemaining.end(), command);
        const uint32_t row = std::get<0>(command);
        const uint32_t column = std::get<1>(command);

        const auto currentValueFindLocation = ImplementStdRangesFind(g_BATTLESHIPS_SHIP_NAMES.begin(), g_BATTLESHIPS_SHIP_NAMES.end(), opponentBoard[row][column]); // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)

        if (currentValueFindLocation != g_BATTLESHIPS_SHIP_NAMES.end())
        {
            opponentShipsRemaining[opponentBoard[row][column]]--;                                                                     // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
            opponentBoard[row][column] = g_BATTLESHIPS_SUCCESSFUL_ATTACK + opponentBoard[row][column][1] + g_BATTLESHIPS_SUCCESSFUL_ATTACK; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        }

        else
        {
            opponentBoard[row][column] = " " + g_BATTLESHIPS_MISSED_ATTACK + " "; // NOLINT(cppcoreguidelines-pro-bounds-constant-array-index)
        }

        commandsRemaining.erase(commandFindLocation);

        m_turnCount++;
    }
} // namespace TerminalGames

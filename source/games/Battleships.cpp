#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <string>
#include <thread>
#include <tuple>
#include <unordered_map>
#include <vector>

#include "games/Battleships.hpp"
#include "helpers/Globals.hpp"
#include "helpers/PageBuilder.hpp"
#include "helpers/Terminal.hpp"

namespace TerminalGames
{
    Battleships::Battleships(const bool& p_useAnsiEscapeCodes) :
        m_computerSpeed(0),
        m_turnCount(0),
        m_hasSavedGameSettings(false),
        m_isGameOver(false),
        m_saveGameSettings(false)
    {
        m_pageBuilder.SetProperties(Pages::BATTLESHIPS, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Battleships::SetupGame()
    {
        m_randomNumberGenerator() % 2 == 0 ? m_currentPlayer = "Player One" : m_currentPlayer = "Player Two";
        m_shipsRemainingOne = m_shipsRemainingTwo = {
            {Globals::G_BATTLESHIPS_CARRIER_NAME,     Globals::G_BATTLESHIPS_CARRIER_SIZE    },
            {Globals::G_BATTLESHIPS_BATTLESHIP_NAME,  Globals::G_BATTLESHIPS_BATTLESHIP_SIZE },
            {Globals::G_BATTLESHIPS_DESTROYER_NAME,   Globals::G_BATTLESHIPS_DESTROYER_SIZE  },
            {Globals::G_BATTLESHIPS_SUBMARINE_NAME,   Globals::G_BATTLESHIPS_SUBMARINE_SIZE  },
            {Globals::G_BATTLESHIPS_PATROL_BOAT_NAME, Globals::G_BATTLESHIPS_PATROL_BOAT_SIZE}
        };
        m_previousCommand = {0, 0};
        m_turnCount = 0;
        m_isGameOver = false;

        for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_BOARD_HEIGHT; i++)
        {
            for (uint32_t j = 0; j < Globals::G_BATTLESHIPS_BOARD_WIDTH; j++)
            {
                m_boardOne.at(i).at(j) = "   ";
                m_boardTwo.at(i).at(j) = "   ";
                m_commandsRemainingOne.emplace_back(i, j);
                m_commandsRemainingTwo.emplace_back(i, j);
            }
        }
    }

    void Battleships::GetUserOptions()
    {
        if (!(m_saveGameSettings && m_hasSavedGameSettings))
        {
            m_computerSpeedName = "N/A    ";
            m_playerCount = "N/A";

            GetPlayerCount();

            GetComputerSpeed();
        }

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

    void Battleships::UpdateGameInfo()
    {
        m_gameInfo.m_battleshipsGameInfo = {
            .m_boardOne = m_boardOne,
            .m_boardTwo = m_boardTwo,
            .m_shipsRemainingOne = m_shipsRemainingOne,
            .m_shipsRemainingTwo = m_shipsRemainingTwo,
            .m_computerSpeedName = m_computerSpeedName,
            .m_currentPlayer = m_currentPlayer,
            .m_playerCount = m_playerCount,
            .m_turnCount = m_turnCount,
            .m_isGameOver = m_isGameOver};
    }

    bool Battleships::IsGameOver()
    {
        (IsShipPresent(m_boardOne) || IsShipPresent(m_boardTwo)) ? m_isGameOver = false : m_isGameOver = true;

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
        // This function is assumed to be only called during one player games where player one is the user and player two is the computer.

        while (true)
        {
            const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = Terminal::GetUserCommandFromGameGrid(m_previousCommand, m_pageBuilder, m_gameInfo, true);

            if (ValidateCommand(m_commandsRemainingOne, SELECTED_COMMAND))
            {
                ExecuteGeneralCommand(m_boardTwo, m_shipsRemainingTwo, m_commandsRemainingOne, SELECTED_COMMAND);
                m_previousCommand = SELECTED_COMMAND;
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
            const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = m_commandsRemainingOne[m_randomNumberGenerator() % m_commandsRemainingOne.size()];
            ExecuteGeneralCommand(m_boardTwo, m_shipsRemainingTwo, m_commandsRemainingOne, SELECTED_COMMAND);
        }

        else
        {
            const std::tuple<uint32_t, uint32_t> SELECTED_COMMAND = m_commandsRemainingTwo[m_randomNumberGenerator() % m_commandsRemainingTwo.size()];
            ExecuteGeneralCommand(m_boardOne, m_shipsRemainingOne, m_commandsRemainingTwo, SELECTED_COMMAND);
        }
    }

    void Battleships::GameOver()
    {
        Terminal::GetUserChoiceFromGameOverMenu(m_pageBuilder.GetGameOverPage(m_gameInfo), m_pageBuilder.GetQuitOptionSelectionPage());
    }

    void Battleships::RestartGame()
    {
        m_saveGameSettings = true;
    }

    void Battleships::ResetGame()
    {
        m_saveGameSettings = false;
        m_hasSavedGameSettings = false;
    }

    void Battleships::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_playerCount = std::to_string(Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)) + "  ";
    }

    void Battleships::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS);

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
        std::tuple<bool, bool> shipIsHorizontalOrVertical = {false, false};

        // For each ship
        for (uint32_t currentShip = 0; currentShip < Globals::G_BATTLESHIPS_SHIP_COUNT; currentShip++)
        {
            std::vector<std::tuple<uint32_t, uint32_t>> currentShipPositions;

            // For each ship grid location (intentionally a signed int)
            for (int32_t currentShipSize = 0; currentShipSize < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); currentShipSize++)
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
                    shipIsHorizontalOrVertical = {false, false}; // Reset these values
                }

                while (true) // While ship grid location is incorrect
                {
                    try
                    {
                        Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, Globals::G_BATTLESHIPS_SHIP_INSTRUCTIONS.at(currentShip)));

                        const std::tuple<uint32_t, uint32_t> SELECTED_SHIP_GRID_LOCATION = Terminal::GetUserCommandFromGameGrid({startingRow, startingColumn}, m_pageBuilder, m_gameInfo, false);

                        if (ValidateUserShipPosition(currentShipPositions, SELECTED_SHIP_GRID_LOCATION, shipIsHorizontalOrVertical))
                        {
                            currentShipPositions.push_back(SELECTED_SHIP_GRID_LOCATION);

                            // Place ship on selected grid location
                            m_boardOne.at(std::get<0>(SELECTED_SHIP_GRID_LOCATION)).at(std::get<1>(SELECTED_SHIP_GRID_LOCATION)) = Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip);

                            UpdateGameInfo();

                            break;
                        }
                    }

                    catch (Globals::Exceptions::BackspaceKeyPressed& e)
                    {
                        if (currentShipSize != 0)
                        {
                            // Undo previous ship placement and refresh display
                            m_boardOne.at(std::get<0>(currentShipPositions.back())).at(std::get<1>(currentShipPositions.back())) = "   ";
                            UpdateGameInfo();
                            currentShipPositions.pop_back();
                            Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, Globals::G_BATTLESHIPS_SHIP_INSTRUCTIONS.at(currentShip)));

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
        const std::vector<std::tuple<uint32_t, uint32_t>>& p_currentShipPositions,
        const std::tuple<uint32_t, uint32_t>& p_selectedShipGridLocation,
        std::tuple<bool, bool>& p_shipIsHorizontalOrVertical)
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the computer.

        const uint32_t SELECTED_SHIP_GRID_ROW = std::get<0>(p_selectedShipGridLocation);
        const uint32_t SELECTED_SHIP_GRID_COLUMN = std::get<1>(p_selectedShipGridLocation);

        if (m_boardOne.at(SELECTED_SHIP_GRID_ROW).at(SELECTED_SHIP_GRID_COLUMN) != "   ")
        {
            return false;
        }

        if (p_currentShipPositions.empty())
        {
            return true;
        }

        const uint32_t PREVIOUS_SELECTED_SHIP_GRID_ROW = std::get<0>(p_currentShipPositions.back());
        const uint32_t PREVIOUS_SELECTED_SHIP_GRID_COLUMN = std::get<1>(p_currentShipPositions.back());

        // As selected grid locations are added incrementally only the previous selection needs to be checked.
        const bool ROWS_ARE_THE_SAME = PREVIOUS_SELECTED_SHIP_GRID_ROW == SELECTED_SHIP_GRID_ROW;
        const bool COLUMNS_ARE_THE_SAME = PREVIOUS_SELECTED_SHIP_GRID_COLUMN == SELECTED_SHIP_GRID_COLUMN;

        // Prevents selection of a diagonal grid location relative to the previous selection.
        if (!ROWS_ARE_THE_SAME && !COLUMNS_ARE_THE_SAME)
        {
            return false;
        }

        const uint32_t ROW_DIFFERENCE_TO_PREVIOUS_SELECTION = std::abs(static_cast<int>(SELECTED_SHIP_GRID_ROW) - static_cast<int>(PREVIOUS_SELECTED_SHIP_GRID_ROW));
        const uint32_t COLUMN_DIFFERENCE_TO_PREVIOUS_SELECTION = std::abs(static_cast<int>(SELECTED_SHIP_GRID_COLUMN) - static_cast<int>(PREVIOUS_SELECTED_SHIP_GRID_COLUMN));

        // Only adjacents grid locations are allowed
        if ((ROW_DIFFERENCE_TO_PREVIOUS_SELECTION > 1) && (COLUMN_DIFFERENCE_TO_PREVIOUS_SELECTION > 1))
        {
            return false;
        }

        if (p_currentShipPositions.size() == 1)
        {
            p_shipIsHorizontalOrVertical = {ROWS_ARE_THE_SAME, COLUMNS_ARE_THE_SAME};
            return true;
        }

        if (std::get<0>(p_shipIsHorizontalOrVertical) && !ROWS_ARE_THE_SAME)
        {
            return false;
        }

        if (std::get<1>(p_shipIsHorizontalOrVertical) && !COLUMNS_ARE_THE_SAME)
        {
            return false;
        }

        return true;
    }

    void Battleships::GetComputerShipPositions(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board) // NOLINT(readability-function-cognitive-complexity)
    {
        // For each ship
        for (uint32_t currentShip = 0; currentShip < Globals::G_BATTLESHIPS_SHIP_COUNT; currentShip++)
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

                    startingRow = m_randomNumberGenerator() % Globals::G_BATTLESHIPS_BOARD_HEIGHT; // Any row value allowed as ship is horizontal

                    startingColumn = m_randomNumberGenerator() % (Globals::G_BATTLESHIPS_BOARD_WIDTH - Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip));

                    // Column values increment by one
                    for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); i++)
                    {
                        shipPositions.emplace_back(startingRow, startingColumn + i);
                    }
                }

                else // Vertical
                {
                    // As the ship will be placed vertically and assuming the first row value will be the smallest and all other
                    // row values will increment, then a max starting row value exists which is linked with the size of the
                    // ship. Therefore get a random value from 0 to the max starting row value.

                    startingRow = m_randomNumberGenerator() % (Globals::G_BATTLESHIPS_BOARD_HEIGHT - Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip));

                    startingColumn = m_randomNumberGenerator() % Globals::G_BATTLESHIPS_BOARD_WIDTH; // Any column value allowed as ship is vertical

                    // Row values increment by one
                    for (uint32_t j = 0; j < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); j++)
                    {
                        shipPositions.emplace_back(startingRow + j, startingColumn);
                    }
                }

                // Check if a ship has already been placed at the requested ship positions for the current ship
                bool locationIsAlreadyOccupied = false;
                for (std::tuple<uint32_t, uint32_t> currentPosition : shipPositions)
                {
                    const auto CURRENT_POSITION_FIND_LOCATION = Globals::ImplementStdRangesFind(
                        Globals::G_BATTLESHIPS_SHIP_NAMES.begin(),
                        Globals::G_BATTLESHIPS_SHIP_NAMES.end(),
                        p_board.at(std::get<0>(currentPosition)).at(std::get<1>(currentPosition)));

                    if (CURRENT_POSITION_FIND_LOCATION != Globals::G_BATTLESHIPS_SHIP_NAMES.end())
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
                        p_board.at(std::get<0>(currentPosition)).at(std::get<1>(currentPosition)) = Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip);
                    }

                    break; // Go to next ship to place
                }
            }
        }
    }

    bool Battleships::IsShipPresent(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board)
    {
        for (const std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>& currentRow : p_board)
        {
            for (const std::string& currentValue : currentRow)
            {
                const auto CURRENT_VALUE_FIND_LOCATION = Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), currentValue);

                if (CURRENT_VALUE_FIND_LOCATION != Globals::G_BATTLESHIPS_SHIP_NAMES.end())
                {
                    return true;
                }
            }
        }

        return false;
    }

    bool Battleships::ValidateCommand(const std::vector<std::tuple<uint32_t, uint32_t>>& p_commandsRemaining, const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = Globals::ImplementStdRangesFind(p_commandsRemaining.begin(), p_commandsRemaining.end(), p_command);

        return COMMAND_FIND_LOCATION != p_commandsRemaining.end();
    }

    void Battleships::ExecuteGeneralCommand(
        std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_opponentBoard,
        std::unordered_map<std::string, uint32_t>& p_opponentShipsRemaining,
        std::vector<std::tuple<uint32_t, uint32_t>>& p_commandsRemaining,
        const std::tuple<uint32_t, uint32_t>& p_command)
    {
        const auto COMMAND_FIND_LOCATION = Globals::ImplementStdRangesFind(p_commandsRemaining.begin(), p_commandsRemaining.end(), p_command);
        const uint32_t ROW = std::get<0>(p_command);
        const uint32_t COLUMN = std::get<1>(p_command);

        const auto CURRENT_VALUE_FIND_LOCATION = Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), p_opponentBoard.at(ROW).at(COLUMN));

        if (CURRENT_VALUE_FIND_LOCATION != Globals::G_BATTLESHIPS_SHIP_NAMES.end())
        {
            p_opponentShipsRemaining.at(p_opponentBoard.at(ROW).at(COLUMN))--;
            p_opponentBoard.at(ROW).at(COLUMN) = Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK + p_opponentBoard.at(ROW).at(COLUMN).at(1) + Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK;
        }

        else
        {
            p_opponentBoard.at(ROW).at(COLUMN) = " " + Globals::G_BATTLESHIPS_MISSED_ATTACK + " ";
        }

        p_commandsRemaining.erase(COMMAND_FIND_LOCATION);

        m_turnCount++;
    }
}

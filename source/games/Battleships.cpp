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
        m_hasSavedGameOptions(false),
        m_isGameOver(false),
        m_saveGameOptions(false)
    {
        m_pageBuilder.SetProperties(Pages::BATTLESHIPS, p_useAnsiEscapeCodes);
        m_randomNumberGenerator.seed(std::chrono::system_clock::now().time_since_epoch().count());
    }

    void Battleships::SetupGame()
    {
        m_currentPlayer = Globals::G_BATTLESHIPS_PLAYER_CHOICE_OPTIONS[m_randomNumberGenerator() % 2];
        m_shipsRemainingOne = Globals::G_BATTLESHIPS_STARTING_SHIP_REMAINING;
        m_shipsRemainingTwo = Globals::G_BATTLESHIPS_STARTING_SHIP_REMAINING;
        m_previousCommand = {0, 0};
        m_turnCount = 0;
        m_isGameOver = false;

        for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_BOARD_HEIGHT; i++)
            for (uint32_t j = 0; j < Globals::G_BATTLESHIPS_BOARD_WIDTH; j++)
            {
                m_boardOne.at(i).at(j) = Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE;
                m_boardTwo.at(i).at(j) = Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE;
                m_commandsRemainingOne.emplace_back(i, j);
                m_commandsRemainingTwo.emplace_back(i, j);
            }
    }

    void Battleships::GetUserOptions()
    {
        if (!(m_saveGameOptions && m_hasSavedGameOptions))
        {
            m_computerSpeedName = Globals::G_GAME_UNKNOWN_OPTION;
            m_playerCount = Globals::G_GAME_UNKNOWN_OPTION;

            GetPlayerCount();
            GetComputerSpeed();
        }

        if (m_playerCount == "1")
            GetUserShipPositions();
        else
            GetComputerShipPositions(m_boardOne);

        GetComputerShipPositions(m_boardTwo);
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
            .m_isGameOver = m_isGameOver,
        };
    }

    bool Battleships::IsGameOver()
    {
        (IsShipPresent(m_boardOne) || IsShipPresent(m_boardTwo)) ? m_isGameOver = false : m_isGameOver = true;

        return m_isGameOver;
    }

    void Battleships::ToggleCurrentPlayer()
    {
        m_currentPlayer == Globals::G_BATTLESHIPS_PLAYER_ONE ? m_currentPlayer = Globals::G_BATTLESHIPS_PLAYER_TWO : m_currentPlayer = Globals::G_BATTLESHIPS_PLAYER_ONE;
    }

    bool Battleships::IsCurrentTurnUsers()
    {
        return m_playerCount == "1" && m_currentPlayer == Globals::G_BATTLESHIPS_PLAYER_ONE;
    }

    void Battleships::ExecuteUserCommand()
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the
        // computer. Therefore, user commands will be executed against player two's board (m_boardTwo).

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

        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(m_computerSpeed));

        if (m_currentPlayer == "Player One")
            ExecuteGeneralCommand(m_boardTwo, m_shipsRemainingTwo, m_commandsRemainingOne, m_commandsRemainingOne[m_randomNumberGenerator() % m_commandsRemainingOne.size()]);

        else
            ExecuteGeneralCommand(m_boardOne, m_shipsRemainingOne, m_commandsRemainingTwo, m_commandsRemainingTwo[m_randomNumberGenerator() % m_commandsRemainingTwo.size()]);
    }

    void Battleships::GameOver()
    {
        Terminal::GetUserChoiceFromGameOverMenu(m_pageBuilder.GetGameOverPage(m_gameInfo), m_pageBuilder.GetQuitOptionSelectionPage());
    }

    void Battleships::RestartGame()
    {
        m_saveGameOptions = true;
    }

    void Battleships::ResetGame()
    {
        m_saveGameOptions = false;
        m_hasSavedGameOptions = false;
    }

    void Battleships::GetPlayerCount()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetPlayerCountOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_playerCount = Globals::G_GAME_MAX_ONE_PLAYER_OPTIONS[Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS)];
    }

    void Battleships::GetComputerSpeed()
    {
        UpdateGameInfo();

        const std::vector<std::string> MENUS = m_pageBuilder.GetComputerSpeedOptionSelectionGamePages(m_gameInfo);
        const std::vector<std::string> QUIT_MENUS = m_pageBuilder.GetQuitOptionSelectionPage();
        m_computerSpeed = Terminal::GetUserChoiceFromGameMenus(MENUS, QUIT_MENUS);
        m_computerSpeedName = Globals::G_GAME_COMPUTER_SPEED_OPTIONS[m_computerSpeed];
    }

    void Battleships::GetUserShipPositions()
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the
        // computer. Therefore, user commands will be executed against player ones's board (m_boardOne).

        UpdateGameInfo();

        uint32_t startingRow = 0;
        uint32_t startingColumn = 0;
        uint32_t lastShipStartingRow = 0;
        uint32_t lastShipStartingColumn = 0;
        bool shipIsHorizontal = false;
        bool shipIsVertical = false;

        // For each ship
        for (uint32_t currentShip = 0; currentShip < Globals::G_BATTLESHIPS_SHIP_COUNT; currentShip++)
        {
            std::vector<std::tuple<uint32_t, uint32_t>> currentShipPositions;

            // For each ship grid location (intentionally a signed int)
            for (int32_t currentShipSize = 0; currentShipSize < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); currentShipSize++)
            {
                // Set cursor position to the last known valid user selected ship grid location for the currentShip
                if (!currentShipPositions.empty())
                {
                    startingRow = std::get<0>(currentShipPositions.back());
                    startingColumn = std::get<1>(currentShipPositions.back());
                }

                else
                {
                    // No valid user selected ship grid location available for currentShip. There are two reasons which cause
                    // this:
                    // 1. On the very first execution of this line of code as no ship grid locations have been selected.
                    // 2. When the user has undone all selected ship grid locations for the currentShip meaning there are no
                    //    valid previous ship grid locations. Thus, get the last known ship grid locations for the previous
                    //    currentShip. Also, since all ship grid locations for the currentShip have been undone we reset the
                    //    shipIs... booleans.
                    startingRow = lastShipStartingRow;
                    startingColumn = lastShipStartingColumn;
                    shipIsHorizontal = false;
                    shipIsVertical = false;
                }

                while (true) // While ship grid location is incorrect
                {
                    try
                    {
                        Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, Globals::G_BATTLESHIPS_SHIP_INSTRUCTIONS.at(currentShip)));

                        const std::tuple<uint32_t, uint32_t> SELECTED_SHIP_GRID_LOCATION = Terminal::GetUserCommandFromGameGrid({startingRow, startingColumn}, m_pageBuilder, m_gameInfo, false);

                        if (ValidateUserShipPosition(currentShipPositions, SELECTED_SHIP_GRID_LOCATION, shipIsHorizontal, shipIsVertical))
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
                            m_boardOne.at(std::get<0>(currentShipPositions.back())).at(std::get<1>(currentShipPositions.back())) = Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE;
                            currentShipPositions.pop_back();
                            UpdateGameInfo();
                            Terminal::PrintOutput(m_pageBuilder.GetPageWithMessage(m_gameInfo, Globals::G_BATTLESHIPS_SHIP_INSTRUCTIONS.at(currentShip)));

                            // Go back one in for loop (and another -1 to account for increment)
                            currentShipSize -= 2;
                            break;
                        }
                    }
                }
            }

            // Update the last known ship grid location selection for what will be the previous currentShip
            lastShipStartingRow = std::get<0>(currentShipPositions.back());
            lastShipStartingColumn = std::get<1>(currentShipPositions.back());
        }
    }

    bool Battleships::ValidateUserShipPosition(
        const std::vector<std::tuple<uint32_t, uint32_t>>& p_currentShipPositions,
        const std::tuple<uint32_t, uint32_t>& p_selectedShipGridLocation,
        bool& p_shipIsHorizontal,
        bool& p_shipIsVertical)
    {
        // This function is assumed to be only called during one player games where player one is the user and player two is the
        // computer. Therefore, user commands will be executed against player ones's board (m_boardOne).

        const uint32_t SELECTED_SHIP_GRID_ROW = std::get<0>(p_selectedShipGridLocation);
        const uint32_t SELECTED_SHIP_GRID_COLUMN = std::get<1>(p_selectedShipGridLocation);

        if (m_boardOne.at(SELECTED_SHIP_GRID_ROW).at(SELECTED_SHIP_GRID_COLUMN) != Globals::G_BATTLESHIPS_EMPTY_GRID_VALUE)
            return false;

        // If this is empty then this is the first ship grid location selection so it is automatically valid
        if (p_currentShipPositions.empty())
            return true;

        // As selected grid locations are added incrementally only the previous selection needs to be checked against the
        // current selection
        const uint32_t PREVIOUS_SELECTED_SHIP_GRID_ROW = std::get<0>(p_currentShipPositions.back());
        const uint32_t PREVIOUS_SELECTED_SHIP_GRID_COLUMN = std::get<1>(p_currentShipPositions.back());

        const bool ROWS_ARE_THE_SAME = PREVIOUS_SELECTED_SHIP_GRID_ROW == SELECTED_SHIP_GRID_ROW;
        const bool COLUMNS_ARE_THE_SAME = PREVIOUS_SELECTED_SHIP_GRID_COLUMN == SELECTED_SHIP_GRID_COLUMN;

        // Prevent selection of a diagonal grid location relative to the previous selection
        if (!ROWS_ARE_THE_SAME && !COLUMNS_ARE_THE_SAME)
            return false;

        const uint32_t ROW_DIFFERENCE_TO_PREVIOUS_SELECTION = std::abs(static_cast<int>(SELECTED_SHIP_GRID_ROW) - static_cast<int>(PREVIOUS_SELECTED_SHIP_GRID_ROW));
        const uint32_t COLUMN_DIFFERENCE_TO_PREVIOUS_SELECTION = std::abs(static_cast<int>(SELECTED_SHIP_GRID_COLUMN) - static_cast<int>(PREVIOUS_SELECTED_SHIP_GRID_COLUMN));

        // Only allow adjacents grid locations relative to the previous selection
        if ((ROW_DIFFERENCE_TO_PREVIOUS_SELECTION > 1) && (COLUMN_DIFFERENCE_TO_PREVIOUS_SELECTION > 1))
            return false;

        // If there has only been one selection yet this selection is automatically valid. Also as there have now been two
        // selections we can determine whether the ship is being placed horizontally or vertically.
        if (p_currentShipPositions.size() == 1)
        {
            p_shipIsHorizontal = ROWS_ARE_THE_SAME;
            p_shipIsVertical = COLUMNS_ARE_THE_SAME;
            return true;
        }

        // If ship is known to be horizontal then rows must be the same
        if (p_shipIsHorizontal && !ROWS_ARE_THE_SAME)
            return false;

        // If ship is known to be vertical then columns must be the same
        if (p_shipIsVertical && !COLUMNS_ARE_THE_SAME)
            return false;

        return true;
    }

    void Battleships::GetComputerShipPositions(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board) // NOLINT(readability-function-cognitive-complexity)
    {
        // For each ship
        for (uint32_t currentShip = 0; currentShip < Globals::G_BATTLESHIPS_SHIP_COUNT; currentShip++)
        {
            std::vector<std::tuple<uint32_t, uint32_t>> shipPositions;
            uint32_t startingRow = 0;
            uint32_t startingColumn = 0;
            bool locationIsAlreadyOccupied = false;

            while (true)
            {
                shipPositions.clear();
                locationIsAlreadyOccupied = false;

                // Get a random ship orientation
                if (static_cast<bool>(m_randomNumberGenerator() % 2)) // Horizontal
                {
                    // As the ship will be placed horizontally and assuming the first column value will be the smallest and all
                    // other column values will increment, then a max possible starting column value exists which is linked with
                    // the size of the ship. Therefore get a random value from 0 to the max possible starting column value.

                    startingRow = m_randomNumberGenerator() % Globals::G_BATTLESHIPS_BOARD_HEIGHT; // Any row value allowed as ship is horizontal

                    startingColumn = m_randomNumberGenerator() % (Globals::G_BATTLESHIPS_BOARD_WIDTH - Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip));

                    // Column values increment by one
                    for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); i++)
                        shipPositions.emplace_back(startingRow, startingColumn + i);

                    // Row values increment by one
                    for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); i++)
                    {
                        if (Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), p_board.at(startingRow).at(startingColumn + i)) == Globals::G_BATTLESHIPS_SHIP_NAMES.end())
                            shipPositions.emplace_back(startingRow, startingColumn + i);

                        else
                        {
                            locationIsAlreadyOccupied = true;
                            break;
                        }
                    }
                }

                else // Vertical
                {
                    // As the ship will be placed vertically and assuming the first row value will be the smallest and all other
                    // row values will increment, then a max possible starting row value exists which is linked with the size of
                    // the ship. Therefore get a random value from 0 to the max possible starting row value.

                    startingRow = m_randomNumberGenerator() % (Globals::G_BATTLESHIPS_BOARD_HEIGHT - Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip));

                    startingColumn = m_randomNumberGenerator() % Globals::G_BATTLESHIPS_BOARD_WIDTH; // Any column value allowed as ship is vertical

                    // Row values increment by one
                    for (uint32_t i = 0; i < Globals::G_BATTLESHIPS_SHIP_SIZES.at(currentShip); i++)
                    {
                        if (Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), p_board.at(startingRow + i).at(startingColumn)) == Globals::G_BATTLESHIPS_SHIP_NAMES.end())
                            shipPositions.emplace_back(startingRow + i, startingColumn);

                        else
                        {
                            locationIsAlreadyOccupied = true;
                            break;
                        }
                    }
                }

                if (!locationIsAlreadyOccupied)
                    break;
            }

            // Place ship
            for (std::tuple<uint32_t, uint32_t> currentPosition : shipPositions)
                p_board.at(std::get<0>(currentPosition)).at(std::get<1>(currentPosition)) = Globals::G_BATTLESHIPS_SHIP_NAMES.at(currentShip);
        }
    }

    bool Battleships::IsShipPresent(std::array<std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>, Globals::G_BATTLESHIPS_BOARD_HEIGHT>& p_board)
    {
        for (const std::array<std::string, Globals::G_BATTLESHIPS_BOARD_WIDTH>& currentRow : p_board)
            for (const std::string& currentValue : currentRow)
                if (Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), currentValue) != Globals::G_BATTLESHIPS_SHIP_NAMES.end())
                    return true;

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
        const uint32_t ROW = std::get<0>(p_command);
        const uint32_t COLUMN = std::get<1>(p_command);

        // If board value contains a ship then it is a hit
        if (Globals::ImplementStdRangesFind(Globals::G_BATTLESHIPS_SHIP_NAMES.begin(), Globals::G_BATTLESHIPS_SHIP_NAMES.end(), p_opponentBoard.at(ROW).at(COLUMN)) != Globals::G_BATTLESHIPS_SHIP_NAMES.end())
        {
            p_opponentShipsRemaining.at(p_opponentBoard.at(ROW).at(COLUMN))--;
            p_opponentBoard.at(ROW).at(COLUMN) = Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK + p_opponentBoard.at(ROW).at(COLUMN).at(1) + Globals::G_BATTLESHIPS_SUCCESSFUL_ATTACK;
        }

        else // Miss
            p_opponentBoard.at(ROW).at(COLUMN) = " " + std::string(1, Globals::G_BATTLESHIPS_MISSED_ATTACK) + " ";

        p_commandsRemaining.erase(Globals::ImplementStdRangesFind(p_commandsRemaining.begin(), p_commandsRemaining.end(), p_command));

        m_turnCount++;
    }
}

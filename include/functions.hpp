/**
 * @file functions.hpp
 * @author Junaid Afzal
 * @brief This file contains functions that are used by all the games
 * and thus to avoid repeating code, they are all collated here.
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef functions_hpp
#define functions_hpp

#include <vector>
#include <string>
#include <Windows.h>

/**
 * @brief Bold text colours for the terminal
 * using ANSI escape codes
 *
 */
const std::string WHITE = "\x1B[1;37m";
const std::string RED = "\x1B[1;31m";
const std::string BLUE = "\x1B[1;34m";
const std::string RESET = "\x1B[0m";

/**
 * @brief Displays the main UI
 *
 * @param CurrentSelection
 */
std::string Main_Game_Display(const unsigned int &CurrentSelection);

/**
 * @brief Creates an empty new line for any of the game boxes
 *
 * @return std::string
 */
std::string Main_Empty_Line(void);

/**
 * @brief Creates a new line containing text for any of the game boxes
 *
 * @param Input
 * @return std::string
 */
std::string Main_New_Line(const std::string &Input);

/**
 * @brief Creates the top line of any of the game boxes
 *
 * @return std::string
 */
std::string Main_Top_Line(void);

/**
 * @brief Creates the bottom line of any of the game boxes
 *
 * @return std::string
 */
std::string Main_Bottom_Line(void);

/**
 * @brief Creates the bottom bar which contains the title of the game
 *
 * @return std::string
 */
std::string Main_Bottom_Bar(void);

/**
 * @brief A Windows specific method to clear the contents of
 * the terminal with thanks to: https://www.cplusplus.com/articles/4z18T05o
 */
void Clear_Terminal(void);

/**
 * @brief Toggles the current player between PLAYER ONE
 * and PLAYER TWO.
 *
 * @param CurrentPlayer
 */
void Toggle_Player(std::string &CurrentPlayer);

/**
 * @brief Checks if each character in Input is a lower case letter,
 * and if it is, 32 is subtracted from the character to capitalise it.
 * Thus, non-letters in Input will remain unaffected.
 *
 * @param Input
 */
void Capitalise_Word(std::string &Input);

/**
 * @brief Used by Hangman to create a list of the 1,000 most used word in English
 * with thanks to: https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
 * and is placed here to keep the hangman.cpp file small and easily navigable.
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> Generate_Word_List(void);

#endif
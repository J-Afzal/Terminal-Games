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

/**
 * @brief Bold text colours for the terminal
 * using ANSI escape codes
 *
 */
#define RESET   "\x1B[0m"
#define BLACK   "\x1B[1;30m"
#define RED     "\x1B[1;31m"
#define GREEN   "\x1B[1;32m"
#define YELLOW  "\x1B[1;33m"
#define BLUE    "\x1B[1;34m"
#define MAGENTA "\x1B[1;35m"
#define CYAN    "\x1B[1;36m"
#define WHITE   "\x1B[1;37m"

/**
 * @brief Displays the main UI
 *
 * @param CurrentSelection
 */
void Display_UI(const unsigned int &CurrentSelection);

/**
 * @brief Checks if each character in Input is a lower case letter,
 * and if it is, 32 is subtracted from the character to capitalise it.
 * Thus, non-letters in Input will remain unaffected.
 *
 * @param Input
 */
void Capitalise_Word(std::string &Input);

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
 * @brief Used by Hangman to create a list of the 1,000 most used word in English
 * with thanks to: https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
 * and is placed here to keep the hangman.cpp file small and easily navigable.
 *
 * @return std::vector<std::string>
 */
std::vector<std::string> Generate_Word_List(void);

#endif

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
 * @brief Gets an input from the user and checks if it
 * is within the range that was given.
 *
 * @param NumberOfPlayers
 * @param MinPlayers
 * @param MaxPlayers
 * @return true, if user input is within range
 * @return false, if user input is NOT within range
 */
bool Get_Number_Of_Players(unsigned int &NumberOfPlayers,
                           const unsigned int &MinPlayers,
                           const unsigned int &MaxPlayers);

/**
 * @brief Gets an input from the user for which player they would
 * like to be and is only used when there is only one human
 * player. This function is not case sensitive.
 *
 * @param UserPlayerChoice
 * @return true, if user input is 'player one' or 'player two'
 * @return false, if user input neither 'player one' or 'player two'
 */
bool Get_User_Player_Choice(std::string &UserPlayerChoice);

/**
 * @brief Gets an input from the user for which AI difficulty
 * they would like to be. This function is not case sensitive.
 *
 * @param AIDifficulty
 * @return true, if user input is 'easy' or 'hard'
 * @return false, if user input is NOT 'easy' or 'hard'
 */
bool Get_AI_Difficulty(std::string &AIDifficulty);

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

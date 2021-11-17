/**
 * @file hangman.hpp
 * @author Junaid Afzal
 * @brief Hangman specific functions
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef hangman_hpp
#define hangman_hpp

#include <vector>
#include <string>
#include <Windows.h>

/**
 * @brief Game loop for Hangman
 *
 * @param ConsoleHandle
 */
void Play_Hangman(const HANDLE &ConsoleHandle);

/**
 * @brief The number of players are retrieved, if only one human player is present
 * they are asked which player they would like to be, if AI is involved the user
 * is prompted for the AI difficulty, depending on the previous responses the user
 * or AI is asked for the word to be guessed and finally the current player is randomly assigned.
 *
 * @param NumberOfPlayers
 * @param PlayerThatIsGuessing
 * @param AIDifficulty
 * @param WordToBeGuessed
 * @param CurrentGuessOfWord
 * @param ValidMovesRemaining
 * @param IncorrectGuesses
 * @param ConsoleHandle
 */
void Setup_Game(unsigned int &NumberOfPlayers,
                std::string &PlayerThatIsGuessing,
                std::string &AIDifficulty,
                std::string &WordToBeGuessed,
                std::string &CurrentGuessOfWord,
                std::vector<std::string> &ValidMovesRemaining,
                const std::vector<std::string> &IncorrectGuesses,
                const HANDLE &ConsoleHandle);

/**
 * @brief Does what what you think
 *
 * @param IncorrectGuesses
 * @return unsigned int
 */
unsigned int Get_Number_Of_Players(const std::vector<std::string> &IncorrectGuesses);

/**
 * @brief Does what what you think
 *
 * @param NumberOfPlayers
 * @param IncorrectGuesses
 * @return std::string
 */
std::string Get_User_Player_Choice(const unsigned int &NumberOfPlayers,
                                   const std::vector<std::string> &IncorrectGuesses);

/**
 * @brief Does what what you think
 *
 * @param NumberOfPlayers
 * @param IncorrectGuesses
 * @return std::string
 */
std::string Get_AI_Difficulty(const unsigned int &NumberOfPlayers,
                              const std::vector<std::string> &IncorrectGuesses);

/**
 * @brief The user is prompted for the word to be guessed, and if necessary,
 * repeated until a valid word is given (only letters allowed).
 *
 * @param IncorrectGuesses
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param ConsoleHandle
 * @return std::string
 */
std::string Get_Word_To_Be_Guessed_From_User(const std::vector<std::string> &IncorrectGuesses,
                                             const unsigned int &NumberOfPlayers,
                                             const std::string &AIDifficulty,
                                             const HANDLE &ConsoleHandle);

/**
 * @brief This function calls Generate_Word_List() and then picks a
 * random word within the list.
 *
 * @return std::string
 */
std::string Get_Word_To_Be_Guessed_From_AI(void);

/**
 * @brief The current hangman state is displayed, and to the right of that,
 * the current incorrect guess are displayed, and to the right of that,
 * the numebr of players and the AI difficulty is displayed.
 *
 * @param NumberOfErrors
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param IncorrectGuesses
 * @param CurrentGuessOfWord
 * @param WordToBeGuessed
 * @param GameOver
 * @return std::string
 */
std::string Hangman_Game_Display(const unsigned int &NumberOfErrors,
                                 const std::string &NumberOfPlayers,
                                 const std::string &AIDifficulty,
                                 const std::vector<std::string> &IncorrectGuesses,
                                 const std::string &CurrentGuessOfWord,
                                 const std::string &WordToBeGuessed,
                                 const bool &GameOver);

/**
 * @brief Creates an empty new line for any of the game boxes
 *
 * @return std::string
 */
std::string Hangman_Empty_Line(void);

/**
 * @brief Creates a new line containing text for any of the game boxes
 *
 * @param Input
 * @return std::string
 */
std::string Hangman_New_Line(const std::string &Input);

/**
 * @brief Creates the top line of any of the game boxes
 *
 * @return std::string
 */
std::string Hangman_Top_Line(void);

/**
 * @brief Creates the bottom line of any of the game boxes
 *
 * @return std::string
 */
std::string Hangman_Bottom_Line(void);

/**
 * @brief Creates the bottom bar which contains the title of the game
 *
 * @return std::string
 */
std::string Hangman_Bottom_Bar(void);

/**
 * @brief Checks whether the numbers of errors are ten (final hangman state)
 * and if CurrentGuessOfWord and WordToBeGuessed are the same.
 *
 * @param NumberOfErrors
 * @param WordToBeGuessed
 * @param CurrentGuessOfWord
 * @return true, if number of errors is 10 or CurrentGuessOfWord and WordToBeGuessed is the same
 * @return false, if number of errors is NOT 10 or CurrentGuessOfWord and WordToBeGuessed is NOT the same
 */
bool Winning_Conditions_Met(const unsigned int &NumberOfErrors,
                            const std::string &WordToBeGuessed,
                            const std::string &CurrentGuessOfWord);

/**
 * @brief The user is prompted for their next guess and, if necessary,
 * repeated until a valid guess is given (note that only single letter
 * guesses are allowed).
 *
 * @param NumberOfErrors
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param CorrectGuesses
 * @param ValidMovesRemaining
 * @param IncorrectGuesses
 * @param CurrentGuessOfWord
 * @param WordToBeGuessed
 * @param ConsoleHandle
 */
void Get_Next_User_Guess(unsigned int &NumberOfErrors,
                         const unsigned int &NumberOfPlayers,
                         const std::string &AIDifficulty,
                         std::vector<std::string> &CorrectGuesses,
                         std::vector<std::string> &ValidMovesRemaining,
                         std::vector<std::string> &IncorrectGuesses,
                         std::string &CurrentGuessOfWord,
                         const std::string &WordToBeGuessed,
                         const HANDLE &ConsoleHandle);

/**
 * @brief If AIDifficulty is set to easy, then a random valid letter is chosen
 * as the guess.
 *
 * @param NumberOfErrors
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param IncorrectGuesses
 * @param CorrectGuesses
 * @param ValidMovesRemaining
 * @param CurrentGuessOfWord
 * @param WordToBeGuessed
 */
void Get_Next_AI_Guess(unsigned int &NumberOfErrors,
                       const unsigned int &NumberOfPlayers,
                       const std::string &AIDifficulty,
                       std::vector<std::string> &IncorrectGuesses,
                       std::vector<std::string> &CorrectGuesses,
                       std::vector<std::string> &ValidMovesRemaining,
                       std::string &CurrentGuessOfWord,
                       const std::string &WordToBeGuessed);

/**
 * @brief Does what the function name says and also updates the CurrentGuessOfWord
 * with all occurrences of the guess, if the guess is correct.
 *
 * @param WordToBeGuessed
 * @param Guess
 * @param CurrentGuessOfWord
 * @return true, if guess is present in WordToBeGuessed
 * @return false, if guess is NOT present in WordToBeGuessed
 */
bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                            const unsigned char &Guess,
                                            std::string &CurrentGuessOfWord);

/**
 * @brief First calls Display_Game() once more. If hangman is in its final state, then
 * the winner is the guesser and if not then the guesser has lost. This information is
 * then displayed to the user along with the word that was being guessed and the _getch()
 * is used to get a key press for what the GameIsRunning should be set to (true = play
 * another game and false = quit game).
 *
 * @param NumberOfErrors
 * @param NumberOfPlayers
 * @param AIDifficulty
 * @param IncorrectGuesses
 * @param CurrentGuessOfWord
 * @param WordToBeGuessed
 * @param NumberOfTurns
 * @param GameIsRunning
 */
void Display_Game_Over_Message(const unsigned int &NumberOfErrors,
                               const unsigned int &NumberOfPlayers,
                               const std::string &AIDifficulty,
                               const std::vector<std::string> &IncorrectGuesses,
                               const std::string &CurrentGuessOfWord,
                               const std::string &WordToBeGuessed,
                               const unsigned int &NumberOfTurns,
                               bool &GameIsRunning);

#endif

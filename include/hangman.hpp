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

#pragma once
#include <vector>
#include <string>
#include <Windows.h>

namespace Hangman
{
    /**
     * @brief Game loop for Hangman
     *
     * @param ConsoleHandle
     */
    void Play(const HANDLE &ConsoleHandle);

    /**
     * @brief The number of players are retrieved, if only one human player is present
     * they are asked which player they would like to be, if AI is involved the user
     * is prompted for the AI difficulty, depending on the previous responses the user
     * or AI is asked for the word to be guessed and finally the current player is randomly assigned.
     *
     * @param ValidMovesRemaining
     * @param IncorrectGuesses
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param PlayerThatIsGuessing
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param ConsoleHandle
     * @param QuitToMainMenu
     */
    void Setup_Game(std::vector<char> &ValidMovesRemaining,
                    const std::vector<char> &IncorrectGuesses,
                    std::string &WordToBeGuessed,
                    std::string &CurrentGuessOfWord,
                    std::string &PlayerThatIsGuessing,
                    std::string &AIDifficulty,
                    int &NumberOfPlayers,
                    const HANDLE &ConsoleHandle,
                    bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param IncorrectGuesses
     * @param QuitToMainMenu
     * @return int
     */
    int Get_Number_Of_Players(const std::vector<char> &IncorrectGuesses,
                              bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param IncorrectGuesses
     * @param NumberOfPlayers
     * @param QuitToMainMenu
     * @return std::string
     */
    std::string Get_User_Player_Choice(const std::vector<char> &IncorrectGuesses,
                                       const int &NumberOfPlayers,
                                       bool &QuitToMainMenu);

    /**
     * @brief
     *
     * @param IncorrectGuesses
     * @param NumberOfPlayers
     * @param QuitToMainMenu
     * @return std::string
     */
    std::string Get_AI_Difficulty(const std::vector<char> &IncorrectGuesses,
                                  const int &NumberOfPlayers,
                                  bool &QuitToMainMenu);

    /**
     * @brief The user is prompted for the word to be guessed, and if necessary,
     * repeated until a valid word is given (only letters allowed).
     *
     * @param IncorrectGuesses
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param ConsoleHandle
     * @param QuitToMainMenu
     * @return std::string
     */
    std::string Get_Word_To_Be_Guessed_From_User(const std::vector<char> &IncorrectGuesses,
                                                 const std::string &AIDifficulty,
                                                 const int &NumberOfPlayers,
                                                 const HANDLE &ConsoleHandle,
                                                 bool &QuitToMainMenu);

    /**
     * @brief This function calls Return_Word_List() and then picks a
     * random word within the list.
     *
     * @return std::string
     */
    std::string Get_Word_To_Be_Guessed_From_AI(void);

    /**
     * @brief The current hangman state is displayed, and to the right of that,
     * the numebr of players and the AI difficulty is displayed,
     * and to the right of that, the current incorrect guess are displayed,
     *
     * @param IncorrectGuesses
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param NumberOfErrors
     * @param GameOver
     * @return std::string
     */
    std::string Get_Game_Display(const std::vector<char> &IncorrectGuesses,
                                 const std::string &WordToBeGuessed,
                                 const std::string &CurrentGuessOfWord,
                                 const std::string &AIDifficulty,
                                 const std::string &NumberOfPlayers,
                                 const int &NumberOfErrors,
                                 const bool &GameOver);

    /**
     * @brief Creates a new line containing text for Hangman game
     *
     * @param Input
     * @return std::string
     */
    std::string New_Line(const std::string &Input);

    /**
     * @brief Creates an empty new line for Hangman game
     *
     * @return std::string
     */
    std::string Empty_Line(void);

    /**
     * @brief Creates the top line for Hangman game
     *
     * @return std::string
     */
    std::string Top_Line(void);

    /**
     * @brief Creates the bottom line for Hangman game
     *
     * @return std::string
     */
    std::string Bottom_Line(void);

    /**
     * @brief Creates the bottom bar for Hangman game
     *
     * @return std::string
     */
    std::string Bottom_Bar(void);

    /**
     * @brief Checks whether the numbers of errors are ten (final hangman state)
     *
     * @param NumberOfTurns
     * @return true, if number of turns is 10
     * @return false, if number of turns is NOT 10
     */
    bool Game_Over(const int &NumberOfTurns);

    /**
     * @brief Checks if CurrentGuessOfWord and WordToBeGuessed are the same.
     *
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @return true, if CurrentGuessOfWord and WordToBeGuessed are the same
     * @return false, if CurrentGuessOfWord and WordToBeGuessed are NOT the same
     */
    bool Winning_Conditions_Met(const std::string &WordToBeGuessed,
                                const std::string &CurrentGuessOfWord);

    /**
     * @brief The user is prompted for their next guess and, if necessary,
     * repeated until a valid guess is given (note that only single letter
     * guesses are allowed).
     *
     * @param ValidMovesRemaining
     * @param IncorrectGuesses
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param NumberOfErrors
     * @param ConsoleHandle
     * @param QuitToMainMenu
     */
    void Get_Next_User_Guess(std::vector<char> &ValidMovesRemaining,
                             std::vector<char> &IncorrectGuesses,
                             const std::string &WordToBeGuessed,
                             std::string &CurrentGuessOfWord,
                             const std::string &AIDifficulty,
                             const int &NumberOfPlayers,
                             int &NumberOfErrors,
                             const HANDLE &ConsoleHandle,
                             bool &QuitToMainMenu);

    /**
     * @brief If AIDifficulty is set to easy, then a random valid letter is chosen
     * as the guess.
     *
     * @param ValidMovesRemaining
     * @param IncorrectGuesses
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param NumberOfErrors
     */
    void Get_Next_AI_Guess(std::vector<char> &ValidMovesRemaining,
                           std::vector<char> &IncorrectGuesses,
                           const std::string &WordToBeGuessed,
                           std::string &CurrentGuessOfWord,
                           int &NumberOfErrors);

    /**
     * @brief Does what the function name says and also updates the CurrentGuessOfWord
     * with all occurrences of the guess, if the guess is correct.
     *
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param Guess
     * @return true, if guess is present in WordToBeGuessed
     * @return false, if guess is NOT present in WordToBeGuessed
     */
    bool Check_Guess_Against_Word_To_Be_Guessed(const std::string &WordToBeGuessed,
                                                std::string &CurrentGuessOfWord,
                                                const char &Guess);

    /**
     * @brief If hangman is in its final state, then the winner is the guesser and if
     * not then the guesser has lost. This information is then displayed to the user along with
     * the word that was being guessed
     *
     * @param IncorrectGuesses
     * @param WordToBeGuessed
     * @param CurrentGuessOfWord
     * @param AIDifficulty
     * @param NumberOfPlayers
     * @param NumberOfErrors
     * @param NumberOfTurns
     * @param GameIsRunning
     */
    void Display_Game_Over_Message(const std::vector<char> &IncorrectGuesses,
                                   const std::string &WordToBeGuessed,
                                   const std::string &CurrentGuessOfWord,
                                   const std::string &AIDifficulty,
                                   const int &NumberOfPlayers,
                                   const int &NumberOfErrors,
                                   const int &NumberOfTurns,
                                   bool &GameIsRunning);
}
/**
 * @file hangman.hpp
 * @author Junaid Afzal
 * @brief Hangman namespace functions and classes
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include <string>
#include <vector>
#include <Windows.h>
#include "game.hpp"

/**
 * @brief Contains all the data/functions for the Hangman game
 *
 */
class Hangman : public Game
{
public:
    explicit Hangman(const HANDLE &ConsoleHandle);

    ~Hangman();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Setup_Game() override;

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    /**
     * @brief
     *
     * @return true, if Execute_Next_User_Command()
     * @return false, if Execute_Next_AI_Command()
     */
    bool Next_Turn_Is_User() override;

    /**
     * @brief The user is prompted for their next guess and, if necessary,
     * repeated until a valid guess is given (note that only single letter
     * guesses are allowed).
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Execute_Next_User_Command() override;

    /**
     * @brief If AIDifficulty is set to easy, then a random valid letter is chosen.
     *
     */
    void Execute_Next_AI_Command() override;

    /**
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Display_Game_Over_Message() override;

private:
    std::vector<char> m_MovesRemaining, m_IncorrectGuesses;
    std::string m_WordToBeGuessed, m_CurrentGuessOfWord, m_AIDifficulty;
    int m_NumberOfPlayers{}, m_NumberOfErrors{}, m_NumberOfTurns{};
    bool m_GameOver{}, m_UserIsGuessing{};
    HANDLE m_ConsoleHandle;
    const int m_Width = 62;
    // ANSI escape codes for bold text colours
    const std::string WHITE = "\x1B[1;37m";
    const std::string BLUE = "\x1B[1;34m";

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_Number_Of_Players();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_User_Player_Choice();

    /**
     * @brief
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_AI_Difficulty();

    /**
     * @brief The user is prompted for the word to be guessed, and if necessary,
     * repeated until a valid word is given (only letters allowed).
     *
     * @return true, if quit to main menu
     * @return false, if continue with game
     */
    bool Get_Word_From_User();

    /**
     * @brief A word from list of the ~1,000 most used word in English from:
     * https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
     *
     * @return std::string
     */
    void Get_Random_Word();

    /**
     * @brief updates the CurrentGuessOfWord with all occurrences of the guess,
     * if the guess is correct.
     *
     * @param Guess
     */
    void Check_Guess_And_Update_Current_Guess(const char &Guess);

    /**
     * @brief Creates a string that contains all the ASCII characters to
     * display the current state of the game.
     *
     * @return std::string
     */
    std::string Get_Game_Display();
};

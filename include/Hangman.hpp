/**
 * @file Hangman.hpp
 * @author Junaid Afzal
 * @brief Hangman game object
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once
#include "Game.hpp"

class Hangman : public Game
{
public:
    explicit Hangman();

    ~Hangman() override = default;

    void Setup_Game() override;

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    /**
     * @return true if next turn is user, false if next turn is AI
     */
    bool Next_Turn_Is_User() override;

    /**
     * @brief The user is prompted for their next guess and, if necessary,
     * repeated until a valid guess is given (note that only single letter
     * guesses are allowed).
     */
    void Execute_Next_User_Command() override;

    /**
     * @brief If AIDifficulty is set to easy, then a random valid letter is chosen.
     */
    void Execute_Next_AI_Command() override;

    /**
     * @brief The final game state is displayed and the user is promoted
     * whether they want to restart or quit to the main menu.
     */
    void Display_Game_Over_Message() override;

private:
    std::vector<char> m_MovesRemaining, m_IncorrectGuesses;
    std::string m_WordToBeGuessed, m_CurrentGuessOfWord;
    int m_NumberOfErrors{};
    bool m_GameOver{}, m_UserIsGuessing{};

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Difficulty();

    /**
     * @brief The user is prompted for the word to be guessed, and if necessary,
     * repeated until a valid word is given (only letters allowed).
     */
    void Get_Word_From_User();

    /**
     * @return std::string containing a word from list of the ~1,000 most used word in English from:
     * https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
     */
    void Get_Word_From_AI();

    /**
     * @brief updates the CurrentGuessOfWord with all occurrences of the guess,
     * if the guess is correct.
     */
    void Check_Guess_And_Update_Current_Guess(const char &Guess);

    /**
     * @return std::string that contains all the
     * ASCII characters to display the current state of the game.
     */
    std::string Get_Game_Display();
};

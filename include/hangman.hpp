/**
 * @file hangman.hpp
 * @author Junaid Afzal
 * @brief Hangman namespace funtions and classes
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
     * @brief Game class that contains all the data/functions for the Hangman game
     *
     */
    class Game
    {
    public:
        Game(const HANDLE &ConsoleHandle);

        ~Game();

        /**
         * @brief
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Setup_Game(void);

        /**
         * @brief
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Get_Number_Of_Players(void);

        /**
         * @brief
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Get_User_Player_Choice(void);

        /**
         * @brief
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Get_AI_Difficulty(void);

        /**
         * @brief The user is prompted for the word to be guessed, and if necessary,
         * repeated until a valid word is given (only letters allowed).
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Get_Word_From_User(void);

        /**
         * @brief A word from list of the ~1,000 most used word in English from:
         * https://www.ef.co.uk/english-resources/english-vocabulary/top-1000-words/
         *
         * @return std::string
         */
        void Get_Random_Word(void);

        bool Game_Over(void);

        /**
         * @brief
         *
         * @return true, if m_CurrentGuessOfWord and m_WordToBeGuessed are the same
         * @return false, if m_CurrentGuessOfWord and m_WordToBeGuessed are NOT the same
         */
        bool Winning_Conditions_Met(void);

        /**
         * @brief
         *
         * @return true, if number of turns is 10
         * @return false, if number of turns is NOT 10
         */
        bool No_Guesses_Left(void);

        /**
         * @brief
         *
         * @return true, if Execute_Next_User_Command()
         * @return false, if Execute_Next_AI_Command()
         */
        bool Next_Turn_Is_User(void);

        /**
         * @brief The user is prompted for their next guess and, if necessary,
         * repeated until a valid guess is given (note that only single letter
         * guesses are allowed).
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Execute_Next_User_Guess(void);

        /**
         * @brief If AIDifficulty is set to easy, then a random valid letter is chosen.
         *
         */
        void Execute_Next_AI_Guess(void);

        /**
         * @brief The final game state is displayed and the user is promoted
         * whether they want to restart or quit to the main menu.
         *
         * @return true, if quit to main menu
         * @return false, if continue with game
         */
        bool Display_Game_Over_Message(void);

    private:
        std::vector<char> m_MovesRemaining, m_IncorrectGuesses;
        std::string m_WordToBeGuessed, m_CurrentGuessOfWord, m_AIDifficulty;
        int m_NumberOfPlayers, m_NumberOfErrors, m_NumberOfTurns;
        bool m_GameOver, m_WinningConditionsMet, m_UserIsGuessing;
        HANDLE m_ConsoleHandle;

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
        std::string Get_Game_Display(void);

        /**
         * @brief Creates a new line containing text for Hangman game box
         *
         * @param Input
         * @return std::string
         */
        std::string New_Line(const std::string &Input);

        /**
         * @brief Creates an empty new line for Hangman game box
         *
         * @return std::string
         */
        std::string Empty_Line(void);

        /**
         * @brief Creates the top line for Hangman game box
         *
         * @return std::string
         */
        std::string Top_Line(void);

        /**
         * @brief Creates the bottom line for Hangman game box
         *
         * @return std::string
         */
        std::string Bottom_Line(void);

        /**
         * @brief Creates the bottom bar for Hangman game box
         *
         * @return std::string
         */
        std::string Bottom_Bar(void);
    };

}

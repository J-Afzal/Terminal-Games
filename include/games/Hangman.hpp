/**
 * @file Hangman.hpp
 * @author Junaid Afzal
 * @brief The game object that runs Hangman
 * and is run using the inherited Play() function
 * @version 1.0
 * @date 07-11-2021
 *
 * @copyright Copyright (c) 2021
 *
 */

#pragma once

#include <random>
#include <string>
#include <vector>

#include "Game.hpp"

class Hangman : public Game
{
public:
    /**
     * @brief Construct a new Hangman object
     * @param ASCIIOnly determines whether to use ANSI escapes codes (false)
     * or just ASCII characters (true)
     */
    explicit Hangman(const bool& ASCIIOnly);

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::vector<std::string> m_WordList;
    std::vector<char> m_MovesRemaining, m_IncorrectGuesses;
    std::string m_WordToBeGuessed, m_CurrentGuessOfWord, m_NumberOfPlayers, m_AISpeedName;
    uint32_t m_NumberOfTurns, m_NumberOfErrors, m_AISpeed;
    char m_AICommand;
    bool m_GameOver, m_UserIsWordGuesser;

    void Setup_Game() override;

    void Load_Word_List();

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Speed();

    void Get_Word_From_User();

    void Get_Word_From_AI();

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() const override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    void Check_Guess_And_Update_Current_Guess(const char& Guess);

    std::string Get_Game_Over_Message() const override;

    std::string Get_Game_Display() const;
};

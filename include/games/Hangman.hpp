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
#include "Game.hpp"
#include "helpers/StringBuilder.hpp"

class Hangman : public Game
{
public:
    explicit Hangman();

    ~Hangman() override = default;

private:
    std::default_random_engine m_RandomNumberGenerator;
    std::vector<char> m_MovesRemaining, m_IncorrectGuesses;
    std::string m_WordToBeGuessed, m_CurrentGuessOfWord;
    std::string m_NumberOfPlayers, m_AIDifficulty;
    int m_NumberOfTurns{}, m_NumberOfErrors{}, m_AISpeed{};
    bool m_GameOver{}, m_UserIsWordGuesser{};
    StringBuilder m_StringBuilder;

    void Setup_Game() override;

    void Get_Number_Of_Players();

    void Get_User_Player_Choice();

    void Get_AI_Speed();

    void Get_Word_From_User();

    void Get_Word_From_AI();

    bool Game_Over() override;

    void Toggle_Current_Player() override;

    bool Next_Turn_Is_User() override;

    void Execute_Next_User_Command() override;

    void Execute_Next_AI_Command() override;

    void Check_Guess_And_Update_Current_Guess(const char &Guess);

    std::string Get_Game_Over_Message() override;

    std::string Get_Game_Display();
};

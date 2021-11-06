#ifndef functions_hpp
#define functions_hpp

#include <vector>
#include <string>

// Prompt user for the number of human players
bool Get_Number_Of_Players(unsigned int &NumberOfPlayers,
                           const unsigned int &MinPlayers,
                           const unsigned int &MaxPlayers);

// If one human player is selected then the user is asked to choose between player X or player O
bool Get_User_Player_Choice(std::string &UserPlayerChoice);

bool Get_AI_Difficulty(std::string &AIDifficulty);

void Capitalise_Word(std::string &aWord);

// Windows API method taken from https://www.cplusplus.com/articles/4z18T05o
void Clear_Terminal(void);

void Toggle_Player(std::string &CurrentPlayer);

std::vector<std::string> Create_Word_List(void);

#endif

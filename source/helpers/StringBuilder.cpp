/**
 * @file StringBuilder.cpp
 * @author Junaid Afzal
 * @brief Implementation of StringBuilder.hpp
 * @version 1.0
 * @date 04-04-2022
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "helpers/StringBuilder.hpp"

void StringBuilder::Set(const int &GameWidth, const std::string &TopTitle, const std::string &BottomTitle)
{
    m_GameWidth = GameWidth;
    m_TopTitle = TopTitle;
    m_BottomTitle = BottomTitle;
}

std::string StringBuilder::New_Line(const std::string &Input, const Colours &Colour) const
{
    std::string Output;
    Output += (char)186;

    if (Colour == Colours::WHITE)
        Output += Input;
    else if (Colour == Colours::RED)
        Output += m_RED + Input + m_WHITE;
    else if (Colour == Colours::BLUE)
        Output += m_BLUE + Input + m_WHITE;

    return Output + (char)186 + "\n";
}

std::string StringBuilder::New_Line_Centered(const std::string &Input, const Colours &Colour) const
{
    std::string Output;
    Output.insert(Output.size(), floor((m_GameWidth-(double)Input.size())/2), ' ');
    Output += Input;
    Output.insert(Output.size(), ceil((m_GameWidth-(double)Input.size())/2), ' ');
    return New_Line(Output, Colour);
}

std::string StringBuilder::New_Line_Left_Justified(const std::string &Input, const Colours &Colour) const
{
    std::string Output = Input;
    Output.insert(Output.size(), m_GameWidth - Output.size(), ' ');
    return New_Line(Output, Colour);
}

std::string StringBuilder::Empty_Line() const
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), m_GameWidth, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string StringBuilder::Top_Line() const
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), m_GameWidth, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string StringBuilder::Bottom_Line() const
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), m_GameWidth, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string StringBuilder::Top_Box() const
{
    return m_WHITE + Top_Line() + New_Line_Centered(m_TopTitle, Colours::RED) + Bottom_Line();
}

std::string StringBuilder::Bottom_Box() const
{
    return Top_Line() + New_Line_Centered(m_BottomTitle, Colours::RED) + Bottom_Line() + m_RESET;
}

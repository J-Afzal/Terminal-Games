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

StringBuilder::StringBuilder(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& gameWidth, const bool& outputIsOnlyASCII)
{
    this->SetProperties(topTitle, bottomTitle, gameWidth, outputIsOnlyASCII);
}

void StringBuilder::SetProperties(const std::string& topTitle, const std::string& bottomTitle, const uint32_t& gameWidth, const bool& outputIsOnlyASCII)
{
    m_topTitle = topTitle;
    m_bottomTitle = bottomTitle;
    m_gameWidth = gameWidth;

    if (outputIsOnlyASCII) // Remove ANSI escape codes
        m_WHITE = m_RED = m_BLUE =  m_RESET = "";
}

std::string StringBuilder::AddNewLine(const std::string& Input, const Colours& Colour) const
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

std::string StringBuilder::AddNewLineCentred(const std::string& Input, const Colours& Colour) const
{
    std::string Output;
    Output.insert(Output.size(), floor((m_gameWidth-(double)Input.size())/2), ' ');
    Output += Input;
    Output.insert(Output.size(), ceil((m_gameWidth-(double)Input.size())/2), ' ');
    return AddNewLine(Output, Colour);
}

std::string StringBuilder::AddNewLineLeftJustified(const std::string& Input, const Colours& Colour) const
{
    std::string Output = Input;
    Output.insert(Output.size(), m_gameWidth - Output.size(), ' ');
    return AddNewLine(Output, Colour);
}

std::string StringBuilder::AddEmptyLine() const
{
    std::string Output;
    Output += (char)186;
    Output.insert(Output.size(), m_gameWidth, ' ');
    Output += (char)186;
    return Output + "\n";
}

std::string StringBuilder::AddTopLine() const
{
    std::string Output;
    Output += (char)201;
    Output.insert(Output.size(), m_gameWidth, (char)205);
    Output += (char)187;
    return Output + "\n";
}

std::string StringBuilder::AddBottomLine() const
{
    std::string Output;
    Output += (char)200;
    Output.insert(Output.size(), m_gameWidth, (char)205);
    Output += (char)188;
    return Output + "\n";
}

std::string StringBuilder::AddTopBox() const
{
    return m_WHITE + AddTopLine() + AddNewLineCentred(m_topTitle, Colours::RED) + AddBottomLine();
}

std::string StringBuilder::AddBottomBox() const
{
    return AddTopLine() + AddNewLineCentred(m_bottomTitle, Colours::RED) + AddBottomLine() + m_RESET;
}

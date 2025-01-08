#pragma once

#include <array>
#include <cstdint>
#include <string>

namespace TerminalGames
{
    /**
     * @brief Some C++ functions are not supported by some compilers (usually because the function call fails with GNU 12.2.0
     * within the CI workflow). The following functions are crudely implemented below for this project's specific use case.
     */
    // Should work for all std containers
    template<typename T, typename U>
    static T ImplementStdRangesFind(const T& p_begin, const T& p_end, const U& p_value) // NOLINT(bugprone-easily-swappable-parameters)
    {
        for (T i = p_begin; i < p_end; i++)
            if (*i == p_value)
                return i;

        return p_end;
    }

    // Should work for all std containers
    template<typename T, typename U>
    static int32_t ImplementStdCount(const T& p_begin, const T& p_end, const U& p_value) // NOLINT(bugprone-easily-swappable-parameters)
    {
        int32_t count = 0;

        for (T i = p_begin; i < p_end; i++)
            if (*i == p_value)
                ++count;

        return count;
    }

    // Only works for single instance of {} in p_stringToFormat
    static std::string ImplementStdFormat(const std::string& p_stringToFormat, const uint32_t& p_varToInsert)
    {
        const std::string FORMAT_IDENTIFIER = "{}";
        const std::string BEFORE_STRING = p_stringToFormat.substr(0, p_stringToFormat.find(FORMAT_IDENTIFIER));
        const std::string AFTER_STRING = p_stringToFormat.substr(p_stringToFormat.find(FORMAT_IDENTIFIER) + FORMAT_IDENTIFIER.size(), p_stringToFormat.size() - p_stringToFormat.find("{}"));

        return BEFORE_STRING + std::to_string(p_varToInsert) + AFTER_STRING;
    }
}
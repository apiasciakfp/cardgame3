#pragma once

// Non-mirror helper: C++ has no stdlib trim / split / replace-all. These fill the gaps the C#
// source got for free from `string.Trim()`, `string.Split(...)`, `string.Replace(...)`.
// (Justified non-mirror file, like DotnetRandom — see task DECISION_LOG trap #14.)

#include <algorithm>
#include <cctype>
#include <string>
#include <vector>

namespace cardmultigame::technical
{
    // Lower-cases ASCII, mirroring the case-insensitive command matching (string.ToLower()).
    inline std::string ToLower(const std::string& value)
    {
        std::string lowered = value;
        std::transform(lowered.begin(), lowered.end(), lowered.begin(),
                       [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
        return lowered;
    }

    // Whitespace set matching .NET string.Trim() on ASCII input (DA #8a).
    inline const std::string WHITESPACE = " \t\n\r\f\v";

    inline std::string Trim(const std::string& value)
    {
        const auto first = value.find_first_not_of(WHITESPACE);
        if (first == std::string::npos) return "";
        const auto last = value.find_last_not_of(WHITESPACE);
        return value.substr(first, last - first + 1);
    }

    // Distinct from Trim(): strips only the given characters (mirrors string.Trim(',')).
    inline std::string TrimChars(const std::string& value, const std::string& chars)
    {
        const auto first = value.find_first_not_of(chars);
        if (first == std::string::npos) return "";
        const auto last = value.find_last_not_of(chars);
        return value.substr(first, last - first + 1);
    }

    // Literal replace-all, mirroring C# string.Replace(old, "") which replaces EVERY occurrence
    // (DECISION_LOG erratum #1). Empty needle → return unchanged (guards the infinite loop; matches
    // the Python port; diverges from C#'s ArgumentException on the untested whitespace-only edge).
    inline std::string ReplaceAll(std::string value, const std::string& from, const std::string& to)
    {
        if (from.empty()) return value;
        std::string::size_type at = 0;
        while ((at = value.find(from, at)) != std::string::npos)
        {
            value.replace(at, from.size(), to);
            at += to.size();
        }
        return value;
    }

    // Split on whitespace runs (mirrors parameterless string.Split()). .NET keeps empty entries, but
    // they are behaviorally inert at every call site (a "" token Trim(',')s to "" and matches nothing),
    // so dropping empties here yields identical results.
    inline std::vector<std::string> SplitWhitespace(const std::string& value)
    {
        std::vector<std::string> tokens;
        std::string::size_type start = value.find_first_not_of(WHITESPACE);
        while (start != std::string::npos)
        {
            const auto end = value.find_first_of(WHITESPACE, start);
            tokens.push_back(value.substr(start, end - start));
            start = value.find_first_not_of(WHITESPACE, end);
        }
        return tokens;
    }

    // Split on a string separator, KEEPING empty entries (mirrors string.Split(sep, None)).
    inline std::vector<std::string> SplitKeepEmpty(const std::string& value, const std::string& separator)
    {
        std::vector<std::string> parts;
        std::string::size_type start = 0;
        std::string::size_type at;
        while ((at = value.find(separator, start)) != std::string::npos)
        {
            parts.push_back(value.substr(start, at - start));
            start = at + separator.size();
        }
        parts.push_back(value.substr(start));
        return parts;
    }
}

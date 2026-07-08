#include "gamemanagers/selectedrules/creationcommands/SetMaxTurns.hpp"

#include "technical/StringUtils.hpp"

#include <charconv>

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    void SetMaxTurns::ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters)
    {
        // int.TryParse semantics: the WHOLE string must be an integer (rejects "3abc", "", "x").
        // On failure, silently do nothing (WART-18). from_chars consumes leading int only, so we
        // also require it reached the end.
        int maxTurns = 0;
        const char* first = parameters.data();
        const char* last = parameters.data() + parameters.size();
        const auto [ptr, ec] = std::from_chars(first, last, maxTurns);

        const bool wasSuccessful = (ec == std::errc()) && (ptr == last);
        if (wasSuccessful)
        {
            builder.SetMaxTurns(maxTurns);
        }
    }

    bool SetMaxTurns::ShouldReactTo(const std::string& outerCommandName)
    {
        return technical::ToLower(_identifier) == technical::ToLower(outerCommandName);
    }
}

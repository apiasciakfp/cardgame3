#pragma once

#include "gamemanagers/selectedrules/creationcommands/ICreateGameRulesCommand.hpp"

#include <string>

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    class SetMaxTurns : public ICreateGameRulesCommand
    {
        std::string _identifier = "SetMaxTurns";

    public:
        void ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters) override;
        bool ShouldReactTo(const std::string& outerCommandName) override;
    };
}

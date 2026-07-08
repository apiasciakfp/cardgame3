#pragma once

#include "gamemanagers/GameManagerInternalsBuilder.hpp"

#include <string>

namespace cardmultigame::gamemanagers::selectedrules::creationcommands
{
    class ICreateGameRulesCommand
    {
    public:
        virtual ~ICreateGameRulesCommand() = default;

        virtual bool ShouldReactTo(const std::string& outerCommandName) = 0;
        virtual void ChangeGameRuleset(GameManagerInternalsBuilder& builder, const std::string& parameters) = 0;
    };
}

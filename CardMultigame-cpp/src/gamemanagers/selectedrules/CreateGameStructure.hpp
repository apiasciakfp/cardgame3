#pragma once

#include "gamemanagers/GameManagerInternalsBuilder.hpp"
#include "gamemanagers/selectedrules/creationcommands/ICreateGameRulesCommand.hpp"

#include <memory>
#include <string>
#include <utility>
#include <vector>

namespace cardmultigame::gamemanagers::selectedrules
{
    class CreateGameStructure
    {
        std::vector<std::shared_ptr<creationcommands::ICreateGameRulesCommand>> _commands;

        static std::vector<std::shared_ptr<creationcommands::ICreateGameRulesCommand>> RegisterAvailableCreationCommands();

    public:
        CreateGameStructure();

        GameManagerInternalsBuilder BuildRulesAndInitialState(const std::vector<std::pair<std::string, std::string>>& orders);
    };
}

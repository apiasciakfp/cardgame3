#include "gamemanagers/selectedrules/CreateGameStructure.hpp"

#include "gamemanagers/selectedrules/creationcommands/GameVariant.hpp"
#include "gamemanagers/selectedrules/creationcommands/SelectGame.hpp"
#include "gamemanagers/selectedrules/creationcommands/SetDeck.hpp"
#include "gamemanagers/selectedrules/creationcommands/SetMaxTurns.hpp"

namespace cardmultigame::gamemanagers::selectedrules
{
    CreateGameStructure::CreateGameStructure()
        : _commands(RegisterAvailableCreationCommands())
    {
    }

    GameManagerInternalsBuilder CreateGameStructure::BuildRulesAndInitialState(const std::vector<std::pair<std::string, std::string>>& orders)
    {
        GameManagerInternalsBuilder builder;
        // Double loop, NO de-dup: every command that reacts to an order fires (WART-16).
        for (const auto& order : orders)
        {
            for (const auto& orderUser : _commands)
            {
                if (orderUser->ShouldReactTo(order.first))
                {
                    orderUser->ChangeGameRuleset(builder, order.second);
                }
            }
        }

        return builder;
    }

    std::vector<std::shared_ptr<creationcommands::ICreateGameRulesCommand>> CreateGameStructure::RegisterAvailableCreationCommands()
    {
        return {
            std::make_shared<creationcommands::SelectGame>(),
            std::make_shared<creationcommands::SetDeck>(),
            std::make_shared<creationcommands::SetMaxTurns>(),
            std::make_shared<creationcommands::GameVariant>(),
        };
    }
}

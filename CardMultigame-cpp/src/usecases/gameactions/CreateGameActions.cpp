#include "usecases/gameactions/CreateGameActions.hpp"

#include "technical/StringUtils.hpp"
#include "usecases/gameactions/Add10COrDrawACard.hpp"
#include "usecases/gameactions/AddQueenOfHeartsToDeck.hpp"
#include "usecases/gameactions/DrawSingleCardAction.hpp"

namespace cardmultigame::usecases::gameactions
{
    std::vector<std::shared_ptr<IGameAction>> CreateGameActions::HavingOrders(const std::string& actionsToPerform)
    {
        const std::vector<std::string> tokens = technical::SplitWhitespace(actionsToPerform);

        std::vector<std::shared_ptr<IGameAction>> actions;
        for (const auto& token : tokens)
        {
            const std::string sanitized = technical::TrimChars(token, ","); // strip only leading/trailing commas

            if (sanitized == "drawSingleCard") actions.push_back(std::make_shared<DrawSingleCardAction>());
            if (sanitized == "addQH") actions.push_back(std::make_shared<AddQueenOfHeartsToDeck>());
            if (sanitized == "add10cOrDraw") actions.push_back(std::make_shared<Add10COrDrawACard>());
        }

        return actions;
    }
}

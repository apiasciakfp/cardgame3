#pragma once

#include "usecases/gameactions/IGameAction.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cardmultigame::usecases::gameactions
{
    class CreateGameActions
    {
    public:
        std::vector<std::shared_ptr<IGameAction>> HavingOrders(const std::string& actionsToPerform);
    };
}

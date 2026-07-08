#pragma once

#include "gamemanagers/GameManager.hpp"

#include <string>

namespace cardmultigame::gamemanagers
{
    class CreateGameManager
    {
    public:
        GameManager DefaultsWithOrders(const std::string& orderString);
        GameManager Empty();
    };
}

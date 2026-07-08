#pragma once

#include "entities/gamestates/GameState.hpp"

namespace cardmultigame::usecases::gameconditions
{
    class IGameCondition
    {
    public:
        virtual ~IGameCondition() = default;

        virtual void CheckAndUpdate(entities::gamestates::GameState& currentGameState) = 0;
    };
}

#pragma once

#include "usecases/gameconditions/IGameCondition.hpp"

namespace cardmultigame::usecases::gameconditions
{
    // If currentTurn >= maxTurns, declare the game lost.
    class DidTurnsExpire : public IGameCondition
    {
    public:
        void CheckAndUpdate(entities::gamestates::GameState& currentGameState) override;
    };
}

#pragma once

#include "usecases/gameconditions/IGameCondition.hpp"

namespace cardmultigame::usecases::gameconditions
{
    // If a 'Guess' key exists AND its value is true, declare the game won.
    class DidGuessACard : public IGameCondition
    {
    public:
        void CheckAndUpdate(entities::gamestates::GameState& currentGameState) override;
    };
}

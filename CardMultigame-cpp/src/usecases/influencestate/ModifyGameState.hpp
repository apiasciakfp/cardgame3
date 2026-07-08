#pragma once

#include "entities/gamestates/GameState.hpp"

namespace cardmultigame::usecases::influencestate
{
    // STATELESS FOREVER. Commands (functions) over the state bag only — the 'C' in CQS.
    struct ModifyGameState
    {
        static void AddTurn(entities::gamestates::GameState& currentGameState);
        static void DeclareGameToBeLost(entities::gamestates::GameState& currentGameState);
        static void DeclareGameToBeWon(entities::gamestates::GameState& currentGameState);
    };
}

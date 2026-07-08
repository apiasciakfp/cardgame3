#include "usecases/influencestate/ModifyGameState.hpp"

#include "entities/gamestates/GameStateKeys.hpp"

#include <any>

namespace cardmultigame::usecases::influencestate
{
    using entities::gamestates::GameStateKeys;

    void ModifyGameState::AddTurn(entities::gamestates::GameState& currentGameState)
    {
        const int currentTurn = std::any_cast<int>(currentGameState.Get(GameStateKeys::CurrentTurn));
        currentGameState.Set(GameStateKeys::CurrentTurn, currentTurn + 1); // stored as int (trap #13)
    }

    void ModifyGameState::DeclareGameToBeLost(entities::gamestates::GameState& currentGameState)
    {
        currentGameState.Set(GameStateKeys::IsGameLost, true);
    }

    void ModifyGameState::DeclareGameToBeWon(entities::gamestates::GameState& currentGameState)
    {
        currentGameState.Set(GameStateKeys::IsGameWon, true);
    }
}

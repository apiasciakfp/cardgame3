#include "usecases/gameconditions/DidTurnsExpire.hpp"

#include "usecases/influencestate/ModifyGameState.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

namespace cardmultigame::usecases::gameconditions
{
    void DidTurnsExpire::CheckAndUpdate(entities::gamestates::GameState& currentGameState)
    {
        const int currentTurn = influencestate::QueryGameState::CurrentTurn(currentGameState);
        const int maxTurns = influencestate::QueryGameState::MaximumTurns(currentGameState);

        if (currentTurn >= maxTurns)
        {
            influencestate::ModifyGameState::DeclareGameToBeLost(currentGameState);
        }
    }
}

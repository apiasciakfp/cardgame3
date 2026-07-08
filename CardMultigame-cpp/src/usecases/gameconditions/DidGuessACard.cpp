#include "usecases/gameconditions/DidGuessACard.hpp"

#include "usecases/influencestate/ModifyGameState.hpp"

#include <any>

namespace cardmultigame::usecases::gameconditions
{
    void DidGuessACard::CheckAndUpdate(entities::gamestates::GameState& currentGameState)
    {
        const std::any result = currentGameState.Get("Guess"); // un-constanted magic key (WART-6)

        if (result.has_value()) // check non-empty THEN cast (DA #5), not "empty == false"
        {
            const bool isGameWon = std::any_cast<bool>(result);
            if (isGameWon)
            {
                influencestate::ModifyGameState::DeclareGameToBeWon(currentGameState);
            }
        }
    }
}

#include "usecases/influencestate/QueryGameState.hpp"

#include "entities/gamestates/GameStateKeys.hpp"

#include <any>
#include <stdexcept>

namespace cardmultigame::usecases::influencestate
{
    using entities::gamestates::GameStateKeys;

    int QueryGameState::MaximumTurns(const entities::gamestates::GameState& currentState)
    {
        const std::any value = currentState.Get(GameStateKeys::MaxTurns);
        if (!value.has_value())
        {
            throw std::invalid_argument("Current turn cannot be a null");
        }
        return std::any_cast<int>(value);
    }

    bool QueryGameState::IsGameWon(const entities::gamestates::GameState& currentState)
    {
        return std::any_cast<bool>(currentState.Get(GameStateKeys::IsGameWon));
    }

    bool QueryGameState::IsGameLost(const entities::gamestates::GameState& currentState)
    {
        return std::any_cast<bool>(currentState.Get(GameStateKeys::IsGameLost));
    }

    bool QueryGameState::IsGameFinished(const entities::gamestates::GameState& currentState)
    {
        return IsGameWon(currentState) || IsGameLost(currentState);
    }

    int QueryGameState::CurrentTurn(const entities::gamestates::GameState& currentState)
    {
        const std::any value = currentState.Get(GameStateKeys::CurrentTurn);
        if (!value.has_value())
        {
            throw std::invalid_argument("Current turn cannot be a null");
        }
        return std::any_cast<int>(value);
    }

    int QueryGameState::AmountOfCardsLeft(const entities::gamestates::GameState& currentState)
    {
        return ExtractCardDeck(currentState)->CardsLeft();
    }

    std::string QueryGameState::GameUndergoing(const entities::gamestates::GameState& currentState)
    {
        if (std::any_cast<bool>(currentState.Get(GameStateKeys::IsGameWon))) return "Victory";
        else if (std::any_cast<bool>(currentState.Get(GameStateKeys::IsGameLost))) return "Defeat";
        else return "Undergoing";
    }

    std::shared_ptr<entities::decks::CardDeck> QueryGameState::ExtractCardDeck(const entities::gamestates::GameState& currentState)
    {
        return std::any_cast<std::shared_ptr<entities::decks::CardDeck>>(currentState.Get(GameStateKeys::CardDeck));
    }
}

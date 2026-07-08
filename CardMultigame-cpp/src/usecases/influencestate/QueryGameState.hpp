#pragma once

#include "entities/decks/CardDeck.hpp"
#include "entities/gamestates/GameState.hpp"

#include <memory>
#include <string>

namespace cardmultigame::usecases::influencestate
{
    // STATELESS FOREVER. Queries over the state bag only — the 'Q' in CQS. Never mutate.
    struct QueryGameState
    {
        static int MaximumTurns(const entities::gamestates::GameState& currentState);
        static bool IsGameWon(const entities::gamestates::GameState& currentState);
        static bool IsGameLost(const entities::gamestates::GameState& currentState);
        static bool IsGameFinished(const entities::gamestates::GameState& currentState);
        static int CurrentTurn(const entities::gamestates::GameState& currentState);
        static int AmountOfCardsLeft(const entities::gamestates::GameState& currentState);
        static std::string GameUndergoing(const entities::gamestates::GameState& currentState);
        static std::shared_ptr<entities::decks::CardDeck> ExtractCardDeck(const entities::gamestates::GameState& currentState);
    };
}

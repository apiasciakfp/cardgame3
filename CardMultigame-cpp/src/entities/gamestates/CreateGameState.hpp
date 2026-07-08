#pragma once

#include "entities/decks/CardDeck.hpp"
#include "entities/gamestates/GameState.hpp"

#include <memory>

namespace cardmultigame::entities::gamestates
{
    class CreateGameState
    {
    public:
        // stateModifier / deck default to null (nullptr), as in the C# nullable parameters.
        GameState WithModifications(const GameState* stateModifier = nullptr, std::shared_ptr<decks::CardDeck> deck = nullptr);
        GameState DefaultsPlusDeck(std::shared_ptr<decks::CardDeck> deck);
        GameState DefaultsWithFullDeck();
        GameState Default();

    private:
        GameState Sanitize(const GameState* stateModifier);
        static std::shared_ptr<decks::CardDeck> Sanitize(std::shared_ptr<decks::CardDeck> deck);
    };
}

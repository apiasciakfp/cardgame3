#include "entities/gamestates/CreateGameState.hpp"

#include "entities/decks/CreateCardDeck.hpp"
#include "entities/gamestates/GameStateKeys.hpp"

namespace cardmultigame::entities::gamestates
{
    GameState CreateGameState::WithModifications(const GameState* stateModifier, std::shared_ptr<decks::CardDeck> deck)
    {
        std::shared_ptr<decks::CardDeck> deck2 = Sanitize(std::move(deck));
        GameState stateModifier2 = Sanitize(stateModifier);

        GameState constructedState = Default();
        for (const auto& kvPair : stateModifier2.Entries())
        {
            constructedState.Set(kvPair.first, kvPair.second);
        }

        constructedState.Set(GameStateKeys::CardDeck, deck2);
        return constructedState;
    }

    GameState CreateGameState::DefaultsPlusDeck(std::shared_ptr<decks::CardDeck> deck)
    {
        GameState constructedState = Default();
        constructedState.Set(GameStateKeys::CardDeck, std::move(deck));
        return constructedState;
    }

    GameState CreateGameState::DefaultsWithFullDeck()
    {
        GameState constructedState = Default();
        constructedState.Set(GameStateKeys::CardDeck, decks::CreateCardDeck().Simple2ToAWith4Colours());
        return constructedState;
    }

    GameState CreateGameState::Default()
    {
        // Insertion order is load-bearing for the REPL display: CardDeck, CurrentTurn, MaxTurns,
        // IsGameLost, IsGameWon — Lost BEFORE Won (erratum #2). Numerics stored as int (trap #13).
        GameState state;
        state.Set(GameStateKeys::CardDeck, decks::CreateCardDeck().Empty());
        state.Set(GameStateKeys::CurrentTurn, 0);
        state.Set(GameStateKeys::MaxTurns, 0);
        state.Set(GameStateKeys::IsGameLost, false);
        state.Set(GameStateKeys::IsGameWon, false);
        return state;
    }

    GameState CreateGameState::Sanitize(const GameState* stateModifier)
    {
        if (stateModifier == nullptr)
        {
            return GameState{};
        }
        return *stateModifier;
    }

    std::shared_ptr<decks::CardDeck> CreateGameState::Sanitize(std::shared_ptr<decks::CardDeck> deck)
    {
        if (deck == nullptr)
        {
            return decks::CreateCardDeck().Empty();
        }
        return deck;
    }
}

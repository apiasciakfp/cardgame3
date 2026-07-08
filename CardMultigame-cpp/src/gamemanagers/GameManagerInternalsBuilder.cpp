#include "gamemanagers/GameManagerInternalsBuilder.hpp"

#include "entities/gamestates/CreateGameState.hpp"
#include "entities/gamestates/GameStateKeys.hpp"
#include "gamemanagers/selectedrules/CreatePlayedGameRules.hpp"

#include <utility>

namespace cardmultigame::gamemanagers
{
    std::shared_ptr<selectedrules::PlayedGameRules> GameManagerInternalsBuilder::ConstructRuleset()
    {
        return selectedrules::CreatePlayedGameRules().WithModifications(_gameName, _actions, _victories, _gameStops, _compareCards);
    }

    entities::gamestates::GameState GameManagerInternalsBuilder::ConstructGameState()
    {
        const entities::gamestates::GameState* modifier = _initialGameState.has_value() ? &_initialGameState.value() : nullptr;
        return entities::gamestates::CreateGameState().WithModifications(modifier, _deck);
    }

    void GameManagerInternalsBuilder::SetName(std::string name)
    {
        _gameName = std::move(name);
    }

    void GameManagerInternalsBuilder::SetAvailableActions(ActionList actions)
    {
        _actions = std::move(actions);
    }

    void GameManagerInternalsBuilder::SetVictoryConditions(ConditionList victories)
    {
        _victories = std::move(victories);
    }

    void GameManagerInternalsBuilder::SetGameStopConditions(ConditionList gameStops)
    {
        _gameStops = std::move(gameStops);
    }

    void GameManagerInternalsBuilder::SetDeck(std::shared_ptr<entities::decks::CardDeck> cardDeck)
    {
        _deck = std::move(cardDeck);
    }

    void GameManagerInternalsBuilder::SetInitialGameState(entities::gamestates::GameState gameState)
    {
        _initialGameState = std::move(gameState);
    }

    void GameManagerInternalsBuilder::SetMaxTurns(int maxTurns)
    {
        // .value() throws if SetInitialGameState hasn't run — the C# temporal coupling (WART-19).
        _initialGameState.value().Set(entities::gamestates::GameStateKeys::MaxTurns, maxTurns);
    }

    std::shared_ptr<entities::decks::CardDeck> GameManagerInternalsBuilder::GetCardDeck()
    {
        return _deck;
    }

    void GameManagerInternalsBuilder::SetCardComparisonStrategy(std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> selected)
    {
        _compareCards = std::move(selected);
    }
}

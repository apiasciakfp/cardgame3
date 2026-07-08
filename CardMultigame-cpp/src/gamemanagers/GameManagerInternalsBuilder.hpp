#pragma once

#include "entities/decks/CardDeck.hpp"
#include "entities/gamestates/GameState.hpp"
#include "gamemanagers/selectedrules/PlayedGameRules.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"

#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace cardmultigame::gamemanagers
{
    class GameManagerInternalsBuilder
    {
        using ActionList = std::vector<std::shared_ptr<usecases::gameactions::IGameAction>>;
        using ConditionList = std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>;

        std::optional<std::string> _gameName;
        std::shared_ptr<entities::decks::CardDeck> _deck;
        std::optional<ActionList> _actions;
        std::optional<ConditionList> _victories;
        std::optional<ConditionList> _gameStops;
        std::optional<entities::gamestates::GameState> _initialGameState;

        // Specific to the Guessing game.
        std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> _compareCards;

    public:
        std::shared_ptr<selectedrules::PlayedGameRules> ConstructRuleset();
        entities::gamestates::GameState ConstructGameState();

        void SetName(std::string name);
        void SetAvailableActions(ActionList actions);
        void SetVictoryConditions(ConditionList victories);
        void SetGameStopConditions(ConditionList gameStops);
        void SetDeck(std::shared_ptr<entities::decks::CardDeck> cardDeck);
        void SetInitialGameState(entities::gamestates::GameState gameState);
        void SetMaxTurns(int maxTurns); // writes into the initial state -> needs SetInitialGameState first (WART-19)

        std::shared_ptr<entities::decks::CardDeck> GetCardDeck();

        void SetCardComparisonStrategy(std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> selected);
    };
}

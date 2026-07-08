#pragma once

#include "entities/decks/CardDeck.hpp"
#include "entities/gamestates/GameState.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cardmultigame::entities::games
{
    class IGameImplementation
    {
    public:
        virtual ~IGameImplementation() = default;

        virtual std::string Title() = 0;
        virtual std::shared_ptr<decks::CardDeck> CardDeck() = 0;
        virtual std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> AvailableActions() = 0;
        virtual std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> VictoryConditions() = 0;
        virtual std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> GameStopConditions() = 0;
        virtual gamestates::GameState InitialGameState() = 0;
        virtual std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> CardComparisonStrategy() = 0;
    };
}

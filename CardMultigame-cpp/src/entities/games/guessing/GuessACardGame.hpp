#pragma once

#include "entities/games/IGameImplementation.hpp"

namespace cardmultigame::entities::games::guessing
{
    class GuessACardGame : public IGameImplementation
    {
    public:
        std::string Title() override;
        std::shared_ptr<decks::CardDeck> CardDeck() override;
        std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> AvailableActions() override;
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> VictoryConditions() override;
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> GameStopConditions() override;
        gamestates::GameState InitialGameState() override;
        std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> CardComparisonStrategy() override;
    };
}

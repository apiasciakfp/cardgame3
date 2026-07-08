#pragma once

#include "entities/gamestates/GameState.hpp"
#include "usecases/cardcomparison/ICardComparisonStrategy.hpp"
#include "usecases/gameactions/IGameAction.hpp"
#include "usecases/gameconditions/IGameCondition.hpp"

#include <memory>
#include <string>
#include <vector>

namespace cardmultigame::gamemanagers::selectedrules
{
    class PlayedGameRules
    {
        std::string _gameName;
        std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> _actions;
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> _victoryConditions;
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> _gameStopConditions;
        std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> _cardComparator;

    public:
        PlayedGameRules(std::string gameName,
                        std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> actions,
                        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> victories,
                        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> gameStops,
                        std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> compareCards);

        std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> CardComparator();

        // Exposed as mutable lists BY REFERENCE — normally private, but the pattern tests need it (WART-22).
        std::vector<std::shared_ptr<usecases::gameactions::IGameAction>>& GameActions();
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>& VictoryConditions();
        std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>& GameStopConditions();
        std::string GameName();

        void CheckVictoryConditions(entities::gamestates::GameState& currentGameState);
        void CheckGameStopConditions(entities::gamestates::GameState& currentGameState);
    };
}

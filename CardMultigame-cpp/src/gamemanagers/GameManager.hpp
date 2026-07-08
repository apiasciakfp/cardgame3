#pragma once

#include "entities/gamestates/GameState.hpp"
#include "gamemanagers/selectedrules/PlayedGameRules.hpp"

#include <memory>
#include <string>

namespace cardmultigame::gamemanagers
{
    class GameManager
    {
        entities::gamestates::GameState _currentGameState;
        std::shared_ptr<selectedrules::PlayedGameRules> _gameRules;

    public:
        GameManager(entities::gamestates::GameState initialState, std::shared_ptr<selectedrules::PlayedGameRules> rules);

        void ExecuteOrders(const std::string& orderString);

        entities::gamestates::GameState& CurrentState();
    };
}

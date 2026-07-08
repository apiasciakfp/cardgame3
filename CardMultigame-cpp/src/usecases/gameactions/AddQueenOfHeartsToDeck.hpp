#pragma once

#include "usecases/gameactions/IGameAction.hpp"

#include <string>

namespace cardmultigame::usecases::gameactions
{
    class AddQueenOfHeartsToDeck : public IGameAction
    {
    public:
        void ChangeGameState(entities::gamestates::GameState& currentGameState,
                             gamemanagers::selectedrules::PlayedGameRules& gameRules,
                             const std::string& orderParams) override;
        bool ShouldReactTo(const std::string& item1) override; // dormant — throws (WART-14)
    };
}

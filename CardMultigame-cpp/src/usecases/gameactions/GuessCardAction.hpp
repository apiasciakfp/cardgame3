#pragma once

#include "usecases/gameactions/IGameAction.hpp"

#include <string>

namespace cardmultigame::usecases::gameactions
{
    class GuessCardAction : public IGameAction
    {
        std::string _identifier = "Guess";

    public:
        void ChangeGameState(entities::gamestates::GameState& currentGameState,
                             gamemanagers::selectedrules::PlayedGameRules& rules,
                             const std::string& orderParams) override;
        bool ShouldReactTo(const std::string& orderName) override;
    };
}

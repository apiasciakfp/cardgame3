#pragma once

#include "entities/gamestates/GameState.hpp"

#include <string>

// Forward-declare PlayedGameRules to break the IGameAction <-> PlayedGameRules include cycle
// (PlayedGameRules holds vector<shared_ptr<IGameAction>>). The .cpp of each action includes the
// full PlayedGameRules definition. (DA #8d — why .hpp/.cpp pairs are locked.)
namespace cardmultigame::gamemanagers::selectedrules
{
    class PlayedGameRules;
}

namespace cardmultigame::usecases::gameactions
{
    class IGameAction
    {
    public:
        virtual ~IGameAction() = default;

        virtual bool ShouldReactTo(const std::string& item1) = 0;
        virtual void ChangeGameState(entities::gamestates::GameState& currentGameState,
                                     gamemanagers::selectedrules::PlayedGameRules& gameRules,
                                     const std::string& orderParams) = 0;
    };
}

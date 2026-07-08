#include "gamemanagers/GameManager.hpp"

#include "technical/parsers/SelectedParser.hpp"
#include "usecases/influencestate/QueryGameState.hpp"

#include <utility>

namespace cardmultigame::gamemanagers
{
    GameManager::GameManager(entities::gamestates::GameState initialState, std::shared_ptr<selectedrules::PlayedGameRules> rules)
        : _currentGameState(std::move(initialState)), _gameRules(std::move(rules))
    {
    }

    void GameManager::ExecuteOrders(const std::string& orderString)
    {
        const std::vector<std::pair<std::string, std::string>> orders = technical::parsers::SelectedParser().ProperlyParse(orderString);

        for (const auto& order : orders)
        {
            if (usecases::influencestate::QueryGameState::IsGameFinished(_currentGameState)) return; // short-circuit (WART-20)

            for (const auto& gameAction : _gameRules->GameActions())
            {
                if (gameAction->ShouldReactTo(order.first))
                {
                    gameAction->ChangeGameState(_currentGameState, *_gameRules, order.second);

                    // Victory BEFORE stop (WART-21): a turn that both matches and expires -> Victory.
                    _gameRules->CheckVictoryConditions(_currentGameState);
                    _gameRules->CheckGameStopConditions(_currentGameState);
                }
            }
        }
    }

    entities::gamestates::GameState& GameManager::CurrentState()
    {
        return _currentGameState;
    }
}

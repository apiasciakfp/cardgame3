#include "gamemanagers/selectedrules/PlayedGameRules.hpp"

#include <utility>

namespace cardmultigame::gamemanagers::selectedrules
{
    PlayedGameRules::PlayedGameRules(std::string gameName,
                                     std::vector<std::shared_ptr<usecases::gameactions::IGameAction>> actions,
                                     std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> victories,
                                     std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>> gameStops,
                                     std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> compareCards)
        : _gameName(std::move(gameName)),
          _actions(std::move(actions)),
          _victoryConditions(std::move(victories)),
          _gameStopConditions(std::move(gameStops)),
          _cardComparator(std::move(compareCards))
    {
    }

    std::shared_ptr<usecases::cardcomparison::ICardComparisonStrategy> PlayedGameRules::CardComparator()
    {
        return _cardComparator;
    }

    std::vector<std::shared_ptr<usecases::gameactions::IGameAction>>& PlayedGameRules::GameActions()
    {
        return _actions;
    }

    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>& PlayedGameRules::VictoryConditions()
    {
        return _victoryConditions;
    }

    std::vector<std::shared_ptr<usecases::gameconditions::IGameCondition>>& PlayedGameRules::GameStopConditions()
    {
        return _gameStopConditions;
    }

    std::string PlayedGameRules::GameName()
    {
        return _gameName;
    }

    void PlayedGameRules::CheckVictoryConditions(entities::gamestates::GameState& currentGameState)
    {
        for (const auto& victory : _victoryConditions)
        {
            victory->CheckAndUpdate(currentGameState);
        }
    }

    void PlayedGameRules::CheckGameStopConditions(entities::gamestates::GameState& currentGameState)
    {
        for (const auto& stop : _gameStopConditions)
        {
            stop->CheckAndUpdate(currentGameState);
        }
    }
}
